####################### SHARED_LIB ####################
# Shared object for the Socket Abstraction Layer

add_library(socketAbst SHARED
		Socket.cpp
		SocketException.cpp
		ServerSocket.cpp
		Connection.cpp
		ConnectionTCP.cpp
		ApplicationProtocol.cpp
	     )


