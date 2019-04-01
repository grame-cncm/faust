# Dynamic compiler usage, benchmark, tracing and optimizing tools 

Several programs and tools are available to test the dynamic compilation chain, benchmark and trace the compiled programs. 

## dynamic-faust

The **dynamic-faust** tool uses the dynamic compilation chain, and compiles a Faust DSP source to a LLVM IR (.ll), bicode (.bc), machine code (.mc) or object code (.o) output file.

`dynamic-faust [-target xxx] [-opt (native|generic)] [additional Faust options (-vec -vs 8...)] foo.dsp`

Here are the available options:

- `-target xxx to cross-compile the code for a different architecture (like 'i386-apple-macosx10.6.0:opteron')`
- `-opt (native|generic) to discover and compile with the best compilation parameters`
- `-o foo.ll to generate a LLVM IR textual file`
- `-o foo.bc to generate a LLVM bitcode file`
- `-o foo.mc to generate a LLVM machine code file`
- `-o foo.o to generate a LLVM object code file`

## dynamic-jack-gtk

The **dynamic-jack-gtk** tool uses the dynamic compilation chain, compiles a Faust DSP source, and runs it with the LLVM or Interpreter backend. It can also read a precompiled DSP factory, either in IR (.ll), bitcode (.bc), or machine code (.mc) when using the LLVM backend, or byte code (.bc) when using the Interpreter backend.

`dynamic-jack-gtk [-llvm|interp] [-nvoices N] [-midi] [-osc] [-httpd] [additional Faust options (-vec -vs 8...)] foo.dsp/foo.fbc/foo.ll/foo.bc/foo.mc`

Here are the available options:

- `-llvm/interp to choose either LLVM or Interpreter backend`
- `-nvoices N to start the DSP in polyphonic mode with N voices`
- `-midi to activate MIDI control`
- `-osc to activate OSC control`
- `-httpd to activate HTTPD control`

Additional Faust compiler options can be given. Note that the Interpreter backend can be launched in *trace* mode, so that various statistics on the running code are collected and displayed while running and/or when closing the application. For developers, the *FAUST_INTERP_TRACE* environment variable can be set to values from 1 to 5 (see the **interp-trace** tool). 

## poly-dynamic-jack-gtk

The **poly-dynamic-jack-gtk** tool uses the dynamic compilation chain, compiles a Faust DSP source, activate the -effect auto model by default, and runs it with the LLVM or Interpreter backend.

`poly-dynamic-jack-gtk [-llvm|interp] [-nvoices N] [-midi] [-osc] [-httpd] [additional Faust options (-vec -vs 8...)] foo.dsp`

Here are the available options:

- `-llvm/interp to choose either LLVM or Interpreter backend`
- `-nvoices N to start the DSP in polyphonic mode with N voices`
- `-midi to activate MIDI control`
- `-osc to activate OSC control`
- `-httpd to activate HTTPD control`

Additional Faust compiler options can be given. Note that the Interpreter backend can be launched in *trace* mode, so that various statistics on the running code are collected and displayed while running and/or when closing the application. For developers, the *FAUST_INTERP_TRACE* environment variable can be set to values from 1 to 5 (see the **interp-trace** tool). 

## interp-tracer

The **interp-tracer** tool runs and instruments the compiled program using the Interpreter backend. Various statistics on the code are collected and displayed while running and/or when closing the application, typically FP_SUBNORMAL, FP_INFINITE and FP_NAN values, or INTEGER_OVERFLOW and DIV_BY_ZERO operations. Mode 4 and 5 allow to display the stack trace of the running code when FP_INFINITE, FP_NAN or INTEGER_OVERFLOW values are produced. The -control mode allows to check control parameters, by explicitly setting their *min* and *max* values (for now).

`interp-tracer [-trace <1-7>] [-control] [-output] [additional Faust options (-ftz xx)] foo.dsp`

Here are the available options:

 - `-control to activate min/max control check`
 - `-output to print output frames`
 - `-trace 1 to collect FP_SUBNORMAL only` 
 - `-trace 2 to collect FP_SUBNORMAL, FP_INFINITE and FP_NAN`
 - `-trace 3 to collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW and DIV_BY_ZERO`
 - `-trace 4 to collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW, DIV_BY_ZERO and LOAD errors, fails at first FP_INFINITE, FP_NAN or LOAD error`
 - `-trace 5 to collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW, DIV_BY_ZERO and LOAD errors, continue after FP_INFINITE, FP_NAN or LOAD error`
 - `-trace 6 to only check LOAD errors and continue`
 - `-trace 7 to only check LOAD errors and exit`

## faustbench

The **faustbench** tool uses the C++ backend to generate a set of C++ files produced with different Faust compiler options. All files are then compiled in a unique binary that will measure DSP CPU of all versions of the compiled DSP. The tool is supposed to be launched in a terminal, but it can be used to generate an iOS project, ready to be launched and tested in Xcode. 

`faustbench [-notrace] [-generic] [-ios] [-single] [-fast] [-run <num>] [-opt <level(0..3|-1)>] [-double] [additional Faust options (-vec -vs 8...)] foo.dsp` 

Here are the available options:

 - `-notrace to only generate the best compilation parameters`
 - `-generic' to compile for a generic processor, otherwise -march=native will be used`
 - `-ios to generate an iOS project`
 - `-single to only execute the scalar test`
 - `-fast to only execute some tests`
 - `-run <num> to execute each test <num> times`
 - `-opt <level (0..3|-1)>' to pass an optimisation level to c++ (-1 means "maximal level =-Ofast for now" if range changes in the future)`
 - `-double to compile DSP in double and set FAUSTFLOAT to double`

Use `export CXX=/path/to/compiler` before running faustbench to change the C++ compiler, and `export CXXFLAGS=options` to change the C++ compiler options. Additional Faust compiler options can be given.

## faustbench-llvm

The **faustbench-llvm** tool uses the libfaust library and its LLVM backend to dynamically compile DSP objects produced with different Faust compiler options, and then measure their DSP CPU. Additional Faust compiler options can be given beside the ones that will be automatically explored by the tool.

`faustbench-llvm [-notrace] [-generic] [-single] [-run <num] [-opt <level(0..4|-1)>] [additional Faust options (-vec -vs 8...)] foo.dsp` 

Here are the available options:

- `-notrace to only generate the best compilation parameters`
- `-generic to compile for a generic processor, otherwise the native CPU will be used`
- `-single to only scalar test`
- `-run <num> to execute each test <num> times`
- `-opt <level>' to pass an optimisation level to LLVM, between 0 and 4 (-1 means "maximal level" if range changes in the future)`

## faustbench-wasm

The **faustbench-wasm** tool tests a given DSP program in [node.js](https://nodejs.org/en/), comparing with a [Binaryen](https://github.com/WebAssembly/binaryen) optimized version of the wasm module.

`faustbench-wasm foo.wasm` 

## faust2benchwasm

The **faust2benchwasm** tool generates an HTML page embedding benchmark code, to be tested in browsers, and displaying the performances as MBytes/sec and DSP CPU use.

`faust2benchwasm [-opt] [-html] [-emcc] [-jsmem] [additional Faust options (-ftz 2...)] foo.dsp` 

Here is the available options:

- `-opt to optimize the wasm module using Binaryen tools`
- `-html to generate a ready to use HTML test page`
- `-emcc to compile the generated C code with Emscripten (still experimental)`
- `-jsmem to generate a wasm module and wrapper code using JavaScript side allocated wasm memory`

