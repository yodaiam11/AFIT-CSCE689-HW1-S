#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "Server.h"

#include <stdexcept>
#include <iostream>

#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <errno.h>  
#include <unistd.h>  
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <sys/time.h>

#define TRUE   1  
#define FALSE  0
#define PORT 9999

class TCPServer : public Server 
{
public:
   TCPServer();
   ~TCPServer();

   void bindSvr(const char *ip_addr, unsigned short port);
   void listenSvr();
   void shutdown();

   //added variables needed for server
   int opt = TRUE;
   int master_sock, new_sock, client_sock[30], addrlength, max_clients = 30, sockact, i, valueread, sockdes;
   int max_sockdes;
   struct sockaddr_in address;

   //data buffer
   char buffer[1025]; 

   //socket descriptors  
   fd_set readfiledes;

   //a welcome message to client
   char* welmessage = "Hello, Welcome to Ryan's server\r\n";

private:
 


};


#endif
