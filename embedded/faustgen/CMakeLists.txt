cmake_minimum_required(VERSION 3.4.0)
project (faustgen)

set(ROOT ${CMAKE_CURRENT_SOURCE_DIR})

option ( USE_LLVM_CONFIG 	"Use llvm-config"	off )

#######################################
set (CMAKE_CXX_STANDARD 11)

#######################################
# Max part
if (NOT DEFINED MAXSDK)
	message (FATAL_ERROR "MAXSDK path undefined ! Call cmake with -DMAXSDK=path/toMax/sdk")
else()
	message (STATUS "Using MAXSDK from ${MAXSDK}")
endif()
set (MAXINCL ${MAXSDK}/max-includes  ${MAXSDK}/msp-includes)
if (APPLE)
	set (MAXLIBS "-F${MAXSDK}/max-includes -framework MaxAPI  -F${MAXSDK}/msp-includes -framework MaxAudioAPI")
elseif (WIN32)
	set (MAXLIBS ${MAXSDK}/max-includes/x64/MaxAPI.lib  ${MAXSDK}/msp-includes/x64/MaxAudio.lib)
endif()

#######################################
# Faust part
execute_process (COMMAND faust --includedir OUTPUT_VARIABLE FINC)
string ( STRIP ${FINC} FAUSTINC )
execute_process (COMMAND faust --libdir OUTPUT_VARIABLE FLIB)
string ( STRIP ${FLIB} FAUSTLIB )

#######################################
# libsndfile
if (WIN32)
	if (NOT DEFINED LIBSNDFILE)
		set (LIBSNDFILE "C:/Program Files/Mega-Nerd/libsndfile")
    set (SNDFILELIB ${LIBSNDFILE}/lib/libsndfile-1.lib)
	set (SNDFILEINC ${LIBSNDFILE}/include)
else()
	set (SNDFILEINC ${ROOT}/MacOS/sndfile) 
	file (GLOB SNDFILELIB MacOS/sndfile/*.a)
endif()

#######################################
# faust libraries
if (APPLE)
	file (GLOB DSPLIBS ${ROOT}/../../libraries/*.lib)
endif()

####################################
# LLVM
include (../../build/misc/llvm.cmake)
if(USE_LLVM_CONFIG)
	llvm_config()
else()
	llvm_cmake()
endif()

####################################
# compiler dependent settings
if (WIN32)
	set (FAUSTLIBS ${FAUSTLIB}/libfaust.lib ${FAUSTLIB}/libOSCFaust.lib)
	set (WINSRC ${MAXSDK}/max-includes/common/dllmain_win.c ${MAXSDK}/max-includes/common/commonsyms.c)
else()
	set (MACLIBS "-framework CoreServices -framework IOKit")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
	set (FAUSTLIBS ${FAUSTLIB}/libfaust.a ${FAUSTLIB}/libOSCFaust.a)
endif()

####################################
# Add the faustgen target
####################################
add_library(faustgen MODULE ${ROOT}/src/faustgen~.cpp ${WINSRC} ${DSPLIBS})
target_include_directories (faustgen PRIVATE ${ROOT}/src/ ${MAXINCL} ${FAUSTINC} ${SNDFILEINC})
target_link_libraries (faustgen ${FAUSTLIBS}  ${MAXLIBS} ${LLVM_LIBS} ${SNDFILELIB} )

if (APPLE)
set_target_properties (faustgen PROPERTIES 
	LINK_FLAGS "${MACLIBS} -Wl,-U,_object_new_imp -Wl,-U,_object_method_imp"
	BUNDLE TRUE
	BUNDLE_EXTENSION mxo
	MACOSX_BUNDLE_INFO_PLIST ${ROOT}/Info.plist
	RESOURCE "${DSPLIBS}"
	OUTPUT_NAME faustgen~)

elseif (WIN32)
set_target_properties (faustgen PROPERTIES 
	COMPILE_FLAGS "-DWIN_VERSION -DWIN_EXT_VERSION"
	LINK_FLAGS "winmm.lib ws2_32.lib"
	SUFFIX ".mxe64"
	OUTPUT_NAME faustgen~)
endif()
