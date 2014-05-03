#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/time.h>
#include <sys/select.h>
#include <vector>
#include <algorithm>

#include "person.H"
#include "reqchannel.H"
#include "buffer.H"
#include "timer.H"


int num_requests;
int buffer_size;
int num_channels;
int items_written, items_read;

RequestChannel* control;
vector<int*> open_channels;
vector<Person*> people;
BoundedBuffer<string>* buffer;

int* open_fds;

Semaphore mutex;
Timer exec_time;


//functions for the pthreads to do and their creation
//------------------------------------------------------------------------------

//Request thread, Person-specific
void* request_exec(void* argument) {
    int tid = *((int*) argument);

    Person* newGuy = people[tid];
    
    for(int i = 0; i < num_requests; i++) {
        buffer->deposit("data " + newGuy->name);
    }

    return NULL;
}

void process_returned_value(string returned) {
    int data = atoi(returned.substr(returned.size()-2, 2).c_str());
    //cout << data << "\n";
    if(returned.find("data John Doe") != std::string::npos) {
        people[0]->stat_buffer->deposit(data);
    }
    else if(returned.find("data Joe Smith") != std::string::npos) {
        people[1]->stat_buffer->deposit(data);
    }
    else if(returned.find("data Jane Smith") != std::string::npos) {
        people[2]->stat_buffer->deposit(data);
    }
    else {
        cout << "bad request\n";
    }
}

void* event_handler(void* argument) {
    string request = "";
    string returned = "";
    int data = 0;

    vector<RequestChannel*> channels;
    fd_set readset, writeset;
    FD_ZERO(&readset); 
    int maxfd = 0; 
    for(int i = 0; i < num_channels; i++) {
        channels.push_back(new RequestChannel(control->send_request("newthread"), RequestChannel::CLIENT_SIDE));
        FD_SET(channels[i]->read_fd(), &readset);
        maxfd = max(maxfd, channels[i]->read_fd());

        request = buffer->withdraw();
        channels[i]->cwrite(request);
        items_written++;
    }

    while(true) {
        FD_ZERO(&readset); 
        for(int i = 0; i < channels.size(); i++) {
            FD_SET(channels[i]->read_fd(), &readset);
        }

        int numready = select(maxfd + 1, &readset, NULL, NULL, NULL);
        if (numready == -1) {
            cout << "Fatal error, aborting\n";
            break; 
        }



        for(int i = 0; i < channels.size(); i++) {            
            if(FD_ISSET(channels[i]->read_fd(), &readset)) {
                if(items_written < num_requests*people.size()) {
                    request = buffer->withdraw();
                    channels[i]->cwrite(request); 
                    items_written++;
                }

                returned = channels[i]->cread();
                process_returned_value(returned);
                items_read++;   
            }
        }

        if(items_read == num_requests*people.size()) {
            break;
        }
    } 



    for(int i = 0; i < channels.size(); i++) {
        channels[i]->cwrite("quit");  
    }

    exec_time.finish();
    
    cout << "Execution Time: " << exec_time.sec() << " sec, " << exec_time.usec() << " usec\n";
    
        
    return NULL;
}

//Statistics thread, Person-specific
void* stat_exec(void* argument) {
    int tid = *((int*) argument);

    Person* newGuy = people[tid];

    while(true) {
        if(items_read == num_requests*people.size()) {
            mutex.P();
            newGuy->printHistogram();
            mutex.V();
            break;
        }
        else {
            newGuy->addToHistogram(newGuy->stat_buffer->withdraw());
        }
    }
    
    delete newGuy;

    return NULL;
}

//Main program execution
//------------------------------------------------------------------------------
void run_program() {
    cout << "Establishing control channel...";
    control = new RequestChannel("control", RequestChannel::CLIENT_SIDE);
    cout << "done." << endl;
    
    BoundedBuffer<string> request_buffer(buffer_size);
    buffer = &request_buffer;
    mutex.init(1);
    items_written = 0;
    items_read = 0;
    
    //Create event handler thread
    pthread_t event_handler_t;
    pthread_create(&event_handler_t, NULL, event_handler, NULL);

    //Create Individual People
    Person* JohnDoe = new Person("John Doe", 0, buffer_size);
    people.push_back(JohnDoe);
    pthread_create(&JohnDoe->request_t, NULL, request_exec, (void*) &JohnDoe->id);
    pthread_create(&JohnDoe->stat_t, NULL, stat_exec, (void*) &JohnDoe->id);
    
    Person* JoeSmith = new Person("Joe Smith", 1, buffer_size);
    people.push_back(JoeSmith);
    pthread_create(&JoeSmith->request_t, NULL, request_exec, (void*) &JoeSmith->id);
    pthread_create(&JoeSmith->stat_t, NULL, stat_exec, (void*) &JoeSmith->id);
    
    Person* JaneSmith = new Person("Jane Smith", 2, buffer_size);
    people.push_back(JaneSmith);
    pthread_create(&JaneSmith->request_t, NULL, request_exec, (void*) &JaneSmith->id);
    pthread_create(&JaneSmith->stat_t, NULL, stat_exec, (void*) &JaneSmith->id);

    pthread_join(people[0]->request_t, NULL);
    pthread_join(people[1]->request_t, NULL);
    pthread_join(people[2]->request_t, NULL);

    pthread_join(people[0]->stat_t, NULL);
    pthread_join(people[1]->stat_t, NULL);
    pthread_join(people[2]->stat_t, NULL);

    pthread_join(event_handler_t, NULL);

    //Clean up everything
    control->send_request("quit");
    delete control;
}

//Parse Command Line Arguments
//------------------------------------------------------------------------------
void print_CLA_error() {
    cout << "Error: program needs arguments in the following format with positive integer arguments:\n" <<
            "\t-n <number of data requests per person>\n" <<
            "\t-b <size of bounded buffer in requests>\n" <<
            "\t-w <number of request channels>\n";
}

int parse_CLA(int argc, char* argv[]) {
    if(argc != 7) {
        print_CLA_error(); //If incorrect number of arguments, program must exit
        return -1;
    }
    else {
        int correct_args = 0;
        for(int i = 0; i < argc; i++) {
            if(argv[i] == string("-n")) {
                correct_args++;
                num_requests = atoi(argv[i+1]);
                assert(num_requests != 0);
            }
            if(argv[i] == string("-b")) {
                correct_args++;
                buffer_size = atoi(argv[i+1]);
                assert(buffer_size != 0);
            }
            if(argv[i] == string("-w")) {
                correct_args++;
                num_channels = atoi(argv[i+1]);
                assert(num_channels != 0);
            }
        }
        if(correct_args != 3) { //if arguments are incorrect, program must exit
            print_CLA_error();
            return -1;
        }
    }
    return 0;
}

//main
//------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
    //Parse command line arguments
    if(parse_CLA(argc, argv) == -1) {
        return -1;
    }
        
    //fork separate processes
    int pid = fork();
    if(pid == -1) {
        cout << "Error forking processes\n";
    }
    else if(pid == 0) {
        exec_time.start();
        run_program();
    }
    else {
	    execv("./dataserver", NULL);
	}
}