# regular.cmake : this file selects only some backends. But it has the advantage of not
# requiring LLVM, a large dependency.
# Possible configuration values are among: 
#    OFF       don't include the backend
#    COMPILER  embed the backend in the faust compiler
#    STATIC    embed the backend in the faust static library
#    DYNAMIC   embed the backend in the faust dynamic library
#    WASM      embed the backend in the faust wasm library

set ( C_BACKEND      COMPILER STATIC DYNAMIC      CACHE STRING  "Include C backend" FORCE )
set ( CODEBOX_BACKEND      COMPILER STATIC DYNAMIC      CACHE STRING  "Include Codebox backend" FORCE )
set ( CPP_BACKEND    COMPILER STATIC DYNAMIC      CACHE STRING  "Include CPP backend" FORCE )
# To generate libfaust.wasm including Cmajor
set ( CMAJOR_BACKEND COMPILER STATIC DYNAMIC WASM CACHE STRING  "Include Cmajor backend" FORCE )
#set ( CMAJOR_BACKEND COMPILER STATIC DYNAMIC      CACHE STRING  "Include Cmajor backend" FORCE )
set ( CSHARP_BACKEND COMPILER STATIC DYNAMIC      CACHE STRING  "Include CSharp backend" FORCE )
set ( DLANG_BACKEND  COMPILER STATIC DYNAMIC      CACHE STRING  "Include Dlang backend" FORCE )
set ( FIR_BACKEND                        OFF      CACHE STRING  "Include FIR backend" FORCE )
set ( INTERP_BACKEND                     OFF      CACHE STRING  "Include Interpreter backend" FORCE )
set ( JAVA_BACKEND   COMPILER STATIC DYNAMIC      CACHE STRING  "Include JAVA backend" FORCE )
set ( JAX_BACKEND    COMPILER STATIC DYNAMIC      CACHE STRING  "Include JAX backend"  FORCE )
set ( JULIA_BACKEND  COMPILER STATIC DYNAMIC      CACHE STRING  "Include Julia backend" FORCE )
set ( JSFX_BACKEND  COMPILER STATIC DYNAMIC CACHE STRING  "Include JSFX backend" FORCE )
set ( LLVM_BACKEND                       OFF      CACHE STRING  "Include LLVM backend" FORCE )
set ( OLDCPP_BACKEND COMPILER STATIC DYNAMIC      CACHE STRING  "Include old CPP backend" FORCE )
set ( RUST_BACKEND   COMPILER STATIC DYNAMIC      CACHE STRING  "Include Rust backend" FORCE )
set ( SDF3_BACKEND   COMPILER STATIC DYNAMIC        CACHE STRING  "Include SDF3 backend"      FORCE )
# Template is deactivated 
set ( TEMPLATE_BACKEND                   OFF      CACHE STRING  "Include Template backend" FORCE )
set ( VHDL_BACKEND   COMPILER STATIC DYNAMIC      CACHE STRING  "Include VHLD backend" FORCE )
set ( WASM_BACKEND   COMPILER STATIC DYNAMIC WASM CACHE STRING  "Include WASM backend" FORCE )
