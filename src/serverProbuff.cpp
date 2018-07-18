/*!
 *  \brief main Server executable.
 *
 *
 */

#include <cstdlib>
#include <iostream>
#include "ServerSocket.hpp"
#include "MotorPort.hpp"
#include "SocketException.hpp"
#include "ConnectionTCP.hpp"
#include "ApplicationProtocol.hpp"
#include "../build/proto/message.pb.h"
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>


using namespace std;




void HandleConnection(ConnectionTCP *conn);
void ShowConnectionDetails(ConnectionTCP *conn);

char* DEVICE;

int main (int argc, char *argv[])
{
	if ( argc != 3 ) {
		cerr << "Usage: " << argv[0] << " <PORT> <SERIAL_DEVICE>" << endl;
		exit (1);
	}

	unsigned short PORT = atoi(argv[1]);
	DEVICE = (char*)argv[2];

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
			MotorPort *motor;
			cout << "MESSAGE(0, " << message.value() << ")"  << endl;

			//////////////////////////
			// Prepare Service Message
			/*
				int address;
				bool operation;
				int length;
				int data;
				int crc;
			*/

			message_data outgoing_message;
			actuator_data data;
			data.address = 1;
			data.operation = true;
			data.length = sizeof(data);
			data.data = message.value();
			data.crc = 1;
			memcpy((void*)outgoing_message.payload, (void*) &data, sizeof(data));

			try {
				// Create serial object
				motor = new MotorPort(DEVICE);
			} catch (SerialException &e) {
				cerr << e.what() << endl;
				exit(1);
			}

				cout << "\tmotor 0 end point created " << endl;
			try {
				motor->send((char*) &outgoing_message,  sizeof(outgoing_message));
			} catch(SerialException &e) {
				std::cerr << e.what() << std::endl;
			}

				cout << "\tsend to serial port succedded.." << endl;
			break;

		}
		case AppMessage::Message::MOTOR1:
		{
			MotorPort *motor;
			cout << "MESSAGE(1, " << message.value() << ")"  << endl;

			//////////////////////////
			// Prepare Service Message
			/*
				int address;
				bool operation;
				int length;
				int data;
				int crc;
			*/

			message_data outgoing_message;
			actuator_data data;
			data.address = 1;
			data.operation = true;
			data.length = sizeof(data);
			data.data = message.value();
			data.crc = 1;
			memcpy((void*)outgoing_message.payload, (void*) &data, sizeof(data));

			try {
				// Create serial object
				motor = new MotorPort(DEVICE);
			} catch (SerialException &e) {
				cerr << e.what() << endl;
				exit(1);
			}

				cout << "\tmotor 1 end point created " << endl;
			try {
				motor->send((char*) &outgoing_message,  sizeof(outgoing_message));
			} catch(SerialException &e) {
				std::cerr << e.what() << std::endl;
			}

				cout << "\tsend to serial port succedded.." << endl;
			break;
		}
		case AppMessage::Message::SERVO0:
		{
			// TODO: create the respective ServoPort class to handle this case
			MotorPort *motor;
			cout << "MESSAGE(2, " << message.value() << ")"  << endl;

			//////////////////////////
			// Prepare Service Message
			/*
				int address;
				bool operation;
				int length;
				int data;
				int crc;
			*/

			message_data outgoing_message;
			actuator_data data;
			data.address = 1;
			data.operation = true;
			data.length = sizeof(data);
			data.data = message.value();
			data.crc = 1;
			memcpy((void*)outgoing_message.payload, (void*) &data, sizeof(data));

			try {
				// Create serial object
				motor = new MotorPort(DEVICE);
			} catch (SerialException &e) {
				cerr << e.what() << endl;
				exit(1);
			}

				cout << "\tservo 0 end point created " << endl;
			try {
				motor->send((char*) &outgoing_message,  sizeof(outgoing_message));
			} catch(SerialException &e) {
				std::cerr << e.what() << std::endl;
			}

				cout << "\tsend to serial port succedded.." << endl;
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

