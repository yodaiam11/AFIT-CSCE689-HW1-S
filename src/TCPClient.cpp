#include "TCPClient.h"
//#include "TCPConn.h"


/**********************************************************************************************
 * TCPClient (constructor) - Creates a Stdin file descriptor to simplify handling of user input. 
 *
 **********************************************************************************************/

#define PORT 9999 

TCPClient::TCPClient() {

}

/**********************************************************************************************
 * TCPClient (destructor) - No cleanup right now
 *
 **********************************************************************************************/

TCPClient::~TCPClient() {

}

/**********************************************************************************************
 * connectTo - Opens a File Descriptor socket to the IP address and port given in the
 *             parameters using a TCP connection.
 *
 *    Throws: socket_error exception if failed. socket_error is a child class of runtime_error
 **********************************************************************************************/

void TCPClient::connectTo(const char *ip_addr, unsigned short port) {

	client_fileDes = socket(AF_INET, SOCK_STREAM, 0);
	if (client_fileDes == 0)
	{
		std::cout << "error creating server socket" << "\n";
	}

	client_add.sin_family = AF_INET;
	client_add.sin_port = htons(port);
	inet_pton(AF_INET, ip_addr, &client_add.sin_addr);

	std::cout << " client socket created" << "\n";
}

/**********************************************************************************************
 * handleConnection - Performs a loop that checks if the connection is still open, then 
 *                    looks for user input and sends it if available. Finally, looks for data
 *                    on the socket and sends it.
 * 
 *    Throws: socket_error for recoverable errors, runtime_error for unrecoverable types
 **********************************************************************************************/

void TCPClient::handleConnection() {

	if (connect(client_fileDes, (struct sockaddr*) & client_add,
		sizeof(client_add)) < 0) {
		printf("\n error : Connect Failed \n");
	}
	std::cout << " server connection succesfull" << "\n";


	char buf[socket_bufsize];
	//ZeroMemory(buf, 2013);
	memset(buf, 0, sizeof(buf));

	//int newBytes = read(client_fileD, buf, strlen(buf) + 1);
	int newBytes = recv(client_fileDes, buf, 99, 0);
	std::cout << "bytes recieved " << newBytes << "\n";
	if (newBytes <= 0)
	{
		// Drop the client
		close(client_fileDes);
		//FD_CLR(sock_listen, &master_list);
	}
	else
	{
		printf("%s\n ", buf);
		std::cout << " This is the client" << "\n";

		while (1)
		{
			char temp;
			std::string s;
			//char temp[] = "";
			//string work = "";
			char buffer[33];
			std::cout << "\n" << "Please enter a number from the menu" << "\n\n" << "Type menu to see the options available" << "\n\n" << "User Input: ";
			std::cin >> s;
			std::cout << "\n";
			//itoa(temp, buffer, 10);
			//std::cout << s << "\n";

			//int sock = 0, valread;
			//char* hello = "Hello from client";
			//send(sock, hello, strlen(hello), 0);
			//printf("Hello message sent\n");
			//valread = read(sock, buffer, 1024);
			//printf("%s\n", buffer);
			//return 0;

			if (s == "exit")
			{
				break;
			}
			else if (s == "1")
			{
				std::cout << "Menu 1" << "\n\n";
				//handleConnection();
			}
			else if (s == "2")
			{
				std::cout << "Menu 2" << "\n\n";
			}
			else if (s == "3")
			{
				std::cout << "Menu 3" << "\n\n";
			}
			else if (s == "4")
			{
				std::cout << "Menu 4" << "\n\n";
			}
			else if (s == "5")
			{
				std::cout << "Menu 5" << "\n\n";
			}
			else if (s == "passwd")
			{
				std::cout << "Does nothing yet, but in HW2, will be able to change your password" << "\n\n";
			}
			else if (s == "hello")
			{
				std::cout << "Hello from the other side..." << "\n\n";
			}
			else if (s == "menu")
			{
				std::cout << "Allowable commands" << "\n" << "1 - Menu 1" << "\n" << "2 - Menu 2" << "\n" << "3 - Menu 3" << "\n" << "4 - Menu 4" << "\n" << "5 - Menu 5" << "\n"
					<< "hello - greeting message" << "\n" << "passwd - for HW2" << "\n" << "exit - to disconnect" << "\n\n";
			}
			else
			{
				std::cout << "error, not a readable command" << "\n\n";
			}
		}

	}
}

/**********************************************************************************************
 * closeConnection - Your comments here
 *
 *    Throws: socket_error for recoverable errors, runtime_error for unrecoverable types
 **********************************************************************************************/

void TCPClient::closeConn() {
	std::cout << "See ya later!" << "\n";
}


