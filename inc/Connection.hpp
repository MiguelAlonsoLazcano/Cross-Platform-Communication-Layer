/*! 
 *  \brief Connection Socket Class.   
 * 
 *  Connection Class, constructs a socket which is able to connect, send and receive.
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "Socket.hpp"

class Connection : public Socket {

public:

	/*!
	 * \brief Establish a socket connection to the given remote address and port.
	 */
	void connect(const std::string &remoteAddress, unsigned short remotePort) throw(SocketException);

	/*!
	 * \brief Write the fiven buffer to this socket, 
	 * Call connect() before calling send().
	 */
	void send(const void *buffer, int bufferLen) throw(SocketException);

	/*!
	 * \brief  Read into the given buffer up to bufferLen bytes data from this socket.  
	 * Call connect() before calling recv().
	 */
	int recv(void *buffer, int bufferLen) throw(SocketException);

	/*!
	 * \brief Get the remote address.
	 */
	std::string getRemoteAddress(void) throw(SocketException);

	/*!
	 * \brief Get the remote port.
	 */
	unsigned short getRemotePort(void) throw(SocketException);

protected:

	Connection(int type, int protocol) throw(SocketException);
	Connection(int newConnection);


};

#endif
