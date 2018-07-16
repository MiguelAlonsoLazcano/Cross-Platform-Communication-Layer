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
	AppMessage::Message message;

	message.set_value(100);
	message.set_type(AppMessage::Message::MOTOR0);


	/*
	 * Make a buffer that can hold message + room for a 32bit delimiter
	 */
	int variantSize = google::protobuf::io::CodedOutputStream::VarintSize32(message.ByteSize());
	int messageSize = message.ByteSize()+variantSize;
	char* messageBuf = new char[messageSize];


	/*
	 * Write varint delimiter to buffer
	 */
	google::protobuf::io::ArrayOutputStream arrayOut(messageBuf, messageSize);
	google::protobuf::io::CodedOutputStream codedOut(&arrayOut);
	codedOut.WriteVarint32(message.ByteSize());

	/*
	 * Write Message Object to buffer
	 */
	message.SerializeToCodedStream(&codedOut);

	// For debugging
	//std::cout << "messageSize: " << messageSize << std::endl;

	Connection *conn;
	try {
		// Establish connection with the ServerSocket
		conn = new ConnectionTCP(ADDRESS, PORT);
	} catch(SocketException &e) {
		std::cerr << e.what() << std::endl;
		exit(1);
	}

	// TODO: Create and send messages from an interactive user input
	try {
		conn->send(messageBuf,  messageSize);

	} catch(SocketException &e) {
		std::cerr << e.what() << std::endl;
		exit(1);
	}
	return 0;

}




