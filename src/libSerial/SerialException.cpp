/*!
 *  \brief Serial Exception Class.
 *
 *  Serial Exception Class, Signals a problem with the execution of a system call.
 */

#include "SerialException.hpp"


SerialException::SerialException(const string &message, bool inclSysMsg) throw():
exceptionMessage(message)
{

	if (inclSysMsg) {
		exceptionMessage.append(": ");
		exceptionMessage.append(strerror(errno));
	}
}

SerialException::~SerialException() throw() { }

const char *SerialException::what() const throw()
{

	return exceptionMessage.c_str();
}
