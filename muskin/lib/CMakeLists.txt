ADD_DEFINITIONS( -fopenmp --std=c++11)
#ADD_DEFINITIONS(--std=c++11)

add_library(node SHARED node_t)
add_library(mesh SHARED mesh_t)
add_library(mgldraw SHARED mglDrawData)
add_library(prparser SHARED parserPrTree)

target_link_libraries(mesh mgldraw)
target_link_libraries(mesh prparser)
