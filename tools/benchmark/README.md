# Dynamic compiler usage, benchmark, tracing and optimizing tools 

Several programs and tools are available to test the dynamic compilation chain, benchmark and trace the compiled programs. 

## dynamic-faust

The **dynamic-faust** tool uses the dynamic compilation chain, and compiles a Faust DSP source to a LLVM IR (.ll), bicode (.bc), machine code (.mc) or object code (.o) output file.

`dynamic-faust [-target xxx] [-opt (native|generic)] [additional Faust options (-vec -vs 8...)] foo.dsp`

Here are the available options:

- `-target xxx to cross-compile the code for a different architecture (like 'i386-apple-macosx10.6.0:opteron')`
- `-opt (native|generic) to discover and compile with the best compilation parameters`
- `-o foo.ll to generate an LLVM IR textual file`
- `-o foo.bc to generate an LLVM bitcode file`
- `-o foo.mc to generate an LLVM machine code file`
- `-o foo.o to generate an object code file`

## dynamic-jack-gtk

The **dynamic-jack-gtk** tool uses the dynamic compilation chain, compiles a Faust DSP source, and runs it with the LLVM or Interpreter backend. It can also read a precompiled DSP factory, either in IR (.ll), bitcode (.bc), or machine code (.mc) when using the LLVM backend, or byte code (.bc) when using the Interpreter backend.

`dynamic-jack-gtk [-llvm|interp] [-nvoices N] [-midi] [-osc] [-httpd] [-resample] [additional Faust options (-vec -vs 8...)] foo.dsp/foo.fbc/foo.ll/foo.bc/foo.mc`

Here are the available options:

- `-llvm/interp to choose either LLVM or Interpreter backend`
- `-nvoices N to start the DSP in polyphonic mode with N voices`
- `-midi to activate MIDI control`
- `-osc to activate OSC control`
- `-httpd to activate HTTPD control`
- `-resample' to resample soundfiles to the audio driver sample rate`

Additional Faust compiler options can be given. Note that the Interpreter backend can be launched in *trace* mode, so that various statistics on the running code are collected and displayed while running and/or when closing the application. For developers, the *FAUST_INTERP_TRACE* environment variable can be set to values from 1 to 7 (see the **interp-trace** tool). 

## poly-dynamic-jack-gtk

The **poly-dynamic-jack-gtk** tool uses the dynamic compilation chain, compiles a Faust DSP source, activate the -effect auto model by default, and runs it with the LLVM or Interpreter backend.

`poly-dynamic-jack-gtk [-llvm|interp] [-nvoices N] [-midi] [-osc] [-httpd] [-resample] [additional Faust options (-vec -vs 8...)] foo.dsp`

Here are the available options:

- `-llvm/interp to choose either LLVM or Interpreter backend`
- `-nvoices N to start the DSP in polyphonic mode with N voices`
- `-midi to activate MIDI control`
- `-osc to activate OSC control`
- `-httpd to activate HTTPD control`
- `-resample' to resample soundfiles to the audio driver sample rate`

Additional Faust compiler options can be given. Note that the Interpreter backend can be launched in *trace* mode, so that various statistics on the running code are collected and displayed while running and/or when closing the application. For developers, the *FAUST_INTERP_TRACE* environment variable can be set to values from 1 to 7 (see the **interp-trace** tool). 

## dynamic-machine-jack-gtk

The **dynamic-machine-jack-gtk** tool runs a previously compiled Faust program (as FBC, that is as 'Faust Byte Code') in the Interpreter backend, configurated to use the FBC => LLVM IR => executable code chain. 

`dynamic-machine-jack-gtk [-nvoices N] [-midi] [-osc] [-httpd] foo.fbc`

Here are the available options:

- `-nvoices N to start the DSP in polyphonic mode with N voices`
- `-midi to activate MIDI control`
- `-osc to activate OSC control`
- `-httpd to activate HTTPD control`

## interp-tracer

The **interp-tracer** tool runs and instruments the compiled program using the Interpreter backend. Various statistics on the code are collected and displayed while running and/or when closing the application, typically FP_SUBNORMAL, FP_INFINITE and FP_NAN values, or INTEGER_OVERFLOW and DIV_BY_ZERO operations. Mode 4 and 5 allow to display the stack trace of the running code when FP_INFINITE, FP_NAN or INTEGER_OVERFLOW values are produced. The -control mode allows to check control parameters, by explicitly setting their *min* and *max* values (for now).

`interp-tracer [-trace <1-7>] [-control] [-output] [additional Faust options (-ftz xx)] foo.dsp`

Here are the available options:

 - `-control to activate min/max control check`
 - `-output to print output frames`
 - `-trace 1 to collect FP_SUBNORMAL only` 
 - `-trace 2 to collect FP_SUBNORMAL, FP_INFINITE and FP_NAN`
 - `-trace 3 to collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW and DIV_BY_ZERO`
 - `-trace 4 to collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW, DIV_BY_ZERO and LOAD/STORE errors, fails at first FP_INFINITE, FP_NAN or LOAD/STORE error`
 - `-trace 5 to collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW, DIV_BY_ZERO and LOAD/STORE errors, continue after FP_INFINITE, FP_NAN or LOAD/STORE error`
 - `-trace 6 to only check LOAD/STORE errors and continue`
 - `-trace 7 to only check LOAD/STORE errors and exit`

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
- `-single to only execute the scalar test`
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

## faust-tester

The **faust-tester** tool allows to test a Faust effect DSP with test input signals, like dirac impulse or periodic pulses.

`faust-tester [-imp] [-pulse] foo.dsp` 

Here is the available options:

- `-imp to test with an dirac impulse`
- `-pulse to test with a periodic pulse`

## faust-osc-controller

The **faust-osc-controller** tool allows to control an OSC aware Faust running program (that is a DSP program possibly compiled with *faust2xx* and the *-osc* option). It will ask the program for its JSON description to build a "proxy" User Interface to control the distant program. Communications can be bi-directionnal, so that the proxy controler can display output control values coming from the distant program (like bargraphs for instance). 

`faust-osc-controller root [-port <port>] [-outport <port>]` 

Set root to the OSC program name (like '/freeverb'). Then use the available options:

- `-port <port> to set the OSC input port`
- `-outport <port>' to set the OSC output port`

Note that the OSC *input port* of the **faust-osc-controller** tool has to be the *output port* of the controlled program. And the OSC *output port* of the **faust-osc-controller** tool has to be the *input port* of the controlled program. The controler and controlled programs both have to send messages using the -xmit (1|2) parameter, depending if you use real paths or aliases.

Example:

- launch the remote program with `clarinetMIDI -port 5000 -outport 5001 -xmit 1`. Look at the OSC 'root' name that may be a bit different. 
- then start the controller tool like with: `faust-osc-controller /clarinet -port 5001 -outport 5000 -xmit 1`

