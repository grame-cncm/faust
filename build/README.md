
# How to compile

### Prerequisites
- you must have [cmake](https://cmake.org/) version 3.4.0 or greater installed.
- you must have [LLVM](http://llvm.org/) version 3.8 or greater installed to compile the llvm backend.
- you must have [libmicrohttpd](https://www.gnu.org/software/libmicrohttpd/) installed to compile the http library.
- on Windows, you have the option to use MS [Visual Studio](http://www.microsoft.com/express/) or the [MSYS2](http://www.msys2.org/) environment. The current Makefile is targetting MSYS2 by default. See Windows specific notes.


## About cmake projects

Build of Faust components is cmake based. Cmake is highly state dependant since it maintains a cache with the various settings of the project. The compilation process takes place in 2 phases:
- 1) **project generation** : this is the step where you choose what you want to include in your project and to compile in a second step. The faust compiler, the OSC and HTTP libraries are included by default but you can add (or remove) the faust libraries (static or dynamic versions). You can also choose the form of your project : a Makefile, an Xcode or Visual Studio project, or any of the generator provided by cmake on your platform. You may think of this step as the definition of the targets that will be available from your project. Note that at this step, you also choose the faust backends you want to include in the different components (compiler and faust libraries). See the backends section for more details.

- 2) **compilation of the project** : once your project is generated, the default is to compile all the targets that are included. But single targets are still available and can be compiled individually. Note that your project will always include an `install` target, which always installs all the components included in the project.

These 2 phases are independent and it's possible to modify the project at any time.
If you're familiar with cmake, you can directly use cmake commands otherwise, a Makefile is provided that includes and demonstrates all the project options.

## Using the Makefile
The Makefile includes 2 kind of targets, addressing the 2 phases of the compilation (see above):
- 1) targets to configure the project: these targets are named `configxxx` and add components to the project (e.g. `make configstatic` adds the libfaust static library to the project). This scheme is now obsolete but maintained for compatibility. See the _"Customizing the project targets"_ section for more details.
- 2) targets to compile

By default, you can simply type `make` in the `build` folder to compile the **Faust** compiler and the **OSC and HTTP** libraries.
On output, you'll find applications in the `build/bin` folder and libraries in the `build/lib` folder.

Type `make help` for details on targets and options.

## Customizing the embedded backends
The `backends` folder contains a set of files describing the Faust backends to be embedded into  each possible output (compiler, static library, dynamic library). By default, the project makes use of `backends.cmake`.
You can freely customize this file to your needs or create a new one. A `BACKENDS` option is provided by the Makefile to use any file (note it always look for the backends files into the backends folder). At cmake level, use of the `-C backend_file.cmake` will populate the cmake cache with the correponding settings.

## Customizing the project targets
The `targets` folder contains a set of files describing the targets to be embedded into your ptoject. By default, the project includes the faust, osc and http targets, corresponding to the faust compiler, the osc and the httpd static libraries.
You can freely customize this file to your needs or create a new one. A `TARGETS` option is provided by the Makefile to use any file (note it always look for the targets files into the targets folder). At cmake level, use of the `-C targets_file.cmake` will populate the cmake cache with the correponding settings.


## Advanced settings with cmake

You can directly invoke `cmake` with the appropriate options. In this case, it is recommended to create a new folder and to invoke `cmake` from this folder:

`> mkdir your_output_folder`  
`> cd your_output_folder`  
`> cmake <your options> .. -G "a cmake generator"`

You can have a look at the `Makefile` for examples of cmake invocations and at the `CMakeLists.txt` file for the available cmake options.

**Warning**: running cmake from the build folder may override the existing Makefile.

## Compiling on Windows
#### Using MSYS2
Use of the `make` command assumes that you have [MSYS2](http://www.msys2.org/) installed.

Building with [MSYS2](http://www.msys2.org/) has been successfully tested. It is recommended to install the following package using `packman`:
> pacman -S mingw-w64-x86_64-gcc

In this case, make sure to uninstall the previous gcc version first:
> pacman -R gcc

#### Using MSVC
To compile using Visual Studio, you can configure manually your project using a commands prompt (e.g. Windows PowerShell):

`> mkdir your_output_folder`  
`> cd your_output_folder`  
`> cmake -C ../backends/backends.cmake .. -G "Visual Studio 14 2015 Win64"`

Then you can open the Visual Studio solution located in `your_output_folder` or continue using the command line:

`> cmake --build .`  

If `make` is available from your commands prompt, you can get similar results with the following options :

`> make  GENERATOR="Visual Studio 14 2015 Win64"`


## Notes regarding the backends compilation

### Notes regarding LLVM
- you must have `llvm-config` available from the command line.
- LLVM supported versions starts at 3.8, older versions may work but are not supported anymore.
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

#### Potential issues with llvm-config:
If `llvm-config` is available under a version name (e.g. llvm-config-5.0.0) you can use this name with the LLVM_CONFIG option e.g.:
> cd faustdir &&
cmake .. -DLLVM_CONFIG=llvm-config-5.0.0

When the project generation fails to configure LLVM, you can try using the cmake llvm-config file (if available). To do so :
> cd faustdir &&
cmake .. -DUSE_LLVM_CONFIG=off

You can bump into similar issues but at link time (encountered on Windows): try the same strategy.


### Notes regarding the `interpreter` backend
The 'interpreter' backend is not supported on windows using MSVC compilers
This is due to label dereferencing operator && that is only supported by gcc version 5 or greater.

------
More details are available from the [Faust wiki pages](https://github.com/grame-cncm/faust/wiki)
