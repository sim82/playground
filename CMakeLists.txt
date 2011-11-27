SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -std=c++0x")

#add_executable( map map_test.cpp )

add_executable( heap heap.cpp )

add_executable( synth synth.cpp )
add_executable( watch_tune watch_tune.cpp )
add_executable( reverse_bits reverse_bits.cpp )



add_executable( pool pool.cpp )
add_executable( pool2 pool2.cpp )
add_executable( bind bind.cpp )
#add_executable( named_pipe named_pipe.cpp )

#add_executable( opencl opencl.cpp )
add_executable( red_code red_code.cpp )
add_executable( c_compiler c_compiler.cpp )
add_executable( bit_fiddle bit_fiddle.cpp )

target_link_libraries(synth jack)
target_link_libraries(watch_tune jack)

#target_link_libraries( named_pipe pthread )
#target_link_libraries( opencl OpenCL )
target_link_libraries(pool pthread)
add_executable( compact_vector compact_vector.cpp )

target_link_libraries(pool2 pthread)
