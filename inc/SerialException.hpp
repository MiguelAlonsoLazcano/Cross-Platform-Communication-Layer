/*!
 *  \brief Serial Exception Class.
 *
 *  Serial Exception Class, Signals a problem with the execution of a system call.
 */

#ifndef SERIALEXCEPTION_H_
#define SERIALEXCEPTION_H_

#include <string>
#include <cstring>
#include <exception>

using namespace std;


class SerialException : public exception {

public:

	/*!
	 * \brief Construct a SocketException.
	 * \param Exception message.
	 * \param incSysMsg true if system message (from strerror(errno))
	 */
	SerialException(const string &message, bool inclSysMsg = false) throw();

	/*!
	 * \brief Guarantee that no exceptions are thrown.
	 */
	~SerialException() throw();

	/*!
	 * \brief Get exception message.
	 */
	const char *what() const throw();

private:

	string exceptionMessage;
};

#endif
