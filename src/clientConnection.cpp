/*!
 *  \brief client Connection executable.
 *
 *
 */
#include <cstdlib>
#include <iostream>
#include "ConnectionTCP.hpp"
#include "SocketException.hpp"
#include "ApplicationProtocol.hpp"

#define BUFFSIZE 32

int main (int argc, char *argv[])
{
	if ( argc != 3 ) {
		cerr << "Usage: " << argv[0] << " <ADDRESS> <PORT> " << endl;
		exit (1);
	}
	char BUFF[BUFFSIZE] = "ONE MESSAGE";
	std::string ADDRESS = argv[1];
	unsigned short PORT = atoi(argv[2]);

	// MESSAGE 0
	message outgoing_message;
	actuator_data data;
	data.value = 100;

	outgoing_message.type = MOTOR0;
	memcpy((void*)outgoing_message.payload, (void*) &data, sizeof(data));

	// MESSAGE 1
	message outgoing_message1;
	actuator_data data1;
	data1.value = 50;

	outgoing_message1.type = MOTOR1;
	memcpy((void*)outgoing_message1.payload, (void*) &data1, sizeof(data1));

	// MESSAGE 2
	message outgoing_message2;
	actuator_data data2;
	data2.value = 15;

	outgoing_message2.type = SERVO0;
	memcpy((void*)outgoing_message2.payload, (void*) &data2, sizeof(data2));

	std::cout << "connecting to " << ADDRESS << ":" << PORT << endl;
	Connection *conn;
	try {
		// Establish connection with the ServerSocket
		conn = new ConnectionTCP(ADDRESS, PORT);
	} catch(SocketException &e) {
		std::cerr << e.what() << std::endl;
		exit(1);
	}

	try {
	conn->send((char*) &outgoing_message,  sizeof(outgoing_message));
	} catch(SocketException &e) {
		std::cerr << e.what() << std::endl;
	}

	try {
	conn->send((char*) &outgoing_message1,  sizeof(outgoing_message1));
	} catch(SocketException &e) {
		std::cerr << e.what() << std::endl;
	}

	try {
	conn->send((char*) &outgoing_message2,  sizeof(outgoing_message2));
	} catch(SocketException &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;

}
