# CMAKE oscpack
project(oscpack)
cmake_minimum_required(VERSION 2.6)

if(WIN32)
	add_definitions(-DWINVER=0x0500)
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
else(WIN32)
	add_definitions(-Wall -fPIC)
endif(WIN32)

if (${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL powerpc OR
	${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL ppc)
	message(STATUS "OSC host is big endian")
	add_definitions(-DOSC_HOST_BIG_ENDIAN=1)

elseif (${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL i386 OR
		${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL x86 OR
		${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL x86_64 OR
		${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL i686)
	message(STATUS "OSC host is little endian")
	add_definitions(-DOSC_HOST_LITTLE_ENDIAN=1)

else(${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL powerpc)
	message(SEND_ERROR "${CMAKE_HOST_SYSTEM_PROCESSOR} unknown endianess")

endif (${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL powerpc OR
	${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL ppc)

if(APPLE AND (${CMAKE_GENERATOR} STREQUAL Xcode) )
	set (CMAKE_OSX_ARCHITECTURES "x86_64 i386")
endif()


# SET MAIN DIRECTORY.
set(OSCPACK ${CMAKE_CURRENT_SOURCE_DIR}/..)

set(IP_PATH ${OSCPACK}/ip)
set(IP_WIN32_PATH ${OSCPACK}/ip/win32)
set(IP_POSIX_PATH ${OSCPACK}/ip/posix)
set(SRC_PATH ${OSCPACK}/osc)
set(EX_PATH ${OSCPACK}/examples)

# SET INCLUDES
include_directories( .. )

# SET SOURCES
FILE(GLOB OSC_SRC "${SRC_PATH}/*.cpp")
FILE(GLOB IP_SRC "${IP_PATH}/*.cpp")

if (CMAKE_HOST_WIN32)
	FILE(GLOB IP_IMPL_SRC  "${IP_WIN32_PATH}/*.cpp")
else (CMAKE_HOST_WIN32)
	FILE(GLOB IP_IMPL_SRC  "${IP_POSIX_PATH}/*.cpp")
endif (CMAKE_HOST_WIN32)

ADD_LIBRARY( oscpack STATIC ${OSC_SRC} ${IP_SRC} ${IP_IMPL_SRC} )
if (CMAKE_HOST_WIN32)
	TARGET_LINK_LIBRARIES( oscpack ws2_32 winmm)
endif (CMAKE_HOST_WIN32)
set_target_properties (oscpack PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${OSCPACK}/..
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OSCPACK}/..)

if (${GENTOOLS})
  message (STATUS "Generating tools. Use -DGENTOOLS=0 to change")

#######################################
# set sample targets
 set (TOOLS 	examples/SimpleReceive examples/SimpleSend examples/OscDump
		tests/OscReceiveTest tests/OscSendTests tests/OscUnitTests )

 foreach(tool ${TOOLS})
	add_executable( ${tool}  ${OSCPACK}/${tool}.cpp )
	target_link_libraries( ${tool} oscpack)
	add_dependencies(${tool} oscpack)
 endforeach(tool)

else (${GENTOOLS})
  message (STATUS "Don't generates tools. Use -DGENTOOLS=1 to change")
endif (${GENTOOLS})
