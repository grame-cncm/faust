# CMAKE oscpack
project(OSCFaust)
cmake_minimum_required(VERSION 3.4.0)

#######################################
# versions management
set (VERSION 1.2.2)
set (SOVERS 1)

#######################################
# options
option ( OSCDYNAMIC 	"Include Faust OSC dynamic library"	off )

#######################################
# check for variables that are normally set at upper level
if (NOT DEFINED LIBDIR)
	set (LIBDIR lib)
endif()
if (NOT DEFINED LIBSDIR)
	set (LIBSDIR lib)
endif()
if (NOT DEFINED ROOT)
	set (ROOT ../..)
endif()

#######################################
# SET MAIN DIRECTORY.
set (OSC ${ROOT}/architecture/osclib)
set (FAUSTOSC ${OSC}/faust/src)
set (FAUSTH ${OSC}/faust/faust)
set (CMAKE_BUILD_TYPE Release)

#######################################
# collect source files
FILE(GLOB SRC ${OSC}/oscpack/osc/*.cpp  ${OSC}/oscpack/ip/*.cpp  
	${FAUSTOSC}/*.cpp 
	${FAUSTOSC}/lib/*.cpp 
	${FAUSTOSC}/msg/*.cpp 
	${FAUSTOSC}/nodes/*.cpp 
	${FAUSTOSC}/osc/*.cpp)

FILE(GLOB SRCH ${OSC}/oscpack/osc/*.h  ${OSC}/oscpack/ip/*.h  
	${FAUST}/*.h 
	${FAUST}/osc/*.h 
	${FAUSTOSC}/*.h 
	${FAUSTOSC}/lib/*.h 
	${FAUSTOSC}/msg/*.h 
	${FAUSTOSC}/nodes/*.h 
	${FAUSTOSC}/osc/*.h)

set( INCLUDE
	${OSC}/oscpack 
	${OSC}/faust 
	${FAUSTOSC} 
	${FAUSTOSC}/lib 
	${FAUSTOSC}/osc  
	${FAUSTOSC}/threads  
	${OSC}/..)

if (WIN32 OR MSYS)
	file (GLOB PLATFORM_SRC	${OSC}/oscpack/ip/win32/*.cpp ${OSC}/faust/src/threads/winthreads_impl.cpp)
else()
	file (GLOB PLATFORM_SRC	${OSC}/oscpack/ip/posix/*.cpp ${OSC}/faust/src/threads/pthreads_impl.cpp)
endif()

####################################
# compiler dependent settings
if (NOT MSVC)
	set(CMAKE_CXX_FLAGS_DEBUG "-g -Wextra -Wno-unused-parameter")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wextra -Wno-unused-parameter")
endif()

#######################################
# add libraries
if (INCLUDE_OSC)
	add_library( oscstatic STATIC ${SRC} ${SRCH} ${PLATFORM_SRC})
	target_include_directories (oscstatic PRIVATE ${INCLUDE} )
	target_link_libraries(oscstatic  ws2_32 winmm)
	set (TARGETS oscstatic)
	if (MSVC)
		set_target_properties(oscstatic  PROPERTIES 
			OUTPUT_NAME libOSCFaust
			COMPILE_DEFINITIONS _CRT_SECURE_NO_WARNINGS)
	else()
		set_target_properties(oscstatic  PROPERTIES OUTPUT_NAME OSCFaust)
	endif()
endif()

if (NOT IOS AND OSCDYNAMIC)
	add_library( oscdynamic SHARED ${SRC} ${SRCH} ${PLATFORM_SRC} )
	target_include_directories (oscdynamic PRIVATE ${INCLUDE} )
	set_target_properties(oscdynamic PROPERTIES 
		VERSION ${VERSION}
		SOVERSION ${SOVERS}
		OUTPUT_NAME OSCFaust)
	if (WIN32 OR MSYS) 
		target_link_libraries(oscdynamic ws2_32 winmm)
	else()
		target_link_libraries(oscdynamic pthread)
	endif()
	set (TARGETS ${TARGETS} oscdynamic)
endif()


file (GLOB HEADERS ${OSC}/faust/faust/osc/*.h)
set_target_properties(${TARGETS} PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBDIR}
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBDIR}
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBDIR})

# public headers are similar for both static and dynamic libs but only attached to the static one
if (INCLUDE_OSC)
	set_target_properties(oscstatic PROPERTIES PUBLIC_HEADER "${HEADERS}")
else()
	set_target_properties(oscdynamic PROPERTIES PUBLIC_HEADER "${HEADERS}")
endif()	

if (IOS)
	set_target_properties(oscstatic PROPERTIES OUTPUT_NAME OSCFaust.ios)
	# on iOS, assume little_endian
	target_compile_definitions (oscstatic PRIVATE -DOSC_HOST_LITTLE_ENDIAN=1)

else()
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
if (PACK)
	set (CMAKE_INSTALL_PREFIX .)
endif()

install ( TARGETS ${TARGETS}
	RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIBSDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIBSDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIBSDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/faust/osc
)

install (
    FILES     ${FAUSTH}/OSCControler.h ${FAUSTH}/OSCIO.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/faust/gui
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

