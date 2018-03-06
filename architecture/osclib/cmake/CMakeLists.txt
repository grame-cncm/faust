# CMAKE oscpack
project(OSCFaust)
cmake_minimum_required(VERSION 3.4.0)

set (TARGET OSCFaust)

#######################################
# SET MAIN DIRECTORY.
set (ROOT ${CMAKE_CURRENT_SOURCE_DIR}/..)
set (CMAKE_BUILD_TYPE Release)

#######################################
# collect source files
FILE(GLOB SRC ${ROOT}/oscpack/osc/*.cpp  
	${ROOT}/faust/src/lib/*.cpp 
	${ROOT}/faust/src/msg/*.cpp 
	${ROOT}/faust/src/nodes/*.cpp 
	${ROOT}/faust/src/osc/*.cpp)

add_library( ${TARGET} STATIC ${SRC} )

target_include_directories (${TARGET} PRIVATE 
	${ROOT}/oscpack 
	${ROOT}/faust 
	${ROOT}/faust/src 
	${ROOT}/faust/src/lib 
	${ROOT}/faust/src/osc  
	${ROOT}/faust/src/threads  
	${ROOT}/..)

if (WIN32)
	file (GLOB PLATFORM_SRC	${ROOT}/oscpack/ip/win32/*.cpp ${ROOT}/faust/src/threads/winthreads_impl.cpp)
	target_link_libraries( ${TARGET} ws2_32 winmm)
else()
	file (GLOB PLATFORM_SRC	${ROOT}/oscpack/ip/posix/*.cpp ${ROOT}/faust/src/threads/pthreads_impl.cpp)
endif()
target_sources (${TARGET} PRIVATE ${PLATFORM_SRC})
target_compile_definitions (${TARGET} PRIVATE -DOSC_HOST_BIG_ENDIAN=1)
set_target_properties(${TARGET} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${ROOT})


#######################################
# check for endianness
include (TestBigEndian)
TEST_BIG_ENDIAN(IS_BIG_ENDIAN)
if(IS_BIG_ENDIAN)
	target_compile_definitions (${TARGET} PRIVATE -DOSC_HOST_BIG_ENDIAN=1)
else()
	target_compile_definitions (${TARGET} PRIVATE -DOSC_HOST_LITTLE_ENDIAN=1)
endif()

#if(APPLE)
########################################
##   iOS support
#	if ( IOS )
#		set (CMAKE_XCODE_EFFECTIVE_PLATFORMS "iPhoneOS")
#		set (CMAKE_OSX_ARCHITECTURES "armv6 armv7 i386")
#		set (CMAKE_OSX_SYSROOT "iphoneos")
#		set (libtype STATIC)
#	else ()
#		set (CMAKE_OSX_ARCHITECTURES "x86_64 i386")
#	endif ()
#endif(APPLE)
