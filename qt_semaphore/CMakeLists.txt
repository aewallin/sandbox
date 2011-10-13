project(qt_semaphore)

cmake_minimum_required(VERSION 2.4)

if (CMAKE_BUILD_TOOL MATCHES "make")
    add_definitions(-Wall  -Wno-deprecated -Werror )
endif (CMAKE_BUILD_TOOL MATCHES "make")
# -pedantic-errors

FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui QtXml QtOpenGL REQUIRED)
INCLUDE(${QT_USE_FILE})
MESSAGE(STATUS "QT_USE_FILE = " ${QT_USE_FILE} )

set( PROJECT_SRC 
     ${${PROJECT_NAME}_SOURCE_DIR}/main.cpp 
)

include_directories( ${CMAKE_SOURCE_DIR} )


add_executable( 
    ${PROJECT_NAME} 
    ${PROJECT_SRC}
)
target_link_libraries( 
    ${PROJECT_NAME} 
    ${QT_LIBRARIES} 
)


