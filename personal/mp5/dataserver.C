#include <cassert>
#include <cstring>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <vector>
#include <sstream>


#include "NetworkRequestChannel.H"

using namespace std;

char* port_number;
int backlog;
vector<pthread_t*> clients;
vector<int> client_fds;


//Main server-side program, receives and returns data from clients in new threads
//------------------------------------------------------------------------------
string to_string(int number) {
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

string process_string(string request) {
    usleep(1000 + (rand() % 5000));

    if (request.compare(0, 5, "hello") == 0) {
        return "Hello to you too!";
    }
    else if (request.compare(0, 4, "data") == 0) {
        return to_string(rand() % 100);
    }
    else {
        return "unknown request";
    }
}



//Parse Command Line Arguments
//------------------------------------------------------------------------------
void print_CLA_error() {
    cout << "Error: program needs arguments in the following format with positive integer arguments:\n" <<
            "\t-p <port number for data server>\n" <<
			"\t-b <backlog of the server socket>\n";
}

int parse_CLA(int argc, char* argv[]) {
    if(argc != 5) {
        print_CLA_error(); //If incorrect number of arguments, program must exit
        return -1;
    }
    else {
        int correct_args = 0;
        for(int i = 0; i < argc; i++) {
            if(argv[i] == string("-b")) {
                correct_args++;
                backlog = atoi(argv[i+1]);
                assert(backlog != 0);
            }
            if(argv[i] == string("-p")) {
                correct_args++;
                port_number = argv[i+1];
                assert(port_number != NULL);
            }
        }
        if(correct_args != 2) { //if arguments are incorrect, program must exit
            print_CLA_error();
            return -1;
        }
    }
    return 0;
}

//Main Function
//------------------------------------------------------------------------------

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char * argv[]) {
	if(parse_CLA(argc, argv) == -1) {
        return -1;
    }

    //Beginning of main code from Beej's guide

	fd_set master; // master file descriptor list
	fd_set read_fds; // temp file descriptor list for select()
	int fdmax; // maximum file descriptor number

	int listener; // listening socket descriptor
	int newfd; // newly accept()ed socket descriptor

	struct sockaddr_storage remoteaddr; // client address
	socklen_t addrlen;

	char buf[256]; // buffer for client data
	int nbytes;

	char remoteIP[INET6_ADDRSTRLEN];
	
	int yes=1; // for setsockopt() SO_REUSEADDR, below
	int i, j, rv;
	
	struct addrinfo hints, *ai, *p;
	
	FD_ZERO(&master); // clear the master and temp sets
	FD_ZERO(&read_fds);
	
	// get us a socket and bind it
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if ((rv = getaddrinfo(NULL, port_number, &hints, &ai)) != 0) {
		fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
		exit(1);
	}

	for(p = ai; p != NULL; p = p->ai_next) {
		listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (listener < 0) { 
			continue;
		}

		// lose the pesky "address already in use" error message
		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
		if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
			close(listener);
			continue;
		}
		break;
	}

	// if we got here, it means we didn't get bound
	if (p == NULL) {
		fprintf(stderr, "selectserver: failed to bind\n");
		exit(2);
	}

	freeaddrinfo(ai); // all done with this

	// listen
	if (listen(listener, 10) == -1) {
		perror("listen");
		exit(3);
	}

	// add the listener to the master set
	FD_SET(listener, &master);

	// keep track of the biggest file descriptor
	fdmax = listener; // so far, it's this one
	
	// main loop
	while(true) {
		read_fds = master; // copy it
		if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
			perror("select");
			exit(4);
		}
		//run through the existing connections looking for data to read
		for(i = 0; i <= fdmax; i++) {
			//a file descriptor is ready for action
			if (FD_ISSET(i, &read_fds)) {
				//ready file descriptor is the listener, so handle the new connection
				if (i == listener) {
					addrlen = sizeof(remoteaddr);
					newfd = accept(listener, (struct sockaddr *)&remoteaddr, &addrlen);
					//there was an error accepting the connection
					if (newfd == -1) {
						perror("accept");
					}
					//connected successfully, add new file descriptor to master set
					else {
						FD_SET(newfd, &master); 
						if(newfd > fdmax) { 
							fdmax = newfd;
						}
						printf("selectserver: new connection from %s on socket %d\n", inet_ntop(remoteaddr.ss_family, get_in_addr((struct sockaddr*)&remoteaddr), remoteIP, INET6_ADDRSTRLEN), newfd);
					}
				}
				//ready file descriptor is a worker, handle data from client
				else {
					nbytes = recv(i, buf, sizeof buf, 0);
					string buffer(buf);
					//something went wrong with client connection
					if (nbytes <= 0) {
						//client exited
						if (nbytes == 0) {
							printf("selectserver: socket %d hung up\n", i);
						}	
						//there was an error reading
						else {
							perror("recv");
						}
						//In either case, we must terminate this connection
						close(i); 
						FD_CLR(i, &master);
					}
					//the client has politely requested to quit
					else if(buffer == "quit" ) {
						printf("selectserver: socket %d hung up\n", i);
						close(i); 
						FD_CLR(i, &master);
					}
					//we got some data from the client 
					else {
						string to_return = process_string(buf);
						cout << "socket " << i << " received '" << buffer << "' and returned '" << to_return << "'\n";
						if (send(i, to_return.c_str(), nbytes, 0) == -1) {
							perror("send");
						}	
					}
					memset(buf, 0, sizeof(buf));
				} // END handle data from client
			} // END got new incoming connection
		} // END looping through file descriptors
	} // END for(;;)--and you thought it would never end!

    return 0;
}