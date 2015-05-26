cmake_minimum_required(VERSION 2.6)
project(OSCFaust)

#######################################
# cmake build types configuration
set (CMAKE_CONFIGURATION_TYPES Debug Release)

set (TARGET	OSCFaust)
#######################################
# versions management
set (version 0.95)
set (SOVERS 0)

#######################################
# Options disabled by default
option ( SHARED 	"compiles a shared library" off )

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
	set (CMAKE_OSX_ARCHITECTURES "i386 x86_64")
endif()

#######################################
# set directories, src and headers.
set (ROOT 			${CMAKE_CURRENT_SOURCE_DIR}/../src)
set (LIBDIR 		${CMAKE_CURRENT_SOURCE_DIR}/../..)
set (SRCFOLDERS 	lib .. msg osc nodes)
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
set(HEADERS ${HEADERS} "${ROOT}/../faust/*.h")		# add header files
set(HEADERS ${HEADERS} "${ROOT}/../faust/osc/*.h")		# add header files
file (GLOB HEADERFILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${HEADERS})

foreach(folder ${SRCFOLDERS})
	set(INCL ${INCL} "${ROOT}/${folder}")			# add include folders
endforeach(folder)
set(INCL ${INCL} "${ROOT}/threads")					# add other include folders
set(INCL ${INCL} "${ROOT}/../../..")				# add faust arch include folder

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

if(WIN32)
  	set ( LIBS ws2_32.lib ${ROOT}/../../oscpack.lib)
endif()
if(UNIX)
  	set ( LIBS -L${ROOT}/../.. -loscpack)
endif()

if (SHARED)
	message (STATUS "Target is a shared library - Use -DSHARED=no to change.")
	set(LIB SHARED)
else()
	message (STATUS "Target is a static library - Use -DSHARED=yes to change.")
	set(LIB STATIC)
endif()

add_library ( ${TARGET} ${LIB} ${SRCFILES}  ${OSCPACK} ${HEADERFILES} )
set_source_files_properties (${HEADERFILES} PROPERTIES HEADER_FILE_ONLY TRUE)
set_target_properties (${TARGET} PROPERTIES 
	VERSION ${version} 
	SOVERSION ${SOVERS}
	ARCHIVE_OUTPUT_DIRECTORY "${ROOT}/../.."
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${ROOT}/../.."
)
target_link_libraries ( ${TARGET} ${LIBS} )

if (WIN32)
 set (OUTLIB "${TARGET}.lib")
else (WIN32)
 set (OUTLIB "lib${TARGET}.a")
endif (WIN32)


