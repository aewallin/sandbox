cmake_minimum_required(VERSION 2.6)
PROJECT(openmp_for)


if (CMAKE_BUILD_TOOL MATCHES "make")
    add_definitions(-Wall -fno-math-errno)
endif (CMAKE_BUILD_TOOL MATCHES "make")
#     -Werror 

 
ADD_EXECUTABLE(openmp_for main.cpp)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(openmp_for PUBLIC OpenMP::OpenMP_CXX)
endif()


