/*!
 *  \brief SerialPort Class.
 *
 *  Serial class responsible for setup a serial connection to the respective endpoint
 */

#ifndef SERIALPORT_H_
#define SERIALPORT_H_

#include "SerialException.hpp"
#include <unistd.h>          // UNIX standard definitions
#include <fcntl.h> 	     // File control definitions
#include <termios.h>	     // POSIX terminal control definitions
#include <cstring> 	     // For memset

class SerialPort {

public:
	/*!
	 * \brief Defaul destructor.
	 */
	~SerialPort();

	/*!
	 * \brief Set the local port.
	 */
	void setSerialPort(char *portname);

	/*!
	 * \brief Set the serial port settings.
	 */
	void setSerialInterface(int speed, int parity) throw(SerialException);

	/*!
	 * \brief Set blocking.
	 */
	void setBlocking(int should_block) throw(SerialException);

	/*!
	 * \brief Write the given buffer to the serial port.
	 */
	void send(char *buffer, unsigned int buf_size) throw(SerialException);

	/*!
	 * \brief Read into the given buffer up to bufferLen bytes data
	 * from this serial port.
	 */
	int recv(char *buffer, unsigned int buf_size) throw(SerialException);

	/*!
	 * \brief Get the connection status.
	 */
	bool isConnected(void);

private:

	/*!
	 * \brief Prevent the user from trying to use value semantics on this object
	 */
	SerialPort(const SerialPort &port);

	void operator=(const SerialPort &port);

protected:

	bool connected = false;
	int serial_handler;

	SerialPort(char* portname, int speed, int parity) throw(SerialException);

	SerialPort(char* portname) throw(SerialException);

};


#endif
