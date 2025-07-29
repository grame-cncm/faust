cmake_minimum_required(VERSION 3.6.0)

set(HAVE_FLAG_SEARCH_PATHS_FIRST 0)

project (faustemcc)

set ( CMAKE_OSX_DEPLOYMENT_TARGET "")
set ( CMAKE_OSX_SYSROOT "")
set ( CMAKE_CXX_COMPILER "emcc")
set (CMAKE_CXX_LINK_FLAGS "")

if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm64")
    message (WARNING "Compiling on M1")
    set (CMAKE_OSX_ARCHITECTURES " ")
endif()

if (UNIVERSAL)
message (WARNING "WASM do not support universal mode. Switch back to native mode before compiling")
endif()

####################################
# emscripten support

file (GLOB BINDINGS ${ROOT}/compiler/generator/wasm/bindings/*.cpp)
set (SRC ${SRC} ${BINDINGS})

set (WASM_EXPORTED "\"['UTF8ToString', 'stringToUTF8', 'FS']\"")
file (GLOB LIBSNDFILE ${WASMGLUE}/*.a)

set (WASM_LINK_FLAGS "--no-heap-copy --bind -O3 --memory-init-file 0 -s LINKABLE=0 -s DYNAMIC_EXECUTION=0 -s WASM=1 -s EXPORT_NAME=\"'FaustModule'\" -s MODULARIZE=1 --preload-file ../../wasm-filesystem@usr -s ASSERTIONS=1 -s ALLOW_MEMORY_GROWTH=1 -s STACK_SIZE=8MB -s DISABLE_EXCEPTION_CATCHING=1 -s EXPORTED_RUNTIME_METHODS=${WASM_EXPORTED} ${LIBSNDFILE}")

####################################
# Add the different targets

add_executable(wasmlib EXCLUDE_FROM_ALL ${SRC} ${HH})
target_include_directories (wasmlib PRIVATE ${FAUST_INC})
target_compile_definitions (wasmlib PRIVATE -DEMCC -DFAUST_LIB ${FAUST_DEFINITIONS})

# TO SUBSTITUTE ?
#target_link_libraries (wasmlib ${LIBSNDFILE})
#target_include_directories (wasmlib PRIVATE ${SRCDIR}/generator/wasm ${FAUST_INC})
#target_compile_definitions (wasmlib PRIVATE -DEMCC -DFAUST_LIB -DWASM_BUILD ${FAUST_DEFINITIONS})

set_target_properties (wasmlib PROPERTIES
        OUTPUT_NAME libfaust-wasm
        LINK_FLAGS ${WASM_LINK_FLAGS}
        COMPILE_FLAGS -O3 
#       RUNTIME_OUTPUT_DIRECTORY ${LIBDIR}   generation in a non default place prevents the data file to be found
        SUFFIX ".js")

scan_backends (wasmlib WASM)
