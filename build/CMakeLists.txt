cmake_minimum_required(VERSION 3.4.0)
project (faust)

#######################################
# Versions
set (VERSION 2.5)
set (STRVERS "v.2.5.3")
set (FAUSTFWKVERS A)
set (SOVERS 3)

set (SRCDIR ../compiler)

#######################################
# Options to select backends
option ( ASMJS_BACKEND 	"Include ASMJS backend" 	off )
option ( C_BACKEND 		"Include C backend" 		off )
option ( CPP_BACKEND 	"Include CPP backend" 		ON )
option ( FIR_BACKEND 	"Include FIR backend" 		off )
option ( INTERP_BACKEND "Include INTERPRETER backend"	off )
option ( JAVA_BACKEND 	"Include JAVA backend"		off )
option ( JS_BACKEND 	"Include JAVASCRIPT backend" off )
option ( LLVM_BACKEND 	"Include LLVM backend"		off )
option ( OLDCPP_BACKEND "Include old CPP backend"	off )
option ( RUST_BACKEND 	"Include RUST backend" 		off )
option ( WASM_BACKEND 	"Include WASM backend"		off )

#######################################
# Output options
# compiles the faust compiler and static library by default
option ( COMPILER 	"Compiles the faust compiler" 	on )
option ( LIBSHARED 	"Compiles the faust library as a shared library" 		off )
option ( LIBSTATIC 	"Compiles the faust library as a static library" 		off )
option ( LIBWASM 	"Compiles the faust library as a Web Assembly library" 	off )
option ( LIBASMJS 	"Compiles the faust library as an ASM JS library" 		off )
option ( UNIVERSAL 	"Compiles and combines i386 and x86_64 architectures"	off )

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
set (FAUST_INC ${SRCDIR} ${SRCDIR}/boxes ${SRCDIR}/documentator ${SRCDIR}/draw ${SRCDIR}/errors ${SRCDIR}/evaluate ${SRCDIR}/extended ${SRCDIR}/generator ${SRCDIR}/generator/fir ${SRCDIR}/generator/interpreter ${SRCDIR}/normalize ${SRCDIR}/parallelize ${SRCDIR}/parser ${SRCDIR}/patternmatcher ${SRCDIR}/propagate ${SRCDIR}/signals ${SRCDIR}/tlib ${SRCDIR}/utils  ${SRCDIR}/draw/device ${SRCDIR}/draw/schema ${SRCDIR}/../architecture /usr/local/include)

####################################
# check backends 
if (ASMJS_BACKEND)
	message(STATUS "Include ASMJS backend")
	set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -DASMJS_BUILD)
	file (GLOB BACKEND_SRC	${BACKEND_SRC}	${SRCDIR}/generator/asmjs/*.cpp)
	file (GLOB BACKEND_H 	${BACKEND_H} 	${SRCDIR}/generator/asmjs/*.hh)
	set (FAUST_INC ${FAUST_INC} ${SRCDIR}/generator/asmjs)
endif()

if (C_BACKEND)
	message(STATUS "Include C backend")
	set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -DC_BUILD)
	file (GLOB BACKEND_SRC	${BACKEND_SRC}	${SRCDIR}/generator/c/*.cpp)
	file (GLOB BACKEND_H 	${BACKEND_H} 	${SRCDIR}/generator/c/*.hh)
	set (FAUST_INC ${FAUST_INC} ${SRCDIR}/generator/c)
endif()

if (CPP_BACKEND)
	message(STATUS "Include CPP backend")
	set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -DCPP_BUILD)
	file (GLOB BACKEND_SRC	${BACKEND_SRC}	${SRCDIR}/generator/cpp/*.cpp)
	file (GLOB BACKEND_H 	${BACKEND_H} 	${SRCDIR}/generator/cpp/*.hh)
	set (FAUST_INC ${FAUST_INC} ${SRCDIR}/generator/cpp)
endif()

if (FIR_BACKEND)
	message(STATUS "Include FIR backend")
	set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -DFIR_BUILD)
endif()

if (INTERP_BACKEND)
	message(STATUS "Include INTERPRETER backend")
	set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -DINTERP_BUILD)
	file (GLOB BACKEND_SRC	${BACKEND_SRC}	${SRCDIR}/generator/interpreter/*.cpp)
	file (GLOB BACKEND_H 	${BACKEND_H} 	${SRCDIR}/generator/interpreter/*.hh)
	set (FAUST_INC ${FAUST_INC} ${SRCDIR}/generator/interpreter)
endif()

if (JAVA_BACKEND)
	message(STATUS "Include JAVA backend")
	set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -DJAVA_BUILD)
	file (GLOB BACKEND_SRC	${BACKEND_SRC}	${SRCDIR}/generator/java/*.cpp)
	file (GLOB BACKEND_H 	${BACKEND_H} 	${SRCDIR}/generator/java/*.hh)
	set (FAUST_INC ${FAUST_INC} ${SRCDIR}/generator/java)
endif()

if (JS_BACKEND)
	message(STATUS "Include JAVASCRIPT backend")
	set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -DJS_BUILD)
	file (GLOB BACKEND_SRC	${BACKEND_SRC}	${SRCDIR}/generator/js/*.cpp)
	file (GLOB BACKEND_H 	${BACKEND_H} 	${SRCDIR}/generator/js/*.hh)
	set (FAUST_INC ${FAUST_INC} ${SRCDIR}/generator/js)
endif()

if (OLDCPP_BACKEND)
	message(STATUS "Include old CPP backend")
	set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -DOCPP_BUILD)
endif()

if (RUST_BACKEND)
	message(STATUS "Include RUST backend")
	set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -DRUST_BUILD)
	file (GLOB BACKEND_SRC	${BACKEND_SRC}	${SRCDIR}/generator/rust/*.cpp)
	file (GLOB BACKEND_H 	${BACKEND_H} 	${SRCDIR}/generator/rust/*.hh)
	set (FAUST_INC ${FAUST_INC} ${SRCDIR}/generator/rust)
endif()

if (WASM_BACKEND)
	message(STATUS "Include WASM backend")
	set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -DWASM_BUILD)
	file (GLOB BACKEND_SRC	${BACKEND_SRC}	${SRCDIR}/generator/wasm/*.cpp)
	file (GLOB BACKEND_H 	${BACKEND_H} 	${SRCDIR}/generator/wasm/*.hh)
	set (FAUST_INC ${FAUST_INC} ${SRCDIR}/generator/wasm)
endif()

####################################
# LLVM 
if (LLVM_BACKEND)
	message(STATUS "Include LLVM backend")
	if (WIN32)
		set (LLVM_CONFIG llvm-config.exe)
		execute_process (COMMAND ${LLVM_CONFIG} --version OUTPUT_VARIABLE LLVM_VERSION)
		string ( STRIP ${LLVM_VERSION} LLVM_PACKAGE_VERSION )
		message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")

		execute_process (COMMAND ${LLVM_CONFIG} --includedir OUTPUT_VARIABLE LLVM_INCLUDE)
		string ( STRIP ${LLVM_INCLUDE} LLVM_INCLUDE_DIRS )
		execute_process (COMMAND ${LLVM_CONFIG} --ldflags OUTPUT_VARIABLE LLVM_LDFLAGS_TMP)
		string ( STRIP ${LLVM_LDFLAGS_TMP} LLVM_LD_FLAGS )
		execute_process (COMMAND ${LLVM_CONFIG}  --libs OUTPUT_VARIABLE LLVM_LIBS_TMP)
		string ( STRIP ${LLVM_LIBS_TMP} LLVM_LIBS )
	else()
		find_package(LLVM REQUIRED CONFIG)
		message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
		message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
		# Find the libraries that correspond to the LLVM components that we wish to use
		llvm_map_components_to_libnames(LLVM_LIBS all)
	endif()

	string (REGEX REPLACE "([0-9])\\.([0-9]).*" "LLVM_\\1\\2" LLVM_VERSION ${LLVM_PACKAGE_VERSION})
	set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -DLLVM_BUILD -D${LLVM_VERSION})
	file (GLOB BACKEND_SRC	${BACKEND_SRC}	${SRCDIR}/generator/llvm/*.cpp)
	file (GLOB BACKEND_H 	${BACKEND_H} 	${SRCDIR}/generator/llvm/*.hh)
	set (FAUST_INC ${FAUST_INC} ${SRCDIR}/generator/llvm ${SRCDIR}/generator/c ${SRCDIR}/generator/cpp)

	# the declarations below are redundant but necessary to cope with different cmake behaviors on different platforms 
	set_property(SOURCE ${SRCDIR}/generator/llvm/llvm_dsp_aux.cpp APPEND_STRING PROPERTY COMPILE_FLAGS "-fno-rtti ${LLVM_DEFINITIONS}")
	set_property(SOURCE ${SRCDIR}/generator/llvm/llvm_dsp_aux.cpp APPEND_STRING PROPERTY CMAKE_CXX_FLAGS "-fno-rtti ${LLVM_DEFINITIONS}")
	set (FAUST_LIBS ${FAUST_LIBS} ${LLVM_LD_FLAGS})
endif()

####################################
# add backends src and headers
set (SRC ${SRC} ${BACKEND_SRC})
set (HH  ${HH} ${BACKEND_H})

if(NOT WIN32)
	set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -std=c++11)
endif()

####################################
# emscripten support
if (LIBWASM)
	set (EXPORTED "\"['_createWasmCDSPFactoryFromString', '_expandCDSPFromString', '_getCLibFaustVersion', '_getWasmCModule', '_getWasmCModuleSize', '_getWasmCHelpers', '_freeWasmCModule', '_freeCMemory', '_cleanupAfterException', '_getErrorAfterException']\"")
	set (EMCC_LINK_FLAGS "-O3 --memory-init-file 0 -s WASM=1 -s EXPORT_NAME=\"'FaustModule'\" -s MODULARIZE=1 -s ASSERTIONS=1 -s ALLOW_MEMORY_GROWTH=1 -s DISABLE_EXCEPTION_CATCHING=1 -s EXPORTED_FUNCTIONS=${EXPORTED}")
	set (CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR>  -o libfaust-wasm.js ${EMCC_LINK_FLAGS} <OBJECTS>")
	set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} "-DEMCC -DWASM_BUILD -O3")
	set (FAUST_INC ${FAUST_INC} ${SRCDIR}/generator/wasm)
elseif(LIBASMJS)
	set (EXPORTED "\"['_createAsmCDSPFactoryFromString', '_expandCDSPFromString', '_getCLibFaustVersion', '_freeCMemory']\"")
	set (EMCC_LINK_FLAGS "-O3 --memory-init-file 0 -s ASSERTIONS=2 -s TOTAL_MEMORY=134217728 -s DISABLE_EXCEPTION_CATCHING=0 -s EXPORTED_FUNCTIONS=${EXPORTED}")
	set (CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR>  -o libfaust.js ${EMCC_LINK_FLAGS} <OBJECTS>")
	set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} "-DEMCC -DASMJS_BUILD -O3")
	set (FAUST_INC ${FAUST_INC} ${SRCDIR}/generator/asmjs)
endif()

####################################
# platform dependent settings 
if(APPLE)
	if (UNIVERSAL)
		set (CMAKE_OSX_ARCHITECTURES "x86_64 i386")
		message (STATUS "Compiles an universal binary")
	endif()
elseif(WIN32)
	if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
		set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -DWIN32 -D__MINGW32__ -std=c++11)
	endif()
	set (FAUST_LIBS ${FAUST_LIBS} Ws2_32.lib)
else()
	set (FAUST_LIBS -lpthread ${FAUST_LIBS})
endif()


####################################
# set include directories
include_directories(${FAUST_INC} ${LLVM_INCLUDE_DIRS})

####################################
# add definitions
add_definitions (${FAUST_DEFINITIONS})

####################################
# Add the different outputs
if (COMPILER)
	message (STATUS "Compiles the faust compiler")
	add_executable(faust ${SRC} ${HH})
	target_link_libraries(faust ${FAUST_LIBS} ${LLVM_LIBS})
endif()

if (LIBSHARED OR LIBSTATIC)
	add_library(faustlib ${LIBTYPE} ${SRC} ${HH})
	set_target_properties(faustlib PROPERTIES 
				OUTPUT_NAME faust
				COMPILE_FLAGS  -DFAUST_LIB)
	target_link_libraries(dynamicfaustlib ${FAUST_LIBS} ${LLVM_LIBS})
endif()

if (LIBWASM)
	message (STATUS "Compiles the faust library as a WASM library")
	add_executable(faust ${SRC} ${HH})
	set_target_properties(faust PROPERTIES  
		OUTPUT_NAME libfaust-wasm
		COMPILE_FLAGS  -DFAUST_LIB
		LINK_FLAGS ${EMCC_LINK_FLAGS}
		SUFFIX ".js" )
endif()	

if (LIBASMJS)
	message (STATUS "Compiles the faust library as a ASMJS library")
	add_executable(faust ${SRC} ${HH})
	set_target_properties(faust PROPERTIES  
		OUTPUT_NAME libfaust
		COMPILE_FLAGS  -DFAUST_LIB
		LINK_FLAGS ${EMCC_LINK_FLAGS}
		SUFFIX ".js" )
endif()	
