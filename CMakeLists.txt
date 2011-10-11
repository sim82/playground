SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -std=c++0x")

add_executable( heap heap.cpp )

add_executable( synth synth.cpp )

target_link_libraries(synth jack)
