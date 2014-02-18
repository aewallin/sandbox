cmake_minimum_required(VERSION 2.6)
 
Project(zmq_pub)
CMAKE_POLICY(SET CMP0012 NEW)

set( CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR} ) # FindZeroMQ.cmake is in the current src dir!
FIND_PACKAGE(ZeroMQ REQUIRED)
IF( ${ZeroMQ_FOUND} )
	MESSAGE( STATUS "ZEROMQ include: " ${ZeroMQ_INCLUDE_DIRS} )
	MESSAGE( STATUS "ZEROMQ     lib: " ${ZeroMQ_LIBRARIES} )
ENDIF()
# ZeroMQ_FOUND - system has libzmq
# ZeroMQ_INCLUDE_DIRS - the libzmq include directories
# ZeroMQ_LIBRARIES - link these to use libzmq

FIND_PACKAGE(Protobuf REQUIRED)
#   PROTOBUF_FOUND - Found the Google Protocol Buffers library
#   PROTOBUF_INCLUDE_DIRS - Include directories for Google Protocol Buffers
#   PROTOBUF_LIBRARIES - The protobuf library
#
# The following cache variables are also defined:
#   PROTOBUF_LIBRARY - The protobuf library
#   PROTOBUF_PROTOC_LIBRARY   - The protoc library
#   PROTOBUF_INCLUDE_DIR - The include directory for protocol buffers
#   PROTOBUF_PROTOC_EXECUTABLE - The protoc compiler
IF( ${PROTOBUF_FOUND} )
	MESSAGE( STATUS "Protobuf  include: " ${PROTOBUF_INCLUDE_DIRS} )
	MESSAGE( STATUS "Protobuf      lib: " ${PROTOBUF_LIBRARIES} )
ENDIF()
INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${PROTOBUF_INCLUDE_DIRS} ${ZeroMQ_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
set( PROTO_SRCS proto.c)
set( PROTO_HDRS proto.h)
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS "mymessage.proto")
#add_library(mymessage mymessage.pb-c.c)
#target_link_libraries(mymessage ${PROTOBUF_LIBRARIES}) 

ADD_EXECUTABLE       (zmq_pub  pub.cc ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(zmq_pub  ${PROTOBUF_LIBRARY} ${ZeroMQ_LIBRARIES} ) 




