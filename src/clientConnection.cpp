/*!
 *  \brief client Connection executable.
 *
 *
 */
#include <cstdlib>
#include <iostream>
#include "ConnectionTCP.hpp"
#include "SocketException.hpp"


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

	std::cout << "connecting to " << ADDRESS << ":" << PORT << endl;
	try {
		// Establish connection with the ServerSocket
		ConnectionTCP conn(ADDRESS, PORT);

		conn.send(BUFF, BUFFSIZE);

	} catch(SocketException &e) {
		std::cerr << e.what() << std::endl;
		exit(1);
	}

	return 0;

}
