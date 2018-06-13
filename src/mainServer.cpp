/*! 
 *  \brief main Server executable.   
 * 
 *  
 */

#include <cstdlib>
#include <iostream>
#include "ServerSocket.hpp"
#include "SocketException.hpp"
#include "ConnectionTCP.hpp"

using namespace std;


#define BUFFSIZE 32

void HandleConnection(ConnectionTCP *conn);

int main (int argc, char *argv[])
{
	if ( argc != 2 ) {
		cerr << "Usage: " << argv[0] << "<PORT> " << endl;
		exit (1);
	}

	unsigned short PORT = atoi(argv[1]); 

	try {
		// Create Server Socket object
		ServerSocket server(PORT);
		
		while(1) {
			HandleConnection(server.accept());
		}
	} catch (SocketException &e) {
		cerr << e.what() << endl;
		exit(1);
	}

	return 0;

}

void HandleConnection(ConnectionTCP *conn)
{
	cout << "Handling TCP Connection ";

	try {
		cout << conn->getRemoteAddress() << ":";
	} catch (SocketException &e) {
		cerr << "Unable to get remote address" << endl;
	}

	try {
		cout << conn->getRemotePort() << endl;
	} catch (SocketException &e) {
		cerr << "Unable to get remote port" << endl;
	}

	char buffer[BUFFSIZE];
	int recvMsg;

	while ((recvMsg = conn->recv(buffer, BUFFSIZE)) > 0)
	{
		cout << "received: " << buffer << endl;
	}

	delete conn;

}

























