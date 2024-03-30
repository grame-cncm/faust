# Dynamic compiler usage, benchmark, tracing and optimizing tools 

Several programs and tools are available to test the dynamic compilation chain, benchmark and trace the compiled programs. 

## dynamic-faust

The **dynamic-faust** tool uses the dynamic compilation chain (based on the LLVM backend), and compiles a Faust DSP source to a LLVM IR (.ll), bicode (.bc), machine code (.mc) or object code (.o) output file. CPU cross-compilation can be done using the `-target` option. The best compilation options for the native CPU (at Faust compiler level) can be discovered using the `-opt` option. When compiling to object code, the resulting file can be used with the appropriate [llvm-dsp-adapter.h](https://github.com/grame-cncm/faust/blob/master-dev/architecture/faust/dsp/llvm-dsp-adapter.h) or [llvm-dsp-adapter.1h](https://github.com/grame-cncm/faust/blob/master-dev/architecture/faust/dsp/llvm-dsp-adapter1.h) wrapper file to obtain a ready to use DSP object to be added in the final project. 

`dynamic-faust [-target xxx] [-opt native|generic] [-o foo.ll|foo.bc|foo.mc|foo.o] [additional Faust options (-vec -vs 8...)] foo.dsp`

Here are the available options:

- `-target xxx to cross-compile the code for a different architecture (like 'x86_64-apple-darwin15.6.0:haswell')`
- `-opt native to activate the best compilation options for the native CPU`
- `-opt generic to activate the best compilation options for a generic CPU`
- `-o foo.ll to generate an LLVM IR textual file`
- `-o foo.bc to generate an LLVM bitcode file`
- `-o foo.mc to generate an LLVM machine code file`
- `-o foo.o to generate an object code file`

## faust2object

The **faust2object** tool  either uses the standard C++ compiler or the LLVM dynamic compilation chain (the **dynamic-faust** tool) to compile a Faust DSP to object code files (.o) and wrapper C++ header files for different CPUs. The DSP name is used in the generated C++ and object code files, thus allowing to generate distinct versions of the code that can finally be linked together in a single binary. Using a C++ wrapper, the DSP can be downsampled of upsampled by a factor, with a filter going from 0 (= no filter), then 1 (lower quality) to 4 (better quality).

`faust2object [nocona] [core2] [penryn] [bonnell] [atom] [silvermont] [slm] [goldmont] [goldmont-plus] [tremont] [nehalem] [corei7] [westmere] [sandybridge] [corei7-avx] [ivybridge] [core-avx-i] [haswell] [core-avx2] [broadwell] [skylake] [skylake-avx512] [skx] [cascadelake] [cooperlake] [cannonlake] [icelake-client] [icelake-server] [tigerlake] [knl] [knm] [k8] [athlon64] [athlon-fx] [opteron] [k8-sse3] [athlon64-sse3] [opteron-sse3] [amdfam10] [barcelona] [btver1] [btver2] [bdver1] [bdver2] [bdver3] [bdver4] [znver1] [znver2] [x86-64] [generic] [-all] [-soundfile] [-sources] [-multi] [-multifun] [-opt native|generic] [-llvm] [-test] [-us <factor>] [-ds <factor>] [-filter <filter(0..4)>] [additional Faust options (-vec -vs 8...)] <file.dsp>`

Here are the available options:

- `'xxx' to compile for 'xxx' CPU`
- `generic to compile for generic CPU`
- `-all to compile for all CPUs`
- `-soundfile when compiling a DSP using the 'soundfile' primitive, add required resources`
- `-sources' to only generate source files`
- `-multi to compile for several CPUs and aggregate them in a 'multi' class that choose the correct one at runtime`
- `-multifun to compile for several CPUs using GCC MultiFun feature and aggregate them in a 'multi' class that choose the correct one at runtime`
- `-opt native to activate the best compilation options for the native CPU`
- `-opt generic to activate the best compilation options for a generic CPU`
- `-llvm to compile using the LLVM backend, otherwise the C++ backend is used`
- `-test to compile a test program which will bench the DSP and render it`
- `-us <factor> to upsample the DSP by a factor (can be 2, 3, 4, 8, 16, 32)`
- `-ds <factor> to downsample the DSP by a factor (can be 2, 3, 4, 8, 16, 32)`
- `-filter <filter> for upsampling or downsampling [0..4], 0 means no filtering`


A set of header and object code files will be generated, and will have to be added in the final project. The header file typically contains the `<DSPName><CPU>` class and a `create<DSPName><CPU>` function needed to create a DSP instance (for instance compiling a `noise.dsp` DSP for a generic CPU will generate the `createnoisegeneric()` creation function). The `-opt native|generic` option runs the **faustbench-llvm** to discover the best possible compilation options and use them in the C++ or LLVM compilation step.

The `-multi` mode generates an additional header file (like `<DSPName>multi.h`, containing a `<DSPName>multi` class) that will dynamically load and instantiate the correct code for the machine CPU (or a generic version if the given CPU is not supported). An instance of this aggregation class will have to be created at runtime (like with `dsp* dsp = new<DSPName>multi();`  or  `dsp* dsp = create<DSPName>multi();`) to load the appropriate object code version depending on the running machine CPU. 

The `-multifun` mode uses the GCC [multiversion feature](https://gcc.gnu.org/wiki/FunctionMultiVersioning) to generate an additional header file (like `<DSPName>multi.h`, containing a `<DSPName>multi` class) that will dynamically load and instantiate the correct code for the machine CPU (or a generic version if the given CPU is not supported). An instance of this aggregation class will have to be created at runtime (like with `dsp* dsp = new<DSPName>multi();`  or  `dsp* dsp = create<DSPName>multi();`) to load the appropriate object code version depending on the running machine CPU. The list of CPUs to be compiled for must be defined in the `FAUST_ARCHS` environment variable.

Note that this code uses the [LLVM](https://llvm.org) `llvm::sys::getHostCPUName()` function to discover the machine CPU. Thus the LLVM tool chain has to be installed, and the `llvm-config --ldflags --libs all --system-libs` command will typically have to be used at link time to add the needed LLVM libraries, along with `-dead_strip` to only keep what is really mandatory in the final binary.

When used with the `-source` option, the `-DSOUNDFILE` and `pkg-config --cflags sndfile` flags have to be added to compile the generated C++ files, and `pkg-config --static --libs` sndfile has to be added at link time.

The `-test` parameter can be used to compile a test program which will bench the DSP, print its UI, and render it.

Note that using the `-inj foo.cpp` option allows to compile any C++ class containing a `dsp` subclass (which **must** be named `mydsp`), so for instance a manually written C++ class. This is a convenient way to optimise any C++ DSP class. 

 Examples:

 - create multi-cpu files using the C++ backend (giving an explicit list of supported CPUs), and then compile them as object files: `faust2object haswell core2 foo.dsp`. 
 - create multi-cpu files using the LLVM backend (giving an explicit list of supported CPUs), and then compile them as object files: `faust2object -llvm haswell core2 foo.dsp`. 
 - create multi-cpu files for all possible CPUs using C++ backend, and then compile them as object files: `faust2object -all foo.dsp`. 
 - create multi-cpu files for all possible CPUs and the multi-loader file, and them compile them as object files: `faust2object -all -multi foo.dsp`. 
 - create multi-cpu files for all possible CPUs and the multi-loader file, them compile them as object files, and compile a test program: `faust2object -all -multi -test foo.dsp`. 
 - define the `FAUST_ARCHS` environment variable, create a multi-cpu file for all possible CPUs defined in this variable and create the multi-loader file: `export FAUST_ARCHS="core2 haswell" && faust2object -sources -multifun foo.dsp`. 
 - define the `FAUST_ARCHS` environment variable, create a multi-cpu file for all possible CPUs defined in this variable and create the multi-loader file, and compile a test program: `export FAUST_ARCHS="core2 haswell" && faust2object -multifun -test foo.dsp`. 
 - compile a `foo.cpp` file (possibly manually written) and containing the `mydsp` class: `faust2object haswell -inj foo.cpp -multi -test foo.dsp`. 

## dynamic-jack-gtk/dynamic-coreaudio-gtk

The **dynamic-jack-gtk/dynamic-coreaudio-gtk** tools use the dynamic compilation chain, compile a Faust DSP source, and run it with the LLVM or Interpreter backend. They can also read a precompiled DSP factory, either in IR (.ll), bitcode (.bc), or machine code (.mc) when using the LLVM backend, or byte code (.fbc) when using the Interpreter backend. The `-edit` option can be used to start an *edit/compile/run loop* where the DSP can be edited with an external editor, will be recompiled on the fly each time it changes, and then executed. 

`dynamic-jack-gtk|dynamic-coreaudio-gtk [-llvm|interp] [-edit] [-generic] [-nvoices <num>] [-all] [-midi] [-osc] [-httpd] [-resample] [additional Faust options (-vec -vs 8...)] foo.dsp/foo.ll/foo.bc/foo.mc/foo.fbc`

Here are the available options:

- `-llvm' to use LLVM backend, using either .dsp, .ll, .bc or .mc files`
- `-interp' to use Interpreter backend, using either .dsp or .fbc (Faust Byte Code) files)`
- `-edit' to start an edit/compile/run loop, using a foo.dsp kind of source file`
- `-generic to JIT for a generic CPU (otherwise 'native' mode is used)`
- `-nvoices <num> to start the DSP in polyphonic mode with <num> voices`
- `-all' to active the 'all voices always playing' mode when polyphony is used`
- `-midi to activate MIDI control`
- `-osc to activate OSC control`
- `-httpd to activate HTTPD control`
- `-resample' to resample soundfiles to the audio driver sample rate`

Additional Faust compiler options can be given. Note that the Interpreter backend can be launched in *trace* mode, so that various statistics on the running code are collected and displayed while running and/or when closing the application. For developers, the *FAUST_INTERP_TRACE* environment variable can be set to values from 1 to 7 (see the [interp-tracer](#interp-tracer) tool). 

## poly-dynamic-jack-gtk

The **poly-dynamic-jack-gtk** tool uses the dynamic compilation chain, compiles a Faust DSP source, activate the -effect auto model by default, and runs it with the LLVM or Interpreter backend.

`poly-dynamic-jack-gtk [-llvm|interp] [-nvoices <num>] [-midi] [-osc] [-httpd] [-resample] [additional Faust options (-vec -vs 8...)] foo.dsp`

Here are the available options:

- `-llvm/interp to choose either LLVM or Interpreter backend`
- `-nvoices <num> to start the DSP in polyphonic mode with <num> voices`
- `-midi to activate MIDI control`
- `-osc to activate OSC control`
- `-httpd to activate HTTPD control`
- `-resample' to resample soundfiles to the audio driver sample rate`

Additional Faust compiler options can be given. Note that the Interpreter backend can be launched in *trace* mode, so that various statistics on the running code are collected and displayed while running and/or when closing the application. For developers, the *FAUST_INTERP_TRACE* environment variable can be set to values from 1 to 7 (see the **interp-trace** tool). 

## dynamic-machine-jack-gtk

The **dynamic-machine-jack-gtk** tool runs a previously compiled Faust program (as FBC, that is as 'Faust Byte Code') in the Interpreter backend, configurated to use the FBC => LLVM IR => executable code chain. 

`dynamic-machine-jack-gtk [-nvoices <num>] [-midi] [-osc] [-httpd] foo.fbc`

Here are the available options:

- `-nvoices <num> to start the DSP in polyphonic mode with <num> voices`
- `-midi to activate MIDI control`
- `-osc to activate OSC control`
- `-httpd to activate HTTPD control`

## interp-tracer

**Note** : In Faust, the interval calculation system on signals is supposed to detect possible problematic computations at compile time, and refuse to compile the corresponding DSP code. But **since the interval calculation is currently quite imperfect**, it can misbehave and generate possible problematic code, that will possibly crash at runtime. 

The **interp-tracer** tool runs and instruments the compiled program using the Interpreter backend. Various statistics on the code are collected and displayed while running and/or when closing the application, typically FP_SUBNORMAL, FP_INFINITE and FP_NAN values, or INTEGER_OVERFLOW, CAST_INT_OVERFLOW and DIV_BY_ZERO operations, or LOAD/STORE errors. 

- [FP_SUBNORMAL, FP_INFINITE and FP_NAN values](https://www.gnu.org/software/libc/manual/html_node/Floating-Point-Classes.html)(*) are produced when compiling with floating point numbers. 
- [INTEGER_OVERFLOW](https://en.wikipedia.org/wiki/Integer_overflow) is produced when computing with integer numbers (actually 32 bits Integer supported by the compiler) and producing out-of-range result. They can be a wanted effect like in the implementation of the [no.noise](https://github.com/grame-cncm/faustlibraries/blob/master/noises.lib#L63) generator.
- DIV_BY_ZERO(*) happens when dividing a number by 0. 
- [CAST_INT_OVERFLOW](https://frama-c.com/2013/10/09/Overflow-float-integer.html)(*) happen when converting a floating point number back in an integer number (like when using the `int(val)` expression). 
- NEGATIVE_BITSHIFT happen when doing bit shift operation with a right-hand negative value
- LOAD/STORE(*) happens when reading or writing outside of `rdtable` or `rwtable`, or when loading a non initialized value (typically used by the Faust compiler developers to check the generated code). 

(*) Those errors typically reveal incorrectly written code which must be corrected.

Mode 4 and 5 allow to display the stack trace of the running code when FP_INFINITE, FP_NAN, INTEGER_OVERFLOW, DIV_BY_ZERO, CAST_INT_OVERFLOW, NEGATIVE_BITSHIFT and LOAD/STORE errors are produced. 

The `-control` option allows to check control parameters, by explicitly setting their *min* and *max* values, then running the DSP and setting all controllers (inside their range) in a random way. 

The `-input` option allows to test effects by sending them an *impulse* then a *noise* test signal on all inputs. 

Mode 4 up to 7 also check LOAD/STORE errors, mode 7 is typically used by the Faust compiler developers to check the generated code. Mode 7 prints the program memory layout as `DumpMem-fooXXX.txt` file.

`interp-tracer [-trace <1-6>] [-control] [-output] [-timeout <num>] [additional Faust options (-ftz xx)] foo.dsp`

Here are the available options:

 - `-control to activate min/max control check then setting all controllers (inside their range) in a random way`
 - `-input to test effects with various test signals (impulse, noise)`
 - `-output to print output frames`
 - ` timeout <num> to stop the application after a given timeout in seconds (default = 10s)`
 - `-trace 1 to collect FP_SUBNORMAL only` 
 - `-trace 2 to collect FP_SUBNORMAL, FP_INFINITE and FP_NAN`
 - `-trace 3 to collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW, DIV_BY_ZERO and CAST_INT_OVERFLOW`
 - `-trace 4 to collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW, DIV_BY_ZERO, CAST_INT_OVERFLOW and LOAD/STORE errors, fails at first FP_INFINITE, FP_NAN, CAST_INT_OVERFLOW or LOAD/STORE error`
 - `-trace 5 to collect FP_SUBNORMAL, FP_INFINITE, FP_NAN, INTEGER_OVERFLOW, DIV_BY_ZERO, CAST_INT_OVERFLOW, NEGATIVE_BITSHIFT and LOAD/STORE errors, continue after FP_INFINITE, FP_NAN or CAST_INT_OVERFLOW, fails after LOAD/STORE errors`
 - `-trace 6 to only check LOAD/STORE errors and exit`
 
 Note that additional Faust compiler options can be used to check specific versions of the generated code. For instance even if the semantics of Faust is always strict, the generated code for `select2` is non-strict by default, and to save CPU, only one branch is computed depending of the condition. The `-sts` option can be used to force both branches to be computed, thus allowing to test both of them for misbehaving behaviours. 

## faustbench

The **faustbench** tool uses the C++ backend to generate a set of C++ files produced with different Faust compiler options. All files are then compiled in a unique binary that will measure the DSP CPU usage of all versions of the compiled DSP. The tool is supposed to be launched in a terminal, but it can be used to generate an iOS project, ready to be launched and tested in Xcode. Using the `-source` option allows to create and keep the intermediate C++ files, with a Makefile to produce the binary. The generated DSP struct memory size in bytes is also printed for each compiler option.

Note that result is given as *MBytes/sec* (higher is better) which is computed as the mean of the 10 best values on the measurement period, and taking in account the number channels that are processed. An estimation of the DSP CPU use (in percentage of the available bandwidth at 44.1 kHz) is also computed using the effective duration of the measure. This value may not be perfectly coherent with the MBytes/sec value which is the one to be taken in account.

`faustbench [-notrace] [-generic] [-ios] [-single] [-fast] [-run <num>] [-bs <frames>] [-source] [-double] [-opt <level(0..3|-1)>] [-us <factor>] [-ds <factor>] [-filter <filter(0..4)>] [additional Faust options (-vec -vs 8...)] foo.dsp` 

Here are the available options:

 - `-notrace to only generate the best compilation parameters`
 - `-generic' to compile for a generic processor, otherwise -march=native will be used`
 - `-ios to generate an iOS project`
 - `-single to only execute the one test (scalar by default)`
 - `-fast to only execute some tests`
 - `-run <num> to execute each test <num> times`
 - `-bs <frames> to set the buffer-size in frames`
 - `-source to keep the intermediate source folder and exit`
 - `-double to compile DSP in double and set FAUSTFLOAT to double`
 - `-opt <level (0..3|-1)>' to pass an optimisation level to C++ (-1 means 'maximal level =-Ofast for now' but may change in the future)`
 - `-us <factor> to upsample the DSP by a factor (can be 2, 3, 4, 8, 16, 32)`
 - `-ds <factor> to downsample the DSP by a factor (can be 2, 3, 4, 8, 16, 32)`
 - `-filter <filter> for upsampling or downsampling [0..4], 0 means no filtering`

Use `export CXX=/path/to/compiler` before running faustbench to change the C++ compiler, and `export CXXFLAGS=options` to change the C++ compiler options. Additional Faust compiler options can be given.

Additional Faust options (like `-mcd 2...`) can be added on the list of all already tested options, to possibly discover a better setup not covered by the standard exploration.

## faustbench-llvm

The **faustbench-llvm** tool uses the libfaust library and its LLVM backend to dynamically compile DSP objects produced with different Faust compiler options, and then measures their DSP CPU usage. Additional Faust compiler options can be given beside the ones that will be automatically explored by the tool.

Note that result is given as *MBytes/sec* (higher is better) which is computed as the mean of the 10 best values on the measurement period and taking in account the number channels that are processed. An estimation of the DSP CPU use (in percentage of the available bandwidth at 44.1 kHz) is also computed using the effective duration of the measure. This value may not be perfectly coherent with the MBytes/sec value which is the one to be taken in account, and is finally used to return the best estimation.

Alhough they are estimated using the LLVM backend, note that the result given by **faustbench-llvm** can perfectly be used to optimize the C++ code later on, since both compilation chains are based on the same LLVM infrastructure.

`faustbench-llvm [-notrace] [-control] [-generic] [-single] [-run <num] [-bs <frames>] [-opt <level(0..4|-1)>] [-us <factor>] [-ds <factor>] [-filter <filter(0..4)>] [additional Faust options (-vec -vs 8...)] foo.dsp` 

Here are the available options:

- `-notrace to only generate the best compilation parameters`
- `-control to update all controller with random values at each cycle`
- `-generic to compile for a generic processor, otherwise the native CPU will be used`
- `-single to only execute the one test (scalar by default)`
- `-run <num> to execute each test <num> times`
- `-bs <frames> to set the buffer-size in frames`
- `-opt <level>' to pass an optimisation level to LLVM, between 0 and 4 (-1 means 'maximal level' if range changes in the future)`
- `-us <factor> to upsample the DSP by a factor (can be 2, 3, 4, 8, 16, 32)`
- `-ds <factor> to downsample the DSP by a factor (can be 2, 3, 4, 8, 16, 32)`
- `-filter <filter> for upsampling or downsampling [0..4], 0 means no filtering`

Additional Faust options (like `-dlt 0...`) can be added on the list of all already tested options, to possibly discover a better setup not covered by the standard exploration.

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

`faust-tester [-imp] [-pulse <num (in samples)>] [-display <num>] foo.dsp` 

Here is the available options:

- `-imp to test with a Dirac impulse`
- `-pulse <num (in samples)> to test with a periodic pulse generated every 'num' samples`
- `-display <num> to diplay 'num' samples (default 44100)`

## faust-osc-controller

The **faust-osc-controller** tool allows to control an OSC aware Faust running program (that is a DSP program possibly compiled with *faust2xx* and the *-osc* option). It will ask the program for its JSON description to build a "proxy" User Interface to control the distant program. Communications can be bi-directionnal, so that the proxy controler can display output control values coming from the distant program (like bargraphs for instance). 

`faust-osc-controller root [-port <port>] [-outport <port>]` 

Set root to the OSC program name (like '/freeverb'). Then use the available options:

- `-ip <host_ip> to set the remote application IP address (default 'localhost')`
- `-port <port> to set the OSC input port`
- `-outport <port>' to set the OSC output port`

Note that the OSC *input port* of the **faust-osc-controller** tool has to be the *output port* of the controlled program. And the OSC *output port* of the **faust-osc-controller** tool has to be the *input port* of the controlled program. The controler and controlled programs both have to send messages using the -xmit (1|2) parameter, depending if you use real paths or aliases.

Example:

- launch the remote program with `clarinetMIDI -port 5000 -outport 5001 -xmit 1`. Look at the OSC 'root' name that may be a bit different. 
- then start the controller tool like with: `faust-osc-controller /clarinet -port 5001 -outport 5000 -xmit 1`

