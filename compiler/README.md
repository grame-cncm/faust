% man(1) Version 2.60.6 (30-June-2023) | Faust man page

NAME
====

Faust - DSP to C/C++, CMajor, CSharp, DLang, Interpreter, Java, LLVM IR, Rust and WebAssembly (wast/wasm)

SYNOPSIS
========

 **faust** \[options] file1 \[file2 ...]

DESCRIPTION
===========

Faust (Functional Audio Stream) is a functional programming language specifically designed for real-time signal processing and synthesis. Faust targets high-performance signal processing applications and audio plug-ins for a variety of platforms and standards.

OPTIONS
===========

Input options:
---------------------------------------

  **-a** \<file>                               wrapper architecture file.

  **-i**        **--inline-architecture-files**   inline architecture files.

  **-A** \<dir>  **--architecture-dir** \<dir>      add the directory \<dir> to the architecture search path.

  **-I** \<dir>  **--import-dir** \<dir>            add the directory \<dir> to the libraries search path.

  **-L** \<file> **--library** \<file>              link with the LLVM module \<file>.


Output options:
---------------------------------------

  **-o** \<file>                               the output file.

  **-e**        **--export-dsp**                  export expanded DSP (with all included libraries).

  **-uim**      **--user-interface-macros**       add user interface macro definitions to the output code.

  **-xml**                                    generate an XML description file.

  **-json**                                   generate a JSON description file.

  **-O** \<dir>  **--output-dir** \<dir>            specify the relative directory of the generated output code and of additional generated files (SVG, XML...).


Code generation options:
---------------------------------------

  **-lang** \<lang> **--language**                 select output language,
                                          'lang' should be c, cpp (default), cmajor, csharp, dlang, fir, interp, java, jax, jsfx, julia, llvm, ocpp, rust or wast/wasm.

  **-single**     **--single-precision-floats**   use single precision floats for internal computations (default).

  **-double**     **--double-precision-floats**   use double precision floats for internal computations.

  **-quad**       **--quad-precision-floats**     use quad precision floats for internal computations.

  **-fx**         **--fixed-point**               use fixed-point for internal computations.

  **-es** 1|0     **--enable-semantics** 1|0      use enable semantics when 1 (default), and simple multiplication otherwise.

  **-lcc**        **--local-causality-check**     check causality also at local level.

  **-light**      **--light-mode**                do not generate the entire DSP API.

  **-clang**      **--clang**                     when compiled with clang/clang++, adds specific #pragma for auto-vectorization.

  **-nvi**        **--no-virtual**                when compiled with the C++ backend, does not add the 'virtual' keyword.

  **-fp**         **--full-parentheses**          always add parentheses around binops.

  **-cir**        **--check-integer-range**       check float to integer range conversion.

  **-exp10**      **--generate-exp10**            pow(10,x) replaced by possibly faster exp10(x).

  **-os**         **--one-sample**                generate one sample computation (same as -os0).

  **-os0**        **--one-sample0**               generate one sample computation (0 = separated control).

  **-os1**        **--one-sample1**               generate one sample computation (1 = separated control and DSP struct).

  **-os2**        **--one-sample2**               generate one sample computation (2 = separated control and DSP struct. Separation in short and long delay lines).

  **-os3**        **--one-sample3**               generate one sample computation (3 = like 2 but with external memory pointers kept in the DSP struct).

  **-cm**         **--compute-mix**               mix in outputs buffers.

  **-ct**         **--check-table**               check rtable/rwtable index range and generate safe access code [0/1: 1 by default].

  **-cn** \<name>  **--class-name** \<name>         specify the name of the dsp class to be used instead of mydsp.

  **-scn** \<name> **--super-class-name** \<name>   specify the name of the super class to be used instead of dsp.

  **-pn** \<name>  **--process-name** \<name>       specify the name of the dsp entry-point instead of process.

  **-mcd** \<n>    **--max-copy-delay** \<n>        threshold between copy and ring buffer implementation (default 16 samples).

  **-dlt** \<n>    **--delay-line-threshold** \<n>  threshold between 'mask' and 'select' ring buffer implementation (default INT_MAX samples).

  **-mem**        **--memory-manager**            allocate static in global state using a custom memory manager.

  **-ftz** \<n>    **--flush-to-zero** \<n>         code added to recursive signals [0:no (default), 1:fabs based, 2:mask based (fastest)].

  **-rui**        **--range-ui**                  whether to generate code to constraint vslider/hslider/nentry values in [min..max] range.

  **-fui**        **--freeze-ui**                 whether to freeze vslider/hslider/nentry to a given value (init value by default).

  **-inj** \<f>    **--inject** \<f>                inject source file \<f> into architecture file instead of compiling a dsp file.

  **-scal**       **--scalar**                    generate non-vectorized code (default).

  **-inpl**       **--in-place**                  generates code working when input and output buffers are the same (scalar mode only).

  **-vec**        **--vectorize**                 generate easier to vectorize code.

  **-vs** \<n>     **--vec-size** \<n>              size of the vector (default 32 samples).

  **-lv** \<n>     **--loop-variant** \<n>          [0:fastest, fixed vector size and a remaining loop (default), 1:simple, variable vector size].

  **-omp**        **--openmp**                    generate OpenMP pragmas, activates --vectorize option.

  **-pl**         **--par-loop**                  generate parallel loops in --openmp mode.

  **-sch**        **--scheduler**                 generate tasks and use a Work Stealing scheduler, activates --vectorize option.

  **-ocl**        **--opencl**                    generate tasks with OpenCL (experimental).

  **-cuda**       **--cuda**                      generate tasks with CUDA (experimental).

  **-dfs**        **--deep-first-scheduling**     schedule vector loops in deep first order.

  **-g**          **--group-tasks**               group single-threaded sequential tasks together when -omp or -sch is used.

  **-fun**        **--fun-tasks**                 separate tasks code as separated functions (in -vec, -sch, or -omp mode).

  **-fm** \<file>  **--fast-math** \<file>          use optimized versions of mathematical functions implemented in \<file>, use 'faust/dsp/fastmath.cpp' when file is 'def', assume functions are defined in the architecture file when file is 'arch'.

  **-mapp**       **--math-approximation**        simpler/faster versions of 'floor/ceil/fmod/remainder' functions.

  **-ns** \<name>  **--namespace** \<name>          generate C++ or D code in a namespace \<name>.

  **-vhdl**          **--vhdl**                   output vhdl file.

  **-vhdl**-trace    **--vhdl-trace**             activate trace.

  **-vhdl**-type 0|1 **--vhdl-type** 0|1          sample format 0 = sfixed (default), 1 = float.

  **-vhdl**-msb \<n>  **--vhdl-msb** \<n>           Most Significant Bit (MSB) position.

  **-vhdl**-lsb \<n>  **--vhdl-lsb** \<n>           Less Significant Bit (LSB) position.

  **-fpga**-mem \<n>  **--fpga-mem** \<n>           FPGA block ram max size, used in -os2/-os3 mode.

  **-wi** \<n>     **--widening-iterations** \<n>   number of iterations before widening in signal bounding.

  **-ni** \<n>     **--narrowing-iterations** \<n>  number of iterations before stopping narrowing in signal bounding.


Block diagram options:
---------------------------------------

  **-ps**        **--postscript**                 print block-diagram to a postscript file.

  **-svg**       **--svg**                        print block-diagram to a svg file.

  **-sd**        **--simplify-diagrams**          try to further simplify diagrams before drawing.

  **-drf**       **--draw-route-frame**           draw route frames instead of simple cables.

  **-f** \<n>     **--fold** \<n>                   threshold to activate folding mode during block-diagram generation (default 25 elements).

  **-fc** \<n>    **--fold-complexity** \<n>        complexity threshold to fold an expression in folding mode (default 2).

  **-mns** \<n>   **--max-name-size** \<n>          threshold during block-diagram generation (default 40 char).

  **-sn**        **--simple-names**               use simple names (without arguments) during block-diagram generation.

  **-blur**      **--shadow-blur**                add a shadow blur to SVG boxes.

  **-sc**        **--scaled-svg**                 automatic scalable SVG.


Math doc options:
---------------------------------------

  **-mdoc**       **--mathdoc**                   print math documentation of the Faust program in LaTeX format in a -mdoc folder.

  **-mdlang** \<l> **--mathdoc-lang** \<l>          if translation file exists (\<l> = en, fr, ...).

  **-stripmdoc**  **--strip-mdoc-tags**           strip mdoc tags when printing Faust -mdoc listings.


Debug options:
---------------------------------------

  **-d**          **--details**                   print compilation details.

  **-time**       **--compilation-time**          display compilation phases timing information.

  **-flist**      **--file-list**                 print file list (including libraries) used to eval process.

  **-tg**         **--task-graph**                print the internal task graph in dot format.

  **-sg**         **--signal-graph**              print the internal signal graph in dot format.

  **-norm**       **--normalized-form**           print signals in normalized form and exit.

  **-me**         **--math-exceptions**           check / for 0 as denominator and remainder, fmod, sqrt, log10, log, acos, asin functions domain.

  **-sts**        **--strict-select**             generate strict code for 'selectX' even for stateless branches (both are computed).

  **-wall**       **--warning-all**               print all warnings.

  **-t** \<sec>    **--timeout** \<sec>             abort compilation after \<sec> seconds (default 120).


Information options:
---------------------------------------

  **-h**          **--help**                      print this help message.

  **-v**          **--version**                   print version information and embedded backends list.

  **-libdir**     **--libdir**                    print directory containing the Faust libraries.

  **-includedir** **--includedir**                print directory containing the Faust headers.

  **-archdir**    **--archdir**                   print directory containing the Faust architectures.

  **-dspdir**     **--dspdir**                    print directory containing the Faust dsp libraries.

  **-pathslist**  **--pathslist**                 print the architectures and dsp library paths.


Example:
---------------------------------------

faust **-a** jack-gtk.cpp -o myfx.cpp myfx.dsp

SEE ALSO
========

Grame Faust site at: **<https://faust.grame.fr>**

BUGS
====

Please report bugs to: **<https://github.com/grame-cncm/faust/issues>**

AUTHOR
======

Copyright (C) 2002-2023, GRAME - Centre National de Creation Musicale.
All rights reserved.

