SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -std=c++0x")

add_executable( heap heap.cpp )

add_executable( synth synth.cpp )

add_executable( pool pool.cpp )
add_executable( pool2 pool2.cpp )
add_executable( bind bind.cpp )
add_executable( named_pipe named_pipe.cpp )

add_executable( opencl opencl.cpp )
add_executable( red_code red_code.cpp )
add_executable( c_compiler c_compiler.cpp )

target_link_libraries(synth jack)

target_link_libraries( named_pipe pthread )
target_link_libraries( opencl OpenCL )
target_link_libraries(pool pthread)

target_link_libraries(pool2 pthread)