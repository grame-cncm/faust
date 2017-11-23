# Dynamic compiler usage, benchmark and optimizing tools 

Several programs and tools are available to test the dynamic compilation chain and benchmark the compiled programs. 

## dynamic-jack-gtk

The **dynamic-jack-gtk** tool uses the dynamic compilation chain, compiles a Faust DSP source, and runs it with the LLVM or Interpreter backend.

`dynamic-jack-gtk [-llvm/interp] [-nvoices N] [-midi] [-osc] [-httpd] [additional Faust options (-vec -vs 8...)] foo.dsp`

Here are the available options:

- `-llvm/interp to choose either LLVM or Interpreter backend`
- `-nvoices N to start the DSP in polyphonic mode with N voices`
- `-midi to activate MIDI control`
- `-osc to activate OSC control`
- `-httpd to activate HTTPD control`

Additional Faust compiler options can be given. Note that the Interpreter backend can be launched in *trace* mode, so that various statistics on the running code are collected and displayed when closing the application. For developers: trace mode is activated by setting the *FAUST_INTERP_TRACE* environment variable to "on". Then *FAUST_INTERP_TRACE_MODE* environment variable can be set to values from 1 to 3: 

 - 1 mode collects the number of FP_SUBNORMAL values generated in the audio computation (not that you'll have to deactivate hardware flush-to-zero protection, typically by removing the AVOIDDENORMALS macro added arround the call to the DSP compute method in architecture files)
 - 2 mode also collects the number of FP_INFINITE and FP_NAN float values
 - 3 mode also collects the number of INTEGER_OVERFLOW and DIV_BY_ZERO operations

## faustbench

The **faustbench** uses the C++ backend to generate a set of C++ files produced with different Faust compiler options. All files are then compiled in a unique binary that will measure DSP CPU of all versions of the compiled DSP. The tool is supposed to be launched in a terminal, but it can be used to generate an iOS project, ready to be launched and tested in Xcode. 

`faustbench [-ios] [-single] [-fast] [-run <num>] [-double] [additional Faust options (-vec -vs 8...)] foo.dsp` 

Here are the available options:

 - `-ios to generate an iOS project`
 - `-single to only scalar test`
 - `-fast to onlyexecute  some tests`
 - `-run <num> to execute each test <num> times`
 - `-double to compile DSP in double and set FAUSTFLOAT to double`

Use `export CXX=/path/to/compiler` before running faustbench to change the C++ compiler, and `export CXXFLAGS=options` to change the C++ compiler options. Additional Faust compiler options can be given.

## faustbench-llvm

The **faustbench-llvm** tool uses the libfaust library and its LLVM backend to dynamically compile DSP objects produced with different Faust compiler options, and then measure their DSP CPU. Additional Faust comptiler options can be given beside the ones that will be automatically explored by the tool.

`faustbench-llvm [-single] [-run <num] [additional Faust options (-vec -vs 8...)] foo.dsp` 

Here are the available options:

- `-single to only scalar test`
- `-run <num> to execute each test <num> times`

## faustbench-wasm

The **faustbench-wasm** tool tests a given DSP program in [node.js](https://nodejs.org/en/), comparing with a [Binaryen](https://github.com/WebAssembly/binaryen) optimized version of the wasm module.

`faustbench-wasm foo.wasm` 

## faust2benchwasm

The **faust2benchwasm** tool generates an HTML page embedding benchmark code, to be tested in browsers, and displaying the performances as MBytes/sec and DSP CPU use.

`faust2benchwasm [-opt] [-html] [-emcc] foo.dsp` 

Here is the available option:

- `-opt to optimize the wasm module using Binaryen tools`
- `-html to generate a ready to use HTML test page`
- `-emcc to compile the generated C code with Emscripten (still experimental)`

