

cmake_minimum_required(VERSION 2.6)
 
PROJECT(utst1)
 
find_package( Boost )
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    MESSAGE(STATUS " found Boost! good. ")
    MESSAGE(STATUS " boost-incude dirs are:" ${Boost_INCLUDE_DIRS})
    MESSAGE(STATUS " linking with: " ${Boost_LIBRARIES})
endif()

 
ADD_EXECUTABLE(utst1 utst1.cpp)
target_link_libraries(utst1 ${Boost_LIBRARIES})


