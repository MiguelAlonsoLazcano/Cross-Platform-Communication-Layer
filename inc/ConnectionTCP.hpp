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
	 * \brief Construct a TCP Socket with no connection by calling its parent Constructor(socket_type, connection_protocol).
	 * \param void.
	 * \return Throw a SocketException in case of parent constructor failed.
	 */
	ConnectionTCP(void) throw(SocketException);

	/*!
	 * \brief Construct a TCP Socket with a connection to the given remote address and port.
	 */
	/*!
	 * \brief Construct a TCP Socket connected to a remote endpoint by calling its parent Constructor(remote_address, remote_port).
	 * \param std::string remote address.
	 * \param uint remote port.
	 * \return Throw a SocketException in case of parent constructor failed.
	 */
	ConnectionTCP(const std::string &remoteAddress, unsigned short remotePort) throw(SocketException);

private:

	/*!
	 * \brief Acess for ServerSocket::accept() connection call.
	 */
	friend class ServerSocket; 

	/*!
	 * \brief Calls parent Constructor(socket_handler), asigns the given socket_handler to
	 * this->socket_handler.
	 * \param int socket_handler.
	 * \return Throw a SocketException in case of invalid socket_handler is given.
	 */
	ConnectionTCP(int newConnection) throw(SocketException);


};

#endif
