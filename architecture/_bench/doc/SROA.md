I also found a separate issue with recursive DSP state promotion.

In simpler cases, Mojo promotes recursive state correctly:

```
load state before the loop
carry state in FP registers inside the loop
store final state after the loop
```

In a slightly more complex generated DSP, Mojo stops promoting the state and leaves stores/loads
inside the frame loop:

```
for i:
    load dsp.rec
    compute new recurrence state
    store dsp.rec
    rotate/copy dsp.rec state in memory
```

The hot-loop memory traffic changed approximately from:

```
simpler case:       loads = 4,  stores = 3
more complex case:  loads = 19, stores = 26
```

C++ keeps the same kind of recursive state register-carried in cases where Mojo starts materializing
it in memory.

So the secondary question is whether this is related to scalar replacement/register-pressure limits
in the current Mojo optimization pipeline.


<!-- - For the same `.dsp` source written in the `faust` language, the C++ compiler appears to be better at -->
<!--   extracting the context needed to apply optimizations. -->
<!---->
<!--   In particular, for the `carre_volterra.dsp` source, the assembly generated from the C++ translation shows -->
<!--   that temporary variables are lifted out of the main loop and written back in cascade at the end of the -->
<!--   loop, drastically reducing memory accesses. This is known as `SROA (scalar replacement of aggregates)`, -->
<!--   and more broadly can be described as `state promotion to local temporaries`. -->
<!---->
<!--   By contrast, the assembly generated from the Mojo translation repeatedly performs main memory accesses. -->
<!---->
<!-- - Another optimization used by C++ for `carre_volterra.dsp` is known as `loop peeling`, where a small number -->
<!--   of initial or final iterations are handled separately so that the main loop can run in a simpler and more -->
<!--   optimized form. -->
