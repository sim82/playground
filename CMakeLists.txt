SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -std=c++0x")

add_executable( heap heap.cpp )

add_executable( bind bind.cpp )
add_executable( named_pipe named_pipe.cpp )

add_executable( opencl opencl.cpp )

target_link_libraries( named_pipe pthread )
target_link_libraries( opencl OpenCL )