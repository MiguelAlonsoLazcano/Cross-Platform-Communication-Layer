/*! 
 *  \brief Brief Socket Class.   
 * 
 *  Socket base class representing basic communication endpoint
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <string>
#include <iostream>
#include <sys/types.h>       // For data types
#include <sys/socket.h>      // For socket(), connect(), send(), and recv()
#include <netdb.h>           // For gethostbyname()
#include <arpa/inet.h>       // For inet_addr()
#include <unistd.h>          // For close()
#include <netinet/in.h>      // For sockaddr_in
#include <errno.h>           // For errno
#include <cstring> 	     // For memset
#include <vector>
#include <ifaddrs.h>	     // For interface addresses

#include "SocketException.hpp"

class Socket {

public:

	/*!
	 * \brief Defaul destructor.
	 */
	~Socket();

	/*!
	 * \brief Get the local address.
	 */
	std::string getLocalAddress(void) throw(SocketException);

	/*!
	 * \brief Get the local port.
	 */
	unsigned short getLocalPort(void) throw(SocketException);

	/*!
	 * \brief Get the IP address.
	 */
	std::vector<std::string> getIPAddress(void) throw(SocketException);

	/*!
	 * \brief Set the local port.
	 */
	void setLocalPort(unsigned short localPort) throw(SocketException);

	/*!
	 * \brief Set the local address and port.
	 */
	void setLocalAddressAndPort(std::string &localAddress, unsigned short localPort) throw(SocketException);

	/*!
	 * \brief Resolve the specified service for the specified protocol. 
	 * The default protocol is "tcp".
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
	 * \brief Socket descriptor. 
	 */
	int sockDesc;             

	Socket(int type, int protocol) throw(SocketException);

	Socket(int sockDesc);	

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

