cmake_minimum_required(VERSION 3.4.0)
project (faustemcc)

set ( CMAKE_OSX_DEPLOYMENT_TARGET	"")
set ( CMAKE_OSX_SYSROOT 		"")
set ( CMAKE_CXX_COMPILER 	"emcc")

if (UNIVERSAL)
message (WARNING "WASM do not support universal mode. Switch back to native mode before compiling")
endif()

####################################
# emscripten support
set (WASM_EXPORTED "\"['_createWasmCDSPFactoryFromString', '_expandCDSPFromString', '_deleteAllWasmCDSPFactories', '_getCLibFaustVersion', '_getWasmCModule', '_getWasmCModuleSize', '_getWasmCHelpers', '_freeWasmCModule', '_freeCMemory', '_cleanupAfterException', '_getErrorAfterException', '_generateCAuxFilesFromString']\"")
set (WASM_EXTRA_EXPORTED "\"['cwrap', 'UTF8ToString', 'stringToUTF8', 'FS']\"")

set (WASM_LINK_FLAGS "--bind -O3 --memory-init-file 0 -s LINKABLE=1 -s WASM=1 -s EXPORT_NAME=\"'FaustModule'\" -s MODULARIZE=1 --preload-file ../../wasm-libraries@libraries -s ASSERTIONS=1 -s ALLOW_MEMORY_GROWTH=1 -s DISABLE_EXCEPTION_CATCHING=1 -s EXPORTED_FUNCTIONS=${WASM_EXPORTED} -s EXTRA_EXPORTED_RUNTIME_METHODS=${WASM_EXTRA_EXPORTED}")

####################################
# Add the different targets
add_executable(wasmlib EXCLUDE_FROM_ALL ${SRC} ${HH})
target_include_directories (wasmlib PRIVATE ${SRCDIR}/generator/wasm ${FAUST_INC})
target_compile_definitions (wasmlib PRIVATE -DEMCC -DFAUST_LIB -DWASM_BUILD ${FAUST_DEFINITIONS})
set_target_properties (wasmlib PROPERTIES
		OUTPUT_NAME libfaust-wasm
		LINK_FLAGS ${WASM_LINK_FLAGS}
		COMPILE_FLAGS -O3 
		RUNTIME_OUTPUT_DIRECTORY ${LIBDIR}
		SUFFIX ".js" )

scan_backends (wasmlib  WASM)
