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
	 * Setup a Message Object
	 */
	AppMessage::Message *message;
	message = new AppMessage::Message();

	/*
	 * Make a buffer that can hold message + room for a 32bit delimiter
	 */
	int messageSize = message->ByteSize()+4;
	char* messageBuf = new char[messageSize];

	/*
	 * Create Protobuf Object
	 */
	//google::protobuf::ClientDetails client;

	try {
		cout << "new connection from: " << conn->getRemoteAddress() << ":";
	} catch (SocketException &e) {
		cerr << "Unable to get remote address" << endl;
	}

	try {
		cout << conn->getRemotePort() << endl;
	} catch (SocketException &e) {
		cerr << "Unable to get remote port" << endl;
	}


	int recvMsg;

	while ( (recvMsg = conn->recv((char*) &messageBuf,messageSize) ) > 0)
	{
		// Read varint delimited protobuf object in to buffer
		google::protobuf::io::ArrayInputStream arrayIn(message,recvMsg);
		google::protobuf::io::CodedInputStream codedIn(&arrayIn);
		google::protobuf::uint32 size;
		codedIn.ReadVarint32(&size);
		google::protobuf::io::CodedInputStream::Limit msgLimit = codedIn.PushLimit(size);
		message->ParseFromCodedStream(&codedIn);
		codedIn.PopLimit(msgLimit);
	}

	delete conn;

}

























