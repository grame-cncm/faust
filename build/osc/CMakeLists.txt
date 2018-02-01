# CMAKE oscpack
project(OSCFaust)
cmake_minimum_required(VERSION 3.4.0)

#######################################
# versions management
set (VERSION 1.0.0)
set (SOVERS 1)

#######################################
# SET MAIN DIRECTORY.
set (OSC ${ROOT}/architecture/osclib)
set (CMAKE_BUILD_TYPE Release)

#######################################
# collect source files
FILE(GLOB SRC ${ROOT}/oscpack/osc/*.cpp  
	${OSC}/faust/src/lib/*.cpp 
	${OSC}/faust/src/msg/*.cpp 
	${OSC}/faust/src/nodes/*.cpp 
	${OSC}/faust/src/osc/*.cpp)

add_library( oscstatic STATIC ${SRC} )
set (TARGETS oscstatic)
if (NOT IOS)
	add_library( oscdynamic SHARED ${SRC} )
	set_target_properties(oscdynamic PROPERTIES 
		VERSION ${VERSION}
		SOVERSION ${SOVERS})
	set (TARGETS ${TARGETS} oscdynamic)
endif()

set_target_properties(${TARGETS} PROPERTIES  INCLUDE_DIRECTORIES
	${OSC}/oscpack 
	${OSC}/faust 
	${OSC}/faust/src 
	${OSC}/faust/src/lib 
	${OSC}/faust/src/osc  
	${OSC}/faust/src/threads  
	${OSC}/..)
	
file (GLOB HEADERS ${OSC}/faust/faust/osc/*.h)

if (WIN32)
	file (GLOB PLATFORM_SRC	${OSC}/oscpack/ip/win32/*.cpp ${OSC}/faust/src/threads/winthreads_impl.cpp)
	target_link_libraries( ${TARGETS} ws2_32 winmm)
else()
	file (GLOB PLATFORM_SRC	${OSC}/oscpack/ip/posix/*.cpp ${OSC}/faust/src/threads/pthreads_impl.cpp)
endif()
set_target_properties(${TARGETS} PROPERTIES 
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBDIR}
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBDIR}
	SOURCES ${PLATFORM_SRC}
	)
# public headers are similar for both static and dynamic libs but only attached to the static one
set_target_properties(oscstatic PROPERTIES PUBLIC_HEADER "${HEADERS}")
	

if (IOS)
	set_target_properties(oscstatic PROPERTIES OUTPUT_NAME OSCFaust.ios)
	# on iOS, assume little_endian
	target_compile_definitions (oscstatic PRIVATE -DOSC_HOST_LITTLE_ENDIAN=1)

else()
	if (WIN32) 
		set_target_properties(oscstatic  PROPERTIES OUTPUT_NAME libOSCFaust)
		set_target_properties(oscdynamic PROPERTIES OUTPUT_NAME OSCFaust)
	else()
		set_target_properties(oscstatic  PROPERTIES OUTPUT_NAME OSCFaust)
		set_target_properties(oscdynamic PROPERTIES OUTPUT_NAME OSCFaust)
	endif()

	#######################################
	# check for endianness
	include (TestBigEndian)
	TEST_BIG_ENDIAN(IS_BIG_ENDIAN)
	if(IS_BIG_ENDIAN)
		set_target_properties(${TARGETS} PROPERTIES COMPILE_DEFINTIONS  -DOSC_HOST_BIG_ENDIAN=1)
	else()
		set_target_properties(${TARGETS} PROPERTIES COMPILE_DEFINTIONS  -DOSC_HOST_LITTLE_ENDIAN=1)
	endif()
endif()	


####################################
# install section
####################################
install ( TARGETS ${TARGETS}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib 
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/faust/osc
)
