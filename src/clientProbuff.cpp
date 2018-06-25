/*!
 *  \brief client Connection executable.
 *
 *
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "ConnectionTCP.hpp"
#include "SocketException.hpp"
#include "../build/proto/message.pb.h"
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/io/coded_stream.h>

int main (int argc, char *argv[])
{
	if ( argc != 3 ) {
		cerr << "Usage: " << argv[0] << " <ADDRESS> <PORT> " << endl;
		exit (1);
	}

	std::string ADDRESS = argv[1];
	unsigned short PORT = atoi(argv[2]);
	std::cout << "connecting to " << ADDRESS << ":" << PORT << endl;


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
	 * Write varint delimiter to buffer
	 */
	google::protobuf::io::ArrayOutputStream arrayOut(messageBuf, messageSize);
	google::protobuf::io::CodedOutputStream codeOut(&arrayOut);
	codeOut.WriteVarint32(message->ByteSize());


	Connection *conn;
	try {
		// Establish connection with the ServerSocket
		conn = new ConnectionTCP(ADDRESS, PORT);
	} catch(SocketException &e) {
		std::cerr << e.what() << std::endl;
		exit(1);
	}


	try {
		conn->send((char*) &messageBuf,  messageSize);

	} catch(SocketException &e) {
		std::cerr << e.what() << std::endl;
		exit(1);
	}
	return 0;

}




