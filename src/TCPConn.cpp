#include "TCPConn.h"
#include "TCPServer.h"
#include "TCPClient.h"

#include <stdexcept>//
#include <iostream>//



TCPConn::TCPConn() {
	
}

TCPConn::~TCPConn() {

}

void TCPConn::handleConnection() {
	std::cout << "It's working, it's working...";
}
