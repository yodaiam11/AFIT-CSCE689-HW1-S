#include "TCPServer.h"


//Source for TCPClient was https://www.geeksforgeeks.org/socket-programming-in-cc-handling-multiple-clients-on-server-without-multi-threading/

TCPServer::TCPServer() {
	
}


TCPServer::~TCPServer() {
 
}

/**********************************************************************************************
 * bindSvr - Creates a network socket and sets it nonblocking so we can loop through looking for
 *           data. Then binds it to the ip address and port
 *
 *    Throws: socket_error for recoverable errors, runtime_error for unrecoverable types
 **********************************************************************************************/

void TCPServer::bindSvr(const char *ip_addr, short unsigned int port) {

	//initialize all client_sockets to 0 
	for (i = 0; i < max_clients; i++)
	{
		client_sock[i] = 0;
	}

	//creates master socket  
	if ((master_sock = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	//allows master socket to have multiple connections  
	if (setsockopt(master_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0)
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
   
}

/**********************************************************************************************
 * listenSvr - Performs a loop to look for connections and create TCPConn objects to handle
 *             them. Also loops through the list of connections and handles data received and
 *             sending of data. 
 *
 *    Throws: socket_error for recoverable errors, runtime_error for unrecoverable types
 **********************************************************************************************/

void TCPServer::listenSvr() {

	//socket type created  
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	//binds socket to port 9999  
	if (bind(master_sock, (struct sockaddr*) & address, sizeof(address)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	printf("Listener on port %d \n", PORT);

	//limits to 5 incoming connections to sockett  
	if (listen(master_sock, 5) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	//accepts the incoming connection  
	addrlength = sizeof(address);
	puts("Waiting for connections ...");


	while (TRUE)
	{

		//std::cout << "I am Hereeeeeeeeeeee.\n";
		//clears socket set  
		FD_ZERO(&readfiledes);

		//adds master socket  
		FD_SET(master_sock, &readfiledes);
		max_sockdes = master_sock;

		//adds child sockets, socket descriptor, valid socket descriptor added, records highest file descriptor number
		for (i = 0; i < max_clients; i++)
		{
			sockdes = client_sock[i];
  
			if (sockdes > 0)
				FD_SET(sockdes, &readfiledes);
 
			if (sockdes > max_sockdes)
				max_sockdes = sockdes;
		}

		//waits for an activity on the sockets 
		sockact = select(max_sockdes + 1, &readfiledes, NULL, NULL, NULL);

		if ((sockact < 0) && (errno != EINTR))
		{
			printf("select error");
		}

		//looking for anything happening on socket 
		if (FD_ISSET(master_sock, &readfiledes))
		{

			if ((new_sock = accept(master_sock, (struct sockaddr*) & address, (socklen_t*)&addrlength)) < 0)
			{
				perror("accept");
				exit(EXIT_FAILURE);
			}

			//socket info for user 
			printf("New connection, socket fd is %d, ip is : %s, port : %d \n", new_sock, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

			//welcome message for new connection  
			if (send(new_sock, welmessage, strlen(welmessage), 0) != strlen(welmessage))
			{
				perror("send");
			}

			puts("Welcome message sent successfully");

			//adds new socket 
			for (i = 0; i < max_clients; i++)
			{  
				if (client_sock[i] == 0)
				{
					client_sock[i] = new_sock;
					printf("Adding to list of sockets as %d\n", i);

					break;
				}
			}

		}

		/*std::string s;
		std::cin >> s;
		if (s == "exit")
		{
			std::cout << "Server signing out!" << "\n";
			break;
		}*/

		//operation on some other socket 
		for (i = 0; i < max_clients; i++)
		{
			sockdes = client_sock[i];
			//checks for closing connection, client disconnect details, and closes socket for reuse
			if (FD_ISSET(sockdes, &readfiledes))
			{

				if ((valueread = read(sockdes, buffer, 1024)) == 0)
				{
					getpeername(sockdes, (struct sockaddr*) & address, \
						(socklen_t*)&addrlength);
					printf("Host disconnected , ip %s , port %d \n",
						inet_ntoa(address.sin_addr), ntohs(address.sin_port));
 
					close(sockdes);
					client_sock[i] = 0;


				}

				//Echo back the message that came in  
				else
				{
					//set the string terminating NULL byte on the end  
					//of the data read  
					buffer[valueread] = '\0';
					send(sockdes, buffer, strlen(buffer), 0);

					/*char* hello = "Hello from server";
					valueread = read(new_sock, buffer, 1024);
					printf("%s\n", buffer);
					send(new_sock, hello, strlen(hello), 0);
					printf("Hello message sent\n");*/
				}
			}
		}
	}
}

/**********************************************************************************************
 * shutdown - Cleanly closes the socket FD.
 *
 *    Throws: socket_error for recoverable errors, runtime_error for unrecoverable types
 **********************************************************************************************/

void TCPServer::shutdown() {
	std::cout << "Thanks for using\n";
}
