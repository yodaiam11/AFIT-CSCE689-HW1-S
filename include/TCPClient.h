#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <iostream>
#include<list>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<sys/un.h>
#include<string.h>
#include<netdb.h> 
#include<netinet/in.h> 
#include<arpa/inet.h> 
#include<string.h>

#include <string>
#include "Client.h"
#include <cstring>
#include <errno.h>

// The amount to read in before we send a packet
const unsigned int stdin_bufsize = 50;
const unsigned int socket_bufsize = 100;

#define PORT 9999

class TCPClient : public Client
{
public:
   TCPClient();
   ~TCPClient();

   virtual void connectTo(const char *ip_addr, unsigned short port);
   virtual void handleConnection();

   virtual void closeConn();

//added variables needed for client
private:

	int client_fileDes;
	struct sockaddr_in client_add;
	char buffer[1024] = { 0 };
	int addr_length, new_sock = 0;

	char* clientInp;

};


#endif
