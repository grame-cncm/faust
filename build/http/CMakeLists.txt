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
set (CMAKE_BUILD_TYPE Release)

#######################################
# collect source files
FILE(GLOB SRC 
	${SRCDIR}/hexa/*.cpp 
	${SRCDIR}/html/*.cpp 
	${SRCDIR}/httpd/*.cpp 
	${SRCDIR}/json/*.cpp 
	${SRCDIR}/lib/*.cpp
	${SRCDIR}/msg/*.cpp
	${SRCDIR}/nodes/*.cpp)

set( INCLUDE 
	${SRCDIR}/hexa 
	${SRCDIR}/html 
	${SRCDIR}/httpd 
	${SRCDIR}/include 
	${SRCDIR}/json 
	${SRCDIR}/lib 
	${SRCDIR}/msg 
	${SRCDIR}/nodes)

#######################################
# libmicrohttpd settings
if (WIN32)
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
add_library( httpdynamic SHARED  ${SRC})
target_include_directories (httpdynamic PRIVATE ${INCLUDE} )
set_target_properties(httpdynamic PROPERTIES 
		VERSION ${VERSION}
		SOVERSION ${SOVERS})
set (TARGETS httpstatic httpdynamic)

file (GLOB HEADERS ${SRCDIR}/msg/include/*.h)
set_target_properties(${TARGETS} PROPERTIES 
	COMPILE_FLAGS  "${LMHD_CFLAGS}"
	LINK_FLAGS     "-L${LMHD_LIBRARY_DIRS} -l${LMHD_LIBRARIES}"
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBDIR}
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBDIR}
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBDIR})

if (WIN32) 
	set_target_properties(httpstatic  PROPERTIES OUTPUT_NAME lib${TARGET})
	set_target_properties(httpdynamic PROPERTIES OUTPUT_NAME ${TARGET})
	target_link_libraries(httpstatic  ws2_32)
	target_link_libraries(httpdynamic ws2_32)
else()
	set_target_properties(httpstatic  PROPERTIES OUTPUT_NAME ${TARGET})
	set_target_properties(httpdynamic PROPERTIES OUTPUT_NAME ${TARGET})
endif()
target_link_libraries(httpstatic   microhttpd)
target_link_libraries(httpdynamic  microhttpd)


####################################
# install section
####################################
install ( TARGETS ${TARGETS}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib 
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/faust/http
)

