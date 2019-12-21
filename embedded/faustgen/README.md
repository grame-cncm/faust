
faustgen~
============================
## The swiss knife for [Faust](https://faust.grame.fr) development in Max/MSP.
--------------

**faustgen~** is a Max external prototyping environment for the Faust programming language with an ultra-short edit-compile-run cycle. 

**faustgen~** is based on the [Faust](https://faust.grame.fr) library and on [LLVM](http://llvm.org).

## How to compile...

### Prerequisites
- you must have [Faust](https://faust.grame.fr/) installed and the `faust` command available from the command line, and the compiled `libfaust` library.
- you must have downloaded the [Max SDK](https://cycling74.com/downloads/sdk).
- you must have [cmake](https://cmake.org/) installed.
- [Windows] you must have [libsndfile](http://www.mega-nerd.com/libsndfile/) installed.

### Project generation
**faustgen~** project is based on cmake. 
It is recommended to build **faustgen~** in a separate subfolder. It isolates the compilation process from the rest of the project. Creates this folder and generate your project using `cmake`.

~~~~
$ mkdir build
$ cd build
$ cmake .. -DMAXSDK="/path/to/the/max/sdk/source/c74support" -G "your generator"
~~~~

You must define the path to the Max SDK the first time you invoke `cmake`. Next the value is cached by cmake.
On Windows, cmake assumes that the libsndfile library is installed in C:/Program Files/Mega-Nerd/libsndfile. To override, you cand define the LIBSNDFILE variable to an alternate location (i.e. add -DLIBSNDFILE=/path/to/libsndfile on the command line).

**Note:** on Windows, you should use the same runtime than the other libraries. Thus make sure everything is compiled with the same Visual Studio version (including LLVM). The current Faust version (2.13.14) makes use of the following cmake generator: "Visual Studio 14 2015 Win64". You must use the same for **faustgen~**.

### Compiling

You can launch your IDE and proceed as usual or you can use cmake build command from your build folder:

~~~~
$ cmake --build . --config Release
~~~~

## Packaging

Packaging is based on the cmake install target and on the resources found the package folder.
Simply call the 'install' target:

~~~~
$ cmake --build . --config Release --target install
~~~~

On output, you should find a folder named **faustgen** in the package folder.

**Note:** on Mac OS, this folder is also compressed to the **faustgen.dmg** image file.

## Limitations and known bugs

--------------
#### [Grame](http://www.grame.fr) - Centre National de Creation Musicale
