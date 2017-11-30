set ( ASMJS_BACKEND  OFF  CACHE BOOL  "Include ASMJS backend" 	FORCE )
set ( C_BACKEND 	 OFF  CACHE BOOL  "Include C backend" 		FORCE )
set ( CPP_BACKEND 	 OFF  CACHE BOOL  "Include CPP backend" 		FORCE )
set ( FIR_BACKEND	 OFF  CACHE BOOL  "Include FIR backend" 		FORCE )
set ( INTERP_BACKEND OFF  CACHE BOOL  "Include INTERPRETER backend" FORCE )
set ( JAVA_BACKEND	 OFF  CACHE BOOL  "Include JAVA backend"		FORCE )
set ( JS_BACKEND	 OFF  CACHE BOOL  "Include JAVASCRIPT backend" FORCE )
set ( LLVM_BACKEND	 OFF CACHE BOOL  "Include LLVM backend"		FORCE )
set ( OLDCPP_BACKEND OFF  CACHE BOOL  "Include old CPP backend"	FORCE )
set ( RUST_BACKEND	 OFF  CACHE BOOL  "Include RUST backend" 	FORCE )
set ( WASM_BACKEND	 OFF  CACHE BOOL  "Include WASM backend"	FORCE )


### don't change the lines below
set ( LIBSTATIC	 	OFF  CACHE BOOL  "Disable static library"	FORCE )
set ( LIBSHARED	 	OFF  CACHE BOOL  "Disable shared library"	FORCE )
set ( COMPILER	 	OFF  CACHE BOOL  "Disable compiler"	FORCE )

set ( CMAKE_OSX_DEPLOYMENT_TARGET	"" 		CACHE STRING "Intended to disabled OSX specific options" FORCE)
set ( CMAKE_OSX_SYSROOT 			"" 		CACHE STRING "Intended to disabled OSX specific options" FORCE)
set ( CMAKE_CXX_COMPILER 		  	"emcc" 	CACHE STRING "Use emscripten compiler" FORCE)
