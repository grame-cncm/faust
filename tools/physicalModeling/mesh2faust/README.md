# `mesh2faust`

`mesh2faust` is an open-source modal physical model generator for the Faust
programming language. `mesh2faust` takes a volumetric mesh of a 3D object as
its main argument, carries out a finite element analysis, and generates the
corresponding Faust modal physical model. A wide range of parameters can be
configured to fine-tune the analysis as well as the behavior of the generated
object.

`mesh2faust` is based on [Vega FEM](http://run.usc.edu/vega/) and should work
both on Linux and OSX.

## Build/Installation

`mesh2faust` relies on [Vega FEM](http://run.usc.edu/vega/) to turn the
provided volumetric mesh into a 3D mesh and to carry the finite element
analysis on it. A lightweight adapted version of this library is part of this
repository.

Vega itself relies on some libraries that must be installed on your system in
order to compile `mesh2faust`. This section walks you through the different
steps to build and install `mesh2faust` on your system.

### Linux

* First, install the Intel MKL Library (<https://software.intel.com/en-us/intel-mkl>).
Unfortunately, this library is not open source (but it's free), so you wont find
it in your usual package manager.
* Get `libarpack` with your package manager (`libarpack2-dev` in Ubuntu).
* Go in `/vega/Makefile-headers/` and run "`selectLinux`"", this will update the
dynamic link of `Makefile-header` to the right Makefile for your system.
* You might have to make some adjustments in
`/vega/Makefile-headers/Makefile-header.linux` in the "MKL Paths" section
(Intel tends to change the organization of this lib pretty often).
* Run: `make`
* Run: `sudo make install`
* NOTE: Additional adjustments might have to be made to `Makefile-header.linux`
(compilation was only tested on Linux Mint)

### OSX

* First, install the Intel MKL Library (<https://software.intel.com/en-us/intel-mkl>).
Unfortunately, this library is not open source (but it's free), so you wont find
it in your usual package manager.
* Get `arpack`. The `mesh2faust` makefiles were configured to work the MacPort
version of `arpack` so we advise you to use this package manager to get it
(e.g., `port install arpack`).
* Go in `/vega/Makefile-headers/` and run "`selectMacOSX`"", this will update the
dynamic link of `Makefile-header` to the right Makefile for your system.
* You might have to make some adjustments in
`/vega/Makefile-headers/Makefile-header.osx` in the "MKL Paths" and "ARPACK" sections
depending on how you installed these 2 packages.
* Run: `make`
* Run: `sudo make install`
* NOTE: Additional adjustments might have to be made to `Makefile-header.osx`
(that's where you want to look at if you get some linker errors, etc.)

## Using `mesh2faust`



## Extra Help

Feel free to contact Romain Michon if you need extra help:
rmichon AT ccrma DOT stanford DOT edu.

## License

Copyright 2017, Romain Michon and Sara R. Martin

Project partly funded by Research Council of Norway et NTNU (Norwegian Technical University of Trondheim).

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
