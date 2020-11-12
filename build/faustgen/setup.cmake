# this file may be used to select different backends
# it's always read by the default makefile target
# values are among: 
#    OFF       don't include the backend
#    COMPILER  embed the backend in the faust compiler
#    STATIC    embed the backend in the faust static library
#    DYNAMIC   embed the backend in the faust dynamic library
#    ASMJS     embed the backend in the faust asmjs library
#    WASM      embed the backend in the faust wasm library


set ( ASMJS_BACKEND  OFF ASMJS  CACHE STRING  "Include ASMJS backend" FORCE )
set ( C_BACKEND      OFF        CACHE STRING  "Include C backend"         FORCE )
set ( CPP_BACKEND    COMPILER STATIC CACHE STRING  "Include CPP backend"       FORCE )
set ( FIR_BACKEND    OFF        CACHE STRING  "Include FIR backend"       FORCE )
set ( INTERP_BACKEND OFF        CACHE STRING  "Include INTERPRETER backend" FORCE )
set ( JAVA_BACKEND   OFF        CACHE STRING  "Include JAVA backend"      FORCE )
set ( JS_BACKEND     OFF        CACHE STRING  "Include JAVASCRIPT backend" FORCE )
set ( LLVM_BACKEND   COMPILER STATIC CACHE STRING  "Include LLVM backend"      FORCE )
set ( OLDCPP_BACKEND OFF        CACHE STRING  "Include old CPP backend"   FORCE )
set ( RUST_BACKEND   OFF        CACHE STRING  "Include RUST backend"      FORCE )
set ( WASM_BACKEND   OFF WASM   CACHE STRING  "Include WASM backend"  FORCE )
set ( DLANG_BACKEND  OFF        CACHE STRING  "Include DLANG backend" FORCE )

set ( INCLUDE_EXECUTABLE  ON   CACHE STRING  "Include faust compiler" FORCE )
set ( INCLUDE_STATIC      ON   CACHE STRING  "Include static faust library" FORCE )
set ( INCLUDE_DYNAMIC     OFF  CACHE STRING  "Include dynamic faust library" FORCE )
set ( INCLUDE_OSC         ON   CACHE STRING  "Include Faust OSC static library" FORCE )
set ( INCLUDE_HTTP        ON   CACHE STRING  "Include Faust HTTPD library" FORCE )
set ( OSCDYNAMIC          OFF  CACHE STRING  "Include Faust OSC dynamic library" FORCE )
set ( HTTPDYNAMIC         OFF  CACHE STRING  "Include Faust HTTP dynamic library" FORCE )
set ( INCLUDE_ITP         OFF  CACHE STRING  "Include Faust Machine library" FORCE )
set ( ITPDYNAMIC          OFF  CACHE STRING  "Include Faust Machine library" FORCE )
