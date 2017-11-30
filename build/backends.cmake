# this file may be used to select different backends
# it's always read by the default makefile target

set ( ASMJS_BACKEND  ON  CACHE BOOL  "Include ASMJS backend" 	FORCE )
set ( C_BACKEND 	 ON  CACHE BOOL  "Include C backend" 		FORCE )
set ( CPP_BACKEND 	 ON  CACHE BOOL  "Include CPP backend" 		FORCE )
set ( FIR_BACKEND	 ON  CACHE BOOL  "Include FIR backend" 		FORCE )
set ( INTERP_BACKEND OFF  CACHE BOOL  "Include INTERPRETER backend" FORCE )
set ( JAVA_BACKEND	 ON  CACHE BOOL  "Include JAVA backend"		FORCE )
set ( JS_BACKEND	 ON  CACHE BOOL  "Include JAVASCRIPT backend" FORCE )
set ( LLVM_BACKEND	 OFF CACHE BOOL  "Include LLVM backend"		FORCE )
set ( OLDCPP_BACKEND ON  CACHE BOOL  "Include old CPP backend"	FORCE )
set ( RUST_BACKEND	 ON  CACHE BOOL  "Include RUST backend" 	FORCE )
set ( WASM_BACKEND	 ON  CACHE BOOL  "Include WASM backend"		FORCE )
