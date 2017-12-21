# CMAKE oscpack
project(OSCFaust)
cmake_minimum_required(VERSION 3.4.0)

set (TARGET OSCFaust)

#######################################
# SET MAIN DIRECTORY.
#set (ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set (OSC ${ROOT}/architecture/osclib)
set (CMAKE_BUILD_TYPE Release)

#######################################
# collect source files
FILE(GLOB SRC ${ROOT}/oscpack/osc/*.cpp  
	${OSC}/faust/src/lib/*.cpp 
	${OSC}/faust/src/msg/*.cpp 
	${OSC}/faust/src/nodes/*.cpp 
	${OSC}/faust/src/osc/*.cpp)

add_library( ${TARGET} STATIC ${SRC} )

target_include_directories (${TARGET} PRIVATE 
	${OSC}/oscpack 
	${OSC}/faust 
	${OSC}/faust/src 
	${OSC}/faust/src/lib 
	${OSC}/faust/src/osc  
	${OSC}/faust/src/threads  
	${OSC}/..)

if (WIN32)
	file (GLOB PLATFORM_SRC	${OSC}/oscpack/ip/win32/*.cpp ${OSC}/faust/src/threads/winthreads_impl.cpp)
	target_link_libraries( ${TARGET} ws2_32 winmm)
else()
	file (GLOB PLATFORM_SRC	${OSC}/oscpack/ip/posix/*.cpp ${OSC}/faust/src/threads/pthreads_impl.cpp)
endif()
target_sources (${TARGET} PRIVATE ${PLATFORM_SRC})
target_compile_definitions (${TARGET} PRIVATE -DOSC_HOST_BIG_ENDIAN=1)
set_target_properties(${TARGET} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBDIR})

if (IOS)
	set_target_properties(${TARGET} PROPERTIES OUTPUT_NAME OSCFaust.ios)
	# on iOS, assume little_endian
	target_compile_definitions (${TARGET} PRIVATE -DOSC_HOST_LITTLE_ENDIAN=1)

else()

	#######################################
	# check for endianness
	include (TestBigEndian)
	TEST_BIG_ENDIAN(IS_BIG_ENDIAN)
	if(IS_BIG_ENDIAN)
		target_compile_definitions (${TARGET} PRIVATE -DOSC_HOST_BIG_ENDIAN=1)
	else()
		target_compile_definitions (${TARGET} PRIVATE -DOSC_HOST_LITTLE_ENDIAN=1)
	endif()
endif()	

