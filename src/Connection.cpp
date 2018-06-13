/*! 
 *  \brief Connection Socket Class.   
 * 
 *  Connection Class, constructs a socket which is able to connect, send and receive.
 */

#include "Connection.hpp"

Connection::Connection(int type, int protocol) throw(SocketException): 
Socket(type, protocol) { }

Connection::Connection(int newConnSD): 
Socket(newConnSD) { }

void Connection::connect(const std::string &remoteAddress,unsigned short remotePort) 
throw(SocketException) {

	// Get the address of the requested host
	sockaddr_in destAddr;
	fillAddr(remoteAddress, remotePort, destAddr);

	// Try to connect to the given port
	if (::connect(sockDesc, (sockaddr *) &destAddr, sizeof(destAddr)) < 0)
		throw SocketException("Connect failed (connect())", true);

}

void Connection::send(const void *buffer, int bufferLen) throw(SocketException) 
{
	
	if (::send(sockDesc, (void *) buffer, bufferLen, 0) < 0) 
    		throw SocketException("Send failed (send())", true);
}

int Connection::recv(void *buffer, int bufferLen) throw(SocketException) 
{

	int rtn;
	if ((rtn = ::recv(sockDesc, (void *) buffer, bufferLen, 0)) < 0) 
		throw SocketException("Received failed (recv())", true);  
	return rtn;
}

std::string Connection::getRemoteAddress() throw(SocketException) 
{

	sockaddr_in addr;
	unsigned int addr_len = sizeof(addr);

	if (getpeername(sockDesc, (sockaddr *) &addr,(socklen_t *) &addr_len) < 0) 
		throw SocketException("Fetch of foreign address failed (getpeername())", true);

	return inet_ntoa(addr.sin_addr);
}

unsigned short Connection::getRemotePort() throw(SocketException)
{

	sockaddr_in addr;
	unsigned int addr_len = sizeof(addr);

	if (getpeername(sockDesc, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) 
		throw SocketException("Fetch of foreign port failed (getpeername())", true);

	return ntohs(addr.sin_port);
}


