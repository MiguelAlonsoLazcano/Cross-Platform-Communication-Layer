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
	 * \param std::string remote address.
	 * \param uint remote port
	 * \return throw a SocketException in case of connect() system call failed.
	 */
	void connect(const std::string &remoteAddress, unsigned short remotePort) throw(SocketException);

	/*!
	 * \brief Write the given buffer to this socket, connect() system call is required before
	 * calling send().
	 * \param void* data buffer.
	 * \param int buffer lenght.
	 * \return Throw a SocketException in case of send() system call failed.
	 */
	void send(const void *buffer, int bufferLen) throw(SocketException);

	/*!
	 * \brief  Read into the given buffer up to bufferLen bytes data from this socket, connect()
	 * system call is required before calling recv().
	 * \param void* data buffer.
	 * \param int buffer lenght.
	 * \return Number of bytes readed.
	 * \return Throw a SocketException in case of ::recv() system call failed.
	 */
	int recv(void *buffer, int bufferLen) throw(SocketException);

	/*!
	 * \brief Get the remote address.
	 * \param void.
	 * \return The remote address where this socket is connected.
	 * \return Throw a SocketException in case of getpeername() system call failed.
	 */
	std::string getRemoteAddress(void) throw(SocketException);

	/*!
	 * \brief Get the remote port.
	 * \param void.
	 * \return The remote port where this socket is connected.
	 * \return Throw a SocketException in case of getpeername() system call failed.
	 */
	unsigned short getRemotePort(void) throw(SocketException);

protected:

	/*!
	 * \brief Calls Socket(socket_type, connection_protocol) constructor.
	 * \param int socket_type, SOCK_STREAM by default.
	 * \param int connection_protocol, IPPROTO_TCP by default.
	 * \return Throw a SocketException in case of Socket() constructor failed.
	 */
	Connection(int type, int protocol) throw(SocketException);

	/*!
	 * \brief Calls Socket(socket_handler) constructor, asigns the given socket_handler to
	 * this->socket_handler.
	 * \param int socket_handler.
	 * \return Throw a SocketException in case of invalid socket_handler is given.
	 */
	Connection(int newConnection);


};

#endif
