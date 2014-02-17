cmake_minimum_required(VERSION 2.6)
 
Project(zmq_repreq_client)
CMAKE_POLICY(SET CMP0012 NEW) # to make IF() below work

set( CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR} ) # FindZeroMQ.cmake is in the current src dir!
FIND_PACKAGE(ZeroMQ REQUIRED)
IF( ${ZeroMQ_FOUND} )
	MESSAGE( STATUS "ZEROMQ include: " ${ZeroMQ_INCLUDE_DIRS} )
	MESSAGE( STATUS "ZEROMQ     lib: " ${ZeroMQ_LIBRARIES} )
ENDIF()
# ZeroMQ_FOUND - system has libzmq
# ZeroMQ_INCLUDE_DIRS - the libzmq include directories
# ZeroMQ_LIBRARIES - link these to use libzmq

INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${ZeroMQ_INCLUDE_DIRS})

ADD_EXECUTABLE       (zmq_repreq_client client.c)
target_link_libraries(zmq_repreq_client ${ZeroMQ_LIBRARIES} ) 




