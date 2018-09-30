# Compiling and Installing the Faust Compiler

This chapter describes how to get and compile the Faust compiler as well as
other tools related to Faust (e.g., [`libfaust`](#libfaust), `libosc`, 
`libhttpd`, etc.). 

TODO: more info here: normalize and explain that there exist pre-compiled
binaries: link to those.

For many years, Faust was nearly dependencies-free, making it easy
to compile using `make`. However, as the compiler developed and started 
supporting more backends and having more features, things slowly became more 
complicated. In particular, [LLVM](https://llvm.org/) support added a 
significant layer of complexity to the compilation process. Moreover, the use 
of `make` was making the build process almost impossible for non-Unix systems 
(i.e., Windows). 

For all these reasons, Faust's build system is now based on 
[CMake](https://cmake.org/). CMake offers great deal of flexibility, both in 
terms of defining the targets to be compiled as well as selecting the different 
backends to be included in each target. However, this flexibility is based on a
set of states (cached by CMake), which can sometimes make the compilation 
process a bit obscure.

The goal of this chapter is to provide practical information about this 
building system. The first section explains how to do a basic Faust 
installation, when LLVM is not required. The second section gives details on 
all the available options.

## Basic Faust Installation

If you don’t have special needs and if you just want to compile Faust code to 
your favorite target (i.e., C++, JAVA, JavaScript, WebAssembly, etc.), 
things are relatively straight forward. This section describes the steps to
generate a basic Faust build for Unix systems and for windows.

### Unix Systems

In this section, we describe the steps to install and run Faust on a fresh 
Ubuntu 16.04 distribution. While this process might slightly differ from one 
Linux distribution to another and on macOS, users used to using the command
line should be able to easily adapt these steps to their needs.

#### Compiling the Compiler

The first step is to compile Faust itself. Let’s start with the minimal 
requirement in terms of packages: the building tools, `git` and `libmicrohttpd`:

```
sudo apt-get update
sudo apt-get install -y build-essential cmake git libmicrohttpd-dev
```

We can now clone 
[the GitHub repository of Faust](https://github.com/grame-cncm/faust):

```
git clone https://github.com/grame-cncm/faust.git
```

Then compile and install Faust:

```
cd faust
make
sudo make install
```

Once the installation has been completed, it can be checked:

```
faust -v
```

This will give you the version of the Faust compiler with a list of the 
available backends:

```
FAUST : DSP to C, C++, Java, JavaScript, old C++, asm.js, WebAssembly 
(wast/wasm) compiler, Version 2.11.1
Copyright (C) 2002-2018, GRAME - Centre National de Creation Musicale. All 
rights reserved. 
```

As you probably noticed the LLVM backend is not installed in this basic setup. 
You will typically need LLVM if you want to compile the library version of 
Faust. A complete installation is described in [the next section](TODO).

We dont have any audio development package installed, but we can nevertheless 
use Faust to compile some of the examples to C++, at least to make sure that 
the compiler works:

```
faust examples/generator/noise.dsp
```

The above command will compile 
[`noise.dsp` (from the Faust distribution)](https://github.com/grame-cncm/faust/blob/master-dev/examples/generator/noise.dsp) 
and print the corresponding C++ code to the standard output.

This C++ code has to be embedded into an architecture file (that describes how 
to relate the audio computation to the external world) before being compiled 
into standalone application or an audio plugin. For that, you will need to 
install some development packages depending of your targets. For example, in
order to compile a Faust program as a [Jack](http://jackaudio.org/) (or 
[ALSA](https://www.alsa-project.org/main/index.php/Main_Page)) application with 
a [Qt interface](https://www.qt.io/), the following development packages will 
have to be installed: 

```
sudo apt-get install -y libasound2-dev libjack-jackd2-dev libqt4-dev

```

It is then possible to use the corresponding [`faust2` script](TODO) to
generate the corresponding application:

```
faust2alqt foo.dsp
```

for an ALSA application with a Qt interface

```
faust2jaqt foo.dsp
```

for a Jack application with a Qt interface.

An overview of all the available Faust targets and of their dependencies is
available in [this section](#a-quick-tour-of-the-faust-targets).

### Windows Systems

TODO

## Advanced Faust Build

The Faust distribution includes the Faust compiler, but also [other elements 
that you may want to compile](#overview-of-the-faust-universe), in particular 
[`libfaust`](libfaust), the library version of the Faust compiler.

The way these elements are compiled can be configured with the appropriate 
files. This section demonstrate how this system works.

### Faust Backends

The Faust compiler can output DSP code for various languages. Support for these 
languages is provided using backends that may or may not be embedded into the 
compiler or into the Faust compiler library version. This is intended to 
simplify the compilation process: some backends (like LLVM) proved to be a bit 
complex to compile, some others are not supported by all compilers (like the 
interpreter backend). In addition, selecting only the set of backends to be 
used, can reduce significantly the size of the resulting binary.

#### Selecting Your Backends

The backends selection is described using backends files which are actually 
`cmake` files that simply populate the `cmake` cache. These files are located 
in the `build/backends` folder of the 
[Faust distribution](https://github.com/grame-cncm/faust). They consist of a 
matrix where each line corresponds to a language support and where the columns 
select (or discard) the corresponding backend for each binary output i.e.:

* the Faust compiler,
* the `libfaust` static library,
* the `libfaust` dynamic library,
* the `libfaust asmjs` library,
* the `libfaust wasm` library.

The following example selects the `ASMJS` backend for the `asmjs library`, the 
`cpp` backend for the compiler and the faust static and dynamic libraries and 
discards the interpreter backend. 

```
set (ASMJS_BACKEND ASMJS CACHE STRING "Include ASMJS backend" FORCE)
set (CPP_BACKEND COMPILER STATIC DYNAMIC CACHE STRING "Include CPP backend" FORCE)
set (INTERP_BACKEND OFF CACHE STRING "Include INTERPRETER backend" FORCE)
```

A `BACKENDS` option is provided to select a backend file using make e.g.:

```
make BACKENDS=backends.cmake
```

By default the selected backends are taken from `backends.cmake`. Note that 
`make` always looks for the backend files in the backends folder.

You can get similar results using direct `cmake` invocation:

```
cd faustdir
cmake -C ../backends/backends.cmake ..
```

The `-C file` option instructs cmake to populate the cache using the file given 
as argument.

Note that once the backends have been selected, they won’t change unless you 
specify another backend file.

#### Review the Compiled Backends

During project generation, `cmake` prints a list of all the backends that will 
be compiled for each component. Below you have an example of this output:

```
-- In target faust: include ASMJS backend
-- In target faust: include C backend
-- In target faust: include CPP backend
-- In target faust: include OCPP backend
-- In target faust: include WASM backend
-- In target staticlib: include ASMJS backend
-- In target staticlib: include C backend
-- In target staticlib: include CPP backend
-- In target staticlib: include OCPP backend
-- In target staticlib: include WASM backend
-- In target staticlib: include LLVM backend
-- In target wasmlib: include WASM backend
-- In target asmjslib: include ASMJS backend
```

Note also that the command `faust -v` prints the list of embedded backends
support by the compiler e.g.:

```
FAUST : DSP to C, C++, FIR, Java, JavaScript, old C++, Rust, asm.js, WebAssembly 
(wast/wasm) compiler, Version 2.11.1
Copyright (C) 2002-2018, GRAME - Centre National de Creation Musicale. All 
rights reserved. 
```

### Building Steps

The compilation process takes place in 2 phases:

* project generation
* project compilation

which are detailed in the following sections.

#### Project Generation

This is the step where you choose what you want to include in your project 
(before compiling it in a second step). The Faust compiler, the OSC, and HTTP 
libraries are included by default, but you can add (or remove) the Faust 
libraries (static or dynamic versions). You can also choose the form of your 
project: a Makefile, an Xcode or Visual Studio project, or any of the generator 
provided by cmake on your platform.

You may think of this step as the definition of the targets that will be 
available from your project. Note that you can also choose the Faust backends 
that you want to include in the different components (compiler and Faust 
libraries).

#### Project Form and Location

`Cmake` provides support for a lot of development environments depending on you 
platform. To know what environments are supported, type `cmake --help` and 
you’ll get a list of the supported generators at the end of the help message.

By default, the Makefile makes use of "Unix Makefiles" (or "MSYS Makefiles" 
on Windows). Thus, when you type `make`, it generates a Makefile and then runs 
a  `make` command using this Makefile. To avoid overwriting the existing 
Makefile, the project is generated in a subfolder named `faustdir` by default 
and is created on the fly.

You can freely change these default settings of `make` and the `FAUSTDIR` and 
`GENERATOR` options, that control the subfolder name and the generator to use. 
For example:

```
make GENERATOR=Xcode
```

will generate an Xcode project in the `faustdir` subfolder

```
make FAUSTDIR=macos GENERATOR=Xcode
````

will generate an Xcode project in the `macos` subfolder, etc. 

You can achieve similar results using direct `cmake` invocation:

```
mkdir macos
cd macos
cmake .. -G Xcode
```

#### Project Targets

By default, the generated project includes the Faust compiler and the OSC and 
HTTPD static libraries, but not the Faust static or dynamic libraries. The 
makefile provides specific targets to include these libraries in your project:

* `make configstatic`: add the `libfaust` static library to your projects
* `make configdynamic`: add the `libfaust` dynamic library to your projects
* `make configall`: add the `libfaust` static and dynamic libraries to your 
projects
* `make reset`: restore the default project settings.

Equivalent settings using direct `cmake` invocation are also available. For 
example, to add/remove the `libfaust` static library to/from your project, you 
can run the following command from your `faustdir`:

```
cmake -DINCLUDE_STATIC=[on/off] ..
```

You can have a look at the Makefile to see the correspondence between the make 
targets and the `cmake` equivalent call. Note that since `cmake` is a state 
machine, it’ll keep all the current settings (i.e. the values of the `cmake` 
variables) unless specified with new values.

#### Re-Generating the Project

The Makefile includes a special target to re-generate a given project. It can
be used to change the backends, but it might also be a necessary step when
including new source files (source files are scanned at project generation and 
are not described explicitly). Simply type:

```
make cmake [options]
```

All the options described in the previous sections can be specified when 
running the cmake target (except the `GENERATOR` option that can’t be changed 
at the cmake level).

A `cmake` equivalent call has the following form:

```
cd faustdir
cmake .. [optional cmake options]
```

#### Miscellaneous Project Configuration Targets

* `make verbose`: activates the printing of the exact command that is ran at 
each make step
* `make silent`: reverts what make verbose did
* `make universal`: [MacOSX only] creates universal binaries
* `make native`: [MacOSX only] reverts native only binaries (default state).

### Compiling Using `make` or `cmake`

Once your project has been generated (see [Building Steps](#building-steps)), 
the default behavior is to compile all the targets that are included in the 
project. So, typing `make` will build the Faust compiler, the OSC static
library and the HTTP static library when these 3 components are included in 
your project.

#### Standard Single Targets

Single targets are available to use with `make` or `cmake`:

* `faust`: to build the Faust compiler
* `osc`: to build the OSC library
* `http`: to build the HTTP library

#### Single Targets Requiring a Project Configuration

* `staticlib`: to build the `libfaust` library in static mode. Requires to call 
`make configstatic` first.
* `dynamiclib`: to build `libfaust` library in dynamic mode. Requires to call 
`make configdynamic` first.
* `oscdynamic`: to build OSC library in dynamic mode. Requires to call 
`make configoscdynamic` first.
* `httpdynamic`: to build HTTP library in dynamic mode. Requires to call 
`make confighttpdynamic` first.

#### Targets Excluded From All

* `wasmlib`: to build `libfaust` as a Web Assembly library.
* `asmjslib`: to build `libfaust` as an ASM JS library.

These targets require the `emcc` compiler to be available from your path.

#### Platform-Specific Targets

* `ioslib`: to build `libfaust` in static mode for iOS.

#### Invoking Targets From `cmake`

The general form to invoke a target using `cmake` commands is the following:

```
cmake --build <project dir> [--target target] [-- native project options]
```

The default `cmake` target is `all`. For example the following command builds 
all the targets included in your project:

```
cmake --build faustdir
```

Cmake takes care of the generator you used and thus provides a universal way 
to build your project from the command line whether it’s Makefile-based or 
IDE-based (e.g. Xcode or Visual Studio).

The following sequence creates and build a project using Visual Studio on 
Windows in release mode :

```
cd your_build_folder
cmake -C ../backends/backends.cmake .. -G "Visual Studio 14 2015 Win64"
cmake --build . --config Release
```

> More information on how to build the Faust compiler on Windows can be
found in the [corresponding section](#windows-systems).

For more details and options, you should refer to the 
[cmake documentation](TODO).

#### The Install and Uninstall Targets

Generated projects always include an `install` target, which installs all the 
components included in the project. There is no `uninstall` target at the 
`cmake` level (not supported by `cmake`). It is provided by the Makefile only 
and is based on the `install_manifest.txt` file that is generated by the 
install target in `build/faustdir`.

Note that cmake ensures that all the targets of your project are up-to-date 
before installing and thus may compile some or all the targets. It can be 
annoying if you invoke `sudo make install`: the object files will then be 
property of the superuser and you can then have errors during later 
compilations due to access rights issues on object files. Hence, it is 
recommended to make sure that all your targets are up-to-date by running `make` 
before running `sudo make install`.
