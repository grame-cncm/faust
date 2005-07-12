Compilation on OSX With Xcode
==============================


¥ The VSTSDK folder from the VST SDK has to be copied in the at the same level of the VST.xcode project.

¥ To compile a Faust VST plug-in:

	- use the vst.cpp architecture file in the faust command line and produce a vst-output.cpp file: faust -a vst.cpp foo.dsp -o vst-output.cpp

	- build the VST.xcode project

