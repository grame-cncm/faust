# Using the Faust Compiler

While the Faust compiler is available in different forms (e.g., 
[Embedded Compiler](TODO), etc.), its most "common" one is the command line
version, which can be invoked using the `faust` command. It translates 
a Faust program into code in a wide range of languages (C, O-C++, C++, Rust, 
JAVA, JavaScript, ASM JavaScript, LLVM, C-LLVM, FIR, and WebAssembly). The 
generated code can be wrapped into an optional *architecture file* allowing to 
directly produce a fully operational program.

A typical call of the Faust command line compiler is:

```
faust [OPTIONS] faustFile.dsp
```

The Faust compiler outputs C++ code by default therefore running 

```
faust noise.dsp 
```

will compile [`noise.dsp`](misc/noise.dsp) and output the corresponding C++ 
code on the standard output. The option `-o` allows to reroute the standard 
output to a file: 

```
faust noise.dsp -o noise.cpp
```

The `-a` option allows us to wrap the generated code into an architecture file:

```
faust -a alsa-gtk.cpp noise.dsp 
```

which can either be placed in the same folder as the current Faust file 
(`noise.dsp` here) or be one of the standard Faust architectures.

<!-- TODO: we must check if talk about architectures somewhere in greater
details and put a link to that here -->

To compile a Faust program into an ALSA application on Linux, the following 
commands can be used: 

```
faust -a alsa-gtk.cpp noise.dsp -o noise.cpp
g++ -lpthread -lasound `pkg-config --cflags --libs gtk+-2.0` noise.cpp -o noise
```

Note that a wide range of [`faust2...` compilation scripts](TODO) can be used
to facilitate this operation by taking a Faust file and returning the
corresponding binary for your platform.

## Structure of the Generated Code

A Faust DSP C++ class derives from the base `dsp` class defined as below (a
similar structure is used for languages than C++):

```
class dsp {
  public:
  dsp() {}
  virtual ~dsp() {}
  
  // Returns the number of inputs of the Faust program
  virtual int getNumInputs() = 0;
  
  // Returns the number of outputs of the Faust program
  virtual int getNumOutputs() = 0;
  
  // This method can be called to retrieve the UI description of
  // the Faust program and its associated fields
  virtual void buildUserInterface(UI* ui_interface) = 0;
  
  // Returns the current sampling rate
  virtual int getSampleRate() = 0;
  
  // Init methods
  virtual void init(int samplingRate) = 0;
  virtual void instanceInit(int samplingRate) = 0;
  virtual void instanceConstants(int samplingRate) = 0;
  virtual void instanceResetUserInterface() = 0;
  virtual void instanceClear() = 0;
  
  // Returns a clone of the instance
  virtual dsp* clone() = 0;
  
  // Retrieve the global metadata of the Faust program
  virtual void metadata(Meta* m) = 0;
  
  // Compute one audio frame
  virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
  
  // Compute a time-stamped audio frame
  virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs,
     FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
};
```

Methods are filled by the compiler with the actual code. In the case of
`noise.dsp`:

```
class mydsp : public dsp {
  private:
  int iRec0[2];
  int fSamplingFreq;
  
  public:
  void metadata(Meta* m) { 
    m->declare("author", "GRAME");
    m->declare("filename", "noise");
    m->declare("name", "Noise");
    m->declare("noises.lib/name", "Faust Noise Generator Library");
    m->declare("noises.lib/version", "0.0");
  }
  virtual int getNumInputs() {
    return 0;
  }
  virtual int getNumOutputs() {
    return 1;
  }
  virtual int getInputRate(int channel) {
    int rate;
    switch (channel) {
      default: {
        rate = -1;
        break;
      }
    }
    return rate;
  }
  virtual int getOutputRate(int channel) {
    int rate;
    switch (channel) {
      case 0: {
        rate = 1;
        break;
      }
      default: {
        rate = -1;
        break;
      }
    }
    return rate;
  }
  static void classInit(int samplingFreq) {}
  virtual void instanceConstants(int samplingFreq) {
    fSamplingFreq = samplingFreq;
  }
  virtual void instanceResetUserInterface() {}
  virtual void instanceClear() {
    for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
      iRec0[l0] = 0;
    }
  }
  virtual void init(int samplingFreq) {
    classInit(samplingFreq);
    instanceInit(samplingFreq);
  }
  virtual void instanceInit(int samplingFreq) {
    instanceConstants(samplingFreq);
    instanceResetUserInterface();
    instanceClear();
  }
  virtual mydsp* clone() {
    return new mydsp();
  }
  virtual int getSampleRate() {
    return fSamplingFreq;
  }
  virtual void buildUserInterface(UI* ui_interface) {
    ui_interface->openVerticalBox("Noise");
    ui_interface->closeBox();
  }
  virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
    FAUSTFLOAT* output0 = outputs[0];
    for (int i = 0; (i < count); i = (i + 1)) {
      iRec0[0] = ((1103515245 * iRec0[1]) + 12345);
      output0[i] = FAUSTFLOAT((4.65661287e-10f * float(iRec0[0])));
      iRec0[1] = iRec0[0];
    }
  }
};
```  

Several fine-grained initialization methods are available. The `instanceInit` 
method calls several additional initialization methods. The `instanceConstants`
method sets the instance constant state. The `instanceClear` method resets the 
instance dynamic state (delay lines...).  The `instanceResetUserInterface` 
method resets all control value to their default state. All of those methods 
can be used individually on an allocated instance to reset part of its state. 

The `init` method combines class static state and instance initialization.

When using a single instance, calling `init` is the simplest way to do 
"what is needed." When using several instances, all of them can be 
initialized using `instanceInit`, with a single call to `classInit` to 
initialize the static shared state.

## Compilation Options


| Short | Long | Description |
| --- | --- | --- |
| `-h` | `--help` | print the help message |
| `-v` | `--version` | print the compiler version information |
| `-d` | `--details` | print the compilation details |
| `-tg` | `--task-graph` | Draw a graph of all internal computational loops as `.dot` (graphviz) file |
| `-sg` | `--signal-graph` | Draw a graph of all internal computational loops as `.dot` (graphviz) file |
| `-ps` | `--postscript` | Generate the block-diagram postscript file |
| `-svg` | `--svg` | Generate the block-diagram svg file |
| `-mdoc` | `--mathdoc` | Generate the full mathematical documentation of a Faust program |
| `-mdlang <l>` | `--mathdoc-lang` | Choose the language of the mathematical description (*l* = en, fr, etc.) |
| `-stripmdoc` | `--strip-mdoc-tags` | Remove documentation tags when printing Faust listings |
| `-sd` | `--simplify-diagrams` |  Try to further simplify block diagrams before drawing them |
| `-f <n>` | `--fold <n>` | Max complexity of svg diagrams before splitting into several files (default 25 elements) |
| `-mns <n>` | `--max-name-size <n>` | Max character size used in svg diagrams labels |
| `-sn` | `--simple-names` | Use simple names (without arguments) for block-diagram generation (default max size: 40 chars) |
| `-xml` | `-xml` | Generate an XML description file |
| `-exp10` | `--generate-exp10` | Function call instead of pow(10) function |
| `-json` | `-json` | Generate a JSON description file |
| `-blur` | `--shadow-blur` | Add a blur to boxes shadows in block diagrams |
| `-lb` | `--left-balanced` | Generate left-balanced expressions in block diagrams |
| `-mb` | `--mid-balanced` | Generate mid-balanced expressions in block diagrams |
| `-rb` | `--right-balanced` | Generate right-balanced expressions in block diagrams |
| `-lt` | `--less-temporaries` | Generate less temporaries in compiling delays |
| `-mcd <n>` | `--max-copy-delay <n>` | Threshold between copy and ring buffer delays (default 16 samples) |
| `-mem` | `--memory` | Allocate static in global state using a custom memory manager |
| `-a <file>` | `-a` | Specifies a wrapper architecture file |
| `-i` | `--inline-architecture-files` | Inline architecture files in the generated code | 
| `-cn <name>` | `--class-name <name>` | Specify the name of the DSP class to be used instead of `mydsp` | 
| `-scn <name>` | `--super-class-name <name>` | Specify the name of the super class to be used instead of `dsp` | 
| `-pn <name>` | `--process-name <name>` | Specify the name of the dsp entry-point instead of process |
| `-t <sec>` | `--timeout <sec>` | Abort compilation after `<sec>` seconds (default 120) |
| `-time` | `--compilation-time` | Flag to display compilation phases timing information |
| `-o <file>` | `-o <file>` | C, C++, JAVA, JavaScript, ASM JavaScript, WebAssembly, LLVM IR or FVM (interpreter) output file |
| `-scal` | `--scalar` | Generate non-vectorized code |
| `-vec` | `--vectorize` | Generate easier to vectorize code |
| `-vs <n>` | `--vec-size <n>` | Size of the vector (default 32 samples) |
| `-lv <n>` | `--loop-variant` | Loop variant when `-vec` [0:fastest (default), 1:simple] |
| `-omp` | `--openMP` | Generate OpenMP pragmas, activates the `--vectorize` option |
| `-pl` | `--par-loop` | Generate parallel loops in `--openMP` mode |
| `-sch` | `--scheduler` | Generate tasks and use a Work Stealing scheduler, activates the `--vectorize` option |
| `-ocl` | `--openCL` | Generate tasks with OpenCL (experimental) | 
| `-cuda`| `--cuda` | Generate tasks with CUDA (experimental) | 
| `-dfs` | `--deepFirstScheduling` | Schedule vector loops in deep first order |
| `-g` | `--groupTasks` | Group single-threaded sequential tasks together when `-omp` or `-sch` is used |
| `-fun` | `--funTasks` | Separate tasks code as separated functions (in `-vec`, `-sch`, or `-omp` mode) |
| `-lang <lang>` | `--language` | Generate various output formats: `c`, `ocpp`, `cpp`, `rust`, `java`, `js`, `ajs`, `llvm`, `cllvm`, `fir`, `wast`/`wasm`, `interp` (default `cpp`) |
| `-uim` | `--user-interface-macros` | Add user interface macro definitions in the output code |
| `-single` | `--single-precision-floats` | Use single precision floats for internal computations (default) |
| `-double` | `--double-precision-floats` | Use `--double-precision-floats` for internal computations |
| `-quad` | `--quad-precision-floats` | Use quad precision floats for internal computations |
| `-es 1|0` | `--enable-semantics 1|0` | Use `--enable-semantics 1|0` when 1, and simple multiplication otherwise |
| `-flist` | `--file-list` | Use --file-list used to eval process |
| `-norm` | `--normalized-form` | Prints signals in normalized form and exits |
| `-A <dir>` | `--architecture-dir <dir>` | Add the directory `<dir>` to the architecture search path |
| `-I <dir>` | `--import-dir <dir>` | Add the directory `<dir>` to the import search path |
| `-L <file>` | `--library <file>` | Link with the LLVM module `<file>` |
| `-O <dir>` | `--output-dir <dir>` | Specify the relative directory of the generated output code, and the output directory of additional generated files (SVG, XML, etc.) |
| `-e` | `--export-dsp` | Export expanded DSP (all included libraries) |
| `-inpl` | `--in-place generates` | Code working when input and output buffers are the same (in scalar mode only) | 
| `-inj <f>` | `--inject <f>` | inject source file `<f>` into architecture file instead of compile a dsp file |
| `-ftz` | `--flush-to-zero` | Flush to zero the code added to recursive signals [0:no (default), 1:fabs based, 2:mask based (fastest)] |
| `-fm <file>` | `--fast-math <file>` | Uses optimized versions of mathematical functions implemented in `<file>`, take the `/faust/dsp/fastmath.cpp` file if 'def' is used |
