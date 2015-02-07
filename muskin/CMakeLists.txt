CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)
PROJECT(MusKin)

INCLUDE_DIRECTORIES( include )

ADD_SUBDIRECTORY(lib)

ADD_DEFINITIONS( --std=c++11 -fopenmp)

#add_library(matrix SHARED
#include/
#src/
#)

#add_library(node SHARED
#include/
#src/
#)

ADD_EXECUTABLE(point src/Point)
TARGET_LINK_LIBRARIES(point node)
TARGET_LINK_LIBRARIES(point mesh)
