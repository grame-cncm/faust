cmake_minimum_required(VERSION 3.4.0)
project (llvm-test)


option ( USE_LLVM_CONFIG 	"Use llvm-config"	off )
set(LIBFAUST_DIR "" CACHE PATH "Path containing libfaust")
set(INCLUDE_DIR "" CACHE PATH "Path containing source headers")

if ("${LIBFAUST_DIR}" STREQUAL "")
	execute_process(COMMAND faust --libdir OUTPUT_VARIABLE LIBDIR)
	string (STRIP ${LIBDIR} LIBFAUST_DIR)
#    set(LIBFAUST_DIR "../../../build/lib" CACHE PATH "Path containing libfaust" FORCE)
endif()
if ("${INCLUDE_DIR}" STREQUAL "")
	execute_process(COMMAND faust --includedir OUTPUT_VARIABLE INCDIR)
	string (STRIP ${INCDIR} INCLUDE_DIR)
#    set(INCLUDE_DIR "../../architecture" CACHE PATH "Path containing headers for libfaust" FORCE)
endif()

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
	set( LIBS ${LIBFAUST_DIR}/libfaust ws2_32 ${LLVM_LD_FLAGS} ${LLVM_LIBS})
else()
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    if (ANDROID)
        set( LIBS -L${LIBFAUST_DIR} -lfaust ${LLVM_LD_FLAGS} ${LLVM_LIBS})
    else()
        set( LIBS -L${LIBFAUST_DIR} -lfaust -lpthread ${LLVM_LD_FLAGS} ${LLVM_LIBS})
    endif()
endif()

####################################
# Add the llvm-test target
####################################
add_executable(llvm-test llvm-test.cpp)
target_include_directories (llvm-test PRIVATE ${INCLUDE_DIR})
target_link_libraries (llvm-test ${LIBS})

add_executable(llvm-algebra-test llvm-algebra-test.cpp)
target_include_directories (llvm-algebra-test PRIVATE ${INCLUDE_DIR})
target_link_libraries (llvm-algebra-test ${LIBS})

add_executable(llvm-test-c llvm-test.c)
target_include_directories (llvm-test-c PRIVATE ${INCLUDE_DIR})
target_link_libraries (llvm-test-c ${LIBS})
