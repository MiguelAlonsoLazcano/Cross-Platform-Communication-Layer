/*! 
 *  \brief Application Protocol Class.   
 * 
 */

#ifndef APPLICATIONPROTOCOL_H_
#define APPLICATIONPROTOCOL_H_

#define PAYLOAD_SIZE 32

enum message_types { MOTOR0 = 0, MOTOR1 = 1, SERVO0 = 2}; 



struct message
{
	message_types type;
	char payload[PAYLOAD_SIZE];

};

struct actuator_data
{
	int value;
};





#endif
