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

## Controlling Code Generation

Several options of the Faust compiler allow to control the generated C++ code. 
By default computation is done sample by sample in a single loop. But the 
compiler can also generate *vector* and *parallel* code.

### Vector Code Generation
  
Modern C++ compilers are able to do autovectorization, that is to use SIMD 
instructions to speedup the code. These instructions can typically operate in 
parallel on short vectors of 4 simple precision floating point numbers, leading 
to a theoretical speedup of $\times4$.
 
Autovectorization of C/C++ programs is a difficult task. Current compilers are 
very sensitive to the way the code is arranged. In particular, complex loops 
can prevent autovectorization. The goal of the vector code generation is to 
rearrange the C++ code in a way that facilitates the autovectorization job of 
the C++ compiler. Instead of generating a single sample computation loop, it 
splits the computation into several simpler loops that communicates by vectors.

The vector code generation is activated by passing the 
[`--vectorize` (or `-vec`)](#compilation-options) option to the Faust compiler. 
Two additional options are available: `--vec-size <n>` controls the size of the 
vector (by default 32 samples) and `--loop-variant 0/1` gives some additional 
control on the loops.  

To illustrate the difference between scalar code and vector code, let's take 
the computation of the RMS (Root Mean Square) value of a signal.  Here is the 
Faust code that computes the Root Mean Square of a sliding window of 1000 
samples:

<!-- faust-run -->
```
// Root Mean Square of n consecutive samples
RMS(n) = square : mean(n) : sqrt;

// Square of a signal
square(x) = x * x;

// Mean of n consecutive samples of a signal (uses fixpoint to avoid the 
// accumulation of rounding errors) 
mean(n) = float2fix : integrate(n) : fix2float : /(n); 

// Sliding sum of n consecutive samples
integrate(n,x) = x - x@n : +~_;

// Convertion between float and fix point
float2fix(x) = int(x*(1<<20));      
fix2float(x) = float(x)/(1<<20);    

// Root Mean Square of 1000 consecutive samples
process = RMS(1000);
```
<!-- /faust-run -->

The [corresponding `compute()` method](#strucutre-of-the-generated-code) 
generated in scalar mode is the following:

```
virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
  FAUSTFLOAT* input0 = inputs[0];
  FAUSTFLOAT* output0 = outputs[0];
  for (int i = 0; (i < count); i = (i + 1)) {
    int iTemp0 = int((1048576.0f * mydsp_faustpower2_f(float(input0[i]))));
    iVec0[(IOTA & 1023)] = iTemp0;
    iRec0[0] = ((iRec0[1] + iTemp0) - iVec0[((IOTA - 1000) & 1023)]);
    output0[i] = FAUSTFLOAT(std::sqrt((9.53674362e-10f * float(iRec0[0]))));
    IOTA = (IOTA + 1);
    iRec0[1] = iRec0[0];
  }
}
```

The `-vec` option leads to the following reorganization of the code:

```
virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
  fInput0_ptr = inputs[0];
  FAUSTFLOAT* fInput0 = 0;
  fOutput0_ptr = outputs[0];
  FAUSTFLOAT* fOutput0 = 0;
  int iRec0_tmp[36];
  int* iRec0 = &iRec0_tmp[4];
  int fullcount = count;
  int index = 0;
  /* Main loop */
  for (index = 0; (index <= (fullcount - 32)); index = (index + 32)) {
    fInput0 = &fInput0_ptr[index];
    fOutput0 = &fOutput0_ptr[index];
    int count = 32;
    /* Recursive loop 0 */
    /* Pre code */
    iYec0_idx = ((iYec0_idx + iYec0_idx_save) & 2047);
    /* Compute code */
    for (int i = 0; (i < count); i = (i + 1)) {
      iYec0[((i + iYec0_idx) & 2047)] = 
      int((1048576.0f mydsp_faustpower2_f(float(fInput0[i]))));
    }
    /* Post code */
    iYec0_idx_save = count;
    /* Recursive loop 1 */
    /* Pre code */
    for (int j0 = 0; (j0 < 4); j0 = (j0 + 1)) {
      iRec0_tmp[j0] = iRec0_perm[j0];
    }
    /* Compute code */
    for (int i = 0; (i < count); i = (i + 1)) {
      iRec0[i] = ((iRec0[(i - 1)] + iYec0[((i + iYec0_idx) & 2047)]) - 
      iYec0[(((i + iYec0_idx) - 1000) & 2047)]);
    }
    /* Post code */
    for (int j = 0; (j < 4); j = (j + 1)) {
      iRec0_perm[j] = iRec0_tmp[(count + j)];
    }
    /* Vectorizable loop 2 */
    /* Compute code */
    for (int i = 0; (i < count); i = (i + 1)) {
      fOutput0[i] = FAUSTFLOAT(std::sqrt((9.53674362e-10f * float(iRec0[i]))));
    }
  }
  
  /* Remaining frames */
  if (index < fullcount) {
    fInput0 = &fInput0_ptr[index];
    fOutput0 = &fOutput0_ptr[index];
    int count = (fullcount - index);
    /* Recursive loop 0 */
    /* Pre code */
    iYec0_idx = ((iYec0_idx + iYec0_idx_save) & 2047);
    /* Compute code */
    for (int i = 0; (i < count); i = (i + 1)) {
      iYec0[((i + iYec0_idx) & 2047)] = int((1048576.0f * 
        mydsp_faustpower2_f(float(fInput0[i]))));
    }
    /* Post code */
    iYec0_idx_save = count;
    /* Recursive loop 1 */
    /* Pre code */
    for (int j0 = 0; (j0 < 4); j0 = (j0 + 1)) {
      iRec0_tmp[j0] = iRec0_perm[j0];
    }
    /* Compute code */
    for (int i = 0; (i < count); i = (i + 1)) {
      iRec0[i] = ((iRec0[(i - 1)] + iYec0[((i + iYec0_idx) & 2047)]) - 
      iYec0[(((i + iYec0_idx) - 1000) & 2047)]);
    }
    /* Post code */
    for (int j = 0; (j < 4); j = (j + 1)) {
      iRec0_perm[j] = iRec0_tmp[(count + j)];
    }
    /* Vectorizable loop 2 */
    /* Compute code */
    for (int i = 0; (i < count); i = (i + 1)) {
      fOutput0[i] = FAUSTFLOAT(std::sqrt((9.53674362e-10f * float(iRec0[i]))));
    }
  }
}
```

While the second version of the code is more complex, it turns out to be much 
easier to vectorize efficiently by the C++ compiler. With the exact same 
compilation options: `-O3 -xHost -ftz -fno-alias -fp-model fast=2`, the scalar 
version leads to a throughput performance of 129.144  MB/s, while the vector 
version achieves 359.548  MB/s, a speedup of x2.8 ! 

<img src="img/compilerStack.svg" class="mx-auto d-block" width="30%">

The vector code generation is built on top of the scalar code generation (see 
previous figure). Every time an expression needs to be compiled, the compiler 
checks if it requires a separate loop or not. Expressions that are shared (and 
are complex enough) are good candidates to be compiled in a separate loop, as 
well as recursive expressions and expressions used in delay lines. 

The result is a directed graph in which each node is a computation loop (see 
figure below). This graph is stored in the class object and a topological 
sort is applied to it before printing the code. 

<img src="img/loopgraph2.svg" class="mx-auto d-block" width="30%">

### Parallel Code Generation

Parallel code generation is activated by passing either the [`--openMP` (or 
`-omp`) option or the `--scheduler` (or `-sch`) option](#compilation-options). 
It implies that the `-vec` option as well as the parallel code generation are 
built on top of the vector code generation.

#### The OpenMP Code Generator

<img src="img/openmpModel.svg" class="mx-auto d-block" width="100%">

The [`--openMP` (or `-omp`) option](#compilation-options), when given to the 
Faust compiler, will insert appropriate [OpenMP](https://www.openmp.org/) 
directives into the C++ code. OpenMP is a well established API that is used to 
explicitly define direct multi-threaded, shared memory parallelism. It is based 
on a fork-join model of parallelism (see figure above). Parallel regions are 
delimited by `#pragma omp parallel` constructs. At the entrance of a parallel 
region, a group of parallel threads is activated. The code within a parallel 
region is executed by each thread of the parallel group until the end of the 
region. 

```
#pragma omp parallel
{
  // the code here is executed simultaneously by every thread of the parallel 
  // team
  ...
}
```

In order not to have every thread doing redundantly the exact same work, OpenMP 
provides specific *work-sharing* directives. For example `#pragma omp sections` 
allows to break the work into separate, discrete sections, each section being 
executed by one thread:

```
#pragma omp parallel
{
  #pragma omp sections
  {
    #pragma omp section
    {
      // job 1
    }
    #pragma omp section
    {
      // job 2
    }
    ...
  }
  ...
}
```

#### Adding Open MP Directives

As said before, parallel code generation is built on top of vector code 
generation. The graph of loops produced by the vector code generator is 
topologically sorted in order to detect the loops that can be computed in 
parallel. The first set $S_0$ (loops $L1$, $L2$ and $L3$) contains the loops 
that don't depend on any other loops, the set $S_1$ contains the loops that 
only depend on loops of $S_0$, (that is loops $L4$ and $L5$), etc.. 

As all the loops of a given set $S_n$ can be computed in parallel, the compiler 
will generate a `sections` construct with a `section` for each loop. 

```
#pragma omp sections
{
  #pragma omp section
  for (...) {
    // Loop 1
  }
  #pragma omp section
  for (...) {
    // Loop 2
  }
  ...
}
```

If a given set contains only one loop, then the compiler checks to see if the 
loop can be parallelized (no recursive dependencies) or not. If it can be 
parallelized, it generates:

```
#pragma omp for
for (...) {
 // Loop code
}
```

otherwise it generates a `single` construct so that only one thread will 
execute the loop:

```
#pragma omp single
for (...) {
 // Loop code
}
```

#### Example of Parallel OpenMP Code

To illustrate how Faust uses the OpenMP directives, here is a very simple 
example, two 1-pole filters in parallel connected to an adder:

<!-- faust-run -->
```
filter(c) = *(1-c) : + ~ *(c);
process = filter(0.9), filter(0.9) : +;
```
<!-- /faust-run -->

The corresponding `compute()` method obtained using the `-omp` option looks
like this:

```
virtual void compute(int fullcount, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
  float fRec0_tmp[36];
  float fRec1_tmp[36];
  FAUSTFLOAT* fInput0 = 0;
  FAUSTFLOAT* fInput1 = 0;
  FAUSTFLOAT* fOutput0 = 0;
  float* fRec0 = &fRec0_tmp[4];
  float* fRec1 = &fRec1_tmp[4];
  fInput0_ptr = inputs[0];
  fInput1_ptr = inputs[1];
  fOutput0_ptr = outputs[0];
  #pragma omp parallel\
      firstprivate(fInput0, fInput1, fOutput0, fRec0, fRec1)
  {
    for (int index = 0; (index < fullcount); index = (index + 32)) {
      fInput0 = &fInput0_ptr[index];
      fInput1 = &fInput1_ptr[index];
      fOutput0 = &fOutput0_ptr[index];
      int count = min(32, (fullcount - index));
      #pragma omp sections
      {
        #pragma omp section
        {
          /* Recursive loop 0 */
          /* Pre code */
          for (int j0 = 0; (j0 < 4); j0 = (j0 + 1)) {
            fRec0_tmp[j0] = fRec0_perm[j0];
          }
          /* Compute code */
          for (int i = 0; (i < count); i = (i + 1)) {
            fRec0[i] = ((0.899999976f * fRec0[(i - 1)]) + 
            (0.100000001f * float(fInput0[i])));
          }
          /* Post code */
          for (int j = 0; (j < 4); j = (j + 1)) {
            fRec0_perm[j] = fRec0_tmp[(count + j)];
          }
        }
        #pragma omp section
        {
          /* Recursive loop 1 */
          /* Pre code */
          for (int j1 = 0; (j1 < 4); j1 = (j1 + 1)) {
            fRec1_tmp[j1] = fRec1_perm[j1];
          }
          /* Compute code */
          for (int i = 0; (i < count); i = (i + 1)) {
            fRec1[i] = ((0.899999976f * fRec1[(i - 1)]) + 
            (0.100000001f * float(fInput1[i])));
          }
          /* Post code */
          for (int j = 0; (j < 4); j = (j + 1)) {
            fRec1_perm[j] = fRec1_tmp[(count + j)];
          }
        }
      }
      #pragma omp single
      {
        /* Vectorizable loop 2 */
        /* Compute code */
        for (int i = 0; (i < count); i = (i + 1)) {
          fOutput0[i] = FAUSTFLOAT((fRec0[i] + fRec1[i]));
        }
      }
    }
  }
}
```

This code requires some comments:

* The parallel construct `#pragma omp parallel` is the fundamental construct 
that starts parallel execution. The number of parallel threads is generally the 
number of CPU cores but it can be controlled in several ways.
* Variables external to the parallel region are shared by default. The pragma 
`firstprivate(fRec0,fRec1)` indicates that each thread should have its private 
copy of `fRec0` and `fRec1`. The reason is that accessing shared variables 
requires an indirection and is quite inefficient compared to private copies.
* The top level loop `for (int index = 0;...)...` is executed by all threads 
simultaneously. The subsequent work-sharing directives inside the loop will 
indicate how the work must be shared between threads. 
* Please note that an implied barrier exists at the end of each work-sharing 
region. All threads must have executed the barrier before any of them can 
continue.
* The work-sharing directive `#pragma omp single` indicates that this first 
section will be executed by only one thread (any of them).
* The work-sharing directive `#pragma omp sections` indicates that each 
corresponding `#pragma omp section`, here our two filters, will be executed in 
parallel.
* The loop construct `#pragma omp for` specifies that the iterations of the 
associated loop will be executed in parallel. The iterations of the loop are 
distributed across the parallel threads. For example, if we have two threads, 
the first one can compute indices between 0 and count/2 and the other one 
between count/2 and count. 
* Finally `#pragma omp single` indicates that this section will be executed 
by only one thread (any of them).

#### The Scheduler Code Generator

With the [`--scheduler` (or `-sch`) option](#compilation-options) given to the 
Faust compiler, the computation graph is cut into separate computation loops 
(called "tasks"), and a "Work Stealing Scheduler" is used to activate and 
execute them following their dependencies. A pool of worked threads is created 
and each thread uses it's own local WSQ (Work Stealing Queue) of tasks. A WSQ 
is a special queue with a Push operation, a "private" LIFO Pop operation and a 
"public" FIFO Pop operation.

Starting from a ready task, each thread follows the dependencies, possibly 
pushing ready sub-tasks into it's own local WSQ. When no more tasks can be 
activated on a given computation path, the thread pops a task from it's local 
WSQ. If the WSQ is empty, then the thread is allowed to "steal" tasks from 
other threads WSQ.

The local LIFO Pop operation allows better cache locality and the FIFO steal 
Pop "larger chuck" of work to be done. The reason for this is that many work 
stealing workloads are divide-and-conquer in nature, stealing one of the oldest 
task implicitly also steals a (potentially) large sub-tree of computations that 
will unfold once that piece of work is stolen and run.

Compared to the OpenMP model (`-omp`) the new model is worse for simple Faust 
programs and usually starts to behave comparable or sometimes better for 
"complex enough" Faust programs. In any case, since OpenMP does not behave so 
well with GCC compilers, and is unusable on OSX in real-time contexts, this 
new scheduler option has it's own value.  We plan to improve it adding a 
"pipelining" idea in the future.

#### Example of Parallel Scheduler Code

To illustrate how Faust generates the scheduler code, let's reuse the previous
example made of two 1-pole filters in parallel connected to an adder:

<!-- faust-run -->
```
filter(c) = *(1-c) : + ~ *(c);
process = filter(0.9), filter(0.9) : +; 
```
<!-- /faust-run -->

When `-sch` option is used, the content of the additional 
`architecture/scheduler.h` file is inserted in the generated code. It contains 
code to deal with WSQ and thread management. The `compute()` and 
`computeThread()` methods are the following:

```
virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
  fInput0_ptr = inputs[0];
  fInput1_ptr = inputs[1];
  fOutput0_ptr = outputs[0];
  fCount = count;
  fIndex = 0;
  /* End task has only one input, so will be directly activated */
  /* Only initialize tasks with more than one input */
  initTask(fScheduler, 4, 2);
  /* Push ready tasks in each thread WSQ */
  initTaskList(fScheduler, -1);
  signalAll(fScheduler);
  computeThread(0);
  syncAll(fScheduler);
}
void computeThread(int num_thread) {
  int count = fCount;
  FAUSTFLOAT* fInput0 = 0;
  FAUSTFLOAT* fInput1 = 0;
  FAUSTFLOAT* fOutput0 = 0;
  int tasknum = 0;
  while ((fIndex < fCount)) {
    fInput0 = &fInput0_ptr[fIndex];
    fInput1 = &fInput1_ptr[fIndex];
    fOutput0 = &fOutput0_ptr[fIndex];
    count = min(32, (fCount - fIndex));
    switch (tasknum) {
      case 0: {
        /* Work Stealing task */
        tasknum = getNextTask(fScheduler, num_thread);
        break;
      }
      case 1: {
        /* Last task */
        fIndex = (fIndex + 32);
        if (fIndex < fCount) {
          /* End task has only one input, so will be directly activated */
          /* Only initialize tasks with more than one input */
          initTask(fScheduler, 4, 2);
          /* Push ready tasks in 'num_thread' WSQ */
          initTaskList(fScheduler, num_thread);
        }
        tasknum = 0;
        break;
      }
      case 2: {
        /* Recursive loop 2 */
        /* Pre code */
        for (int j0 = 0; (j0 < 4); j0 = (j0 + 1)) {
          fRec0_tmp[j0] = fRec0_perm[j0];
        }
        /* Compute code */
        for (int i = 0; (i < count); i = (i + 1)) {
          fRec0[i] = ((0.899999976f * fRec0[(i - 1)]) + 
          (0.100000001f * float(fInput0[i])));
        }
        /* Post code */
        for (int j = 0; (j < 4); j = (j + 1)) {
          fRec0_perm[j] = fRec0_tmp[(count + j)];
        }
        /* One output only */
        activateOneOutputTask(fScheduler, num_thread, 4, &tasknum);
        break;
      }
      case 3: {
        /* Recursive loop 3 */
        /* Pre code */
        for (int j1 = 0; (j1 < 4); j1 = (j1 + 1)) {
          fRec1_tmp[j1] = fRec1_perm[j1];
        }
        /* Compute code */
        for (int i = 0; (i < count); i = (i + 1)) {
          fRec1[i] = ((0.899999976f * fRec1[(i - 1)]) + 
          (0.100000001f * float(fInput1[i])));
        }
        /* Post code */
        for (int j = 0; (j < 4); j = (j + 1)) {
          fRec1_perm[j] = fRec1_tmp[(count + j)];
        }
        /* One output only */
        activateOneOutputTask(fScheduler, num_thread, 4, &tasknum);
        break;
      }
      case 4: {
        /* Vectorizable loop 4 */
        /* Compute code */
        for (int i = 0; (i < count); i = (i + 1)) {
          fOutput0[i] = FAUSTFLOAT((fRec0[i] + fRec1[i]));
        }
        tasknum = 1;
        break;
      }
    }
  }
}
```
