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
option ( LIBMICROHTTPD_CFLAGS 	"Manual C flags for libmicrohttpd"	off )
option ( LIBMICROHTTPD_LDFLAGS 	"Manual link flags for libmicrohttpd"	off )


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
# manual libmicrohttpd settings
macro (set_pkg_config_path)
	set (PP $ENV{PKG_CONFIG_PATH})
	foreach(A ${PP})
		string (REPLACE "\\" "/" A1 ${A} )
		string (REGEX REPLACE "C:/msys[^/]*" "" A2 ${A1} )
		set (LP "${LP}:${A2}")
	endforeach()
	set (ENV{PKG_CONFIG_PATH} ${LP} )
endmacro()

#######################################
# libmicrohttpd settings
if (LIBMICROHTTPD_CFLAGS AND LIBMICROHTTPD_LDFLAGS)
	message(STATUS "Using manual cflags '${LIBMICROHTTPD_CFLAGS}' and ldflags '${LIBMICROHTTPD_LDFLAGS}' for libmicrohttpd")
else()
if (WIN32 AND MSVC)
	if("${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
		set (LMHDIR ${ROOT}/windows/libmicrohttpd/x64)
		set (LMHLIB ${LMHDIR}/libmicrohttpd.lib)
	else () 
		set (LMHDIR ${ROOT}/windows/libmicrohttpd)
		set (LMHLIB ${ROOT}/windows/libmicrohttpd/libmicrohttpd.lib)
	endif()
	set (INCLUDE ${INCLUDE} ${LMHDIR})
else ()
	find_package(PkgConfig REQUIRED)
	if (${PKG_CONFIG_FOUND}) 
		if ( WIN32 OR MSYS )
			set_pkg_config_path ()
			message(STATUS "Using MSYS PKG_CONFIG_PATH $ENV{PKG_CONFIG_PATH}")
		endif()
		pkg_search_module(LMHD libmicrohttpd)
		if (${LMHD_FOUND})
			foreach (A ${LMHD_CFLAGS})
				set(LIBMICROHTTPD__CFLAGS "${LIBMICROHTTPD__CFLAGS} ${A}")
			endforeach()
			foreach (A ${LMHD_LDFLAGS})
				set(LIBMICROHTTPD__LDFLAGS "${LIBMICROHTTPD__LDFLAGS} ${A}")
			endforeach()
			message (STATUS "Found libmicrohttpd ${LMHD_VERSION}")
		else ()
			message (WARNING "Cannot locate libmicrohttpd: skip ${TARGET} generation")
			return ()
		endif()
	else()
		message (WARNING "No pkg-config, cannot locate libmicrohttpd: skip ${TARGET} generation")
		return ()
	endif()
endif()
endif()

if ( WIN32 OR MSYS )
	if (MSVC)
		set (LIBMICROHTTPD__LDFLAGS "${LIBMICROHTTPD__LDFLAGS} ws2_32" )
	else()
		set (LIBMICROHTTPD__LDFLAGS "-lws2_32 ${LIBMICROHTTPD__LDFLAGS}" )
	endif()
endif()


#######################################
# add libraries
if (INCLUDE_HTTP)
	add_library( httpstatic STATIC  ${SRC})
	target_include_directories (httpstatic PRIVATE ${INCLUDE} )
	set (TARGETS httpstatic)
	if (WIN32 AND MSVC) 
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
			COMPILE_FLAGS  "${LIBMICROHTTPD__CFLAGS}"
			LINK_FLAGS     "${LIBMICROHTTPD__LDFLAGS}")
	endif()
endif()

if (HTTPDYNAMIC)
	add_library( httpdynamic SHARED  ${SRC})
	target_include_directories (httpdynamic PRIVATE ${INCLUDE} )
	set_target_properties(httpdynamic PROPERTIES OUTPUT_NAME ${TARGET})
	set_target_properties(httpdynamic PROPERTIES 
		VERSION ${VERSION}
		SOVERSION ${SOVERS})
	set (TARGETS ${TARGETS} httpdynamic)
	if (WIN32 AND MSVC) 
		target_compile_definitions (httpdynamic PRIVATE -D_WIN32 -DMHD_W32LIB)
		target_link_libraries(httpdynamic ws2_32 ${LMHLIB})
	elseif(MSYS)
		target_link_libraries (httpdynamic ${LIBMICROHTTPD__LDFLAGS})
	else()
		target_link_libraries (httpdynamic microhttpd)
		set_target_properties (httpdynamic PROPERTIES 
			COMPILE_FLAGS  "${LIBMICROHTTPD__CFLAGS}"
			LINK_FLAGS     "${LIBMICROHTTPD__LDFLAGS}")
	endif()

endif()

file (GLOB HEADERS ${SRCDIR}/include/*.h)
set_target_properties(${TARGETS} PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBDIR}
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBDIR}
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBDIR})

# public headers are similar for both static and dynamic libs but only attached to the static one
if (INCLUDE_HTTP)
	set_target_properties(httpstatic PROPERTIES PUBLIC_HEADER "${HEADERS}")
else()
	set_target_properties(httpdynamic PROPERTIES PUBLIC_HEADER "${HEADERS}")
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
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/faust/gui
)

