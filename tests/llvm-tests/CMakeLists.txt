cmake_minimum_required(VERSION 3.4.0)
project (llvm-test)


option ( USE_LLVM_CONFIG 	"Use llvm-config"	off )

#######################################
set (CMAKE_CXX_STANDARD 11)

####################################
# LLVM
include (../../build/misc/llvm.cmake)
if(USE_LLVM_CONFIG)
	llvm_config()
else()
	llvm_cmake()
endif()

####################################
# compiler dependent settings
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set (CMAKE_CXX_FLAGS_RELEASE "/MT"  CACHE STRING  "FORCE CXX FLAGS" FORCE)
    set (CMAKE_C_FLAGS_RELEASE "/MT"  CACHE STRING  "FORCE C FLAGS" FORCE)
    set (CMAKE_CXX_FLAGS_DEBUG "/MTd"  CACHE STRING  "FORCE CXX FLAGS" FORCE)
    set (CMAKE_C_FLAGS_DEBUG "/MTd"  CACHE STRING  "FORCE C FLAGS" FORCE)
	set( LIBS ../../../build/lib/libfaust ws2_32 ${LLVM_LD_FLAGS} ${LLVM_LIBS})
else()
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
	set( LIBS -L../../../build/lib -lfaust -lpthread ${LLVM_LD_FLAGS} ${LLVM_LIBS})
endif()

####################################
# Add the llvm-test target
####################################
add_executable(llvm-test llvm-test.cpp)
target_include_directories (llvm-test ../../architecture)
target_link_libraries (llvm-test ${LIBS})
