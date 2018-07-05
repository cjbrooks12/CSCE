#include <cassert>
#include <cstring>
#include <sstream>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <vector>

#include "person.H"
#include "buffer.H"
#include "timer.H"
#include "NetworkRequestChannel.H"

using namespace std;

int num_requests, buffer_size, num_workers;
char* server_name;
char* server_port;
int items_consumed;

vector<Person*> people;
BoundedBuffer<string>* buffer;

Semaphore mutex;
Timer exec_time;

//functions for the pthreads to do
//------------------------------------------------------------------------------

// Request thread, Person-specific
void* request_exec(void* argument) {
    int tid = *((int*) argument);

    Person* newGuy = people[tid];
    
    for(int i = 0; i < num_requests ; i++) {
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

//Worker thread, independant of number of people
void* worker_exec(void* argument) {
    int tid = *((int*) argument);

    // mutex.P();
    NetworkRequestChannel *chan = new NetworkRequestChannel(server_name, server_port);
    // mutex.V();

    while(true) {
        mutex.P(); //ensure check and increment are in the same step
        if(items_consumed == 3*num_requests) {
            mutex.V();
            break;
        }
        else {
            items_consumed++;
            mutex.V();

            string to_send = buffer->withdraw();
            int returned = atoi(chan->send_request(to_send).c_str());
            cout << tid << ": " << items_consumed << " " << to_send << " " << returned << "\n"; 

            if(to_send == "data John Doe") {
                people[0]->stat_buffer->deposit(returned);
            }
            else if(to_send == "data Joe Smith") {
                people[1]->stat_buffer->deposit(returned);
            }
            else if(to_send == "data Jane Smith") {
                people[2]->stat_buffer->deposit(returned);
            }
        }
    }
    
    // mutex.P();
    chan->send_request("quit");
    // mutex.V();

    return NULL;
}

//Statistics thread, Person-specific
void* stat_exec(void* argument) {
    int tid = *((int*) argument);

    Person* newGuy = people[tid];
    BoundedBuffer<int>* hisBuffer = newGuy->stat_buffer;
    
    for(int i = 0; i < num_requests ; i++) {
        newGuy->addToHistogram(hisBuffer->withdraw());
    }
    
    return NULL;
}

//Main program routine
//------------------------------------------------------------------------------
void run_program() {    
    BoundedBuffer<string> request_buffer(buffer_size);
    buffer = &request_buffer;
    mutex.init(1);
    items_consumed = 0;
    
    //Create the people and their respective threads
    people.push_back(new Person("John Doe", 0, buffer_size));
    people.push_back(new Person("Joe Smith", 1, buffer_size));
    people.push_back(new Person("Jane Smith", 2, buffer_size));
        
    for (int i = 0; i < 3; ++i) {
        pthread_create(&people[i]->request_t, NULL, request_exec, &people[i]->id);
        pthread_create(&people[i]->stat_t, NULL, stat_exec, &people[i]->id);
    }

    //Create worker threads and join them
    pthread_t worker_t[num_workers];
    for(int i = 0; i < num_workers; i++) {
        pthread_create(&worker_t[i], NULL, worker_exec, (void*) &i);
    }
    
    //Join all threads to main thread
    for(int i = 0; i < num_workers; i++) {
        pthread_join(worker_t[i], NULL);
    }
    
    for(int i = 0; i < 3; i++) {
        pthread_join(people[i]->request_t, NULL);
        pthread_join(people[i]->stat_t, NULL);
    }
    
    //Clean up everything
    for (int i = 0; i < people.size(); ++i) {
        people[i]->printHistogram();
    }
}

//Parse Command Line Arguments
//------------------------------------------------------------------------------
void print_CLA_error() {
    cout << "Error: program needs arguments in the following format with positive integer arguments:\n" <<
            "\t-n <number of data requests per person>\n" <<
            "\t-b <size of bounded buffer in requests>\n" <<
            "\t-w <number of channels>\n" <<
            "\t-h <name of server host>\n" <<
            "\t-p <port number>\n";
}

int parse_CLA(int argc, char* argv[]) {
    if(argc != 11) {
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
                num_workers = atoi(argv[i+1]);
                assert(num_workers != 0);
            }
            if(argv[i] == string("-h")) {
                correct_args++;
                server_name = argv[i+1];
                assert(server_name != 0);
            }
            if(argv[i] == string("-p")) {
                correct_args++;
                server_port = argv[i+1];
                assert(server_port != 0);
            }
        }
        if(correct_args != 5) { //if arguments are incorrect, program must exit
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
    
    exec_time.start();
    run_program();
    // socket_test();
    exec_time.finish().print();
 
}