#######################################################
####################   PROJECT    #####################
#######################################################
cmake_minimum_required(VERSION 3.3)
project(A9POC)
set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(build-platforms)

######################  GTest #########################
# TODO: Add GTEST support
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})
#######################################################

######################  ARM CC ########################
# TODO: Add ARM CC / CXX support
# CC=arm-linux-gcc
# CXX=arm-linux-g++
# TODO: Configure TOOLCHAIN for specific target
if("${TOOLCHAIN}" STREQUAL "ARM")
     target_build()
 elseif("${TOOLCHAIN}" STREQUAL "HOST")
     host_build()
endif()
#######################################################



################## LINK & INC DIR #####################
link_directories(${CMAKE_SOURCE_DIR}/build)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

####################### SHARED_LIB ####################
# TODO: Create shared object for the Socket Abstraction Layer
# 	libsal.so
# add_library(serverSocket SHARED
#		src/Socket.cpp
#		src/SocketException.cpp
#		src/ServerSocket.cpp
#		src/Connection.cpp
#		src/ConnectionTCP.cpp
#	     )
# set(SOCK_LIBRARY serverSocket.so)
# target_link_libraries(mainServer "${SOCK_LIBRARY}")
#######################################################


#######################  APP ##########################
# add_executable(mainServer src/mainServer.cpp)
# target_link_libraries(mainServer serverSocket.so)
add_executable( mainServer
		src/Socket.cpp
		src/SocketException.cpp
		src/ServerSocket.cpp
		src/Connection.cpp
		src/ConnectionTCP.cpp
		src/ApplicationProtocol.cpp
		src/mainServer.cpp
		)

add_executable( connection
		src/Socket.cpp
		src/SocketException.cpp
		src/ServerSocket.cpp
		src/Connection.cpp
		src/ConnectionTCP.cpp
		src/ApplicationProtocol.cpp
		src/clientConnection.cpp
		)
#######################################################


# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

######################  GTest #########################
# Link runTests with what GTest and pthread library
# add_executable(runTests test/src/..)
#target_link_libraries(runTests ${GTEST_LIBRARIES} pthread libcheckout.so)
#######################################################
