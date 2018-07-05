/*!
 *  \brief Socket Exception Class.
 *
 *  Socket Exception Class, signals a problem with the execution of a socket call.
 */

#include "SocketException.hpp"


SocketException::SocketException(const string &message, bool inclSysMsg) throw():
exceptionMessage(message)
{

	if (inclSysMsg) {
		exceptionMessage.append(": ");
		exceptionMessage.append(strerror(errno));
	}
}

SocketException::~SocketException() throw() { }

const char *SocketException::what() const throw()
{

	return exceptionMessage.c_str();
}



