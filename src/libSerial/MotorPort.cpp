/*!
 *  \brief Brief MotorPort Class.
 *
 *  Abstraction for motor endpoint
 */

#include "MotorPort.hpp"



MotorPort::MotorPort(char* PortName) throw(SerialException):
SerialPort(PortName)
{
	// Set interface 9,600 bps, 8n1 non parity
	setSerialInterface(B9600, 0);
	setBlocking(0);
}
