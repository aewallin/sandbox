cmake_minimum_required(VERSION 2.6)
 
Project(bgl_test)
 

FIND_PACKAGE(Boost)
 
INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})



ADD_EXECUTABLE(bgl_test toposort.cpp)

# target for jpeg image of graph
add_custom_target(jpg 
              "dot" -Tjpg test.dot > test.jpg
            ) 
