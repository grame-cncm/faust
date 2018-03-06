% man(1) Version 1.01 (20 February 2018) | Faust man page

NAME
====

Faust  -  DSP  to  C/C++,  Rust,  LLVM  IR,  JAVA,  JavaScript, asm.js,
WebAssembly (wast/wasm), Interpreter compiler

SYNOPSIS
========

 **faust** \[options] file1 \[file2 ...]

DESCRIPTION
===========

Faust (Functional Audio Stream) is a functional programming language specifically designed for real-time signal processing and synthesis. Faust targets high-performance signal processing applications and audio plug-ins for a variety of platforms and standards.

OPTIONS
=======

**-h**, **--help**
print help message

**-v**, **--version**
print the compiler version

**-d**, **--details**
print compilation details

**-tg**, **--task-graph**
generate the internal task graph in dot format file

**-sg**, **--signal-graph**
generate the internal signal graph in dot format file

**-ps**, **--postscript**
generate a block-diagram representation of the program as a postscript file

**-svg**, **--svg**
generate a block-diagram representation of the program as an SVG file

**-mdoc**, **--mathdoc**
generate the mathematical documentation of a program in LaTeX format

**-mdlang \<l>**, **--mathdoc-lang \<l>**
load mathdoc language \<l> if translation file exists (\<l> = en, fr, ...)

**-stripmdoc**, **--strip-mdoc-tags**
strip mdoc tags when printing Faust -mdoc listings

**-sd**, **--simplify-diagrams**
try to further simplify block-diagrams before drawing them

**-f \<n>**, **--fold \<n>**
set fold threshold used during block-diagram generation (default 25 elements)

**-mns \<n>**, **--max-name-size \<n>**
set max name size threshold during block-diagram generation (default 40 char)

**-sn**, **--simple-names**
use simpler names (without arguments) during block-diagram generation

**-xml** generate an XML description file of the user interface

**-exp10**, **--generate-exp10** function call instead of pow(10) function

**-json** generate a JSON description file of the user interface

**-blur**, **--shadow-blur**
add a shadow blur to SVG boxes

**-lb**, **--left-balanced**
generate left-balanced expressions

**-mb**, **--mid-balanced**
generate mid-balanced expressions (default)

**-rb**, **--right-balanced**
generate right-balanced expressions

**-lt**, **--less-temporaries**
generate less-temporaries when compiling delay lines

**-mcd \<n>**, **--max-copy-delay \<n>**
threshold used to switch from copy based to ring buffer based delay lines (default 16 samples)

**-mem**, **--memory**
allocate static memory in global state using a custom memory manager

**-a \<file>**
indicate the architecture file to use

**-i**, **--inline-architecture-files**
inline all architecture files in the generated code

**-cn \<name>**, **--class-name \<name>**
specify the name of the dsp class to be used instead of mydsp

**-pn \<name>**, **--process-name  \<name>**
specify the name of the dsp entry-point instead of process

**-t \<sec>**, **--timeout \<sec>**
abort compilation after <sec> seconds (default 120)

**-time**, **--compilation-time**
display timing information of the various compilation phases

**-o \<file>**
output file to use for the generated code

**-scal**, **--scalar**
generate code as a single loop

**-vec**, **--vectorize**
generate code as a DAG of multiple loops easier to auto vectorize

**-vls \<n>**, **--vec-loop-size \<n>**
size of the vector DSP loop for auto-vectorization (experimental)

**-vs \<n>**, **--vec-size \<n>**
size of the vector (default 32 samples)

**-lv \<n>**, **--loop-variant \<n>**
Control how loops are generated [<n> = 0:fastest (default), 1:simple]

**-omp**, **--openMP**
generate OpenMP pragmas, activates --vectorize option

**-pl**, **--par-loop**
generate parallel loops in --openMP mode

**-sch**, **--scheduler**
generate tasks and use a Work Stealing scheduler, activates --vectorize option

**-ocl**, **--openCL**
generate tasks with OpenCL (experimental)

**-cuda**, **--cuda**
generate tasks with CUDA (experimental)

**-dfs**, **--deepFirstScheduling**
schedule vector loops in deep first order

**-g**, **--groupTasks**
group single-threaded sequential tasks together when -omp or -sch is used

**-fun**, **--funTasks**
separate tasks code as separated functions (in -vec, -sch, or -omp mode)

**-lang \<lang>**, **--language \<lang>**
generate various output formats  : c, ocpp, cpp, rust, java, js, ajs, llvm, cllvm, fir, wast/wasm, interp
(default cpp)

**-uim**, **--user-interface-macros**
add user interface macro definitions in the output code

**-single**, **--single-precision-floats**
uses single-precisions floats for audio computations (default)

**-double**, **--double-precision-floats**
uses double-precision floats for audio computations

**-quad**, **--quad-precision-floats**
uses quad-precision floats for audio computations

**-es 1|0**, **--enable-semantics 1|0**
use enable semantics when 1, and simple multiplication otherwise

**-flist**, **--file-list**
list all the files used to eval process

**-norm**, **--normalized-form** 
prints signals in normalized form and exits

**-A \<dir>**, **--architecture-dir \<dir>** 
add the directory \<dir> to the architecture search path

**-I \<dir>**, **--import-dir \<dir>** 
add the directory \<dir> to the import search path

**-L \<file>**, **--library \<file>** 
link with the LLVM module \<file>

**-O \<dir>**, **--output-dir \<dir>** 
specify the relative directory of the generated output code, and the output directory of additional generated files (SVG, XML...)

**-e**, **--export-dsp**
export expanded DSP code (all included libraries)

**-inpl**, **--in-place**
generate inplace code when input and output buffers are the same (in scalar mode only)

**-inj \<f>**, **--inject \<f>**
inject source file \<f> into architecture file instead of compiling a dsp file

**-ftz**, **--flush-to-zero**
Adds flush-to-zero code to recursive signals [0:no (default), 1:fabs based, 2:mask based (fastest)]

**-fm \<file>**, **--fast-math \<file>**
uses optimized versions of mathematical functions implemented in \<file>, takes the '/faust/dsp/fastmath.cpp' file if 'def' is used

SEE ALSO
========

Grame Faust site at: **<http://faust.grame.fr>**

BUGS
====

Please report bugs to: **<https://github.com/grame-cncm/faust/issues>**

AUTHOR
======

Copyright (C) 2002-2018, GRAME - Centre National de Creation Musicale.
All rights reserved.

