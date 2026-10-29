# Short delay line tests

A delay whose max delay is below `-mcd` (16 by default) is a copy delay: a line of `mxd + 1`
values read with no mask. `mxd` comes from the interval of the amount, which a float-carried
amount can leave at run time. Each `.dsp` reaches one of these edges, in single and double
precision:

| Program | Edge |
| :--- | :--- |
| `zone.dsp` | in `-double`, a slider read from its float `FAUSTFLOAT` zone passes its declared maximum |
| `fma.dsp` | `a*b + c` below an integer rounded apart, on it when fused into an FMA |
| `nan_control.dsp` | a slider at its minimum gives `sqrt(-1)`, a NaN amount |
| `nan_input.dsp` | the amount comes from the input, which holds a NaN |

The copy-delay read exists in the scalar FIR backend (`cpp`, `c`, `llvm`, `interp`, `rust`...),
the vectorized backend (`-vec`) and the legacy `ocpp` backend, so each is exercised.

The tests are built with the address and undefined behavior sanitizers, recovery disabled: an
index past the line, or a NaN converted to an int, stops the program with an error.

```
make check                       # uses ../../build/bin/faust
make check FAUST=<faust binary>
```

The `fma` cases only reach their edge on a target with a fused multiply-add (arm64, x86-64 with
FMA), so they are built with `-O2 -ffp-contract=fast`.
