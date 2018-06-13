/*! 
 *  \brief ConnectionTCP Class.   
 * 
 *  ConnectionTCP Class, constructs a TCP socket which is able to connect, send and receive.
 */

#include "ConnectionTCP.hpp"

ConnectionTCP::ConnectionTCP() throw(SocketException): 
Connection(SOCK_STREAM, IPPROTO_TCP) 
{ }

ConnectionTCP::ConnectionTCP(const string &remoteAddress, unsigned short remotePort)
throw(SocketException) : Connection(SOCK_STREAM, IPPROTO_TCP) 
{

	connect(remoteAddress, remotePort);
}

ConnectionTCP::ConnectionTCP (int newConnSD) : Connection(newConnSD) 
{

}
