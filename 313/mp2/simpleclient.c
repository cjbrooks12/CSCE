/* 
    File: simpleclient.C

    Author: R. Bettati
            Department of Computer Science
            Texas A&M University
    Date  : 2012/07/11

    Simple client main program for MP2 in CSCE 313
*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <cassert>
#include <string>
#include <iostream>
#include <sstream>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <errno.h>
#include <unistd.h>

#include "reqchannel.h"

using namespace std;

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */ 
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* LOCAL FUNCTIONS -- SUPPORT FUNCTIONS */
/*--------------------------------------------------------------------------*/

string int2string(int number) {
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

/*--------------------------------------------------------------------------*/
/* MAIN FUNCTION */
/*--------------------------------------------------------------------------*/
//Prints the time difference between two values
void print_time_diff(struct timeval * tp1, struct timeval * tp2) {
  long sec = tp2->tv_sec - tp1->tv_sec;
  long musec = tp2->tv_usec - tp1->tv_usec;
  if (musec < 0) {
    musec += 1000000;
    sec--;
  }
  printf(" [sec = %ld, musec = %ld] ", sec, musec);
}

//Emulate the calls to the server locally
//------------------------------------------------------------------------------
string send_request_local(string _request) {
  return _request;
}

//Routine to call server
//------------------------------------------------------------------------------
void call_server() {
    int pid = fork();
	
	if(pid == -1) {
		printf("error forking child process");
	}
	if(pid == 0) {
        RequestChannel chan("control", RequestChannel::CLIENT_SIDE);
        string reply1 = chan.send_request("hello");
        string reply2 = chan.send_request("data Joe Smith");
        string reply3 = chan.send_request("data Jane Smith");
        for(int i = 0; i < 100; i++) {
            string request_string("data TestPerson" + int2string(i));
            string reply_string = chan.send_request(request_string);
        }
        string reply4 = chan.send_request("quit");
        usleep(1000000);
	}
	else {
		execv("./dataserver", NULL);
	}
}

void call_local() {
    int pid = fork();
	
	if(pid == -1) {
		printf("error forking child process");
	}
	if(pid == 0) {
        string reply1 = send_request_local("hello");
        string reply2 = send_request_local("data Joe Smith");
        string reply3 = send_request_local("data Jane Smith");
        for(int i = 0; i < 100; i++) {
            string request_string("data TestPerson" + int2string(i));
            string reply_string = send_request_local(request_string);
        }
        string reply4 = send_request_local("quit");
        usleep(1000000);
	}
	else {
		execv("./dataserver", NULL);
	}
}

int main(int argc, char * argv[]) {
    int no_trials = 5;
    
    struct timeval server_start, local_start; 
    struct timeval server_end, local_end;
	    
	assert(gettimeofday(&server_start, 0) == 0);
	for(int i = 0; i < no_trials; i++) {
        call_server();
	}
    assert(gettimeofday(&server_end, 0) == 0);
    
    assert(gettimeofday(&local_start, 0) == 0);
	for(int i = 0; i < no_trials; i++) {
        call_local();
	}
    assert(gettimeofday(&local_end, 0) == 0);
    
    cout << "\n\nSERVER TIME\n";
	print_time_diff(&server_start, &server_end);
	
	cout << "\nLOCAL TIME\n";
	print_time_diff(&local_start, &local_end);
}




