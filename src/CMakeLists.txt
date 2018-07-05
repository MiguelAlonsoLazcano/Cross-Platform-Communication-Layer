####################### SHARED_LIB ####################
# Shared object for the Socket Abstraction Layer

add_library(socketAbst SHARED
		libsocketAbst/Socket.cpp
		libsocketAbst/SocketException.cpp
		libsocketAbst/ServerSocket.cpp
		libsocketAbst/Connection.cpp
		libsocketAbst/ConnectionTCP.cpp
	     )

