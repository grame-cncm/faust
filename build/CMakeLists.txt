cmake_minimum_required(VERSION 3.0.0)
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
# compiles the faust compiler by default
option ( LIBSHARED 	"Compile the faust library as a shared library" 	off )
option ( LIBSTATIC 	"Compile the faust library as a static library" 	off )

####################################
# source and headers files 
file (GLOB SRC ${SRCDIR}/*.cpp ${SRCDIR}/*/*.cpp ${SRCDIR}/draw/*/*.cpp ${SRCDIR}/generator/fir/*.cpp)
file (GLOB HH  ${SRCDIR}/*.hh  ${SRCDIR}/*/*.hh  ${SRCDIR}/generator/fir/*.hh)

set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -std=c++11)

####################################
# include directories 
set (INC ${SRCDIR} ${SRCDIR}/boxes ${SRCDIR}/documentator ${SRCDIR}/draw ${SRCDIR}/errors ${SRCDIR}/evaluate ${SRCDIR}/extended ${SRCDIR}/generator ${SRCDIR}/generator/fir ${SRCDIR}/generator/interpreter ${SRCDIR}/normalize ${SRCDIR}/parallelize ${SRCDIR}/parser ${SRCDIR}/patternmatcher ${SRCDIR}/propagate ${SRCDIR}/signals ${SRCDIR}/tlib ${SRCDIR}/utils  ${SRCDIR}/draw/device ${SRCDIR}/draw/schema ${SRCDIR}/../architecture /usr/local/include)

####################################
# check backends 
if (ASMJS_BACKEND)
	message(STATUS "Include ASMJS backend")
	set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -DASMJS_BUILD)
	file (GLOB BACKEND_SRC	${BACKEND_SRC}	${SRCDIR}/generator/asmjs/*.cpp)
	file (GLOB BACKEND_H 	${BACKEND_H} 	${SRCDIR}/generator/asmjs/*.hh)
	set (INC ${INC} ${SRCDIR}/generator/asmjs)
endif()

if (C_BACKEND)
	message(STATUS "Include C backend")
	set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -DC_BUILD)
	file (GLOB BACKEND_SRC	${BACKEND_SRC}	${SRCDIR}/generator/c/*.cpp)
	file (GLOB BACKEND_H 	${BACKEND_H} 	${SRCDIR}/generator/c/*.hh)
	set (INC ${INC} ${SRCDIR}/generator/c)
endif()

if (CPP_BACKEND)
	message(STATUS "Include CPP backend")
	set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -DCPP_BUILD)
	file (GLOB BACKEND_SRC	${BACKEND_SRC}	${SRCDIR}/generator/cpp/*.cpp)
	file (GLOB BACKEND_H 	${BACKEND_H} 	${SRCDIR}/generator/cpp/*.hh)
	set (INC ${INC} ${SRCDIR}/generator/cpp)
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
	set (INC ${INC} ${SRCDIR}/generator/interpreter)
endif()

if (JAVA_BACKEND)
	message(STATUS "Include JAVA backend")
	set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -DJAVA_BUILD)
	file (GLOB BACKEND_SRC	${BACKEND_SRC}	${SRCDIR}/generator/java/*.cpp)
	file (GLOB BACKEND_H 	${BACKEND_H} 	${SRCDIR}/generator/java/*.hh)
	set (INC ${INC} ${SRCDIR}/generator/java)
endif()

if (JS_BACKEND)
	message(STATUS "Include JAVASCRIPT backend")
	set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -DJS_BUILD)
	file (GLOB BACKEND_SRC	${BACKEND_SRC}	${SRCDIR}/generator/js/*.cpp)
	file (GLOB BACKEND_H 	${BACKEND_H} 	${SRCDIR}/generator/js/*.hh)
	set (INC ${INC} ${SRCDIR}/generator/js)
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
	set (INC ${INC} ${SRCDIR}/generator/rust)
endif()

if (WASM_BACKEND)
	message(STATUS "Include WASM backend")
	set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -DWASM_BUILD)
	file (GLOB BACKEND_SRC	${BACKEND_SRC}	${SRCDIR}/generator/wasm/*.cpp)
	file (GLOB BACKEND_H 	${BACKEND_H} 	${SRCDIR}/generator/wasm/*.hh)
	set (INC ${INC} ${SRCDIR}/generator/wasm)
endif()

####################################
# LLVM 
if (LLVM_BACKEND)
	message(STATUS "Include LLVM backend")
	find_package(LLVM REQUIRED CONFIG)
	message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
	message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
	# Find the libraries that correspond to the LLVM components that we wish to use
	llvm_map_components_to_libnames(LLVM_LIBS all)

	string (REGEX REPLACE "([0-9])\\.([0-9])\\.[0-9]" "LLVM_\\1\\2" LLVM_VERSION ${LLVM_PACKAGE_VERSION})
	set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -DLLVM_BUILD -D${LLVM_VERSION} -std=gnu++11)
	file (GLOB BACKEND_SRC	${BACKEND_SRC}	${SRCDIR}/generator/llvm/*.cpp)
	file (GLOB BACKEND_H 	${BACKEND_H} 	${SRCDIR}/generator/llvm/*.hh)
	set (INC ${INC} ${SRCDIR}/generator/llvm ${SRCDIR}/generator/c ${SRCDIR}/generator/cpp)
endif()

####################################
# add backends src and headers
set (SRC ${SRC} ${BACKEND_SRC})
set (HH  ${HH} ${BACKEND_H})


####################################
# faust libraries 
if(APPLE)
elseif(WIN32)
	if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
		set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -DWIN32 -D__MINGW32__)
	endif()
	set (FAUST_LIBS Ws2_32.lib)
else()
	set (FAUST_LIBS -lpthread)
endif()


####################################
# output option management
if (LIBSHARED OR LIBSTATIC)
	set (FAUST_DEFINITIONS ${FAUST_DEFINITIONS} -DFAUST_LIB)
	if (LIBSHARED)
		 message (STATUS "Compile the faust library as a shared library")
		 set (LIBTYPE "SHARED")
	else() 
		 message (STATUS "Compile the faust library as a static library")
		 set (LIBTYPE "STATIC")
	endif()
endif()


####################################
# set include directories
include_directories(${INC} ${LLVM_INCLUDE_DIRS})

####################################
# add definitions
add_definitions(${LLVM_DEFINITIONS} ${FAUST_DEFINITIONS})

# Now build our tools
if (LIBSHARED OR LIBSTATIC)
	add_library(faust ${LIBTYPE} ${SRC} ${HH})
else ()
	add_executable(faust ${SRC} ${HH})
endif()

# Link against libraries
target_link_libraries(faust ${FAUST_LIBS} ${LLVM_LIBS})
