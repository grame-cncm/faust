cmake_minimum_required(VERSION 2.6)
project(OSCFaust)

#######################################
# cmake build types configuration
set (CMAKE_CONFIGURATION_TYPES Debug Release)

set (TARGET	OSCFaust)
#######################################
# versions management
set (version 0.50)

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
	else (${CMAKE_SYSTEM_VERSION} VERSION_LESS 9.0.0)
		set (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.5.sdk)
	endif (${CMAKE_SYSTEM_VERSION} VERSION_LESS 9.0.0)

	set (CMAKE_OSX_ARCHITECTURES "i386 x86_64")
	set (CMAKE_C++_FLAGS -mmacosx-version-min=10.4)
endif(APPLE AND (${CMAKE_GENERATOR} STREQUAL Xcode) )

#######################################
# set directories, src and headers.
set (ROOT 			${CMAKE_CURRENT_SOURCE_DIR}/../src)
set (LIBDIR 		${CMAKE_CURRENT_SOURCE_DIR}/../..)
set (SRCFOLDERS 	lib ../include msg osc nodes)
set (OSC_PATH  		"${ROOT}/../../oscpack")

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
set(INCL ${INCL} "${ROOT}/threads")					# add other include folders

#######################################
# set libraries
if(WIN32)
	set(OSCPACK  ${ROOT}/../../oscpack.lib)
else(WIN32)
	set(OSCPACK  ${ROOT}/../../liboscpack.a)
endif(WIN32)

#######################################
# set targets
include_directories (${INCL} ${OSC_PATH} )

add_library ( ${TARGET} STATIC ${SRCFILES} ${HEADERFILES} ${OSCPACK} )
set_source_files_properties (${HEADERFILES} PROPERTIES HEADER_FILE_ONLY TRUE)
set_target_properties (${TARGET} PROPERTIES 
	VERSION ${version} 
	ARCHIVE_OUTPUT_DIRECTORY "${ROOT}/../.."
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${ROOT}/../.."
)

if(WIN32)
  target_link_libraries ( ${TARGET} ws2_32.lib )
endif(WIN32)

if (WIN32)
 set (OUTLIB "${TARGET}.lib")
else (WIN32)
 set (OUTLIB "lib${TARGET}.a")
endif (WIN32)


