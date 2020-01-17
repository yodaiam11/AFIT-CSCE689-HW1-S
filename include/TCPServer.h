#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "Server.h"

#include <stdexcept>//
#include <iostream>//

#include <stdio.h>///
#include <string.h>//strlen/// 
#include <stdlib.h>///
#include <errno.h>///  
#include <unistd.h>//close///  
#include <arpa/inet.h>//close/// 
#include <sys/types.h>///
#include <sys/socket.h>/// 
#include <netinet/in.h>///
#include <sys/time.h>//FD_SET, FD_ISSET, FD_ZERO macros///

class TCPServer : public Server 
{
public:
   TCPServer();
   ~TCPServer();

   void bindSvr(const char *ip_addr, unsigned short port);
   void listenSvr();
   void shutdown();

private:
 


};


#endif
