/*!
 *  \brief Brief Socket Class.
 *
 *  Socket base class representing basic communication endpoint
 */


#include "Socket.hpp"

using namespace std;


Socket::Socket(int type, int protocol) throw(SocketException)
{
	// Make a new socket
	if ((socket_handler = ::socket(PF_INET, type, protocol)) < 0)
		throw SocketException("Socket creation failed (socket())", true);
}

Socket::Socket(int socket_handler) throw(SocketException)
{
	if (socket_handler < 0 )
		throw SocketException("Invalid socket_handler in (Socket(socket_handler))", true);
	this->socket_handler = socket_handler;
}

Socket::~Socket() {

	::close(socket_handler);
	socket_handler = -1;
}

string Socket::getLocalAddress() throw(SocketException)
{
	sockaddr_in addr;
	unsigned int addr_len = sizeof(addr);

	if (getsockname(socket_handler, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0)
		throw SocketException("Fetch of local address failed (getsockname())", true);

	return inet_ntoa(addr.sin_addr);
}

unsigned short Socket::getLocalPort() throw(SocketException)
{
	sockaddr_in addr;
	unsigned int addr_len = sizeof(addr);

	if (getsockname(socket_handler, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0)
		throw SocketException("Fetch of local port failed (getsockname())", true);

	return ntohs(addr.sin_port);
}

void Socket::setLocalPort(unsigned short localPort) throw(SocketException)
{
	// Bind the socket to its port
	sockaddr_in localAddr;
	memset(&localAddr, 0, sizeof(localAddr));
	localAddr.sin_family = AF_INET;
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localAddr.sin_port = htons(localPort);

	if (bind(socket_handler, (sockaddr *) &localAddr, sizeof(sockaddr_in)) < 0)
		throw SocketException("Set of local port failed (bind())", true);

}

void Socket::setLocalAddressAndPort(std::string &localAddress, unsigned short localPort)
throw(SocketException)
{

	// Get the address of the requested host
	sockaddr_in localAddr;
	fillAddr(localAddress, localPort, localAddr);

	if (bind(socket_handler, (sockaddr *) &localAddr, sizeof(sockaddr_in)) < 0)
		throw SocketException("Set of local address and port failed (bind())", true);

}

// Get a Vector of the IP addresses of this computer
std::vector<std::string> Socket::getIPAddress() throw(SocketException) {

	std::vector<std::string> IPAddresses;
	int TempAddress = 0;
	char* TempIPAddress = (char*) malloc(16);

	ifaddrs* ifap = NULL;   //Head of the interface address linked list

	if (getifaddrs(&ifap) == 0 && ifap != NULL)
	{
		//Get another pointer to move down the linked list
		ifaddrs* current = ifap;
		//Move down the linked list until we get to a NULL pointer
		while (current != NULL)
		{
			//Create a pointer of the correct type to work with
			const sockaddr_in* interfaceAddress =
				reinterpret_cast<const sockaddr_in*>(current->ifa_addr);

			if (current->ifa_addr != NULL) {
				if (current->ifa_addr->sa_family == AF_INET) {
				//printf("%s:", current->ifa_name);
					if (interfaceAddress != NULL) {
						TempAddress = ntohl(interfaceAddress->sin_addr.s_addr);
						sprintf(TempIPAddress, "%d.%d.%d.%d", (TempAddress >> 24)
						& 0xFF, (TempAddress >> 16) & 0xFF, (TempAddress >> 8) & 0xFF, TempAddress & 0xFF);

						//Don't include the lookback address
						if (strcmp(TempIPAddress, "127.0.0.1") != 0) {
							IPAddresses.push_back(std::string(TempIPAddress));
						}
						//printf("%s\n", TempIPAddress);
					}
				}
			}
			//Move to the next node in the linked-list
			current = current->ifa_next;
		}
		//Release the interface memory
		freeifaddrs(ifap);
		ifap = NULL;
	} else {
		throw SocketException("Unable to fetch ip addresses from this machine (getifaddrs())", true);
	}
	return IPAddresses;
}



