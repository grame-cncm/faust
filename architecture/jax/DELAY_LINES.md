### Delay Line Implementation in the JAX Backend

The JAX backend uses three strategies for delay lines, chosen by the maximum delay depth (mxd) and the `-mcd` (max copy delay) compiler flag (default: 16):

1. **Direct element copies** for very small delays (mxd 1-2)
2. **Shift register** (`jnp.roll`) for small delays (mxd 3 to mcd-1)
3. **Circular buffers** (IOTA-indexed ring buffers) for large delays (mxd >= mcd)

The `-mcd` flag is not JAX-specific -- all Faust backends use it -- but it has important performance implications for JAX because `jnp.roll` is O(n) while direct copies and circular buffer access are O(1).

#### The Three Strategies

##### Strategy 1a: Scalarized Elements (mxd == 1 or mxd == 2)

For delays of 1 or 2 samples — the z⁻¹/z⁻² states that dominate recursive
filters — each array element becomes an **individual scalar entry** in the
carry dict, updated by plain assignment. No `.at[].set()` is involved.

This matters because a scan body containing many small-array
dynamic-update-slice ops falls off XLA's in-place-update optimization path:
on CPU, a body with ten such arrays measured ~1000x slower per step than the
same recurrence on scalar carry entries. Scalarizing made a 4-section
parametric EQ 9x faster end-to-end (and its gradient 7x faster) with
numerically identical output.

The transformation is decided by an analysis pass
(`NNXScalarizeAnalysis` in `nnx_base_instructions.hh`): a struct array
qualifies when it is declared with size ≤ 4, has no initializer, and every
access anywhere in the emitted code is a single constant index. Any bare
whole-array reference (the `jnp.roll` strategy) or computed index (IOTA
circular buffers) disqualifies it, so the other strategies are unaffected.

**Example: Single-sample delay** (`_ <: _ - mem`, i.e. `y[n] = x[n] - x[n-1]`):

```python
# _initialize_carry (real-typed buffers follow the runtime faust_float dtype):
state["fVec0_0"] = np.zeros((), dtype=self.faust_float)
state["fVec0_1"] = np.zeros((), dtype=self.faust_float)

# tick:
state["fVec0_0"] = input0
output0 = input0 - state["fVec0_1"]
state["fVec0_1"] = state["fVec0_0"]  # copy [0] -> [1]
```

**Example: Biquad lowpass filter** (`fi.lowpass(2, 1000)`, mxd == 2):

A second-order IIR filter implements the difference equation:

    y[n] = b0*x[n] + b1*x[n-1] + b2*x[n-2] - a1*y[n-1] - a2*y[n-2]

The Faust compiler restructures this into `fRec0` with delay depth 2, emitted
as three scalars:

```python
# _initialize_carry:
state["fRec0_0"] = np.zeros((), dtype=self.faust_float)
state["fRec0_1"] = np.zeros((), dtype=self.faust_float)
state["fRec0_2"] = np.zeros((), dtype=self.faust_float)

# tick (simplified, constants folded for clarity):
state["fRec0_0"] = input0 - C2 * (C3 * state["fRec0_2"] + C4 * state["fRec0_1"])
output0 = C2 * (state["fRec0_2"] + state["fRec0_0"] + 2.0 * state["fRec0_1"])
state["fRec0_2"] = state["fRec0_1"]  # copy [1] -> [2]
state["fRec0_1"] = state["fRec0_0"]  # copy [0] -> [1]
```

##### Strategy 1b: Shift Register (`jnp.roll`, mxd 3 to mcd-1)

For delays of 3 or more samples (but below `-mcd`), the compiler uses `jnp.roll` to shift the entire array by one position. The array is written at index 0, past values are read from higher indices.

```python
# For a 4th-order FIR filter (mxd == 4):
state["fVec0"] = state["fVec0"].at[0].set(input0)
output0 = 0.2*state["fVec0"][0] + 0.3*state["fVec0"][1] + ...
state["fVec0"] = jnp.roll(state["fVec0"], 1)  # shift all elements by 1
```

##### Strategy 2: Circular Buffer (IOTA-indexed)

Used when the maximum delay depth is >= `-mcd` (default: >= 16 samples).

Instead of shifting the whole array, a shared integer counter `IOTA0` tracks the current write position. The buffer is sized to the next power of two, and all index arithmetic uses bitwise AND (`& (size-1)`) for O(1) wrapping.

**Example: 1-second feedback delay**

`process = + ~ @(44100) * 0.5` implements: y[n] = x[n] + 0.5 * y[n-44100]

With a maximum delay of 44100 samples (well above the default `-mcd` of 16), the buffer is sized to 65536 (next power of two):

```python
# _initialize_carry:
state["fRec0"] = np.zeros((65536,), dtype=self.faust_float)
state["IOTA0"] = 0

# tick:
state["fRec0"] = state["fRec0"].at[
    (state["IOTA0"] & 65535).astype(jnp.int32)
].set(input0 + 0.5 * state["fRec0"][
    ((state["IOTA0"] - 44101) & 65535).astype(jnp.int32)
])
output0 = state["fRec0"][(state["IOTA0"] & 65535).astype(jnp.int32)]
state["IOTA0"] = state["IOTA0"] + 1
```

Key details:
- `IOTA0` is a **shared** counter across all circular buffers in the DSP, not per-array.
- The mask `& 65535` is equivalent to `% 65536` but faster.
- Reads from the past use `(IOTA0 - delay) & mask`.

**Example: Variable delay**

`process = + ~ @(delay_time) * 0.5` where `delay_time` is a slider. The maximum possible delay determines the buffer size at compile time; the actual delay is computed at runtime:

```python
# tick:
iSlow0 = jnp.int32(params["fHslider0"]) + 1
state["fRec0"] = state["fRec0"].at[
    (state["IOTA0"] & 65535).astype(jnp.int32)
].set(input0 + 0.5 * state["fRec0"][
    ((state["IOTA0"] - iSlow0) & 65535).astype(jnp.int32)
])
```

#### Mixed Usage in Real DSPs

A DSP mixes the shift-register and circular-buffer strategies when it has delay
lines on both sides of `-mcd`. For example, `(_@8) + (+ ~ @(1000) * 0.5)`
compiles the 8-sample delay to a `jnp.roll` shift register (mxd 8, below mcd) and
the 1000-sample feedback delay to an `IOTA`-indexed circular buffer (mxd 1001).

Note that a DSP with many delay lines does not necessarily use `jnp.roll` at all:
`freeverb.dsp`, for instance, generates **no** `jnp.roll` at the default `-mcd`.
All of its comb and allpass delays (256-2048 samples) are far above `-mcd`, so
they become circular buffers (50 `IOTA` references), while its 40 one-sample
damping-filter states use direct element copies (Strategy 1a).

#### Compiler Flag: `-mcd <size>`

```bash
# Default (16): small delays use roll, large delays use circular buffers
faust -lang nnx mydsp.dsp -a architecture/jax/minimal.py

# Lower threshold: more circular buffers (better performance for large DSPs)
faust -lang nnx -mcd 8 mydsp.dsp -a architecture/jax/minimal.py

# Higher threshold: more roll operations
faust -lang nnx -mcd 64 mydsp.dsp -a architecture/jax/minimal.py
```

Both strategies produce identical numerical results -- the choice is purely about performance. The default of 16 is a good balance for most DSPs.

#### Implementation Files

The delay-line strategy selection and code generation live in:

- `compiler/generator/instructions_compiler_jax.cpp/hh` — compiler logic choosing between the strategies
- `compiler/generator/nnx/nnx_instructions.hh` — visitor converting array accesses to the chosen form

#### Verifying Correctness

The impulse test suite (`tests/impulse-tests/Make.nnx`) validates that JAX output matches the C++ reference implementation for 82 DSP files. To test a specific DSP:

```bash
# Compare JAX output against C++ reference
cd tests/impulse-tests
faust -lang nnx dsp/echo.dsp -a archs/impulse_nnx.py -double > ir/nnx/double/nnx_echo.py
python3 ir/nnx/double/nnx_echo.py > ir/nnx/double/echo.ir
./filesCompare ir/nnx/double/echo.ir reference/echo.ir
```
