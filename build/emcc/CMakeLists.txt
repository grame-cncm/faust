cmake_minimum_required(VERSION 3.4.0)
project (faustemcc)

set ( CMAKE_OSX_DEPLOYMENT_TARGET	"")
set ( CMAKE_OSX_SYSROOT 		"")
set ( CMAKE_CXX_COMPILER 	"emcc")

if (UNIVERSAL)
message (WARNING "ASMJS and WASM do not support univeral mode. Switch back to native mode before compiling")
endif()

####################################
# emscripten support
set (WASM_EXPORTED "\"['_createWasmCDSPFactoryFromString', '_expandCDSPFromString', '_getCLibFaustVersion', '_getWasmCModule', '_getWasmCModuleSize', '_getWasmCHelpers', '_freeWasmCModule', '_freeCMemory', '_cleanupAfterException', '_getErrorAfterException']\"")
set (ASMJS_EXPORTED "\"['_createAsmCDSPFactoryFromString', '_expandCDSPFromString', '_getCLibFaustVersion', '_freeCMemory']\"")

set (WASM_LINK_FLAGS "-O3 --memory-init-file 0 -s WASM=1 -s EXPORT_NAME=\"'FaustModule'\" -s MODULARIZE=1 -s ASSERTIONS=1 -s ALLOW_MEMORY_GROWTH=1 -s DISABLE_EXCEPTION_CATCHING=1 -s EXPORTED_FUNCTIONS=${WASM_EXPORTED}")

set (ASMJSLINK_FLAGS "-O3 --memory-init-file 0 -s ASSERTIONS=2 -s TOTAL_MEMORY=134217728 -s DISABLE_EXCEPTION_CATCHING=0 -s EXPORTED_FUNCTIONS=${ASMJS_EXPORTED}")


####################################
# Add the different targets
add_executable(wasmlib EXCLUDE_FROM_ALL ${SRC} ${HH})
target_include_directories (wasmlib PRIVATE ${SRCDIR}/generator/wasm)
target_compile_definitions (wasmlib PRIVATE -DEMCC -DFAUST_LIB -DWASM_BUILD)
set_target_properties (wasmlib PROPERTIES
		OUTPUT_NAME libfaust-wasm
		LINK_FLAGS ${WASM_LINK_FLAGS})

add_executable(asmjslib EXCLUDE_FROM_ALL ${SRC} ${HH})
target_include_directories (asmjslib PRIVATE ${SRCDIR}/generator/asmjs)
target_compile_definitions (asmjslib PRIVATE -DEMCC -DFAUST_LIB -DASMJS_BUILD)
set_target_properties (asmjslib PROPERTIES 
		OUTPUT_NAME libfaust
		LINK_FLAGS ${ASMJSLINK_FLAGS})

set_target_properties(wasmlib asmjslib PROPERTIES  
		COMPILE_FLAGS  -O3 
		RUNTIME_OUTPUT_DIRECTORY ${LIBDIR}
		SUFFIX ".js" )

foreach (TARGET wasmlib asmjslib)
	# add definitions
	target_compile_definitions (${TARGET} PRIVATE ${FAUST_DEFINITIONS})
	# set include directories
	target_include_directories (${TARGET} PRIVATE ${FAUST_INC})
endforeach()

scan_backends (wasmlib  WASM)
scan_backends (asmjslib ASMJS)
