# FAUST OSC Library

## Compiling the Faust OSC library

The Faust OSC library project depends on the oscpack library, which is included in this distribution and will be compiled along the Faust OSC library. 

To compile on OSX or Linux:
	
	> make

The compiler output two static libraries named libOSCFaust.a and liboscpack.a, and placed in the 'osclib' folder. 

Assuming you have installed Android development tools, to compile for Android:

    > make android


The compiler output is a set of static libraries placed in the 'osclib/android/libs' folder.


## Using the library

The library provides a single interface file: OSCControler.h. The following options should be used to compile: -Iosclib/faust/include -Losclib -loscpack -lOSCFaust

See the [ReadMe](/architecture/osclib/faust/README.md) file for more details about the library.


## Examples

The Faust OSC architecture should be typically combined with other architectures. The file 'OSCUI.h' provides the basis for such combination and the file 'jack-console-osc.cpp' provides an example of combination.

In case of trouble, contact me at: <fober@grame.fr>

 
