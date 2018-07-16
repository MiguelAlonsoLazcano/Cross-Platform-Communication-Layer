/*!
 *  \brief Brief SerialPort Class.
 *
 *  Serial class responsible for setup a serial connection to the respective endpoint
 */



#include "SerialPort.hpp"


using namespace std;

SerialPort::SerialPort(char* portname) throw(SerialException)
{
	// Make a new serial connection to the given port
	if ( (serial_handler = open (portname, O_RDWR | O_NOCTTY| O_SYNC)) < 0)
		throw SerialException("SerialPort creation failed (open())", true);
}

SerialPort::~SerialPort() {

	close(serial_handler);
	serial_handler = -1;
}

void SerialPort::setSerialInterface(int speed, int parity) throw(SerialException)
{
	struct termios tty;
	memset(&tty, 0, sizeof tty);
	if ( (tcgetattr(serial_handler, &tty)) < 0 )
		throw SerialException("set interface error (tcgetattr())", true);


	// Set baudrate
	cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

	// 8-bit chars
	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;

	// disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 10;           // read doesn't block (0) | read block waits for 10 chars
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl
					// ignore modem controls,
	tty.c_cflag |= (CLOCAL | CREAD);// enable reading

        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

	if ( (tcsetattr(serial_handler, TCSANOW, &tty)) < 0 )
		throw SerialException("set interface error (tcsetattr())", true);
}

void SerialPort::setBlocking(int should_block) throw(SerialException)
{
	struct termios tty;
        memset (&tty, 0, sizeof tty);

	if ( (tcgetattr (serial_handler, &tty)) < 0)
		throw SerialException("set blocking settings error (tcgetattr())", true);

        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        if ( (tcsetattr (serial_handler, TCSANOW, &tty)) < 0)
		throw SerialException("set blocking settings error (tcsetattr())", true);
}

void SerialPort::send(char *buffer, unsigned int buf_size) throw(SerialException)
{
	if ( (write(serial_handler, (void *) buffer, buf_size)) < 0)
		throw SerialException("Serial interface error (send())", true);
}

int SerialPort::recv(char *buffer, unsigned int buf_size) throw(SerialException)
{
	int rtn;
	if ( (rtn = read(serial_handler, (void *) buffer, buf_size) ) < 0)
		throw SerialException("Serial interface error (read())", true);
	return rtn;
}


