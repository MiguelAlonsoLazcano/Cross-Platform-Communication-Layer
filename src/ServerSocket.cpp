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
	cout << "init server : " << localPort << "... " << endl;
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
