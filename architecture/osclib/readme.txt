======================================================================
                        FAUST OSC Library
======================================================================

----------------------------------------------------------------------
Compiling the Faust OSC library
----------------------------------------------------------------------

The Faust OSC library project depends on the oscpack library, which 
is included in this distribution. You should first compile the oscpack 
library before compiling the FAUST OSC library. Both libraries relies
on CMake, a cross-platform, open-source build system 
(see at http://www.cmake.org).

1) Compiling oscpack
----------------------------------------------------------------------
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
----------------------------------------------------------------------
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

======================================================================
In case of trouble, contact me: <fober@grame.fr>
----------------------------------------------------------------------
Copyright 2011 (c) Grame 
