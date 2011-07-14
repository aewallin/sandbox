

cmake_minimum_required(VERSION 2.6)
 
PROJECT(diangle_test)


if (CMAKE_BUILD_TOOL MATCHES "make")
    add_definitions(-Wall -Werror -fno-math-errno)
endif (CMAKE_BUILD_TOOL MATCHES "make")
 
 
ADD_EXECUTABLE(diangle_test diangle_test.cpp)



