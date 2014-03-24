#include <pthread.h>
#include <stdlib.h>
#include <assert.h>
#include<sys/time.h>
#include <vector>

#include "person.H"
#include "reqchannel.H"
#include "buffer.H"


int num_requests;
int buffer_size;
int num_workers;
int items_consumed;

RequestChannel* control;
vector<Person*> people;
BoundedBuffer<string>* buffer;
vector<BoundedBuffer<int>*> stat_buffers; 

Semaphore mutex;

//Stuff for measuring execution time
//------------------------------------------------------------------------------
typedef struct timeval timer;

timer begin; 
timer end;

void start_timer() {
    assert(gettimeofday(&begin, 0) == 0);
}

timer end_timer() {
    assert(gettimeofday(&end, 0) == 0);
    
    timer difference;
    difference.tv_sec = end.tv_sec - begin.tv_sec;
    difference.tv_usec = end.tv_usec - begin.tv_usec;
    if (difference.tv_usec < 0) {
        difference.tv_usec += 1000000;
        difference.tv_sec--;
    }
    return difference;
}

//functions for the pthreads to do and their creation
//------------------------------------------------------------------------------

//Request thread, Person-specific
void* request_exec(void* argument) {
    int tid = *((int*) argument);

    Person* newGuy = people[tid];
    
    for(int i = 0; i < num_requests ; i++) {
        buffer->deposit("data " + newGuy->getName());
    }

    return NULL;
}

//Worker thread, independant of number of people
void* worker_exec(void* argument) {
    mutex.P();
    RequestChannel chan(control->send_request("newthread"), RequestChannel::CLIENT_SIDE);
    mutex.V();

    while(true) {
        mutex.P();
        if(items_consumed >= 3*num_requests) {
            mutex.V();
            break;
        }
        else {
            items_consumed++;
            mutex.V();
            
            string item = buffer->withdraw();
            int data = atoi(chan.send_request(item).c_str());
            if(item == "data John Doe") {
                stat_buffers[0]->deposit(data);
            }
            else if(item == "data Joe Smith") {
                stat_buffers[1]->deposit(data);
            }
            else if(item == "data Jane Smith") {
                stat_buffers[2]->deposit(data);
            }
            else cout << "bad data request";
        }
    }
    //sem_wait(&mutex);
    chan.send_request("quit");
    //sem_post(&mutex);
    
    return NULL;
}

//Statistics thread, Person-specific
void* stat_exec(void* argument) {
    int tid = *((int*) argument);

    Person* newGuy = people[tid];
    BoundedBuffer<int>* hisBuffer = stat_buffers[tid];
    
    for(int i = 0; i < num_requests ; i++) {
        newGuy->addToHistogram(hisBuffer->withdraw());
    }
    newGuy->printHistogram();
    
    delete newGuy;
    delete hisBuffer;

    return NULL;
}

void print_CLA_error() {
    cout << "Error: program needs arguments in the following format with positive integer arguments:\n" <<
            "\t-n <number of data requests per person>\n" <<
            "\t-b <size of bounded buffer in requests>\n" <<
            "\t-w <number of worker threads>\n";
}

//main
//------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
    //Parse command line arguments
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
                // assert(num_requests != 0);
            }
            if(argv[i] == string("-b")) {
                correct_args++;
                buffer_size = atoi(argv[i+1]);
                // assert(buffer_size != 0);
            }
            if(argv[i] == string("-w")) {
                correct_args++;
                num_workers = atoi(argv[i+1]);
                // assert(num_workers != 0);
            }
        }
        if(correct_args != 3) { //if arguments are incorrect, program must exit
            print_CLA_error();
            return -1;
        }
    }
        
    //fork separate processes
    int pid = fork();
    if(pid == -1) {
        cout << "Error forking processes\n";
        //return -1;
    }
    else if(pid == 0) {
        start_timer();
        cout << "Establishing control channel...";
        control = new RequestChannel("control", RequestChannel::CLIENT_SIDE);
        cout << "done." << endl;
        
        BoundedBuffer<string> this_buffer(buffer_size);
        buffer = &this_buffer;
        pthread_t request_t[3];
        pthread_t stat_t[3];
        mutex.init(1);
        items_consumed = 0;
        
        //Create John Doe stuff
        people.push_back(new Person("John Doe", 0));
            stat_buffers.push_back(new BoundedBuffer<int>(buffer_size));
            int tid0 = people[0]->getId();
            pthread_create(&request_t[0], NULL, request_exec, (void*) &tid0);
            pthread_create(&stat_t[0], NULL, stat_exec, (void*) &tid0);

        //Create Joe Smith stuff
        people.push_back(new Person("Joe Smith", 1));
            stat_buffers.push_back(new BoundedBuffer<int>(buffer_size));
            int tid1 = people[1]->getId();
            pthread_create(&request_t[1], NULL, request_exec, (void*) &tid1);
            pthread_create(&stat_t[1], NULL, stat_exec, (void*) &tid1);
        
        //Create Jane Smith stuff
        people.push_back(new Person("Jane Smith", 2));
            stat_buffers.push_back(new BoundedBuffer<int>(buffer_size));
            int tid2 = people[2]->getId();
            pthread_create(&request_t[2], NULL, request_exec, (void*) &tid2);
            pthread_create(&stat_t[2], NULL, stat_exec, (void*) &tid2);
            
        //Create worker threads of any arbitrary number. Supports up to ~80 workers
        pthread_t worker_t[num_workers];
        for(int i = 0; i < num_workers; i++) {
            pthread_create(&worker_t[i], NULL, worker_exec, NULL);
        }
        
        //Join all threads to main thread for clean exit
        for(int i = 0; i < num_workers; i++) {
            pthread_join(worker_t[i], NULL);
        }
        
        for(int i = 0; i < 3; i++) {
            pthread_join(request_t[i], NULL);
            pthread_join(stat_t[i], NULL);
        }
        
        //Clean up everything
        control->send_request("quit");
        delete control;
        //delete mutex;
        
        timer diff = end_timer();
        
        cout << "Execution Time: " << diff.tv_sec << " sec, " << diff.tv_usec << " usec\n";
    }
    else {
	    execv("./dataserver", NULL);
	}
}






