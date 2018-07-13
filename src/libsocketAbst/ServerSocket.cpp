/*!
 *  \brief Server Socket Class.
 *
 *  Server Class, constructs a TCP socket by default.
 */

#include "ServerSocket.hpp"
#include "ConnectionTCP.hpp"


ServerSocket::ServerSocket(unsigned short local_port) throw(SocketException):
Socket(SOCK_STREAM, IPPROTO_TCP)
{

	// TODO: Test that the IP addresses that is show is always the same where the the server is listening.
	// TODO: Refactory getIPAddress to a separate function call in order to reuse this lines.
	std::vector<std::string> addresses = getIPAddress();
	std::vector<std::string>::const_iterator i = addresses.begin();
	cout << "Server listening: " <<  *i << ":" << local_port << " ... " << endl;
	setLocalPort(local_port);
	setListen();
}

ServerSocket::ServerSocket(std::string &local_address, unsigned short local_port)
throw(SocketException) : Socket(SOCK_STREAM, IPPROTO_TCP)
{

	setLocalAddressAndPort(local_address, local_port);
	setListen();
}

ConnectionTCP *ServerSocket::accept() throw(SocketException)
{

	int newConnSD;
	if ((newConnSD = ::accept(socket_handler, NULL, 0)) < 0)
		throw SocketException("Accept failed (accept())", true);

	return new ConnectionTCP(newConnSD);
}

void ServerSocket::setListen(void) throw(SocketException)
{

	if (::listen(socket_handler, 1) < 0)
		throw SocketException("Set listening socket failed (listen())", true);
}
