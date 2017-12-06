
# How to compile
======================================================================

### Prerequisite
- you must have [cmake](https://cmake.org/) version 3.4.0 or greater installed.
- you must have [LLVM](http://llvm.org/) installed to compile the llvm backend.
- [Windows] you should have a unix like environment installed. [MSYS2](http://www.msys2.org/) is recommended and further windows specific notes assume it is.

## Using the Makefile

Simply type `make` in the `build` folder and on output you should get:
- the faust compilers
- the faust static library
- the faust dynamic library

The build process is actually based on [cmake](https://cmake.org/). It is platform independant although platform specific targets are availble. Type `make help` for all details.

### Customizing the embedded backends

The file `backends.cmake` describes the `make` output and the embedded backends.
You can freely customize this file to your needs.

The file `emmcc.cmake` is used to compile the Web assembly and/or the ASMJS libraries. By default, the WASM backend is included in the Web assembly library and the ASMJS backend is included in the ASMJS library (that's hard coded in the CMakeList.txt) but you can freely customize the backends section.


## Advanced settings with cmake

You can directly invoke `cmake` with the appropriate options. In this case, it is recommended to create a new folder and to invoke `cmake` from this folder:

`> mkdir your_output_folder`  
`> cd your_output_folder`  
`> cmake <your options> .. -G "a cmake generator"`

You can have a look at the `Makefile` for examples of cmake invocations.

## Notes regarding the backends compilation

### Notes regarding LLVM
- you must have `llvm-config` available from the command line.
- using LLVM 5.0.0 works on every platform, you can get binary distributions from the [LLVM Releases page](http://releases.llvm.org/)
- using a previous LLVM version: you have to make sure that it is compiled **with rtti**. You can check using `llvm-config --has-rtti`

#### LLVM on windows:
Install the following msys2 packages using pacman:
- pacman -S mingw-w64-x86_64-llvm
- pacman -S mingw-w64-x86_64-gcc

#### LLVM on GNU/Linux:
LLVM is generally available from the package manager but it might be an old version that don't statisfy the rtti constrain. In this case you should get a binary distribution from the [LLVM Releases page](http://releases.llvm.org/).

Identified potential compile time errors:
- cannot find -ledit -> sudo apt-get install libedit-dev


### Notes regarding the `interpreter` backend
The 'interpreter' backend is not supported on windows using MSVC compilers
This is due to label dereferencing operator && that is only supported by some versions of gcc.
