# jax-only.cmake : build Faust with only the JAX backend, i.e. its two
# framework variants -- NNX (flax.nnx) and Linen (flax.linen). Every other
# backend is disabled.
#
# Possible configuration values are among:
#    OFF       don't include the backend
#    COMPILER  embed the backend in the faust compiler
#    STATIC    embed the backend in the faust static library
#    DYNAMIC   embed the backend in the faust dynamic library
#    WASM      embed the backend in the faust wasm library

set ( AS_BACKEND           OFF                             CACHE STRING  "Include AssemblyScript backend"  FORCE )
set ( C_BACKEND            OFF                             CACHE STRING  "Include C backend"               FORCE )
set ( CODEBOX_BACKEND      OFF                             CACHE STRING  "Include Codebox backend"         FORCE )
set ( CPP_BACKEND          OFF                             CACHE STRING  "Include CPP backend"             FORCE )
set ( CMAJOR_BACKEND       OFF                             CACHE STRING  "Include Cmajor backend"          FORCE )
set ( CSHARP_BACKEND       OFF                             CACHE STRING  "Include CSharp backend"          FORCE )
set ( DLANG_BACKEND        OFF                             CACHE STRING  "Include Dlang backend"           FORCE )
set ( FIR_BACKEND          OFF                             CACHE STRING  "Include FIR backend"             FORCE )
set ( INTERP_BACKEND       OFF                             CACHE STRING  "Include Interpreter backend"     FORCE )
set ( JAVA_BACKEND         OFF                             CACHE STRING  "Include JAVA backend"            FORCE )
set ( JSFX_BACKEND         OFF                             CACHE STRING  "Include JSFX backend"            FORCE )
set ( JULIA_BACKEND        OFF                             CACHE STRING  "Include Julia backend"           FORCE )
set ( LINEN_BACKEND        COMPILER STATIC DYNAMIC         CACHE STRING  "Include Linen backend"           FORCE )
set ( LLVM_BACKEND         OFF                             CACHE STRING  "Include LLVM backend"            FORCE )
set ( NNX_BACKEND          COMPILER STATIC DYNAMIC         CACHE STRING  "Include NNX backend"             FORCE )
set ( OLDCPP_BACKEND       OFF                             CACHE STRING  "Include old CPP backend"          FORCE )
set ( RUST_BACKEND         OFF                             CACHE STRING  "Include Rust backend"             FORCE )
set ( SDF3_BACKEND         OFF                             CACHE STRING  "Include SDF3 backend"             FORCE )
set ( TEMPLATE_BACKEND     OFF                             CACHE STRING  "Include Template backend"         FORCE )
set ( VHDL_BACKEND         OFF                             CACHE STRING  "Include VHDL backend"             FORCE )
set ( WASM_BACKEND         OFF                             CACHE STRING  "Include WASM backend"             FORCE )
