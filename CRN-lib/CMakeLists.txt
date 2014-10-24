CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)
PROJECT(cppBioCheN)

INCLUDE_DIRECTORIES( include )

#ADD_SUBDIRECTORY(test)

ADD_DEFINITIONS( --std=c++11 )

#add_library(matrix SHARED
#include/
#src/
#)

ADD_EXECUTABLE(matrix src/overloadedMatrix)
ADD_EXECUTABLE(odeint-example src/harmonic_oscillator)
ADD_EXECUTABLE(boost-parser src/boost_test)
ADD_EXECUTABLE(ca-model src/ca-model)
#ADD_EXECUTABLE(matrix src/matrix-function)
#target_link_libraries( matrix libmatrix)
