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


	/*
	 * Create and send message from an interactive user input
	 */
	int TYPE, VALUE;
	cout << "\tEnter device: (0) Motor0, (1) Motor1, (2) Servo: ";
	cin >> TYPE;

	switch(TYPE)
	{
		case 0:
			message.set_type(AppMessage::Message::MOTOR0);
			cout << "\tEnter value: [0 -- 100] for Motor: ";
			cin >> VALUE;
			if (VALUE >= 0 && VALUE <= 100)
				message.set_value(VALUE);
			else
			{
				cout << "\t\tInvalid value.. exit" << endl ;
				exit(1);
			}
			break;
		case 1:
			message.set_type(AppMessage::Message::MOTOR1);
			cout << "\tEnter value: [0 -- 100] for Motor: ";
			cin >> VALUE;
			if (VALUE >= 0 && VALUE <= 100)
				message.set_value(VALUE);
			else
			{
				cout << "\t\tInvalid value.. exit" << endl ;
				exit(1);
			}
			break;
		case 2:
			message.set_type(AppMessage::Message::SERVO0);
			cout << "\tEnter value: [-15 -- +15] for Servo: ";
			cin >> VALUE;
			if (VALUE >= -15 && VALUE <= 15)
				message.set_value(VALUE);
			else
			{
				cout << "\t\tInvalid value.. exit" << endl ;
				exit(1);
			}
			break;
		default:
			cout << "\tInvalid device.. exit" << endl;
			exit(1);
	}

	cout << "MESSAGE(" << TYPE << ", " << VALUE << ")" << endl;



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


	try {
		conn->send(messageBuf,  messageSize);

	} catch(SocketException &e) {
		std::cerr << e.what() << std::endl;
		exit(1);
	}
	return 0;

}




