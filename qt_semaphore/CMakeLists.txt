project(qt_semaphore)

cmake_minimum_required(VERSION 2.4)

if (CMAKE_BUILD_TOOL MATCHES "make")
    add_definitions(-Wall  -Wno-deprecated -Werror )
endif (CMAKE_BUILD_TOOL MATCHES "make")
# -pedantic-errors

FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui QtXml QtOpenGL REQUIRED)
INCLUDE(${QT_USE_FILE})
MESSAGE(STATUS "QT_USE_FILE = " ${QT_USE_FILE} )



set( MOC_HEADERS 
   # mandelbrotwidget.hpp
   # renderthread.hpp
)
qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})

set( PROJECT_SRC 
     ${${PROJECT_NAME}_SOURCE_DIR}/main.cpp 
  #   ${${PROJECT_NAME}_SOURCE_DIR}/mandelbrotwidget.cpp 
  #   ${${PROJECT_NAME}_SOURCE_DIR}/renderthread.cpp 
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
 #   ${Boost_LIBRARIES} 
 #   ${OPENGL_LIBRARIES}
)


