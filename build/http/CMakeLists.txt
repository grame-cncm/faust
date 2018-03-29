# CMAKE httpd library
cmake_minimum_required(VERSION 3.4.0)
project(HTTPDFaust)
set (TARGET	HTTPDFaust)

# exclude IOS from build
if (IOS)
	message (WARNING "iOS is not supported by the ${TARGET} library")
	return ()
endif()

#######################################
# options
option ( HTTPDYNAMIC 	"Compiles also the libray as dynamic library"	off )

#######################################
# check for variables that are normally set at upper level
if (NOT DEFINED LIBDIR)
	set (LIBDIR lib)
endif()
if (NOT DEFINED ROOT)
	set (ROOT ../..)
endif()

#######################################
# versions management
set (VERSION 0.7.1)
set (SOVERS 0)

#######################################
# SET MAIN DIRECTORY.
set (HTTP ${ROOT}/architecture/httpdlib)
set (SRCDIR ${HTTP}/src)
set (ARCHDIR ${ROOT}/architecture)
set (CMAKE_BUILD_TYPE Release)

#######################################
# collect source files
FILE(GLOB SRC 
	${SRCDIR}/*.cpp 
	${SRCDIR}/hexa/*.cpp 
	${SRCDIR}/html/*.cpp 
	${SRCDIR}/httpd/*.cpp 
	${SRCDIR}/json/*.cpp 
	${SRCDIR}/lib/*.cpp
	${SRCDIR}/msg/*.cpp
	${SRCDIR}/nodes/*.cpp)

set (SRC ${SRC} ${ROOT}/compiler/parser/sourcefetcher.cpp)

set( INCLUDE 
	${SRCDIR}/hexa 
	${SRCDIR}/html 
	${SRCDIR}/httpd 
	${SRCDIR}/include 
	${SRCDIR}/json 
	${SRCDIR}/lib 
	${SRCDIR}/msg 
	${SRCDIR}/nodes
	${ARCHDIR}
	${ROOT}/compiler/tlib
	)

#######################################
# libmicrohttpd settings
if (WIN32)
	if (MSVC)
		if("${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
			set (LMHDIR ${ROOT}/windows/libmicrohttpd/x64)
		else()
			set (LMHDIR ${ROOT}/windows/libmicrohttpd)
		endif()
		set (LMHLIB ${LMHDIR}/libmicrohttpd.lib)
	else ()  # assume we're using MSYS or MINGW and the arch is 64bits
		set (LMHDIR ${ROOT}/windows/libmicrohttpd/x64)
		set (LMHLIB ${ROOT}/windows/libmicrohttpd/x64/MSYS/libmicrohttpd.lib)
	endif()
	set (INCLUDE ${INCLUDE} ${LMHDIR})
else ()
	include (FindPkgConfig)
	if (${PKG_CONFIG_FOUND}) 
		pkg_check_modules(LMHD libmicrohttpd)
		if (${LMHD_FOUND})
		else ()
			message (WARNING "Cannot locate libmicrohttpd: skip ${TARGET} generation")
			return ()
		endif()
	else()
		message (WARNING "No pkg-config, cannot locate libmicrohttpd: skip ${TARGET} generation")
		return ()
	endif()
endif()

#######################################
# add libraries
add_library( httpstatic STATIC  ${SRC})
target_include_directories (httpstatic PRIVATE ${INCLUDE} )
set (TARGETS httpstatic)
if (WIN32) 
	target_compile_definitions (httpstatic PRIVATE -D_WIN32 -DMHD_W32LIB)
	if (MSVC)
		set_target_properties(httpstatic  PROPERTIES OUTPUT_NAME lib${TARGET})
	else()
		set_target_properties(httpstatic  PROPERTIES OUTPUT_NAME ${TARGET})
	endif()
	target_link_libraries(httpstatic  ws2_32 ${LMHLIB})
else()
	set_target_properties (httpstatic PROPERTIES 
		OUTPUT_NAME ${TARGET}
		COMPILE_FLAGS  "${LMHD_CFLAGS}"
		LINK_FLAGS     "-L${LMHD_LIBRARY_DIRS} -l${LMHD_LIBRARIES}")
endif()

if (HTTPDYNAMIC)
	add_library( httpdynamic SHARED  ${SRC})
	target_include_directories (httpdynamic PRIVATE ${INCLUDE} )
	set_target_properties(httpdynamic PROPERTIES 
		VERSION ${VERSION}
		SOVERSION ${SOVERS})
	set (TARGETS ${TARGETS} httpdynamic)
	if (WIN32) 
		target_compile_definitions (httpdynamic PRIVATE -D_WIN32 -DMHD_W32LIB)
		set_target_properties(httpdynamic PROPERTIES OUTPUT_NAME ${TARGET})
		target_link_libraries(httpdynamic ws2_32 ${LMHLIB})
	else()
		set_target_properties(httpdynamic PROPERTIES 
			OUTPUT_NAME ${TARGET}
			COMPILE_FLAGS  "${LMHD_CFLAGS}"
			LINK_FLAGS     "-L${LMHD_LIBRARY_DIRS} -l${LMHD_LIBRARIES}")
	endif()

endif()

file (GLOB HEADERS ${SRCDIR}/include/*.h)
set_target_properties(${TARGETS} PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBDIR}
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBDIR}
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBDIR})

# public headers are similar for both static and dynamic libs but only attached to the static one
set_target_properties(httpstatic PROPERTIES PUBLIC_HEADER "${HEADERS}")

####################################
# install section
####################################
install ( TARGETS ${TARGETS}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib 
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/faust/gui
)

