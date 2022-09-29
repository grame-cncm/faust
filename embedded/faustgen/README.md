
faustgen~
============================
## The swiss knife for [Faust](https://faust.grame.fr) development in Max/MSP.
--------------

[Faust](https://faust.grame.fr) (Functional Audio Stream) is a functional programming language for sound synthesis and audio processing with a strong focus on the design of synthesizers, musical instruments, audio effects, etc. Faust targets high-performance signal processing applications and audio plug-ins for a variety of platforms and standards, and is distributed with a [huge library](https://faustlibraries.grame.fr) of various DSP algorithms.

**faustgen~** is a Max external prototyping environment for the Faust programming language with an ultra-short edit-compile-run cycle. It is based on the [libfaust](https://faust.grame.fr) library (the embeddable version of the Faust compiler) and on [LLVM](http://llvm.org). The DSP code can be edited in an embedded editor and will be JIT compiled in native code using LLVM when the editor is closed. For faster reloading, the compiled code is saved in the patch and re-loaded when the patch is opened again. The **faustgen~** external contains all standard Faust libraries, but additional ones can be used by adding the `-I <pathname>` option in the `compileoptions` message, or using the `librarypath`message.

The DSP code can describe generator or effects, and can run in polyphonic mode, when following the [polyphonic convention](https://faustdoc.grame.fr/manual/midi/#midi-polyphony-support) to define instruments.  

## How to use 

### Creating

A new **faustgen~** object will be created with a default DSP program (a stereo in/out passthrough). Two different ways of creating objects are available:

- using **faustgen~** object without a specific name let's you define the DSP program only for this instance, with a default name factory ID
- using **faustgen~ name** allows to specify a name for this instance, and share the *same Faust code with all objects with this name*. If you load another patch with a same faustgen~ name, you'll keep the current code. Be carefull, if you change the name you loose your previous code (so copy it before)

### Using

Depending of the number of audio inputs and outputs described in the DSP source code, the **faustgen~** object has:

- N inlets, the first one being the *message control one* and a regular audio inlet, an all other audio inlets only
- M outlets, audio outs from 1 to M-2
- an output messages outlet (see later)
- the right most outlet is used to send MIDI messages if MIDI metadata are used in the DSP UI items

When double-clicking on it, the **faustgen~** object opens several menu items:

- *Edit DSP code* allows to open the integrated text editor, edit the DSP code, then JIT compile it when the window is closed
- *View DSP parameters* print each parameters in the Max console window with its label, complete path (as *xxx/yyy/zzz* syntax) and range, as well as the complete DSP JSON 
- *View compile options* print all Faust compilation options in the Max console window
- *View SVG digram* creates the block diagram SVG view and opens it in a browser
-  *View Web documention* access the standard Faust documention in a browser
- *View libraries* open the embedded Faust libraies in a text editor

### Controlling

The **faustgen~** object can be controlled with the following messages:

- `read <pathname>`: to read an external DSP file (pathname is optional)
- `write <pathname>`: to write the DSP code in an external file (pathname is optional)
- `librarypath <pathname>` to add the folder pathname of additional Faust libraries. Using an empty `librarypath` message will simply clear the librarypath list
- `compileoptions <options>`: to add most of the Faust [compiler options](https://faustdoc.grame.fr/manual/options/) (like `-vec -lv 1 -vs 8`...). The `-single` option can be used to run the DSP code with float samples (remember that Max7 and later use double samples by default, so does **faustgen~**). Using an empty `compileoptions` message will simply clear the option list. Using `nc`(for *no compilation*) allows to avoid automatic DSP recompilation when the `compileoptions` message is triggered.
- `osc <IP inport outport xmit[0|1] bundle[0|1]>`: to activate OSC control in input and output mode, possibly generating messages when *xmit = 1*, and in bundle mode when *bundle = 1* 
- `init`: to generate all inputs and outputs control messages as a message list *[path, init, min, max]* that will be sent on the output messages outlet
- `dump`: to generate all inputs and outputs control messages as a message list *[path, cur, min, max]* that will be sent on the output messages outlet. 
- `mute`: to mute audio rendering
- `polyphony <nvoices>`: to set the DSP in polyphonic mode with *nvoices* 

#### Input controllers 

All control messages are received in the left most inlet (the signal + message inlet) with the `<label|shortname|path> <number>` syntax. Their number and exact syntax obviously depend of the actual Faust DSP code. `Label` is the simple name of the controller (like `freq` of `gain`), the `shortname` is the smallest unique name that can be used, and `path` is the complete path following the OSC convention (like `osc/freq` of `osc/gain` kind of path). The `shortname` or `path` syntax has to be used to be sure all controllers are distincts. The `number` parameter is the actual float value for the controller. Use the *View DSP parameters* menu item to print all controller paths in the Max console with their label, shortname, path and range.

#### Output controllers

When the object has bargraphs, their values are sent on the output messages outlet as a message list *[path, cur, min, max]*.

#### MIDI messages

MIDI messages can be received on the left most inlet when [MIDI  control is activated in the DSP code](https://faustdoc.grame.fr/manual/midi/) (so with the `[midi xxx]` metadata, or when polyphonic mode is used) and will be sent on the right most outlet.

## How to compile

### Prerequisites

- you must have [Faust](https://faust.grame.fr/) installed and the `faust` command available from the command line, and the compiled `libfaust` library. **WARNING**: be sure to have `libfaust` compiled with `#define FAUSTFLOAT double` in [architecture/faust/dsp/dsp.h](https://github.com/grame-cncm/faust/blob/master-dev/architecture/faust/dsp/dsp.h) and [architecture/faust/gui/UI.h](https://github.com/grame-cncm/faust/blob/master-dev/architecture/faust/gui/UI.h)
- you must have downloaded the [Max SDK](https://cycling74.com/downloads/sdk)
- you must have [cmake](https://cmake.org/) installed
- [Windows] you must have [libsndfile](http://www.mega-nerd.com/libsndfile/) installed

### Project generation

**faustgen~** project is based on cmake. It is recommended to build **faustgen~** in a separate subfolder. It isolates the compilation process from the rest of the project. Creates this folder and generate your project using `cmake`.

~~~~
$ mkdir build
$ cd build
$ cmake .. -DMAXSDK="/path/to/the/max/sdk/source/c74support" -G "your generator"
~~~~

You must define the path to the Max SDK the first time you invoke `cmake`. Next the value is cached by cmake.
On Windows, cmake assumes that the libsndfile library is installed in C:/Program Files/Mega-Nerd/libsndfile. To override, you cand define the LIBSNDFILE variable to an alternate location (i.e. add -DLIBSNDFILE=/path/to/libsndfile on the command line).

**Note:** on Windows, you should use the same runtime than the other libraries. Thus make sure everything is compiled with the same Visual Studio version (including LLVM). The current Faust version (2.13.14) makes use of the following cmake generator: "Visual Studio 14 2015 Win64". You must use the same for **faustgen~**.

### Version number

Manually raise the version number in `src/faustgen~.h`, `CMakeLists.txt`, `changelog.txt`, `package/help/faustgen~.maxhelp`, `Info.plist`and `../../build/MakeRelease.bat` files.

### Compiling

You can launch your IDE and proceed as usual or you can use cmake build command from your build folder:

~~~~
$ cmake --build . --config Release
~~~~

## How to package

Packaging is based on the cmake install target and on the resources found the package folder.
Simply call the 'install' target:

~~~~
$ cmake --build . --config Release --target install
~~~~

On output, you should find a folder named **faustgen** in the package folder.

**Note:** on macOS, this folder is also compressed to the **faustgen.dmg** image file.

## Limitations and known bugs

--------------
#### [Grame](http://www.grame.fr) - Centre National de Creation Musicale
