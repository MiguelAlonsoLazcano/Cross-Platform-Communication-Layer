#######################################################
####################   PROJECT    #####################
#######################################################

cmake_minimum_required(VERSION 3.3)
project(A9POC)


################## LINK & INC DIR #####################
link_directories(${CMAKE_SOURCE_DIR}/build)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)
set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(FindProtobuf)
find_package(Protobuf REQUIRED)
find_package(Threads  REQUIRED)

include(build-platforms)
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


####################  PROTBUFF ########################
# Protocol Buffer static library
add_subdirectory(proto)

#######################################################


################# SOCK ABSTRACTION ####################
# Socket Abstraction share library
add_subdirectory(src)

#######################################################


#######################  APP ##########################
# SERVER
add_executable(mainServer src/serverProbuff.cpp)
target_link_libraries(mainServer socketAbst proto
			${PROTOBUF_LIBRARY}
			${CMAKE_THREAD_LIBS_INIT} )
# CLIENT
add_executable(connection src/clientProbuff.cpp)
target_link_libraries(connection socketAbst proto
			${PROTOBUF_LIBRARY}
			${CMAKE_THREAD_LIBS_INIT} )
#######################################################
