cmake_minimum_required(VERSION 3.4.0)

set(HAVE_FLAG_SEARCH_PATHS_FIRST 0)

project (faustemcc)

set ( CMAKE_OSX_DEPLOYMENT_TARGET	"")
set ( CMAKE_OSX_SYSROOT 		"")
set ( CMAKE_CXX_COMPILER 	"emcc")
set ( CMAKE_CXX_LINK_FLAGS "")
set ( CMAKE_CXX_FLAGS "-DEMCC")

if (UNIVERSAL)
message (WARNING "WASM do not support universal mode. Switch back to native mode before compiling")
endif()

set (WASMGLUE ${ROOT}/build/wasmglue)

####################################
# emscripten support

file (GLOB BINDINGS ${ROOT}/compiler/generator/wasm/bindings/*.cpp)
set (SRC ${SRC} ${BINDINGS})

set (WASM_EXTRA_EXPORTED "\"['UTF8ToString', 'stringToUTF8', 'FS']\"")
file (GLOB LIBSNDFILE ${WASMGLUE}/*.a)

#--preload-file
set (WASM_LINK_FLAGS "--no-heap-copy --bind -O3 --memory-init-file 0 -s LINKABLE=0 -s WASM=1 -s EXPORT_NAME=\"'FaustModule'\" -s MODULARIZE=1 --embed-file ../../wasm-filesystem@usr -s ASSERTIONS=1 -s ALLOW_MEMORY_GROWTH=1 -s DISABLE_EXCEPTION_CATCHING=1 -s EXTRA_EXPORTED_RUNTIME_METHODS=${WASM_EXTRA_EXPORTED} ${LIBSNDFILE}")


####################################
# Add the different targets
add_executable(wasmlib EXCLUDE_FROM_ALL ${SRC} ${HH})
target_link_libraries (wasmlib ${LIBSNDFILE})
target_include_directories (wasmlib PRIVATE ${SRCDIR}/generator/wasm ${FAUST_INC})
target_compile_definitions (wasmlib PRIVATE -DEMCC -DFAUST_LIB -DWASM_BUILD ${FAUST_DEFINITIONS})
set_target_properties (wasmlib PROPERTIES
		OUTPUT_NAME libfaust-wasm
		LINK_FLAGS ${WASM_LINK_FLAGS}
		COMPILE_FLAGS -O3 
		RUNTIME_OUTPUT_DIRECTORY ${LIBDIR}
		SUFFIX ".js" )


scan_backends (wasmlib  WASM)
