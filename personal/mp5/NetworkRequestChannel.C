#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "NetworkRequestChannel.H"

using namespace std;

//Data Members
//------------------------------------------------------------------------------
const int MAX_MESSAGE = 255;
const int HOSTNAME_LEN = 255;

struct addrinfo hints;
struct addrinfo *res;

char hostname[HOSTNAME_LEN];

//Helper functions
//------------------------------------------------------------------------------
string toString(int number) {
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

//Constructors and destructor
//------------------------------------------------------------------------------

//Client Side
NetworkRequestChannel::NetworkRequestChannel(char* _server_host_name, char* _port_no) {
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;

    //Get info of compute server, check for errors
    int status = getaddrinfo(_server_host_name, _port_no, &hints, &res);
    if (status != 0) {
        cout << "getaddrinfo error: " << gai_strerror(status) << "\n";
        exit(1);
    }

    //traverse linked list to find a working IP address
    for(struct addrinfo *p = res; p != NULL; p = p->ai_next) {
        res = p;
    }

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(sockfd == -1) {
        cout << "socket error: " << gai_strerror(sockfd) << "\n";
        exit(1);
    }

    int connected = connect(sockfd, res->ai_addr, res->ai_addrlen);
    if(connected == -1) {
        cout << "connect error: " << gai_strerror(connected) << "\n";
        exit(1);            
    }

    new_fd = sockfd;
}
	
//Server Side
NetworkRequestChannel::NetworkRequestChannel(char* _port_no, int backlog) {
}

	
NetworkRequestChannel::~NetworkRequestChannel() {
	shutdown(new_fd, 2);
	close(new_fd);

	shutdown(sockfd, 1);
	close(sockfd);

	freeaddrinfo(res);
}

//Data transfer functions
//------------------------------------------------------------------------------
string NetworkRequestChannel::send_request(string _request) {
	cwrite(_request);
	string str = cread();
	return str;
}

string NetworkRequestChannel::cread() {
	char buf[MAX_MESSAGE];
    int bytes_received = recv(new_fd, buf, MAX_MESSAGE, 0);

    if(bytes_received == -1) {
    	cout << "recv() error: " << gai_strerror(bytes_received) << "\n";
    	return NULL;
    }
    else {
    	string str(buf);
    	return str;
	}
}

int NetworkRequestChannel::cwrite(string _msg) {
	const char* msg = _msg.c_str();

	if(sizeof(msg) >= MAX_MESSAGE) {
		cerr << "Message too long for Channel!\n";
		return -1;
	}

	int len, bytes_sent;
	len = _msg.size();
	bytes_sent = send(new_fd, msg, len, 0);
	if(bytes_sent == -1) {
    	cout << "send() error: " << gai_strerror(bytes_sent) << "\n";
		return -1;		
	}
	else return bytes_sent;
}