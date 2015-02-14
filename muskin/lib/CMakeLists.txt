ADD_DEFINITIONS( -fopenmp --std=c++11)
#ADD_DEFINITIONS(--std=c++11)

add_library(node SHARED node)
add_library(mesh SHARED mesh)
add_library(mgldraw SHARED mglDrawData)
add_library(prparser SHARED parserPrTree)
add_library(ptreexml SHARED pTreeXML)
#add_library(ptreejson SHARED pTreeJSON)

target_link_libraries(mesh mgldraw)
target_link_libraries(mesh prparser)
target_link_libraries(mesh ptreexml)
#target_link_libraries(mesh ptreejson)
