project(libwgl_example1)

cmake_minimum_required(VERSION 2.4)

if (CMAKE_BUILD_TOOL MATCHES "make")
    add_definitions(-Wall  -Wno-deprecated -Werror )
endif (CMAKE_BUILD_TOOL MATCHES "make")
# -pedantic-errors

FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui QtXml QtOpenGL REQUIRED)
INCLUDE(${QT_USE_FILE})
MESSAGE(STATUS "QT_USE_FILE = " ${QT_USE_FILE} )

find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
    MESSAGE(STATUS "found OPENGL, lib = " ${OPENGL_LIBRARIES} )
endif(OPENGL_FOUND)

# find BOOST and boost-python
find_package( Boost )
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    MESSAGE(STATUS "found Boost: " ${Boost_LIB_VERSION})
    MESSAGE(STATUS "boost-incude dirs are: " ${Boost_INCLUDE_DIRS})
endif()

# Find QGLViewer

set( CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR} )

find_package(QGLViewer )



#find_library(QGLViewer 
#            NAMES qglviewer libqglviewer libqglgraphicssystem
#            PATHS /usr/local/lib /usr/lib /usr/lib/qt4/plugins/graphicssystems/
#            DOC "The libqgl library"
#            REQUIRED
#)

MESSAGE(STATUS "libqglviewer lib is: " ${QGLVIEWER_LIBRARIES})
MESSAGE(STATUS "libqglviewer include is: " ${QGLVIEWER_INCLUDE_DIR})


set( MOC_HEADERS 
#    appwindow.hpp
#    glthread.hpp
#    glwidget.hpp
)
qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})

set( PROJECT_SRC 
     ${${PROJECT_NAME}_SOURCE_DIR}/main.cpp 
     ${${PROJECT_NAME}_SOURCE_DIR}/simpleviewer.cpp 
     ${MOC_OUTFILES}
)


include_directories( ${CMAKE_SOURCE_DIR} )
add_executable( 
    ${PROJECT_NAME} 
    ${PROJECT_SRC}
)
target_link_libraries( 
    ${PROJECT_NAME} 
    ${QT_LIBRARIES} 
    ${Boost_LIBRARIES} 
    ${OPENGL_LIBRARIES}
    ${QGLVIEWER_LIBRARIES}
)


