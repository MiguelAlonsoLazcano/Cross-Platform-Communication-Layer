/*!
 *  \brief MotorPort Class.
 *
 *  Abstraction for motor endpoint
 */

#ifndef MOTORPORT_H_
#define MOTORPORT_H_

#include "SerialPort.hpp"

class MotorPort : public SerialPort {

public:

	/*!
	 * \brief Construct a serial port.
	 */
	MotorPort(char* PortName) throw(SerialException);



private:



};

#endif
