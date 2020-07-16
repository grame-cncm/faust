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

This chapter explains how to do a basic Faust installation, when LLVM is not
required. For more detailed compilation options, including instructions for
compiling `libfaust`, the library version of the compiler, refer to the
[advanced building](https://github.com/grame-cncm/faust/wiki/Building) page on the Faust Github wiki.

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
FAUST : DSP to C, C++, Java, old C++, WebAssembly 
(wast/wasm) compiler, Version 2.27.1
Copyright (C) 2002-2020, GRAME - Centre National de Creation Musicale. All 
rights reserved. 
```

As you probably noticed the LLVM backend is not installed in this basic setup. 
You will typically need LLVM if you want to compile the library version of 
Faust. For more details, run `make help` in the root folder of the distribution
or see the [advanced compiling](https://github.com/grame-cncm/faust/wiki/Building)
page on the wiki.

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

See compilation instructions on the [wiki](https://github.com/grame-cncm/faust/wiki/BuildingSimple)
