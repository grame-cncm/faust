cmake_minimum_required(VERSION 3.4.0)
project (faustemcc)

option (WORKLET "Compile wasm glue library for worklet" off)

set (CMAKE_OSX_DEPLOYMENT_TARGET "")
set (CMAKE_OSX_SYSROOT 	"")
set (CMAKE_CXX_COMPILER "emcc")

if (UNIVERSAL)
message (WARNING "WASM do not support universal mode. Switch back to native mode before compiling")
endif()

if (WORKLET)
message(STATUS "Compile wasm glue library for worklet")
set (WASM_COMPILE_FLAGS "-O3 -DAUDIO_WORKLET")
set (WASM_LINK_FLAGS_EXTRA "-s BINARYEN_ASYNC_COMPILATION=0 -s SINGLE_FILE=1 -s ASSERTIONS=0")
set (LIB_NAME "libfaust-worklet-glue")
else()
set (WASM_COMPILE_FLAGS "-O3")
set (WASM_LINK_FLAGS_EXTRA "-s ASSERTIONS=1")
set (LIB_NAME "libfaust-glue")
endif()

set (WGLUE wasmglue)

####################################
# source and headers files
file (GLOB SRC ${SRCDIR}/generator/wasm/wasm_dsp_aux.cpp ${SRCDIR}/generator/wasm/wasm_errormsg.cpp ${SRCDIR}/generator/export.cpp)
file (GLOB HH ${SRCDIR}/generator/wasm/wasm_dsp_aux.hh ${SRCDIR}/generator/export.hh)
set (LIBSNDFILE "${ROOT}/build/wasmglue/libsndfile.a ${ROOT}/build/wasmglue/libogg.a ${ROOT}/build/wasmglue/libvorbis.a ${ROOT}/build/wasmglue/libvorbisenc.a ${ROOT}/build/wasmglue/libFLAC.a")

#
####################################
# include directories
set (FAUST_INC ${SRCDIR}
	${SRCDIR}/errors 
	${SRCDIR}/generator
	${SRCDIR}/tlib ${SRCDIR}/transform ${SRCDIR}/utils
	${SRCDIR}/../architecture /usr/local/include)


####################################
# emscripten support
set (WASM_EXTRA_EXPORTED "\"['FS']\"")

set (WASM_LINK_FLAGS "--bind --memory-init-file 0 -s LINKABLE=1 -s WASM=1 -s EXPORT_NAME=\"'FaustModule'\" -s MODULARIZE=1 -s ASSERTIONS=0 -s ALLOW_MEMORY_GROWTH=1 -s DISABLE_EXCEPTION_CATCHING=1 -s EXTRA_EXPORTED_RUNTIME_METHODS=${WASM_EXTRA_EXPORTED} ${LIBSNDFILE} ${WASM_LINK_FLAGS_EXTRA}") 
 
####################################
# Add the different targets
add_executable(${WGLUE} EXCLUDE_FROM_ALL ${SRC} ${HH})
target_include_directories (${WGLUE} PRIVATE ${SRCDIR}/generator/wasm ${FAUST_INC})
target_compile_definitions (${WGLUE} PRIVATE -DEMCC ${FAUST_DEFINITIONS})
set_target_properties (${WGLUE} PROPERTIES
		OUTPUT_NAME ${LIB_NAME}
		LINK_FLAGS ${WASM_LINK_FLAGS}
		COMPILE_FLAGS ${WASM_COMPILE_FLAGS}
		RUNTIME_OUTPUT_DIRECTORY ${LIBDIR}
		SUFFIX ".js")
