SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -std=c++0x")
LINK_DIRECTORIES( /usr/lib/llvm )

# add_executable( object_hog object_hog.cpp )
# target_link_libraries( object_hog ivymike )

add_executable( future future.cpp )
#add_executable( map map_test.cpp )
add_executable( atomic atomic.cpp )
add_executable( heap heap.cpp )
add_executable( bitset bitset.cpp )
#add_executable( synth synth.cpp )
add_executable( watch_tune watch_tune.cpp )
add_executable( reverse_bits reverse_bits.cpp )



add_executable( pool pool.cpp )
add_executable( pool2 pool2.cpp )
add_executable( bind bind.cpp )
#add_executable( named_pipe named_pipe.cpp )
add_executable( entity entity.cpp )
add_executable( entity_nonshared entity_nonshared.cpp )
#add_executable( opencl opencl.cpp )
add_executable( red_code red_code.cpp )
add_executable( c_compiler c_compiler.cpp )
add_executable( bit_fiddle bit_fiddle.cpp )
add_executable( rand rand.cpp )

add_executable( framebuffer framebuffer.cpp )
add_executable( emator emator.cpp )
add_executable( llvm_plf llvm_plf.cpp )


target_link_libraries(future pthread)

add_executable( boost_math boost_math.cpp )
target_link_libraries(watch_tune jack)
add_executable( fixed fixed.cpp )
#target_link_libraries(synth jack)

#target_link_libraries( named_pipe pthread )
#target_link_libraries( opencl OpenCL )
target_link_libraries(pool pthread)
add_executable( compact_vector compact_vector.cpp )

target_link_libraries(pool2 pthread)
target_link_libraries(framebuffer X11 )


target_link_libraries( llvm_plf pthread ffi dl m LLVMInterpreter LLVMX86Disassembler LLVMX86AsmParser LLVMX86CodeGen LLVMSelectionDAG LLVMAsmPrinter LLVMMCParser LLVMX86Desc LLVMX86Info LLVMX86AsmPrinter LLVMX86Utils LLVMJIT LLVMRuntimeDyld LLVMExecutionEngine LLVMCodeGen LLVMScalarOpts LLVMInstCombine LLVMTransformUtils LLVMipa LLVMAnalysis LLVMTarget LLVMMC LLVMObject LLVMCore LLVMSupport)
