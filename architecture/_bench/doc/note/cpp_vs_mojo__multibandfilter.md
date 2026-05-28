# C++ vs Mojo benchmark analysis: `multibandfilter`

## Scope

This report analyzes the benchmark and assembly observations for the Faust `multibandfilter` DSP when generated through the C++ backend and the Mojo backend.

The focus is not only on which backend is faster, but on why the result changes depending on:

- scalar vs vectorized Faust mode;
- single precision vs double precision;
- frontend/backend code shape;
- compiler optimization behavior;
- memory traffic and state handling in recursive DSP code.

The central finding is that `multibandfilter` is a recursive filter cascade. This kind of DSP strongly rewards code that keeps recurrence state local, compact, and register-carried. It penalizes transformations that materialize many intermediate buffers or repeatedly move state through memory.

## Summary of the observed cases

### Mojo scalar f32 beats C++ scalar f32

In scalar single precision, Mojo is faster than C++ for this DSP.

The most interesting Mojo-positive observations are:

- Mojo produces a smaller compute frame.
- Mojo saves fewer general-purpose registers around the compute body.
- Mojo preserves several recurrence expressions as direct fused negative multiply-subtract instructions.
- Mojo uses compact 64-bit moves to rotate adjacent `f32` state cells.
- Mojo’s coefficient reload pattern is relatively regular.
- The hot loop maps the recursive filter cascade into a tight scalar recurrence loop.

This is the case where Mojo shows a clean scalar-codegen advantage.

### C++ scalar f64 beats Mojo scalar f64

In double precision, after fixing the previous pathological Mojo f64 lowering, C++ is still faster.

The main reason is different from the previous f64 bug. The relevant advantage is that C++ appears to promote the recursive state into registers across the sample loop and flush it back only after the loop. Mojo still keeps more of the recurrence state memory-backed and performs state stores/rotations inside each frame.

For a recursive filter, that is a major difference.

### Mojo vec f32 is much slower than Mojo scalar f32

Mojo vector mode for this DSP is not behaving like efficient SIMD acceleration. The assembly shows a very large stack frame, many scratch buffers, many scalar inner loops over 32-sample chunks, and many intermediate stores/loads.

This is a poor match for a recursive filter cascade. The vectorized Faust mode exposes block-level processing, but because the DSP has loop-carried dependencies, the generated code cannot simply compute many independent samples at once in SIMD registers. Instead, it materializes intermediate arrays stage by stage.

For this DSP, scalar mode fits the algorithm much better than vec mode.

## Important fixed issue: explicit `F64(...)` literal wrapping

Before the final comparison, there was a misleading and important f64 lowering issue.

The generated Mojo source and LSP reported correct types:

- `FaustFloat = F64`;
- expressions were seen as `F64` / `Float64`;
- assertions such as `dreal == dfaust` and `F64.dtype == FaustFloat.dtype` compiled.

However, the emitted assembly still showed a bad pattern:

```asm
fcvt s..., d...
bl _tanf
bl ... SIMD,dtype=f32,size=1 ... pow ...
fcvt d..., s...
```

So the source-level type information looked correct, but the lowered code routed through `f32` math.

The fix was to stop aggressively wrapping every real numeral as `F64(...)`. Mojo real numerals are already double/f64 in the relevant context, so the backend now prefers plain real numerals such as:

```mojo
0.05
1.0
10.0
```

instead of:

```mojo
F64(0.05)
F64(1.0)
F64(10.0)
```

After this change, the assembly improved and the double path correctly used:

```asm
bl _tan
bl ... SIMD,dtype=f64,size=1 ... pow ...
```

with no unnecessary `f64 -> f32 -> f64` conversion chain.

This is an important backend lesson: in Mojo code generation, explicit casts should not be emitted defensively. They should be emitted only at real type boundaries.

## Background concepts

### Scalar mode

Scalar mode means the generated `compute` function processes frames one by one.

Conceptually:

```text
for each sample:
    read input
    compute all filter stages for this sample
    update recurrence state
    write output
```

For recursive filters, scalar mode is often a natural fit because each output sample depends on previous state. The state update happens immediately, and the compiler may be able to keep some of that state in registers.

### Faust vec mode

Faust vector mode reorganizes computation around blocks. Instead of producing one tight per-sample recurrence loop, it often creates stage-oriented loops over a vector/block size.

Conceptually, for a filter cascade, vec mode can look like:

```text
compute stage 0 for a block -> temporary buffer
compute stage 1 for a block -> temporary buffer
compute stage 2 for a block -> temporary buffer
...
write final output block
```

This can be useful when the DSP is feed-forward, parallel, or easily vectorizable across samples. However, for recursive filters, each sample depends on previous samples, so the compiler cannot freely compute all samples independently.

That means vec mode may introduce temporary buffers and extra memory movement without getting real SIMD acceleration.

### Register spilling

The CPU has a limited number of registers. Registers are the fastest place to keep temporary values. The compiler tries to keep active variables in registers whenever possible.

When there are too many live values at once, the compiler must temporarily store some of them to memory, usually on the stack. This is called register spilling.

A simple spill pattern looks like:

```asm
str s0, [sp, #96]   ; spill value to stack
...
ldr s0, [sp, #96]   ; reload value later
```

Spilling is not always catastrophic, but in a hot DSP loop it matters because the loop runs for every sample. More spills mean more memory traffic and more dependency pressure.

### State rotation

Recursive filters keep history. A typical state update looks like:

```text
rec[2] = rec[1]
rec[1] = rec[0]
rec[0] = new_value
```

This is state rotation: after computing a new value, old values move to the next history slot.

For `f32`, each state cell is 4 bytes. Two adjacent `f32` cells are 8 bytes. A compiler can move two adjacent state cells with one 64-bit `d` load/store:

```asm
ldur d29, [x19, #132]
str  d29, [x19, #136]
```

In scalar f32 Mojo, this is a compact and reasonable pattern. It shifts two adjacent scalar `f32` cells together.

This same kind of pattern was suspicious in the earlier broken f64 case because the generated code mixed `s` stores with `d` loads. But in the correct f32 case, a `d` move over two adjacent `f32` values is a useful compact state-copy idiom.

## Case 1: Mojo scalar f32 vs C++ scalar f32

### Observed result

Mojo scalar f32 is faster than C++ scalar f32 for `multibandfilter`.

The assembly suggests that Mojo wins because its hot loop has a good shape for this DSP. The advantage is not one single magic instruction. It is the combination of several codegen properties.

### Smaller compute frame

The Mojo scalar f32 compute body uses a smaller stack frame than the C++ compute body.

Mojo scalar f32:

```asm
sub sp, sp, #288
```

C++ scalar f32 compute uses a larger frame.

A smaller frame usually indicates that the function needs less stack storage for spills, temporary values, or saved context. It does not prove performance by itself, but it is a good sign. For a long recursive filter cascade, stack pressure is meaningful because many coefficients and state values are live around the same time.

### Fewer saved general-purpose registers

Mojo also saves a smaller set of general-purpose registers around the compute body. This reduces prologue/epilogue overhead and suggests that the generated function has a lighter register-management footprint.

This matters most when the function is called many times in a benchmark harness. It matters less than the hot loop, but it is still part of the overall shape.

### Direct fused recurrence operations

The Mojo hot loop contains direct fused negative multiply-subtract instructions such as:

```asm
fnmsub ...
```

This is relevant because recursive filters often contain expressions of the form:

```text
a - b * c
```

or:

```text
-(a * b) + c
```

A fused multiply-subtract instruction computes this in one fused floating-point operation. This is good for both speed and numerical behavior because it avoids separate multiply and subtract instructions.

The important part is not only that Mojo uses FMA instructions. The important part is that the subtractive recurrence structure remains visible in the final machine code. The loop maps cleanly to the hardware’s fused operations.

### Compact f32 state rotation

Mojo scalar f32 rotates adjacent `f32` state cells with 64-bit moves. This is compact because two `f32` values fit in one 64-bit register lane.

Conceptually, instead of doing:

```text
move rec[i]
move rec[i + 1]
```

it can do:

```text
move two adjacent f32 cells together
```

In assembly this appears as `d` register load/store operations over adjacent state cells.

For f32 recursive state, this is a useful pattern. It keeps state rotation compact even though the computation itself is scalar.

### Regular coefficient reload pattern

Mojo still reloads coefficients from the stack. It is not spill-free. However, the reload pattern is relatively regular: coefficient values are loaded from stable stack offsets and then fed into the recurrence chain.

Regularity matters because it gives the backend and the CPU scheduler a predictable structure. The loop is not full of irregular control flow. It is mostly:

```text
load coefficient
fused operation
load coefficient
fused operation
state update
```

### Why scalar fits this DSP

`multibandfilter` is a recursive cascade. Each stage depends on previous state, and each stage feeds the next stage.

Scalar mode matches this dataflow:

```text
one sample enters
all stages process that sample
state is updated
one sample exits
```

This keeps the working set small. The compiler can focus on scheduling a tight recurrence chain rather than managing many temporary arrays.

In the f32 scalar case, Mojo takes good advantage of this. The result is a compact scalar loop that maps well to the hardware.

## Case 2: C++ scalar f64 vs Mojo scalar f64

### Observed result

After fixing the previous f64 lowering issue, C++ scalar f64 is faster than Mojo scalar f64.

This result is not caused by the old pathological f64-to-f32 lowering. The newer fixed Mojo f64 assembly correctly uses double math. So the remaining difference is a normal code-generation difference.

### Main reason: C++ promotes recursive state into registers

The key observation is that C++ appears to keep recurrence state live in registers across the sample loop.

In the C++ loop, state values are moved through registers during the loop, and final state is flushed back to the DSP object only after the loop finishes.

Conceptually:

```text
load state before loop
for each sample:
    compute using register-carried state
    rotate state using register moves
store final state after loop
```

This is very good for recursive filters. It avoids repeatedly touching memory for the same state variables at every sample.

### Mojo keeps more state memory-backed

The Mojo f64 loop still writes intermediate recurrence state into the DSP object during each sample and performs memory-based state rotation.

Conceptually:

```text
for each sample:
    compute new rec value
    store rec value into dsp memory
    load/rotate state through dsp memory
    continue
```

This increases per-sample memory traffic.

For a recursive filter cascade, this is expensive. The DSP is not doing one or two state updates. It has many stages, and each stage has recurrence state. Multiplying the extra memory operations by every sample and every filter stage becomes significant.

### This is scalar replacement / local state promotion

The relevant compiler optimization is often called scalar replacement or local state promotion.

The idea is:

```text
memory-backed object field:
    dsp.rec0[0]
    dsp.rec0[1]
    dsp.rec0[2]

promoted scalar locals:
    rec0_0
    rec0_1
    rec0_2
```

The compiler can replace repeated memory accesses with local scalar variables, keep those variables in registers, and write them back at the end.

For recursive DSP code, this can be very powerful.

The C++ compiler appears to do this more aggressively in this case. Mojo does not fully do it for the generated recurrence state. This is the same class of issue previously observed in other state-heavy DSPs such as `carre_volterra`.

### Why f64 exposes this more strongly

Double precision increases the cost of memory traffic:

- each value is 8 bytes instead of 4;
- state arrays occupy more memory;
- state movement uses wider loads/stores;
- register pressure is higher because double values occupy FP registers and the filter has many live coefficients/state variables.

Therefore, the difference between register-carried state and memory-backed state becomes more visible in f64.

In f32, Mojo’s compact loop shape can win. In f64, the cost of not fully promoting state can dominate.

## Case 3: Mojo scalar f32 vs Mojo vec f32

### Observed result

Mojo scalar f32 is much faster than Mojo vec f32 for `multibandfilter`.

The vec assembly explains why: the generated code is not an efficient SIMD version of the scalar loop. It is a block-scheduled program with many scalar inner loops and large temporary buffers.

### Massive stack frame

Mojo vec f32 uses a very large stack frame:

```asm
sub sp, sp, #2912
```

This is much larger than scalar f32:

```asm
sub sp, sp, #288
```

This means vec mode materializes many temporary arrays or block buffers on the stack.

### Many scratch buffers

The vec assembly sets up many stack regions:

```asm
add x24, sp, #1136
add x27, sp, #1408
add x28, sp, #1680
add x23, sp, #1952
add x25, sp, #2496
add x26, sp, #2768
```

These are not signs of simple SIMD acceleration. They are signs of block-level intermediate storage.

The generated code computes one stage over a block, writes a temporary buffer, then another stage reads that temporary buffer and writes another one.

### Many scalar loops over 32 samples

The vec assembly contains many loops of this shape:

```asm
mov w30, #32
LBB0_2:
    ldr s...
    fmul s...
    fmadd s...
    str s...
    subs x30, x30, #1
    b.ne LBB0_2
```

The arithmetic still uses scalar `s` registers. This is not a tight NEON vector loop processing several samples per instruction. It is scalar arithmetic repeated over a block size of 32.

The important point is that Faust vec mode is not automatically equivalent to hardware SIMD vectorization. It changes the scheduling of the generated program, but the backend/compiler still has to lower that schedule efficiently.

### Intermediate buffers dominate

The vec code repeatedly writes intermediate results to stack arrays:

```text
stage output -> temporary buffer
next stage reads temporary buffer
next stage output -> another temporary buffer
...
```

This increases memory traffic substantially.

Scalar mode, in contrast, can process a sample through the full cascade and keep many intermediate values in registers.

### Recursive filters are hard to vectorize across time

This is the central DSP reason.

For feed-forward DSPs, samples are often independent:

```text
out[i] = f(in[i])
```

That is easy to vectorize because `out[i]`, `out[i + 1]`, `out[i + 2]`, and `out[i + 3]` can be computed independently.

For recursive filters, samples depend on previous samples:

```text
out[i] depends on out[i - 1]
out[i] depends on state from previous frames
```

This creates loop-carried dependencies.

A loop-carried dependency means the next iteration cannot be freely computed before the previous one has produced its state. That limits SIMD vectorization across time.

Faust vec mode can still try to process blocks, but for this DSP it ends up paying the overhead of block scheduling without getting enough parallel arithmetic benefit.

### Why scalar wins here

Scalar mode follows the natural dependency chain of the filter:

```text
sample i enters
state from sample i - 1 is used
state is updated
sample i + 1 can now be computed
```

This is sequential, but it is also compact and local.

Vec mode tries to reorganize the computation into block-stage loops. For a recursive cascade, that creates temporary arrays and extra copying. The resulting program has much more memory traffic and control overhead.

Therefore, for `multibandfilter`, scalar mode is the better fit.

## Architectural interpretation

### C++ backend architecture

The C++ backend benefits from a mature compiler pipeline. Clang/LLVM is very good at optimizing conventional C++ code, especially when the generated code is expressed in a form that exposes local scalar state.

In f64 scalar mode, C++ appears to benefit from scalar replacement of recursive state. It carries state values through registers and stores them back after the loop.

That is the ideal pattern for a recursive filter.

### Mojo backend architecture

The Mojo backend has a strong scalar story in f32 for this DSP. The generated scalar loop is compact, uses fused recurrence instructions, and has good state movement patterns for f32.

However, Mojo currently seems less able to automatically promote small DSP state arrays into register-carried locals in the f64 case. This leaves performance on the table for recursive DSPs.

This suggests a possible backend-level transformation:

```text
load small fixed-size state arrays into local scalar variables before the frame loop;
use local variables inside the loop;
write them back to the DSP object after the loop.
```

This would make the Mojo code shape closer to what C++ achieves after optimization.

### Faust vec mode architecture

Faust vec mode is not universally better. It is a code scheduling strategy. It can help when the DSP has enough independent work across samples or when the backend/compiler can lower the vector schedule to efficient SIMD.

For `multibandfilter`, the vec schedule is a poor match because the DSP is recursive. The generated Mojo vec code materializes many block buffers and scalar loops. It increases memory traffic instead of reducing it.

## Analysis observations

### Observation 1: precision changes the bottleneck

In f32 scalar, Mojo’s compact hot-loop shape wins.

In f64 scalar, the cost of memory-backed recurrence state becomes more important, and C++ wins by carrying state in registers.

So the relative backend performance is precision-dependent.

### Observation 2: vector mode is not automatically SIMD

The Mojo vec assembly shows scalar arithmetic inside many 32-sample loops. This is vector mode at the Faust scheduling level, not necessarily vectorized machine code.

For this DSP, vec mode adds block buffers and stage loops but does not remove the core recurrence dependency.

### Observation 3: recursive DSPs reward local state promotion

The most important optimization for recursive filters is not always SIMD. Often it is state locality.

A recursive filter can be very fast if its history values stay in registers during the sample loop. It can become much slower if every sample repeatedly loads/stores state through memory.

### Observation 4: explicit casts can hurt Mojo lowering

The previous f64 issue showed that source-level type correctness is not always enough. Explicit `F64(...)` wrapping around every real literal caused bad f32 lowering. Removing unnecessary casts restored the expected f64 path.

The backend should therefore avoid defensive casts and generate simpler typed expressions.

### Observation 5: inspect architecture is essential

The benchmark numbers alone only say which case is faster. The inspect architecture explains why.

For this investigation, the inspect output exposed:

- true vs broken f64 lowering;
- scalar hot-loop shape;
- state rotation strategy;
- register pressure and stack frame size;
- vec-mode temporary buffer explosion;
- C++ state promotion behavior.

This validates the decision to keep a minimal inspect architecture separate from the benchmark architecture.

## Conclusions

### Conclusion 1: Mojo scalar f32 is strong for this DSP

Mojo f32 scalar generates a good loop for `multibandfilter`. The loop is compact, recurrence-oriented, and uses fused scalar floating-point operations effectively.

This is a positive result for the Mojo backend.

### Conclusion 2: C++ f64 wins because of state promotion

C++ f64 wins not because Mojo is still doing the old broken f64 lowering, but because C++ handles recursive state more aggressively. It promotes state into registers and avoids per-sample DSP memory rotation.

This identifies a concrete optimization target for the Mojo backend.

### Conclusion 3: Faust vec mode is a bad fit for this recursive filter

For `multibandfilter`, Mojo vec mode is much slower because it creates many scalar block loops and temporary buffers. The DSP’s recurrence dependencies prevent easy SIMD-style parallelism across samples.

Scalar mode is more appropriate for this DSP.

### Conclusion 4: backend codegen should minimize unnecessary conversions

The literal-conversion issue showed that explicit casts can disturb Mojo lowering even when source-level types look correct. The backend should emit plain real numerals in typed real contexts and reserve explicit conversions for actual type boundaries.

### Conclusion 5: next optimization target is local state promotion

The most promising next optimization for recursive DSPs in the Mojo backend is manual or generated local state promotion:

```text
before loop:
    rec0_0 = dsp.rec0[0]
    rec0_1 = dsp.rec0[1]
    rec0_2 = dsp.rec0[2]

inside loop:
    use rec0_0, rec0_1, rec0_2 as locals
    rotate locals directly

after loop:
    dsp.rec0[0] = rec0_0
    dsp.rec0[1] = rec0_1
    dsp.rec0[2] = rec0_2
```

This would directly attack the main f64 weakness and may also improve other state-heavy DSPs.

## Suggested report framing

The clean framing is:

```text
`multibandfilter` shows that Mojo can generate excellent scalar f32 code for recursive DSPs, but also exposes two important backend/codegen lessons. First, recursive filters are highly sensitive to state locality: when state is carried in registers, performance improves; when state is repeatedly moved through memory, performance drops. Second, Faust vec mode is not automatically beneficial for recursive DSPs, because block scheduling can introduce large temporary buffers without overcoming loop-carried dependencies. The Mojo backend should therefore favor clean scalar code for such DSPs and prioritize local state promotion over naive vector-mode expansion.
```
