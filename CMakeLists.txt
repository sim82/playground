# build with clang:
# CC=clang CXX=clang++ cmake .. -DCMAKE_USER_MAKE_RULES_OVERRIDE=~/src/playground/ClangOverrides.txt -DCMAKE_BUILD_TYPE=Release
# cmake  -DCMAKE_C_COMPILER=/usr/lib/clang-analyzer/scan-build/ccc-analyzer -DCMAKE_CXX_COMPILER=/usr/lib/clang-analyzer/scan-build/c++-analyzer ..
# scan-build -o static_analysis_results make


cmake_minimum_required(VERSION 2.8)
#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wno-mismatched-tags  -std=c++0x")
#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall  -std=c++1y -fsanitize=address")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall  -std=c++14")

LINK_DIRECTORIES( /usr/lib/llvm )

#include_directories( axe/include )
include_directories( /space/src/boost_1_52_0 )
#add_executable( test test.cpp )
# add_executable( game game.cpp )
link_directories( /space/src/boost_1_52_0/stage/lib )
# add_executable( object_hog object_hog.cpp )
# target_link_libraries( object_hog ivymike )

#add_executable( future future.cpp )
#add_executable( map map_test.cpp )
add_executable( const_hash const_hash.cpp )
add_executable( atomic atomic.cpp )
add_executable( heap heap.cpp )
add_executable( bitset bitset.cpp )
#add_executable( synth synth.cpp )
#add_executable( watch_tune watch_tune.cpp )
add_executable( reverse_bits reverse_bits.cpp )
#add_executable( axe_parser axe_parser.cpp )
add_executable( scope_rollback scope_rollback.cpp )
add_executable( phone_code phone_code.cpp )

add_executable( pool pool.cpp )
add_executable( pool2 pool2.cpp )
add_executable( bind bind.cpp )
#add_executable( named_pipe named_pipe.cpp )
add_executable( entity entity.cpp entity_main.cpp entity_member3.cpp entity_custom.cpp )
add_executable( entity_nonshared entity_nonshared.cpp )
#add_executable( opencl opencl.cpp )
add_executable( red_code red_code.cpp )
add_executable( c_compiler c_compiler.cpp )
#add_executable( bit_fiddle bit_fiddle.cpp )
#add_executable( rand rand.cpp )

add_executable( framebuffer framebuffer.cpp )
add_executable( emator emator.cpp )
#add_executable( rel_ptr rel_ptr.cpp )
add_executable( buddy buddy.cpp )
add_executable( lz77 lz77.cpp )
#add_executable( inplace_queue inplace_queue.cpp )
#add_executable( inplace_queue_atomic inplace_queue_atomic.cpp )
# add_executable( inplace_queue_locked inplace_queue_locked.cpp )

#target_link_libraries( inplace_queue_atomic pthread )
#target_link_libraries( inplace_queue_locked pthread )

add_executable( message_passing message_passing.cpp message_passing_main.cpp)
target_link_libraries( message_passing  pthread )

add_executable(implant implant.cpp)
add_executable(malloc_bench malloc_bench.cpp)
# add_executable( llvm_plf llvm_plf.cpp )

# add_executable( game1 game1.cpp entity.cpp game1_entity.cpp )
#add_executable( llvm_plf llvm_plf.cpp )


#target_link_libraries(future pthread)

add_executable( boost_math boost_math.cpp )
#target_link_libraries(watch_tune jack)
add_executable( fixed fixed.cpp )
#target_link_libraries(synth jack)

add_executable( id_map id_map.cpp )
#add_executable( boost_async boost_async.cpp )
add_executable( disk_hash disk_hash.cpp )
add_executable( taggard taggard.cpp )
add_executable( binary_heap binary_heap.cpp )

# add_executable( game1 game1.cpp )
#target_link_libraries( named_pipe pthread )
#target_link_libraries( opencl OpenCL )
target_link_libraries(pool pthread)
add_executable( compact_vector compact_vector.cpp )

target_link_libraries(pool2 pthread)
target_link_libraries(framebuffer X11 )

#add_executable(boost_spirit boost_spirit.cpp)

add_executable( actor actor.cpp )
#add_executable( persistency persistency.cpp )
add_executable( message_passing_2 message_passing_2.cpp mp2.cpp )
target_link_libraries(message_passing_2 pthread)


add_executable( openhash openhash.cpp )
add_executable( nested_coroutine nested_coroutine.cpp )

add_executable( fsa fsa.cpp )

add_executable( message_passing_3 message_passing_3.cpp mp3.cpp )

add_executable( ml_bitmap ml_bitmap.cpp )

add_executable( spirit spirit.cpp)
# target_link_libraries(game1 X11)

# target_link_libraries( llvm_plf pthread ffi dl m LLVM-3.1)

# target_link_libraries( boost_async boost_thread boost_system )
# target_link_libraries( llvm_plf pthread ffi dl m LLVMInterpreter LLVMX86Disassembler LLVMX86AsmParser LLVMX86CodeGen LLVMSelectionDAG LLVMAsmPrinter LLVMMCParser LLVMX86Desc LLVMX86Info LLVMX86AsmPrinter LLVMX86Utils LLVMJIT LLVMRuntimeDyld LLVMExecutionEngine LLVMCodeGen LLVMScalarOpts LLVMInstCombine LLVMTransformUtils LLVMipa LLVMAnalysis LLVMTarget LLVMMC LLVMObject LLVMCore LLVMSupport)
