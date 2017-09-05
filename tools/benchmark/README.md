# Dynamic compiler usage, benchmark and optimizing tools 

Several programs and tools are available to test the dynamic compilation chain and benchmark the compiled programs. 

## dynamic-jack-gtk

**dynamic-jack-gtk** tool uses the dynamic compilation chain, compiles a Faust DSP source, and runs it with the LLVM or Interpreter backend.

`dynamic-jack-gtk [-llvm/interp] [-nvoices N] [-midi] [-osc] [-httpd] [additional Faust options (-vec -vs 8...)] foo.dsp`

Here are the available options:

- `-llvm/interp to chosse eithe LLVM or Interpreter backend`
- `-nvoices N to satrt th DSP in polyphonic mode with N voices`
- `-midi to activate MIDI control`
- `-osc to activate OSC control`
- `-httpd to activate HTTPD control`

Additional Faust compiler options can be given.

## faustbench

**faustbench** uses the C++ backend to generate a set of C++ files produced with different Faust compiler options. All files are then compiled in a unique binary that will measure DSP CPU of all versions of the compiled DSP. The tool is supposed to be launched in a terminal, but it can be used to generate an iOS project, ready to be launched and tested in Xcode. 

`faustbench [-ios] [-fast] [-double] [additional Faust options (-vec -vs 8...)] <file.dsp>` 

Here are the available options:

 - `-ios to generate an iOS project`
 - `-fast to execute only some tests`
 - `-double to compile DSP in double and set FAUSTFLOAT to double`

Use `export CXX=/path/to/compiler` before running faustbench to change the C++ compiler, and `export CXXFLAGS=options` to change the C++ compiler options. Additional Faust compiler options can be given.

## faustbench-llvm

**faustbench-llvm** tool uses the libfaust library and its LLVM backend to dynamically compile DSP objects produced with different Faust compiler options, and then measure their DSP CPU. Additional Faust comptiler options can be given beside the ones that will be automatically explored by the tool.

`faustbench-llvm [additional Faust options (-vec -vs 8...)] <file.dsp>` 


