## Hardcoded targets for faust
## NB: In order to build the dynamic library, you need to build the exectuable library.
## See faust/build/CMakeLists.txt for more context
set(MSVC_STATIC         OFF CACHE STRING  "Use static runtimes with MSVC" FORCE)
set(INCLUDE_STATIC      OFF CACHE STRING  "Include static library"        FORCE)
set(INCLUDE_EXECUTABLE  ON  CACHE STRING  "Include runtime executable"    FORCE)
set(INCLUDE_DYNAMIC     ON  CACHE STRING  "Include dynamic library"       FORCE)
set(INCLUDE_OSC         OFF CACHE STRING  "Include Faust OSC library"     FORCE)
set(INCLUDE_HTTP        OFF CACHE STRING  "Include Faust HTTPD library"   FORCE)

set ( C_BACKEND      COMPILER STATIC DYNAMIC        CACHE STRING  "Include C backend"         FORCE )
set ( CPP_BACKEND    COMPILER STATIC DYNAMIC        CACHE STRING  "Include CPP backend"       FORCE )
set ( CMAJOR_BACKEND COMPILER STATIC DYNAMIC        CACHE STRING  "Include Cmajor backend"    FORCE )
set ( CSHARP_BACKEND COMPILER STATIC DYNAMIC        CACHE STRING  "Include CSharp backend"    FORCE )
set ( DLANG_BACKEND  COMPILER STATIC DYNAMIC        CACHE STRING  "Include Dlang backend"     FORCE )
set ( FIR_BACKEND    COMPILER STATIC DYNAMIC        CACHE STRING  "Include FIR backend"       FORCE )
set ( INTERP_BACKEND COMPILER STATIC DYNAMIC        CACHE STRING  "Include Interpreter backend" FORCE )
set ( JAVA_BACKEND   COMPILER STATIC DYNAMIC        CACHE STRING  "Include JAVA backend"      FORCE )
set ( JAX_BACKEND    COMPILER STATIC DYNAMIC        CACHE STRING  "Include JAX backend"       FORCE )
set ( JULIA_BACKEND  COMPILER STATIC DYNAMIC        CACHE STRING  "Include Julia backend"     FORCE )
set ( LLVM_BACKEND   COMPILER STATIC DYNAMIC        CACHE STRING  "Include LLVM backend"      FORCE )
set ( OLDCPP_BACKEND COMPILER STATIC DYNAMIC        CACHE STRING  "Include old CPP backend"   FORCE )
set ( RUST_BACKEND   COMPILER STATIC DYNAMIC        CACHE STRING  "Include Rust backend"      FORCE )
set ( TEMPLATE_BACKEND   OFF    CACHE STRING  "Include Template backend"  FORCE )
set ( WASM_BACKEND   COMPILER STATIC DYNAMIC WASM   CACHE STRING  "Include WASM backend"      FORCE )

target_compile_definitions(dynamiclib PUBLIC LLVM_BUILD_UNIVERSAL=1)
find_package(SndFile REQUIRED)
target_link_libraries(dynamiclib PUBLIC SndFile::sndfile)

include(FindCurses)

## Link the Pure Data external with llvm
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
add_definitions(${LLVM_DEFINITIONS})

execute_process(COMMAND ${LLVM_DIR_TEMP}/../../../bin/llvm-config --libs all
                OUTPUT_VARIABLE llvm_components)
## If you're seeing linker errors, uncomment this message line and 
## make sure it's printing many paths to .lib files.
message(llvm_components: ${llvm_components})
string(STRIP "${llvm_components}" llvm_components)
include_directories(${LLVM_INCLUDE_DIRS})
message("LLVM_INCLUDE_DIRS: " ${LLVM_INCLUDE_DIRS})
target_link_directories(dynamiclib PRIVATE "${LLVM_INCLUDE_DIRS}/../lib")
target_link_libraries(dynamiclib PRIVATE "${llvm_components}" ${CURSES_LIBRARIES})