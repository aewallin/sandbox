
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RenderWindowUISingleInheritance)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}) 

file(GLOB UI_FILES *.ui)
file(GLOB QT_WRAP *.h)
file(GLOB CXX_FILES *.cxx)

QT4_WRAP_UI(UISrcs ${UI_FILES})
QT4_WRAP_CPP(MOCSrcs ${QT_WRAP})
add_executable(RenderWindowUISingleInheritance MACOSX_BUNDLE ${CXX_FILES} ${UISrcs} ${MOCSrcs})
 
if(VTK_LIBRARIES)
  if(${VTK_VERSION} VERSION_LESS "6")
    target_link_libraries(RenderWindowUISingleInheritance ${VTK_LIBRARIES} QVTK)
  else()
    target_link_libraries(RenderWindowUISingleInheritance ${VTK_LIBRARIES})
  endif()
else()
  target_link_libraries(RenderWindowUISingleInheritance vtkHybrid QVTK vtkViews ${QT_LIBRARIES})
endif()
