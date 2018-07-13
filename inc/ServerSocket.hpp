/*! 
 *  \brief Server Socket Class.   
 *
 *  Server Class, constructs a TCP socket by default.
 */

#ifndef SERVERSOCKET_H_
#define SERVERSOCKET_H_

#include "Socket.hpp"

class ConnectionTCP;


class ServerSocket : public Socket {

public:

	/*!
	 * \brief Construct a TCP socket by calling its parent constructor Socket(socket_type, connection_protocol).
	 * \param int port, assing the given port to this socket local port.
	 * \return Throw a SocketException in case of parent constructor failed.
	 */
	ServerSocket(unsigned short local_port) throw(SocketException);

	/*!
	 * \brief Construct a TCP socket by calling its parent constructor Socket(socket_type, connection_protocol).
	 * \param string address, assing the given address to this socket local address.
	 * \param int port, assing the given port to this socket local port.
	 * \return Throw a SocketException in case of parent constructor failed.
	 */
	ServerSocket(std::string &local_address, unsigned short local_port) throw(SocketException);

	/*!
	 * \brief Blocks until a new connection is establisehd on this socket.
	 * \param void.
	 * \return Throw a SocketException in case of accept() system call failed.
	 */

	ConnectionTCP *accept(void) throw(SocketException) ;

	/*!
	 * \TODO: add support for UDP connection 
	 * \brief Blocks until a new connection is establisehd on this socket.
	 * ConnectionUDP *accept(void) throw(SocketException) ;	 
	 */


private:

	/*!
	 * \brief Start listen on in the given port number.
	 * \param void.
	 * \return Throw a SocketException in case of listen() system call failed.
	 */
	void setListen(void) throw(SocketException);

};

#endif
