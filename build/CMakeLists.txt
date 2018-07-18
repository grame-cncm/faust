cmake_minimum_required(VERSION 3.4.0)
project (faust)

#######################################
# versions management
set (VERSION 2.7.0)
set (SOVERS 2)

get_filename_component(ROOT ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
set (SRCDIR ${ROOT}/compiler)
set (BINDIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set (LIBDIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set (CMAKE_CXX_STANDARD 11)


#######################################
# Output options
option ( DEPLOYMENT_TARGET 	"[MacOS]"	off )
option ( UNIVERSAL 	"Compiles and combines i386 and x86_64 architectures [MacOS]"	off )
option ( IOS     	"Compiles for iOS"	off )
option ( USE_LLVM_CONFIG    "Force use off llvm-config"	on )
option ( INCLUDE_EXECUTABLE	"Include runtime executable"	on )
option ( INCLUDE_STATIC    	"Include static library"	off )
option ( INCLUDE_DYNAMIC    "Include dynamic library"	off )
option ( INCLUDE_OSC    	"Include Faust OSC library"	on )
option ( INCLUDE_HTTP    	"Include Faust HTTPD library"	on )

if (NOT DEFINED DEPLOYMENT_TARGET_VERSION)
	set ( DEPLOYMENT_TARGET_VERSION  10.11)
endif()

#######################################
# Check output options
if (UNIVERSAL AND NOT APPLE)
	message(WARNING "UNIVERSAL option is only available on MacOS or iOS")
endif()

####################################
# source and headers files
file (GLOB SRC ${SRCDIR}/*.cpp ${SRCDIR}/*/*.cpp ${SRCDIR}/draw/*/*.cpp ${SRCDIR}/generator/fir/*.cpp)
file (GLOB HH  ${SRCDIR}/*.hh  ${SRCDIR}/*/*.hh  ${SRCDIR}/generator/fir/*.hh)

####################################
# include directories
set (FAUST_INC ${SRCDIR}
	${SRCDIR}/boxes ${SRCDIR}/documentator ${SRCDIR}/draw
	${SRCDIR}/errors ${SRCDIR}/evaluate ${SRCDIR}/extended
	${SRCDIR}/generator
	${SRCDIR}/generator/fir
	${SRCDIR}/generator/interpreter
	${SRCDIR}/normalize ${SRCDIR}/parallelize ${SRCDIR}/parser
	${SRCDIR}/patternmatcher ${SRCDIR}/propagate ${SRCDIR}/signals
	${SRCDIR}/tlib ${SRCDIR}/utils
	${SRCDIR}/draw/device ${SRCDIR}/draw/schema
	${SRCDIR}/../architecture /usr/local/include)


####################################
function(backend NAME DIR TARGET)
	message(STATUS "In target ${TARGET}: include ${NAME} backend")
	target_compile_definitions (${TARGET} PRIVATE -D${NAME}_BUILD)
	if (NOT "${DIR}" STREQUAL "")
		file (GLOB BACKEND_SRC	${SRCDIR}/generator/${DIR}/*.cpp ${SRCDIR}/generator/${DIR}/*.hh)
		target_sources (${TARGET} PRIVATE ${BACKEND_SRC})
		target_include_directories (${TARGET} PRIVATE ${SRCDIR}/generator/${DIR})
	endif()
endfunction()

####################################
function (scan_backends TARGET FLAG)
	string (FIND "${ASMJS_BACKEND}" ${FLAG} POS)
	if (${POS} GREATER -1)
		backend (ASMJS asmjs ${TARGET})
	endif()
	string (FIND "${C_BACKEND}" ${FLAG} POS)
	if (${POS} GREATER -1)
		backend (C c ${TARGET})
	endif()
	string (FIND "${CPP_BACKEND}" ${FLAG} POS)
	if (${POS} GREATER -1)
		backend (CPP cpp ${TARGET})
	endif()
	string (FIND "${FIR_BACKEND}" ${FLAG} POS)
	if (${POS} GREATER -1)
		backend (FIR "" ${TARGET})
	endif()
	string (FIND "${INTERP_BACKEND}" ${FLAG} POS)
	if (${POS} GREATER -1)
		backend (INTERP interpreter ${TARGET})
	endif()
	string (FIND "${JAVA_BACKEND}" ${FLAG} POS)
	if (${POS} GREATER -1)
		backend (JAVA java ${TARGET})
	endif()
	string (FIND "${JS_BACKEND}" ${FLAG} POS)
	if (${POS} GREATER -1)
		backend (JS js ${TARGET})
	endif()
	string (FIND "${OLDCPP_BACKEND}" ${FLAG} POS)
	if (${POS} GREATER -1)
		backend (OCPP "" ${TARGET})
	endif()
	string (FIND "${RUST_BACKEND}" ${FLAG} POS)
	if (${POS} GREATER -1)
		backend (RUST rust ${TARGET})
	endif()
	string (FIND "${WASM_BACKEND}" ${FLAG} POS)
	if (${POS} GREATER -1)
		backend (WASM wasm ${TARGET})
	endif()
	string (FIND "${LLVM_BACKEND}" ${FLAG} POS)
	if (${POS} GREATER -1)
		backend (LLVM llvm ${TARGET})
		target_compile_definitions (${TARGET} PRIVATE -D${LLVM_VERSION})
		target_include_directories (${TARGET} PRIVATE ${SRCDIR}/generator/c ${SRCDIR}/generator/cpp  ${LLVM_INCLUDE_DIRS})
	endif()
endfunction()

####################################
# Manual LLVM scan
macro (llvm_config)
	if ( NOT DEFINED LLVM_CONFIG)
		set (LLVM_CONFIG llvm-config)
	endif()
	find_program (LC ${LLVM_CONFIG})
	if (${LC} STREQUAL LC-NOTFOUND)
		message (FATAL_ERROR "Cannot find program ${LLVM_CONFIG} (llvm-config or derived expected)")
	endif()
	execute_process (COMMAND ${LLVM_CONFIG} --version OUTPUT_VARIABLE LLVM_VERSION)
	string ( STRIP ${LLVM_VERSION} LLVM_PACKAGE_VERSION )
	message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")

	execute_process (COMMAND ${LLVM_CONFIG} --includedir OUTPUT_VARIABLE LLVM_INCLUDE)
	string ( STRIP ${LLVM_INCLUDE} LLVM_INCLUDE_DIRS )
	execute_process (COMMAND ${LLVM_CONFIG} --ldflags OUTPUT_VARIABLE LLVM_LDFLAGS_TMP)
	string ( STRIP ${LLVM_LDFLAGS_TMP} LLVM_LD_FLAGS )
	execute_process (COMMAND ${LLVM_CONFIG}  --libs OUTPUT_VARIABLE LLVM_LIBS_TMP)
	string ( STRIP ${LLVM_LIBS_TMP} LLVM_LIBS )
	execute_process (COMMAND ${LLVM_CONFIG}  --system-libs OUTPUT_VARIABLE LLVM_SYS_LIBS_TMP)
	string ( STRIP ${LLVM_SYS_LIBS_TMP} LLVM_SYS_LIBS)
	set (LLVM_LIBS ${LLVM_LIBS} ${LLVM_SYS_LIBS})
endmacro()

####################################
# Manual LLVM scan
macro (include_llvm)
	set (INCLUDE_LLVM off)
	if (LLVM_BACKEND)
		string (FIND "${LLVM_BACKEND}" "STATIC"  POS)
		if (${POS} GREATER -1 AND INCLUDE_STATIC)
			set (INCLUDE_LLVM on)
		endif()
		string (FIND "${LLVM_BACKEND}" "DYNAMIC" POS)
		if (${POS} GREATER -1 AND INCLUDE_DYNAMIC)
			set (INCLUDE_LLVM on)
		endif()
		string (FIND "${LLVM_BACKEND}" "COMPILER"  POS)
		if (${POS} GREATER -1)
			set (INCLUDE_LLVM on)
		endif()
	endif()
endmacro()

####################################
# LLVM
include_llvm()
if (INCLUDE_LLVM )
	if(USE_LLVM_CONFIG)
		llvm_config()
	else()
		find_package(LLVM REQUIRED CONFIG)
		if (COMMAND llvm_map_components_to_libnames)
			message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
			message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
			# Find the libraries that correspond to the LLVM components that we wish to use
			llvm_map_components_to_libnames(LLVM_LIBS all)
			list(REMOVE_ITEM LLVM_LIBS LTO)
		else()
			llvm_config()
		endif()
	endif()

	string (REGEX REPLACE "([0-9])\\.([0-9]).*" "LLVM_\\1\\2" LLVM_VERSION ${LLVM_PACKAGE_VERSION})

	# the declarations below are redundant but necessary to cope with different cmake behaviors on different platforms
	set (TMP ${SRCDIR}/generator/llvm)
	set_property(SOURCE ${TMP}/llvm_dsp_aux.cpp ${TMP}/llvm_dynamic_dsp_aux.cpp APPEND_STRING PROPERTY COMPILE_FLAGS "-fno-rtti ${LLVM_DEFINITIONS}")
	set_property(SOURCE ${TMP}/llvm_dsp_aux.cpp ${TMP}/llvm_dynamic_dsp_aux.cpp APPEND_STRING PROPERTY CMAKE_CXX_FLAGS "-fno-rtti ${LLVM_DEFINITIONS}")
	set (FAUST_LIBS ${FAUST_LIBS} ${LLVM_LD_FLAGS} ${LLVM_LIBS})
endif()

####################################
# platform dependent settings
if(APPLE)
	if(IOS)
		set (CMAKE_XCODE_EFFECTIVE_PLATFORMS "iphoneos")
		set (CMAKE_OSX_ARCHITECTURES "arm64 armv7 armv7s")
		set (CMAKE_OSX_SYSROOT "iphoneos")
		set (CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 8.0)
	else()
		if (DEPLOYMENT_TARGET)
			set (CMAKE_OSX_DEPLOYMENT_TARGET ${DEPLOYMENT_TARGET_VERSION})
		endif()
		set (MACSDK /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk)
		if (EXISTS ${MACSDK})
			set (CMAKE_OSX_SYSROOT ${MACSDK})
		else()
			message ("WARNING No SDK at ${MACSDK}")
		endif()
		if (UNIVERSAL)
			message (STATUS "Compiles an universal binary")
			set (CMAKE_OSX_ARCHITECTURES x86_64 i386)
			set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -DLLVM_BUILD_UNIVERSAL)
		endif()
	endif()
elseif(WIN32)
	if (NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
		set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -DWIN32 -D__MINGW32__)
	endif()
	set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -D_CRT_SECURE_NO_WARNINGS -D_USE_MATH_DEFINES)
	set (FAUST_LIBS ${FAUST_LIBS} Ws2_32.lib)
else()
	set (FAUST_LIBS -lpthread ${FAUST_LIBS})
endif()


####################################
# compiler dependent settings
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
else()
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

####################################
# Manual LLVM scan
macro (llvm_config)
	if ( NOT DEFINED LLVM_CONFIG)
		set (LLVM_CONFIG llvm-config)
	endif()
	find_program (LC ${LLVM_CONFIG})
	if (${LC} STREQUAL LC-NOTFOUND)
		message (FATAL_ERROR "Cannot find program ${LLVM_CONFIG} (llvm-config or derived expected)")
	endif()
	execute_process (COMMAND ${LLVM_CONFIG} --version OUTPUT_VARIABLE LLVM_VERSION)
	string ( STRIP ${LLVM_VERSION} LLVM_PACKAGE_VERSION )
	message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")

	execute_process (COMMAND ${LLVM_CONFIG} --includedir OUTPUT_VARIABLE LLVM_INCLUDE)
	string ( STRIP ${LLVM_INCLUDE} LLVM_INCLUDE_DIRS )
	execute_process (COMMAND ${LLVM_CONFIG} --ldflags OUTPUT_VARIABLE LLVM_LDFLAGS_TMP)
	string ( STRIP ${LLVM_LDFLAGS_TMP} LLVM_LD_FLAGS )
	execute_process (COMMAND ${LLVM_CONFIG}  --libs OUTPUT_VARIABLE LLVM_LIBS_TMP)
	string ( STRIP ${LLVM_LIBS_TMP} LLVM_LIBS )
	execute_process (COMMAND ${LLVM_CONFIG}  --system-libs OUTPUT_VARIABLE LLVM_SYS_LIBS_TMP)
	string ( STRIP ${LLVM_SYS_LIBS_TMP} LLVM_SYS_LIBS)
	set (LLVM_LIBS ${LLVM_LIBS} ${LLVM_SYS_LIBS})
endmacro()

####################################
# Add the different targets
####################################
if (INCLUDE_EXECUTABLE)
	add_executable(faust ${SRC} ${HH})
	target_compile_definitions (faust PRIVATE ${FAUST_DEFINITIONS})
	target_include_directories (faust PRIVATE ${FAUST_INC} ${LLVM_INC})
	target_link_libraries (faust PRIVATE ${FAUST_LIBS})
	scan_backends (faust COMPILER)
	set_target_properties(faust  PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY ${BINDIR})
	set (INSTALL_TARGETS faust)
endif()

# static faust library
if (INCLUDE_STATIC)
	add_library(staticlib STATIC ${SRC} ${HH})
	target_compile_definitions (staticlib PRIVATE ${FAUST_DEFINITIONS})
	target_include_directories (staticlib PRIVATE ${FAUST_INC} ${LLVM_INC})
	target_link_libraries (staticlib PRIVATE ${FAUST_LIBS})
	set_target_properties(staticlib PROPERTIES 
		ARCHIVE_OUTPUT_DIRECTORY ${LIBDIR}
		LIBRARY_OUTPUT_DIRECTORY ${LIBDIR}
		ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBDIR}
		LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBDIR})
	if (WIN32)
		if (MSVC)
			set_target_properties(staticlib  PROPERTIES OUTPUT_NAME libfaust)
		else()
			set_target_properties(staticlib  PROPERTIES OUTPUT_NAME faust)
		endif()
	endif()
	if (IOS)
		set_target_properties(staticlib PROPERTIES OUTPUT_NAME faust.ios)
	else()
		set_target_properties(staticlib PROPERTIES OUTPUT_NAME faust)
	endif()
	set_target_properties(staticlib PROPERTIES COMPILE_FLAGS  -DFAUST_LIB
		POSITION_INDEPENDENT_CODE ON)
	set (INSTALL_TARGETS ${INSTALL_TARGETS} staticlib)
	scan_backends (staticlib STATIC)
endif()


# dynamic faust library
if (INCLUDE_DYNAMIC)
	add_library(dynamiclib SHARED ${SRC} ${HH})
	target_compile_definitions (dynamiclib PRIVATE ${FAUST_DEFINITIONS})
	target_include_directories (dynamiclib PRIVATE ${FAUST_INC} ${LLVM_INC})
	target_link_libraries (dynamiclib PRIVATE ${FAUST_LIBS})
	if (WIN32)
		enable_language(RC)
		set_target_properties(dynamiclib PROPERTIES
			ARCHIVE_OUTPUT_DIRECTORY  ${LIBDIR}
			RUNTIME_OUTPUT_DIRECTORY  ${LIBDIR})
		set_target_properties(dynamiclib PROPERTIES OUTPUT_NAME faust)
		target_sources (faust PRIVATE ${ROOT}/windows/faust.rc)
		target_sources (dynamiclib PRIVATE ${ROOT}/windows/faustdll.rc)
	else()
		if (IOS)
			set_target_properties(dynamiclib PROPERTIES OUTPUT_NAME faust.ios)
		else()
			set_target_properties(dynamiclib PROPERTIES OUTPUT_NAME faust)
		endif()
		set_target_properties(dynamiclib PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${LIBDIR})
		set_target_properties(dynamiclib PROPERTIES
			LIBRARY_OUTPUT_DIRECTORY ${LIBDIR}
			VERSION ${VERSION}
			SOVERSION ${SOVERS})
	endif()
	set_target_properties(dynamiclib PROPERTIES COMPILE_FLAGS -DFAUST_LIB)
	scan_backends (dynamiclib DYNAMIC)
	set (INSTALL_TARGETS ${INSTALL_TARGETS} dynamiclib)
endif()


####################################
# add sub projects (emcc, osclib)
####################################
if (NOT (${CMAKE_GENERATOR} STREQUAL Xcode OR ${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC))
	add_subdirectory (emcc)
elseif (NOT IOS)
	message ("WARNING Targets asmjslib and wasmlib are not included with Xcode or Visual Studio")
endif()
if (INCLUDE_OSC)
	add_subdirectory (osc)
	set (SUBTARGETS ${SUBTARGETS} osc)
endif()
if (INCLUDE_HTTP)
	add_subdirectory (http)
	set (SUBTARGETS ${SUBTARGETS} http)
endif()


####################################
# install section
####################################
set (ARCHDIR ${ROOT}/architecture)
set (ARCHINC ${ARCHDIR}/faust)
set (ARCHDIRS ${ARCHINC}/au ${ARCHINC}/audio ${ARCHINC}/dsp ${ARCHINC}/gui ${ARCHINC}/midi ${ARCHINC}/unity ${ARCHINC}/vst)

message (STATUS "Install location is ${CMAKE_INSTALL_PREFIX}")
message (STATUS "Include targets: ${INSTALL_TARGETS} ${SUBTARGETS}")

####################################
# install the faust compiler and libraries
install ( TARGETS ${INSTALL_TARGETS}
	RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/faust
)

####################################
# install headers
install (
    DIRECTORY ${ARCHDIRS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/faust
    FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
    	GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    PATTERN ".DS_Store" EXCLUDE
    PATTERN "*.o" EXCLUDE
)
install (
    FILES     ${ARCHINC}/misc.h ${ARCHINC}/sound-file.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/faust
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)
install (
    FILES     ${SRCDIR}/generator/libfaust.h ${SRCDIR}/generator/libfaust-c.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/faust/dsp
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)
# the file below is part of the httpd lib but installed even if the lib is not part of the config
# this is due to the fact that faust -i will try to read it (depending on the architecture file)
install (
    FILES     ${ARCHDIR}/httpdlib/src/include/HTTPDControler.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/faust/gui
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

####################################
# install faust2xxx tools
file (GLOB FAUST2XXX ${ROOT}/tools/faust2appls/faust2* ${ROOT}/tools/faust2appls/encoderunitypackage ${ROOT}/tools/faust2sc-1.0.0/faust2sc )
install (
    FILES     ${FAUST2XXX} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_EXECUTE WORLD_READ
)
install (
    FILES     ${ROOT}/tools/faust2appls/faustoptflags ${ROOT}/tools/faust2appls/faustpath DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_EXECUTE WORLD_READ
)


####################################
# install shared resources
install (
    FILES     ${ROOT}/faust.1 DESTINATION ${CMAKE_INSTALL_PREFIX}/share/man
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

install (
    FILES  ${ARCHDIR}/httpdlib/src/hexa/jsscripts DESTINATION ${CMAKE_INSTALL_PREFIX}/share/faust/js
    RENAME jsscripts.js
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

install (
    FILES  ${ARCHDIR}/httpdlib/src/hexa/stylesheet DESTINATION ${CMAKE_INSTALL_PREFIX}/share/faust/js
    RENAME stylesheet.js
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

# install faust libraries
file (GLOB FAUSTDSPLIBS ${ROOT}/libraries/*.lib ${ROOT}/libraries/old/*.lib)
# install various files from the architecture root folder
file (GLOB FAUSTARCHS   ${ARCHDIR}/*.cpp ${ARCHDIR}/*.c
						${ARCHDIR}/*.rs  ${ARCHDIR}/*.js
						${ARCHDIR}/*.java ${ARCHDIR}/*.h
						${ARCHDIR}/mathdoctexts-*.txt  ${ARCHDIR}/latexheader.tex)
install (
    FILES     ${FAUSTDSPLIBS} ${FAUSTARCHS} DESTINATION ${CMAKE_INSTALL_PREFIX}/share/faust
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

# install folders
set (ARCHSRC android api AU iOS juce max-msp nodejs osclib sam smartKeyboard unity webaudio)
foreach (dir ${ARCHSRC})
	set(ARCHFOLDERS ${ARCHFOLDERS} ${ARCHDIR}/${dir})
endforeach()
set(ARCHFOLDERS ${ARCHFOLDERS} ${ARCHDIR}/httpdlib/html/js)

install (
    DIRECTORY ${ARCHFOLDERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/share/faust
    FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
    	GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    PATTERN ".DS_Store" EXCLUDE
    PATTERN "*.o" EXCLUDE
)

####################################
# install ios lib
if (APPLE)
	install (
		FILES     ${ARCHDIR}/ios-libsndfile.a DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
		PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
	)
endif()
