cmake_minimum_required(VERSION 2.6)
 
Project(bgl_test)
 

FIND_PACKAGE(Boost)
 
INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})

add_definitions( -Werror -Wall -Wundef -Wshadow -Wno-error=shadow -Wno-long-long -Wno-deprecated -pedantic -pedantic-errors)
# -Wno-error=uninitialized

# set(CMAKE_BUILD_TYPE Release)
 set(CMAKE_BUILD_TYPE Debug)

ADD_EXECUTABLE(bgl_test main.cpp)
