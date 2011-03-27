======================================================================
                        FAUST OSC Library
======================================================================

----------------------------------------------------------------------
 Compiling the library
----------------------------------------------------------------------

The Faust OSC library project depends on the oscpack library, which 
is included in this distribution. You should first compile the oscpack 
library before compiling the FAUST OSC library. Both libraries rely
on CMake, a cross-platform, open-source build system 
(see at http://www.cmake.org).

1) Compiling oscpack
-----------------------------------
To compile:
	change to oscpack/cmake directory
	type:  cmake -G "your target generator"
	run your project/makefile and compile

Typically on linux systems:
	> cd oscpack/cmake
	> cmake -G "Unix Makefiles"
	> make

The compiler output is a static library named liboscpack.a and placed 
in the 'osclib' folder. Note that when 'Release' and 'Debug' targets
apply, only the 'Release' output goes to the 'osclib' folder.


2) Compiling the FAUST OSC library
-----------------------------------
To compile:
	change to faust/cmake directory
	type:  cmake -G "your target generator"
	run your project/makefile and compile

Typically on linux systems:
	> cd faust/cmake
	> cmake -G "Unix Makefiles"
	> make

The compiler output is a static library named libOSCFaust.a and placed 
in the 'osclib' folder. Note that when 'Release' and 'Debug' targets
apply, only the 'Release' output goes to the 'osclib' folder.


----------------------------------------------------------------------
 Using the library
----------------------------------------------------------------------
The library provides a single interface file: OSCControler.h
The following options should be used to compile:
	-Iosclib/faust/include -Losclib -loscpack -lOSCFaust
See the faust/readme.txt file for more details about the library.


----------------------------------------------------------------------
 Examples
----------------------------------------------------------------------
The FAUST OSC architecture should be typically combined with other 
architectures. The file 'OSCUI.h' provides the basis for such combination
and the file 'jack-console-osc.cpp' provides an example of combination.

======================================================================
In case of trouble, contact me: <fober@grame.fr>
----------------------------------------------------------------------
Copyright 2011 (c) Grame 
