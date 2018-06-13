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
	 * \brief Construct a TCP socket.
	 */
	ServerSocket(unsigned short localPort) throw(SocketException);

	/*!
	 * \brief Construct a TCP socket.
	 */
	ServerSocket(std::string &localAddress, unsigned short localPort) throw(SocketException);

	/*!
	 * \brief Blocks until a new connection is establisehd on this socket.
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
	 */
	void setListen(void) throw(SocketException);

};

#endif
