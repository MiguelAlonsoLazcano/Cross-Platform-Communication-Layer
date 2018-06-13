/*! 
 *  \brief Socket Exception Class.   
 * 
 *  Socket Exception Class, signals a problem with the execution of a socket call.
 */

#ifndef SOCKETEXCEPTION_H_
#define SOCKETEXCEPTION_H_

#include <string>            
#include <cstring>
#include <exception>
       
using namespace std;


class SocketException : public exception {

public:

	/*!
	 * \brief Construct a SocketException.
	 * \param Exception message.
	 * \param incSysMsg true if system message (from strerror(errno))
	 */
	SocketException(const string &message, bool inclSysMsg = false) throw();
	
	/*!
	 * \brief Guarantee that no exceptions are thrown.
	 */
	~SocketException() throw();

	/*!
	 * \brief Get exception message.
	 */
	const char *what() const throw();

private:
  
	string exceptionMessage;  
};

#endif
