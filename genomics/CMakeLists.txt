CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)
PROJECT(Transcriptomics)

INCLUDE_DIRECTORIES( include )

ADD_DEFINITIONS( --std=c++11 )

ADD_EXECUTABLE(Reads src/getReads)
ADD_EXECUTABLE(Accond src/removeEscapes)
ADD_EXECUTABLE(MicroSat src/getMicroSatellite)
