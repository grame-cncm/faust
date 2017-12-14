
# How to compile
======================================================================

### Prerequisites
- you must have [cmake](https://cmake.org/) version 3.4.0 or greater installed.
- you must have [LLVM](http://llvm.org/) installed to compile the llvm backend.
- on Windows, you should have MS [Visual Studio](http://www.microsoft.com/express/) installed. The current Makefile is targetting Visual Studio 14 2015 Win64. See Windows specific notes.


## Using the Makefile

Simply type `make` in the `build` folder to compile the **Faust** compiler.
On output, you'll find applications in the `bin` folder and libraries in the `lib` folder.

Type `make help` for all details on targets and options.

## Customizing the embedded backends

The file `backends.cmake` describes the embedded backends for each possible output.
You can freely customize this file to your needs or use another one.


## Advanced settings with cmake

You can directly invoke `cmake` with the appropriate options. In this case, it is recommended to create a new folder and to invoke `cmake` from this folder:

`> mkdir your_output_folder`  
`> cd your_output_folder`  
`> cmake <your options> .. -G "a cmake generator"`

You can have a look at the `Makefile` for examples of cmake invocations.

**Warning**: running cmake from the build folder may override the existing Makefile.


## Usefull cmake options

- CMAKE_VERBOSE_MAKEFILE : a boolean value that sets the Makefiles in verbose mode. Ex: `cmake -DCMAKE_VERBOSE_MAKEFILE=ON`
-


## Compiling on Windows
Using the `make` command assumes that you have [MSYS2](http://www.msys2.org/) installed.

Building with [MSYS2](http://www.msys2.org/) has been successfully tested. It is recommended to install the following package using `packman`:
> pacman -S mingw-w64-x86_64-gcc

To compile using Visual Studio, you'll have to configure manually your project using a commands prompt (e.g. Windows PowerShell):

`> mkdir your_output_folder`  
`> cd your_output_folder`  
`> cmake -C ../backends.cmake .. -G "Visual Studio 14 2015 Win64"`

Then you can open the Visual Studio solution located in `your_output_folder` or continue using the command line:

`> cmake --build .`  




## Notes regarding the backends compilation

### Notes regarding LLVM
- you must have `llvm-config` available from the command line.
- using LLVM 5.0.0 works on every platform, you can get binary distributions from the [LLVM Releases page](http://releases.llvm.org/)
- using a previous LLVM version: you have to make sure that it is compiled **with rtti**. You can check using `llvm-config --has-rtti`

#### LLVM on windows:
Install the following msys2 packages using pacman if you compile using MSYS2 environment:
- pacman -S mingw-w64-x86_64-llvm

Compiling using Visual Studio and LLVM 5.0.0 may lead to a link error:

`Error	LNK1181	cannot open input file 'LTO-NOTFOUND.obj'`

This is due to an incorrect `llvm-config` output. Open the solution and edit the project properties and remove the faulty input LTO-NOTFOUND entry from the `Linker->Input` section.

#### LLVM on GNU/Linux:
LLVM is generally available from the package manager but it might be an old version that don't statisfy the rtti constrain. In this case you should get a binary distribution from the [LLVM Releases page](http://releases.llvm.org/).

Identified potential compile time errors:
- cannot find -ledit -> sudo apt-get install libedit-dev

#### LLVM on MacOS:

While compiling with llvm 5.0.0 you may get the following link error:
> Undefined symbols for architecture x86_64: "\_futimens"

seems to be related to xcode version, the problem is not present using xcode 9


### Notes regarding the `interpreter` backend
The 'interpreter' backend is not supported on windows using MSVC compilers
This is due to label dereferencing operator && that is only supported by gcc version 5 or greater.
