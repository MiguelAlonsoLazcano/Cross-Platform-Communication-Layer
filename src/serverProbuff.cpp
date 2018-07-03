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
#include "../build/proto/message.pb.h"
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>


using namespace std;




void HandleConnection(ConnectionTCP *conn);
void ShowConnectionDetails(ConnectionTCP *conn);


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

	/*
	 * Show connection details
	 */
	ShowConnectionDetails(conn);

	/*
	 * Setup a Message Object
	 */
	AppMessage::Message message;

	/*
	 * Make a buffer that can hold message + room for a 32bit delimiter
	 */
	int recvMsg = 0;

	// Read delimiter
	char bite; int recv_bytes = 0; unsigned int length = 0;
	int received = conn->recv(&bite, 1);
	if (received < 0)
		std::cout << "received " << received << std::endl;
	else
		recv_bytes += received;
	length = (bite & 0x7f);
	// For debugging
	// std::cout << "received length " << length << std::endl;
	char* messageBuf = new char[length];


	recvMsg = conn->recv(messageBuf, length);
		// For debugging
		// std::cout << "received... " << recvMsg << std::endl;

	// Read varint delimited protobuf object in to buffer
	google::protobuf::io::ArrayInputStream arrayIn(messageBuf,recvMsg);
	google::protobuf::io::CodedInputStream codedIn(&arrayIn);
	google::protobuf::io::CodedInputStream::Limit msgLimit = codedIn.PushLimit(length);
	message.ParseFromCodedStream(&codedIn);
	codedIn.PopLimit(msgLimit);


	switch(message.type())
	{
		case AppMessage::Message::MOTOR0:
		{
			cout << "\tMOTOR0: " << message.value()  << endl;
			break;
		}
		case AppMessage::Message::MOTOR1:
		{
		cout << "\tMOTOR1: " << message.value()   << endl;
			break;
		}
		case AppMessage::Message::SERVO0:
		{
			cout << "\tSERVO0: " << message.value()   << endl;
			break;
		}
	}

	delete conn;

}



void ShowConnectionDetails(ConnectionTCP *conn)
{
	try {
		cout << "Connect  request: " << conn->getRemoteAddress() << ":";
	} catch (SocketException &e) {
		cerr << "Unable to get remote address" << endl;
	}

	try {
		cout << conn->getRemotePort() << endl;
	} catch (SocketException &e) {
		cerr << "Unable to get remote port" << endl;
	}
}

