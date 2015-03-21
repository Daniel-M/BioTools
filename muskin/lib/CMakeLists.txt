CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)
ADD_DEFINITIONS( -fopenmp --std=c++11)
#ADD_DEFINITIONS(--std=c++11)

add_library(iteratefd SHARED iterateFD)
add_library(prparser SHARED parserPrTree)
add_library(mgldraw SHARED mglDrawData)
add_library(chem SHARED chem_t)
add_library(voxel SHARED voxel_t)
add_library(node SHARED node_t)
add_library(mesh SHARED mesh_t)

target_link_libraries(voxel chem)

target_link_libraries(mesh mgldraw)
target_link_libraries(mesh prparser)
target_link_libraries(mesh iteratefd)
