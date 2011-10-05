project(libqgl_thread)

cmake_minimum_required(VERSION 2.4)

if (CMAKE_BUILD_TOOL MATCHES "make")
    add_definitions(-Wall  -Wno-deprecated -Werror )
endif (CMAKE_BUILD_TOOL MATCHES "make")

FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui QtXml QtOpenGL REQUIRED)
INCLUDE(${QT_USE_FILE})
MESSAGE(STATUS "QT_USE_FILE = " ${QT_USE_FILE} )

# Find QGLViewer
set( CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR} )
find_package(QGLViewer REQUIRED)

set( MOC_HEADERS 
    glthread.hpp
    simpleviewer.hpp
)
qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})


set( PROJECT_SRC 
     ${${PROJECT_NAME}_SOURCE_DIR}/main.cpp 
     ${${PROJECT_NAME}_SOURCE_DIR}/simpleviewer.cpp 
     ${${PROJECT_NAME}_SOURCE_DIR}/glthread.cpp 
     ${${PROJECT_NAME}_SOURCE_DIR}/gldata.cpp 
     ${MOC_OUTFILES}
)

include_directories( ${CMAKE_SOURCE_DIR} )
add_executable( 
    ${PROJECT_NAME} 
    ${PROJECT_SRC}
)
target_link_libraries( 
    ${PROJECT_NAME} 
    ${QGLVIEWER_LIBRARIES}
    ${QT_LIBRARIES}
)
