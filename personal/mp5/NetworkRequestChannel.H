#ifndef _networkreqchannel_H_
#define _networkreqchannel_H_

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class NetworkRequestChannel {
private:

public:
	int sockfd, new_fd;

	//Client-side constructor
	NetworkRequestChannel(char* _server_host_name, char* _port_no);
	//Server-side constructor
	NetworkRequestChannel(char* _port_no, int backlog);
	//Common destructor
	~NetworkRequestChannel();

	//Read and write from socket file descriptors
	string send_request(string _request);
	string cread();
	int cwrite(string _msg);
};

#endif