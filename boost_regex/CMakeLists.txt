cmake_minimum_required(VERSION 2.6)

Project(regex_test)

FIND_PACKAGE(Boost COMPONENTS regex)
 
INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})

# set(CMAKE_BUILD_TYPE Release)
 set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Profile)

MESSAGE(STATUS " CMAKE_BUILD_TYPE  = " ${CMAKE_BUILD_TYPE})
MESSAGE(STATUS " libs = " ${Boost_LIBRARIES} ${Boost_REGEX_LIBRARY} )

ADD_EXECUTABLE(regex_test main.cpp)
target_link_libraries(regex_test ${Boost_LIBRARIES})
