/*! 
 *  \brief Socket Class.
 * 
 *  Socket base class representing basic communication endpoint.
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <string>
#include <iostream>
#include <sys/types.h>       // For data types
#include <sys/socket.h>      // For socket(), connect(), send(), and recv()
#include <netdb.h>           // For gethostbyname()
#include <arpa/inet.h>       // For inet_addr()
#include <unistd.h>          // UNIX standard definitions
#include <netinet/in.h>      // For sockaddr_in
#include <errno.h>           // For errno
#include <cstring> 	     // For memset
#include <vector>
#include <ifaddrs.h>	     // For interface addresses
#include <cstdlib>
#include <cstdio>


#include "SocketException.hpp"

class Socket {

public:

	/*!
	 * \brief Close this socket_handler destructor by calling close() system call.
	 * \param void.
	 * \return none.
	 */
	~Socket();

	/*!
	 * \brief Fetch the local address of this socket.
	 * \param void.
	 * \return Throw a SocketException in case of getsockname() system call failed.
	 */
	std::string getLocalAddress(void) throw(SocketException);

	/*!
	 * \brief Fetch the local port of this socket.
	 * \param void.
	 * \return Throw a SocketException in case of getsockname() system call failed.
	 */
	unsigned short getLocalPort(void) throw(SocketException);

	/*!
	 * \brief Fetch the IP address of this socket.
	 * \param void.
	 * \return Throw a SocketException in case of getifaddrs() system call failed.
	 */
	std::vector<std::string> getIPAddress(void) throw(SocketException);

	/*!
	 * \brief Bind the given port to this socket local port.
	 * \param int port.
	 * \return Throw a SocketException in case of bind() system call failed.
	 */
	void setLocalPort(unsigned short localPort) throw(SocketException);

	/*!
	 * \brief Bind the given address and port to this socket local address and local port.
	 * \param string address.
	 * \param int port.
	 * \return Throw a SocketException in case of bind() system call failed.
	 */
	void setLocalAddressAndPort(std::string &local_address, unsigned short local_port) throw(SocketException);

	/*!
	 * TODO: Resolve the service for the specified protocol. The default protocol is "tcp".
	 */
	static unsigned short resolveService(const std::string &service, const std::string &protocol = "tcp") throw(SocketException);

private:

	/*! 	
	 * \brief Prevent the user from trying to use value semantics on this object
	 */
	Socket(const Socket &sock);

	void operator=(const Socket &sock);

protected:

	/*! 	
	 * \brief Socket handler.
	 */
	int socket_handler;

	/*!
	 * \brief Socket constructor, creates a socket endpoint.
	 * \param int socket type.
	 * \param int connection protocol.
	 * \return Throw a SocketException in case of socket() systme call failed.
	 */
	Socket(int type, int protocol) throw(SocketException);

	/*!
	 * \brief Socket constructor, creates a socket endpoint, asigns the given socket_handler to
	 * this->socket_handler.
	 * \param int socket handler.
	 * \return Throw a SocketException in case of invalid socket_handler is given.
	 */
	Socket(int socket_handler) throw(SocketException);

};


// Function to fill in address structure given an address and port
static void fillAddr(const string &address, unsigned short port, sockaddr_in &addr) 
{
  memset(&addr, 0, sizeof(addr));  // Zero out address structure
  addr.sin_family = AF_INET;       // Internet address

  hostent *host;  // Resolve name
  if ((host = gethostbyname(address.c_str())) == NULL) {
    // strerror() will not work for gethostbyname() and hstrerror() 
    // is supposedly obsolete
    throw SocketException("Failed to resolve name (gethostbyname())");
  }
  addr.sin_addr.s_addr = *((unsigned long *) host->h_addr_list[0]);

  addr.sin_port = htons(port);     // Assign port in network byte order
}


#endif

