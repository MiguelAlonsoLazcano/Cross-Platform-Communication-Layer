/*! 
 *  \brief ConnectionTCP Class.   
 * 
 *  ConnectionTCP Class, constructs a TCP socket which is able to connect, send and receive.
 */

#ifndef CONNECTIONTCP_H_
#define CONNECTIONTCP_H_

#include "Connection.hpp"

class ConnectionTCP : public Connection {

public:

	/*!
	 * \brief Construct a TCP Socket with no connection.
	 */
	ConnectionTCP(void) throw(SocketException);

	/*!
	 * \brief Construct a TCP Socket with a connection to the given remote address and port.
	 */
	ConnectionTCP(const std::string &remoteAddress, unsigned short remotePort) throw(SocketException);

private:
	/*!
	 * \brief Acess for ServerSocket::accept() connection creation.
	 */
	friend class ServerSocket; 

	ConnectionTCP(int newConnection);


};

#endif
