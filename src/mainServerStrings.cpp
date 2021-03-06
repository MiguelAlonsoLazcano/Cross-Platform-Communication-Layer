/*!
 *  \brief main Server executable with Strings.
 *
 *
 */

#include <cstdlib>
#include <iostream>
#include "ServerSocket.hpp"
#include "SocketException.hpp"
#include "ConnectionTCP.hpp"
#include "ApplicationProtocol.hpp"

using namespace std;


#define BUFFSIZE 32

void HandleConnection(ConnectionTCP *conn);

int main (int argc, char *argv[])
{
	if ( argc != 2 ) {
		cerr << "Usage: " << argv[0] << " <PORT> " << endl;
		exit (1);
	}

	unsigned short PORT = atoi(argv[1]);

	try {
		// Create Server Socket object
		ServerSocket server(PORT);
		// TODO : add socket.isOpen() call for a logical termination
		// condition instead of while(1)
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
	string incoming_message;

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
        	cout << "Message from Android: " << buffer << endl;
	}

	delete conn;

}