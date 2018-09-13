# Embedding the Faust Compiler using `libfaust`

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
published with an associated API that imitates the concept of oriented-object 
languages, like C++. Given a Faust source code (as a file or a string), calling 
the `createDSPFactoryXXX` function runs the compilation chain (Faust + LLVM 
JIT) and generates the *prototype* of the class, as a `llvm_dsp_factory` 
pointer.

```
class llvm_dsp_factory : public dsp_factory {
  public:
  virtual ~llvm_dsp_factory();
  
  // Return factory name
  std::string getName();
  
  // Return factory LLVM target
  std::string getTarget();
  
  // Return factory SHA key
  std::string getSHAKey();
  
  // Return factory expanded DSP code
  std::string getDSPCode();
  
  // Create a new DSP instance, to be deleted with C++ 'delete'
  llvm_dsp* createDSPInstance();
  
  // Set a custom memory manager to be used when creating instances
  void setMemoryManager(dsp_memory_manager* manager);
  
  // Return the currently set custom memory manager
  dsp_memory_manager* getMemoryManager();
  
  // Get the Faust DSP factory list of library dependancies
  std::vector<std::string> getLibraryList();
  
  // Get the list of all used includes
  std::vector<std::string> getIncludePathnames();
};
```

