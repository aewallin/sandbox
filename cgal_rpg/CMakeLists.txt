cmake_minimum_required(VERSION 2.6)
 
Project(rpg_test)
 
FIND_PACKAGE(CGAL COMPONENTS Core  REQUIRED)
include( ${CGAL_USE_FILE} )
 
ADD_EXECUTABLE(
    ${PROJECT_NAME} 
    rpg_test.cpp
)
