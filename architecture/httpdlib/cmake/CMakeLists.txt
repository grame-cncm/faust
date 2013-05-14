cmake_minimum_required(VERSION 2.6)
project(HTTPDFaust)

#######################################
# cmake build types configuration
set (CMAKE_CONFIGURATION_TYPES Debug Release)

set (TARGET	HTTPDFaust)
#######################################
# versions management
set (version 0.71)

#######################################
if(WIN32)
	add_definitions(-DWINVER=0x0400 -DWIN32)
  if(MSVC)
	add_definitions(-DMSVC)
  endif(MSVC)
else(WIN32)
	add_definitions(-Wall)
endif(WIN32)

if(APPLE AND (${CMAKE_GENERATOR} STREQUAL Xcode) )
	if (${CMAKE_SYSTEM_VERSION} VERSION_LESS 9.0.0)
		set (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.4u.sdk)
	elseif (${CMAKE_SYSTEM_VERSION} VERSION_LESS 10.8.0)
		set (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.5.sdk)
	else ()
		set (CMAKE_OSX_SYSROOT "macosx10.7")
	endif (${CMAKE_SYSTEM_VERSION} VERSION_LESS 9.0.0)

	set (CMAKE_OSX_ARCHITECTURES "x86_64")
	set (CMAKE_C++_FLAGS -mmacosx-version-min=10.4)
endif(APPLE AND (${CMAKE_GENERATOR} STREQUAL Xcode) )

#######################################
# set directories, src and headers.
set (ROOT 			${CMAKE_CURRENT_SOURCE_DIR}/../src)
set (LIBDIR 		${CMAKE_CURRENT_SOURCE_DIR}/../..)
set (SRCFOLDERS 	lib include msg httpd nodes json html)

set(SRC ${SRC} "${ROOT}/*.cpp")						# add source files
foreach(folder ${SRCFOLDERS})
	set(SRC ${SRC} "${ROOT}/${folder}/*.cpp")		# add source files
endforeach(folder)
if (WIN32)
	set(SRC ${SRC} "${ROOT}/threads/win*.cpp")		# add threads src per platform
else (WIN32)
	set(SRC ${SRC} "${ROOT}/threads/pthread*.cpp")	# add threads src per platform
endif (WIN32)

file (GLOB SRCFILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${SRC})

foreach(folder ${SRCFOLDERS})
	set(HEADERS ${HEADERS} "${ROOT}/${folder}/*.h")		# add header files
endforeach(folder)
set(HEADERS ${HEADERS} "${ROOT}/threads/*.h")		# add header files
file (GLOB HEADERFILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${HEADERS})

foreach(folder ${SRCFOLDERS})
	set(INCL ${INCL} "${ROOT}/${folder}")			# add include folders
endforeach(folder)
set(INCL ${INCL} "${LIBDIR}" "${ROOT}/threads" "/usr/local/include")	# add other include folders

#######################################
# set targets
include_directories (${INCL} )

#######################################
# target lib settings
if (STATIC STREQUAL "yes")
	message (STATUS "Generates a static library - Use -DSTATIC=no to change.")
	set (lib "STATIC")
else ()
	message (STATUS "Generates a dynamic library - Use -DSTATIC=yes to change.")
	set (lib "SHARED")
endif ()

add_library ( ${TARGET} ${lib} ${SRCFILES} ${HEADERFILES} )
set_source_files_properties (${HEADERFILES} PROPERTIES HEADER_FILE_ONLY TRUE)
set_target_properties (${TARGET} PROPERTIES 
	VERSION ${version} 
	ARCHIVE_OUTPUT_DIRECTORY "${ROOT}/.."
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${ROOT}/.."
)

if(WIN32)
  target_link_libraries ( ${TARGET} ws2_32.lib microhttpd.lib)
 set (OUTLIB "${TARGET}.lib")
else()
  set_target_properties ( ${TARGET} PROPERTIES LINK_FLAGS -L/usr/local/lib )
  target_link_libraries ( ${TARGET} microhttpd )
 set (OUTLIB "lib${TARGET}.a")
endif()

