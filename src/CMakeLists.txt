####################### SHARED_LIB ####################
# Shared object for the Socket Abstraction Layer

add_library(socketAbst SHARED
		libsocketAbst/Socket.cpp
		libsocketAbst/SocketException.cpp
		libsocketAbst/ServerSocket.cpp
		libsocketAbst/Connection.cpp
		libsocketAbst/ConnectionTCP.cpp
		libsocketAbst/ApplicationProtocol.cpp
	     )

add_library(serialPort SHARED
		libSerial/SerialPort.cpp
		libSerial/SerialException.cpp
		libSerial/MotorPort.cpp
	     )

