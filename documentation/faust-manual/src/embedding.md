# Embedding the Faust Compiler Using `libfaust`

<!-- TODO: this section could be further developed and better documented -->

The combination of the awesome [LLVM technology](https://llvm.org/) and 
`libfaust` (the library version of the Faust compiler) allows developers to
compile and execute Faust DSP programs on the fly at full speed and without
making compromises. In this section, we demonstrate how the Faust dynamic 
compilation chain can be used to embed the Faust compiler technology directly 
in applications or plugins.

## Dynamic Compilation Chain

The Faust compiler uses an intermediate FIR representation (Faust Imperative 
Representation), which can be translated to several output languages. The FIR 
language describes the computation performed on the samples in a generic 
manner. It contains primitives to read and write variables and arrays, do 
arithmetic operations, and define the necessary control structures (`for` and 
`while` loops, `if` structure, etc.). 

To generate various output languages, several backends have been developed: 
for C, C++, Java, JavaScript, asm.js, LLVM IR, webassemble, etc. The native 
LLVM based compilation chain is particularly interesting: it provides direct 
compilation of a DSP source into executable code in memory, bypassing the 
external compiler requirement.

## LLVM

[LLVM (formerly Low Level Virtual Machine)](https://llvm.org/) is a compiler 
infrastructure, designed for compile-time, link-time, and run-time optimization 
of programs written in arbitrary programming languages. Executable code is 
produced dynamically using a *Just In Time* compiler from a specific code 
representation, called LLVM IR. Clang, the LLVM native C/C++/Objective-C 
compiler is a front-end for the LLVM Compiler. It can, for instance, convert a 
C or C++ source file into LLVM IR code. Domain-specific languages like Faust 
can easily target the LLVM IR. This has been done by developing an LLVM IR 
backend in the Faust compiler.

## Compiling in Memory

The complete chain goes from the Faust DSP source code, compiled in LLVM IR 
using the LLVM backend, to finally produce the executable code using the LLVM 
JIT. All steps take place in memory, getting rid of the classical file-based 
approaches. Pointers to executable functions can be retrieved from the 
resulting LLVM module and the code directly called with the appropriate 
parameters.

The Faust compiler has been packaged as an embeddable library called `libfaust`, 
published with an associated API. Given a Faust source code (as a file or a 
string), calling the `createDSPFactoryXXX` function runs the compilation chain 
(Faust + LLVM JIT) and generates the *prototype* of the class, as a 
`llvm_dsp_factory` pointer.

Note that the library keeps an internal cache of all allocated *factories* so 
that the compilation of the same DSP code -- that is the same source code and 
the same set of *normalized* (sorted in a canonical order) compilation options
-- will return the same (reference counted) factory pointer. 

`deleteDSPFactory` has to be explicitly used to properly decrement the reference 
counter when the factory is not needed anymore. You can get a unique SHA1 key 
of the created factory using its `getSHAKey` method.

Next, the `createDSPInstance` function (corresponding to the `new className` of 
C++) instantiates a `llvm_dsp` pointer to be used through its interface, 
connected to the audio chain and controller interfaces. When finished, 
`delete` can be used to destroy the dsp instance.

Since `llvm_dsp` is a subclass of the dsp base class, an object of this type 
can be used with all the available `audio` and `UI` classes. In essence, this
is like reusing all architecture files already developed for the static C++ 
class compilation scheme like `OSCUI`, `httpdUI` interfaces, etc. (see TODO 
pointer to arch section).

<!-- TODO: we need an example here -->

## Saving/Restoring the Factory

After the DSP factory has been compiled, the application or the plug-in running 
it might need to save it and then restore it. To get the internal factory 
compiled code, several functions are available:

* `writeDSPFactoryToIR`: get the DSP factory LLVM IR (in textual format) as a 
string, 
* `writeDSPFactoryToIRFile`: get the DSP factory LLVM IR (in textual 
format) and write it to a file,
* `writeDSPFactoryToBitcode`: get the DSP factory LLVM IR (in binary format) 
as a string 
* `writeDSPFactoryToBitcodeFile`: save the DSP factory LLVM IR (in binary 
format) in a file,
* `writeDSPFactoryToMachine`: get the DSP factory executable machine code as a 
string,
* `writeDSPFactoryToMachineFile`: save the DSP factory executable machine code 
in a file.

To re-create a DSP factory from a previously saved code, several functions are 
available:

* `readDSPFactoryFromIR`: create a DSP factory from a string containing the 
LLVM IR (in textual format), 
* `readDSPFactoryFromIRFile`: create a DSP factory from a file containing the 
LLVM IR (in textual format),
* `readDSPFactoryFromBitcode`: create a DSP factory from a string containing 
the LLVM IR (in binary format), 
* `readDSPFactoryFromBitcodeFile`: create a DSP factory from a file containing 
the LLVM IR (in binary format),
* `readDSPFactoryFromMachine`: create a DSP factory from a string containing 
the executable machine code,
* `readDSPFactoryFromMachineFile`: create a DSP factory from a file containing 
the executable machine code.

## Additional Functions

Some additional functions are available in the `libfaust` API:

* `expandDSPFromString`/`expandDSPFromFile`: creates a self-contained DSP 
source string where all needed librairies have been included. All compilations 
options are normalized and included as a comment in the expanded string,
* `generateAuxFilesFromString`/`generateAuxFilesFromFile`: from a DSP source 
string or file, generates auxiliary files: SVG, XML, ps, etc. depending of the 
`argv` parameters.

## Using the `libfaust` Library

The `libfaust` library is fully integrated to the Faust distribution. You'll 
have to compile and install it in order to use it. For an exhaustive 
documentation/description of the API, we advise you to have a look at the code 
in the [`faust/dsp/llvm-dsp.h`](TODO) header file. Note that 
`faust/dsp/llvm-c-dsp.h` is a pure C version of the same API. Additional 
functions are available in `faust/dsp/libfaust.h` and their C version can be
found in `faust/dsp/libfaust-c.h`.

More generally, a "typical" use of `libfaust` could look like:

```
// the Faust code to compile (could be in a file too)
string theCode = "import("stdfaust.lib");process = no.noise;";
// compiling in memory (createDSPFactoryFromFile could be used alternatively)
llvm_dsp_factory *m_factory = createDSPFactoryFromString( 
  "faust", theCode, argc, argv, "", m_errorString, optimize );
// creating the DSP instance for interfacing
dsp *m_dsp = m_factory->createDSPInstance();
// creating a generic UI to interact with the DSP
my_ui m_ui = new MyUI();
// linking the interface to the DSP instance
m_dsp->buildUserInterface( m_ui );
// initializing the DSP instance
m_dsp->init( 44100 );
// hypothetical audio callback
while(...){
  m_dsp->compute( 1, m_input, m_output );
}
// cleaning
delete m_dsp;
deleteDSPFactory( m_factory );
m_factory = NULL;
```

Thus, very few code is needed to embed Faust to your project!

## Use Case Examples

The dynamic compilation chain has been used in several projects:

* [FaustLive](TODO): an integrated IDE for Faust development offering on-the-fly
compilation and execution features
* [Faustgen](TODO): a generic Faust 
[Max/MSP](https://cycling74.com/products/max/) object
* [Faust for CSOUND](TODO): a [CSOUND](https://csound.com/) opcode running the 
Faust compiler internally
* [LibAudioStream](TODO): a framework to manipulate audio ressources through 
the concept of streams
* [Faust for JUCE](TODO): a tool integrating the Faust compiler to 
[JUCE](https://juce.com/) developed by Oliver Larkin and available as part of 
the [pMix2 project](https://github.com/olilarkin/pMix2)
* An experimental integration of Faust in 
[Antescofo](http://forumnet.ircam.fr/product/antescofo-en/)
* FaucK: the combination of the 
[ChucK Programming Language](http://chuck.cs.princeton.edu/) and Faust 
