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
	message incoming_message;

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

	while ((recvMsg = conn->recv((char*) &incoming_message,sizeof(incoming_message))) > 0)
	{
		switch(incoming_message.type)
		{
			case MOTOR0:
			{
				actuator_data* data = (actuator_data*)&incoming_message.payload;
				cout << "\tMOTOR0: " << data->value  << endl;
				break;
			}

			case MOTOR1:
			{
				actuator_data* data = (actuator_data*)&incoming_message.payload;
				cout << "\tMOTOR1: " << data->value  << endl;
				break;
			}
			case SERVO0:
			{
				actuator_data* data = (actuator_data*)&incoming_message.payload;
				cout << "\tSERVO0: " << data->value  << endl;
				break;
			}
		}
	}

	delete conn;

}

























