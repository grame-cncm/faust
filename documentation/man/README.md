% man(1) Version 2.87.11 (30-August-2026) | Faust man page

NAME
====

Faust - DSP to C/C++, CMajor, Codebox, CSharp, DLang, Interpreter, Java, LLVM IR, Julia, JSFX, Rust and WebAssembly (wast/wasm)

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
                                          'lang' should be asc, c, cpp (default), cmajor, codebox, csharp, dlang, fir, interp, java, jsfx, julia, linen, llvm, nnx, ocpp, rust, sdf3, vhdl or wast/wasm.

  **-single**     **--single-precision-floats**   use single precision floats for internal computations (default).

  **-double**     **--double-precision-floats**   use double precision floats for internal computations.

  **-quad**       **--quad-precision-floats**     use quad precision floats for internal computations.

  **-fx**         **--fixed-point**               use fixed-point for internal computations.

  **-fx**-size    **--fixed-point-size**          fixed-point number total size in bits (-1 is used to generate a unique fixpoint_t type).

  **-es** 1|0     **--enable-semantics** 1|0      use enable semantics when 1 (default), and simple multiplication otherwise.

  **-lcc**        **--local-causality-check**     check causality also at local level.

  **-light**      **--light-mode**                do not generate the entire DSP API.

  **-clang**      **--clang**                     when compiled with clang/clang++, adds specific #pragma for auto-vectorization.

  **-nvi**        **--no-virtual**                when compiled with the C++ backend, does not add the 'virtual' keyword.

  **-fp**         **--full-parentheses**          always add parentheses around binops.

  **-cir**        **--check-integer-range**       check float to integer range conversion.

  **-exp10**      **--generate-exp10**            pow(10,x) replaced by possibly faster exp10(x).

  **-os**         **--one-sample**                generate one sample computation.

  **-ec**         **--external-control**          separated 'control' and 'compute' functions.

  **-it**         **--inline-table**              inline rdtable/rwtable code in the main class.

  **-cm**         **--compute-mix**               mix in outputs buffers.

  **-ct**         **--check-table**               check rtable/rwtable index range and generate safe access code [0/1: 1 by default].

  **-cn** \<name>  **--class-name** \<name>         specify the name of the dsp class to be used instead of mydsp.

  **-scn** \<name> **--super-class-name** \<name>   specify the name of the super class to be used instead of dsp.

  **-pn** \<name>  **--process-name** \<name>       specify the name of the dsp entry-point instead of process.

  **-mcd** \<n>    **--max-copy-delay** \<n>        use a copy delay up to max delay \<n> and a dense delay above (ocpp only) or a ring buffer (defaut 16 samples).

  **-mdd** \<n>    **--max-dense-delay** \<n>       use a dense delay up to max delay \<n> (if enough density) and a ring buffer delay above (ocpp only, default 1024).

  **-mdy** \<n>    **--min-density** \<n>           minimal density (100*number of delays/max delay) to use a dense delays (ocpp only, default 33).

  **-dlt** \<n>    **--delay-line-threshold** \<n>  use a mask-based ring buffer delays up to max delay \<n> and a select based ring buffers above (default INT_MAX samples).

  **-mem**        **--memory-manager**            allocations done using a custom memory manager.

  **-mem1**       **--memory-manager1**           allocations done using a custom memory manager, using the iControl/fControl and iZone/fZone model.

  **-mem2**       **--memory-manager2**           use iControl/fControl, iZone/fZone model and no explicit memory manager.

  **-mem3**       **--memory-manager3**           use iControl/fControl, iZone/fZone model and no explicit memory manager with access as function parameters.

  **-ls**         **--loop-split**                (ocpp, experimental) emit the materialized DAG as separate loops.

  **-ls**-sched \<s> **--loop-split-scheduling** \<s> intra-loop op order: df (default), bf, model, layers, cs2, cs2b (implies -ls).

  **-ls**-R \<n>   **--loop-split-registers** \<n>  register budget of the model scheduler (default 20, implies -ls).

  **-ls**-U \<n>   **--loop-split-width** \<n>      superscalar width of the model scheduler (default 4, implies -ls).

  **-ls**-fuse    **--loop-split-fuse**           greedy single-consumer fusion of the super-node partition (implies -ls).

  **-ls**-fuse-ops \<n> **--loop-split-fuse-ops** \<n> op-count budget of a fused block (default 1024, compile-time guard; the cost oracle decides, implies -ls-fuse).

  **-mindelay** \<n> **--min-delay** \<n>           (ocpp, experimental) semantic floor for large variable delays: emits max(d, n) when certified dmin \< n and dmax >= 32*n; with n >= vector size, long feedback cycles split legally.

  **-rp**         **--ring-preload**              (ocpp, experimental) ring reads leave as a burst at the head of the loop body, a register move stays at the original slot.

  **-ss** \<n>     **--scheduling-strategy** \<n>   (ocpp, experimental) instruction order of the loop body: 0 depth-first (default), 8 aligned, 9 bank-compositional, 11/12 compositional deep/wide spine.

  **-fir**        **--fir-iir**                   (ocpp, experimental) recognise FIR/IIR kernels in the signal graph and emit their dedicated forms.

  **-iirt**       **--iir-transposed**            (ocpp, experimental) transposed emission for the all-pole kernels recognised by -fir.

  **-lsum**       **--lower-sums**                (ocpp, experimental) recover the polynomial form of large sums before emission.

  **-mxr**        **--matrix-rows**               (ocpp, experimental) group families of parallel rows over a shared vector into matrix-vector emission.

  **-temp** \<n>   **--temp-threshold** \<n>        (ocpp, experimental) materialize single-use expressions of n operations or more as temporaries (1 = SSA form, 0 = off).

  **-stage** \<n>  **--staging-threshold** \<n>     (ocpp, experimental) stage expressions nested deeper than n into named temporaries.

  **-reassoc**    **--reassociate**               (ocpp, experimental) late reassociation of the sums inside single-definition recursive groups (minimal recurrence chain).

  **-lazyselect** **--lazy-select**               (ocpp, experimental) compute the branches of a selection only when selected.

  **-selectn**    **--select-n**                  (ocpp, experimental) rebuild N-way dispatches from their select2 chains (implies -lazyselect).

  **-gatequiv**   **--gate-equivalence**          (ocpp, experimental) one canonical form for the two spellings of a gated signal, so guards reach further.

  **-ls**-cl \<n>  **--loop-split-cl** \<n>         oracle: per-loop per-chunk overhead (default 20 cycles, implies -ls-fuse).

  **-ls**-spill \<n> **--loop-split-spill-weight** \<n> oracle: cycles per register-cycle above R (default 4, implies -ls-fuse).

  **-ls**-load \<n> **--loop-split-load-weight** \<n> oracle: issue slots per buffer load (0 = free, default 1, implies -ls-fuse).

  **-ftz** \<n>    **--flush-to-zero** \<n>         code added to recursive signals [0:no (default), 1:fabs based, 2:mask based (fastest)].

  **-hlf** \<n>    **--hash-load-factor** \<n>      load factor that triggers tlib hash table growth (0.7 by default) ; internal compiler tuning knob, never changes generated code, see TLIB.md.

  **-rui**        **--range-ui**                  whether to generate code to constraint vslider/hslider/nentry values in [min..max] range.

  **-eta**        **--eta-normalization**         normalization loop with the eta harvest: definitions no longer recursive replace their projections (one pass by default).

  **-etai** \<n>   **--eta-iterations** \<n>        iteration budget of the eta normalization loop (implies -eta; the loop may stop earlier).

  **-co**         **--canonical-order**           order the terms of normalized sums and products by value (history-independent) instead of the default serial order.

  **-fui**        **--freeze-ui**                 whether to freeze vslider/hslider/nentry to a given value (init value by default).

  **-inj** \<f>    **--inject** \<f>                inject source file \<f> into architecture file instead of compiling a dsp file.

  **-scal**       **--scalar**                    generate non-vectorized code (default).

  **-inpl**       **--in-place**                  generates code working when input and output buffers are the same (scalar mode only).

  **-vec**        **--vectorize**                 generate easier to vectorize code.

  **-vs** \<n>     **--vec-size** \<n>              size of the vector (default 32 samples).

  **-lv** \<n>     **--loop-variant** \<n>          [0:fastest, fixed vector size and a remaining loop (default), 1:simple, variable vector size, 2:fixed, fixed vector size].

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

  **-noreprc**    **--no-reprc**                  (Rust only) Don't force dsp struct layout to follow C ABI.

  **-ns** \<name>  **--namespace** \<name>          generate C++ or D code in a namespace \<name>.

  **-vhdl**-trace    **--vhdl-trace**             activate trace.

  **-vhdl**-float    **--vhdl-float**             uses IEEE-754 format for samples instead of fixed point.

  **-vhdl**-components \<file> **--vhdl-components** \<file>    path to a file describing custom components for the VHDL backend.

  **-fpga**-mem \<n>     **--fpga-mem** \<n>        FPGA block ram max size, used in -mem1/-mem2 mode.

  **-fpga**-mem-th \<n>  **--fpga-mem-th** \<n>     FPGA array size threshold (in unit of the memory type), used in -mem1/-mem2 mode.

  **-rnt**        **--rust-no-faustdsp-trait**    (Rust only) Don't generate FaustDsp trait implementation.

  **-rnlm**       **--rust-no-libm**              (Rust only) Don't generate FFI calls to libm.


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

  **-rg**         **--retiming-graph**            print the internal signal graph after retiming in dot format.

  **-norm**       **--normalized-form**           print signals in normalized form and exit.

  **-norm1**      **--normalized-form1**          print signals in normalized form with IDs for shared sub-expressions and exit.

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


Environment variables:
---------------------------------------

  FAUST_DEBUG      = FAUST_LLVM1          print LLVM IR before optimisation.

  FAUST_DEBUG      = FAUST_LLVM2          print LLVM IR after optimisation.

  FAUST_DEBUG      = FIR_PRINTER          print FIR after generation.

  FAUST_DEBUG      = FAUST_LLVM_NO_FM     deactivate fast**-math** optimisation in LLVM IR.

  FAUST_OPT        = FAUST_SIG_NO_NORM    deactivate signal normalisation.


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

Copyright (C) 2002-2026, GRAME - Centre National de Creation Musicale.
All rights reserved.

