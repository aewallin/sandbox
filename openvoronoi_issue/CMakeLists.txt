cmake_minimum_required(VERSION 2.6)

Project(voronoi_benchmark)

FIND_PACKAGE(Boost)
 
INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})

# set(CMAKE_BUILD_TYPE Release)
 set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Profile)




# for OpenVoronoi
find_library(OVD_LIBRARY 
            NAMES openvoronoi
            PATHS /usr/local/lib/openvoronoi
            DOC "openvoronoi"
            REQUIRED
)
include_directories( /usr/local/include/openvoronoi )
MESSAGE(STATUS " OpenVoronoi found:  " ${OVD_LIBRARY})
# for OpenVoronoi
set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} ) # Findqd.cmake is in this dir
find_package( qd REQUIRED )
include_directories(${QD_INCLUDE_DIR})

MESSAGE(STATUS " CMAKE_BUILD_TYPE  = " ${CMAKE_BUILD_TYPE})

ADD_EXECUTABLE(bvpvd bvpvd.cpp)
target_link_libraries(bvpvd ${Boost_LIBRARIES}  ${OVD_LIBRARY}  ${QD_LIBRARY} )

