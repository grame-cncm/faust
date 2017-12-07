# Additional Tools for Faust

These additional tools are provided by various contributors to help 
the building process of applications and plugins with Faust. 

Currently the following tools are available :

* `faust2oct` is a script to create dynamically loadable functions for gnu octave
* `faust2appls` contains various "`faust2...`" scripts relying on Faust architectures from `/architecture` to generate a wide range of elements from a Faust code. These scripts get automatically installed when `sudo make install` is ran.
* `faust2sc` is a Ruby program used to generate language modules (e.g. for Haskell and SuperCollider).
* `faust2pd` is a Q program used to generate a user interface patch to use in conjunction with a Faust generated pd plugin.
* `scbuilder` is a Ruby/Python/SCons script for building SuperCollider plugins, either from C++ sources or from Faust specifications.
* `faust2ck` is a wrapper-generator for ChucK Ugens. It allows to create ChucK-compatible C++ code that can be placed in the Chuck source tree to extend the language.
* `faust2flash` allows to convert Faust programs into Flash .swf files that can be published in web pages.
* `sound2faust` allows to convert audio files in Faust 'waveforms'. The output file contains:
  * an interleaved version (all audio channels are generated in a same 'waveform')
  * several 'waveforms' for separated mono channels
  * a resulting 'processor' that simply output all mono 'waveforms' 
* `benchmark` folder contains additional tools to test C++, LLVM, WebAssembly and Interpreter backends, and the performance of their generated code. 
