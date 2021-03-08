# regular.cmake : this file selects only some backends. But it has the advantage of not
# requiring LLVM, a large dependency.
# Possible configuration values are among: 
#    OFF       don't include the backend
#    COMPILER  embed the backend in the faust compiler
#    STATIC    embed the backend in the faust static library
#    DYNAMIC   embed the backend in the faust dynamic library
#    WASM      embed the backend in the faust wasm library

set ( C_BACKEND      COMPILER STATIC DYNAMIC CACHE STRING  "Include C backend" FORCE )
set ( CPP_BACKEND    COMPILER STATIC DYNAMIC CACHE STRING  "Include CPP backend" FORCE )
set ( FIR_BACKEND                        OFF CACHE STRING  "Include FIR backend" FORCE )
set ( INTERP_BACKEND                     OFF CACHE STRING  "Include INTERPRETER backend" FORCE )
set ( JAVA_BACKEND   COMPILER STATIC DYNAMIC CACHE STRING  "Include JAVA backend" FORCE )
set ( LLVM_BACKEND                       OFF CACHE STRING  "Include LLVM backend" FORCE )
set ( CSHARP_BACKEND COMPILER STATIC DYNAMIC CACHE STRING  "Include CSharp backend" FORCE )
set ( OLDCPP_BACKEND COMPILER STATIC DYNAMIC CACHE STRING  "Include old CPP backend" FORCE )
set ( RUST_BACKEND   COMPILER STATIC DYNAMIC CACHE STRING  "Include RUST backend" FORCE )
set ( SOUL_BACKEND   COMPILER STATIC DYNAMIC CACHE STRING  "Include SOUL backend"      FORCE )
set ( WASM_BACKEND   WASM COMPILER STATIC DYNAMIC CACHE STRING  "Include WASM backend" FORCE )
set ( DLANG_BACKEND  COMPILER STATIC DYNAMIC CACHE STRING  "Include DLANG backend"     FORCE )
