#######################################################
####################   PROJECT    #####################
#######################################################
cmake_minimum_required(VERSION 3.3)
project(A9POC)

################## LINK & INC DIR #####################
link_directories(${CMAKE_SOURCE_DIR}/build)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)
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


####################  PROTBUFF ########################
# TODO: Add Protobuf support
find_package(Threads REQUIRED)
add_subdirectory(proto)

#######################################################

#######################  APP ##########################
# SERVER
add_executable(mainServer src/mainServer.cpp)
target_link_libraries(mainServer socketAbst proto
			${PROTOBUF_LIBRARY}
			${CMAKE_THREAD_LIBS_INIT})
# CLIENT
add_executable(connection src/clientConnection.cpp)
target_link_libraries(connection socketAbst proto
			${PROTOBUF_LIBRARY}
			${CMAKE_THREAD_LIBS_INIT})
#######################################################


# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

######################  GTest #########################
# Link runTests with what GTest and pthread library
# add_executable(runTests test/src/..)
#target_link_libraries(runTests ${GTEST_LIBRARIES} pthread libcheckout.so)
#######################################################
