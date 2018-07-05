/*!
 *  \brief Server Socket Class.
 *
 *  Server Class, constructs a TCP socket by default.
 */

#include "ServerSocket.hpp"
#include "ConnectionTCP.hpp"


ServerSocket::ServerSocket(unsigned short localPort) throw(SocketException):
Socket(SOCK_STREAM, IPPROTO_TCP)
{

	// TODO: Test that the IP addresses that is show is always the same where the the server is listening.
	// TODO: Refactory getIPAddress to a separate function call in order to reuse this lines.
	std::vector<std::string> addresses = getIPAddress();
	std::vector<std::string>::const_iterator i = addresses.begin();
	cout << "Server listening: " <<  *i << ":" << localPort << " ... " << endl;
	setLocalPort(localPort);
	setListen();
}

ServerSocket::ServerSocket(std::string &localAddress, unsigned short localPort)
throw(SocketException) : Socket(SOCK_STREAM, IPPROTO_TCP)
{

	setLocalAddressAndPort(localAddress, localPort);
	setListen();
}

ConnectionTCP *ServerSocket::accept() throw(SocketException)
{

	int newConnSD;
	if ((newConnSD = ::accept(sockDesc, NULL, 0)) < 0)
		throw SocketException("Accept failed (accept())", true);

	return new ConnectionTCP(newConnSD);
}

void ServerSocket::setListen(void) throw(SocketException)
{

	if (::listen(sockDesc, 1) < 0)
		throw SocketException("Set listening socket failed (listen())", true);
}
