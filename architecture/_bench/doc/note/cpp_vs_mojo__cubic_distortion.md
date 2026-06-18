# C++ vs Mojo - Cubic Distortion vector lowering

## Scope

This note compares the generated low-level code for `cubic_distortion`, focusing on the vec-mode C++ and
vec-mode Mojo benchmark paths.

The scalar results are close enough to rule out a broad scalar-codegen issue. The performance gap appears in
vec mode: C++ gains throughput from the vector architecture, while Mojo vec mode remains below its own scalar
baseline. The low-level inspection points to one main difference: C++ lowers the vec-mode structure into dense
packed f64x2 SIMD kernels, while Mojo emits mostly scalar f64 operations with only sparse packed SIMD.

## Benchmark result

Observed throughput:

```text
configuration                 throughput
------------------------------------------------
C++  scalar single              13.2 Mframes/s
C++  scalar double              12.1 Mframes/s
C++  vec    single              18.0 Mframes/s
C++  vec    double              16.7 Mframes/s
Mojo scalar single              13.3 Mframes/s
Mojo scalar double              12.3 Mframes/s
Mojo vec    single               9.8 Mframes/s
Mojo vec    double               9.7 Mframes/s
```

The scalar double comparison is close:

```text
Mojo scalar double / C++ scalar double = 12.3 / 12.1 = 101.7%
```

The vec double comparison is the large gap:

```text
Mojo vec double / C++ vec double = 9.7 / 16.7 = 58.1%
C++ vec double is about 1.72x faster than Mojo vec double
```

The important point is that vec mode improves C++ throughput but reduces Mojo throughput:

```text
C++  vec double / C++  scalar double = 16.7 / 12.1 = 1.38x
Mojo vec double / Mojo scalar double =  9.7 / 12.3 = 0.79x
```

## Vector-lowering model

The desired vec-mode lowering is not only a matter of generating a larger function or more loops. The relevant
property is that repeated block operations must become packed SIMD arithmetic.

Scalarized shape:

```text
for i in block:
    a0 = load tmp0[i]
    a1 = load tmp1[i]
    b0 = c0 * a0 + c1 * a1
    store tmp2[i], b0
```

Packed shape:

```text
for i in block step 2:
    a0 = load_f64x2 tmp0[i:i+2]
    a1 = load_f64x2 tmp1[i:i+2]
    b0 = c0 * a0 + c1 * a1
    store_f64x2 tmp2[i:i+2], b0
```

For this DSP, C++ emits many packed f64x2 kernels of the second form. Mojo mostly emits scalar f64 loops of the
first form, plus significant temporary-buffer traffic.

## Instruction counts

Static counts over the inspected double vec sections:

```text
case              fmul.2d   fmla.2d   packed f64 total   scalar f64 fma/mul/sub
--------------------------------------------------------------------------------
Mojo double vec       13         6              19                  666
C++  double vec      600       540            1140                 4006
```

Memory traffic in the same inspected sections:

```text
case              ldr d   str d   ldr q   str q
------------------------------------------------
Mojo double vec    1108     348      28      47
C++  double vec    3078    1838     763     953
```

C++ is much larger and has more total memory traffic, but that traffic supports many packed kernels. The
decisive difference is SIMD density:

```text
Mojo packed f64 arithmetic ops:    19
C++  packed f64 arithmetic ops:  1140
```

C++ is faster here because it reaches high SIMD density, not because the generated shape is minimal. The
large function body, large stack frame, nested block/tail loops, and substantial temporary-buffer traffic
suggest remaining optimization headroom.

## C++ vec double

The C++ vec double section contains many nested block loops and tail paths. The function is large, but the
important loops contain packed f64 arithmetic:

```asm
ext.16b  v0, v2, v4, #8
fmul.2d  v16, v0, v3[0]
fmla.2d  v16, v4, v1[0]
fmla.2d  v16, v2, v1[0]
dup.2d   v2, v4[1]
zip1.2d  v2, v2, v5
fmul.2d  v15, v2, v3[0]
fmla.2d  v15, v5, v1[0]
```

This is the desirable vec-mode shape. The backend materializes temporary block data, but enough of the block
work is performed as f64x2 arithmetic to make the vector architecture profitable.

The C++ function also contains scalar loops, setup code, conversion code, and tails. Those do not negate the
main observation: the generated code includes a large number of packed f64 operations in the vec-mode body.

## Mojo vec double

The Mojo vec double section is much more scalarized. A representative loop operates on one f64 lane at a time:

```asm
ldr   d2, [x9]
ldur  q3, [x9, #-16]
fmul.2d v3, v1, v3
mov   d4, v3[1]
fmadd d2, d1, d2, d4
fadd  d2, d2, d3
fmul  d2, d0, d2
str   d2, [x10, x8, lsl #3]
```

Even where a packed instruction appears, the loop quickly extracts a scalar lane and continues with scalar
operations. The section does contain a few packed f64 operations, especially around grouped output conversion:

```asm
fmla.2d v1, v2, v3
fmla.2d v2, v0, v3
fcvtn   v0.2s, v2.2d
fcvtn2  v0.4s, v1.2d
```

However, these are sparse relative to the total amount of scalar f64 work. Mojo is paying for vec-mode
temporary storage and block scheduling, but it does not recover enough throughput through packed f64x2
arithmetic.

## Direct comparison

The vec double gap is mainly a vector-lowering difference.

```text
C++ vec double:
  large generated function
  many block and tail loops
  1140 packed f64 arithmetic instructions
  16.7 Mframes/s

Mojo vec double:
  smaller generated function
  mostly scalar f64 block processing
  19 packed f64 arithmetic instructions
  9.7 Mframes/s
```

The scalar benchmark shows that Mojo can match C++ on this DSP when vec-mode lowering is not involved. The vec
benchmark shows that Mojo does not currently expose or preserve the block operations in a form that leads to
dense f64x2 SIMD code.

The main backend target is therefore not scalar arithmetic selection, but vector lowering:

```text
preserve vec-mode block operations as contiguous f64 arrays
expose aligned/stride-regular loads and stores where possible
avoid scalar lane extraction inside block loops
generate or enable f64x2 fused multiply-add kernels
keep temporary-buffer traffic proportional to useful packed work
```

For `cubic_distortion`, C++ demonstrates the profitable shape: a larger vec-mode body can be faster when the
extra code represents specialized packed kernels. Mojo currently emits a lighter but more scalarized body, so
the vec architecture adds overhead without delivering comparable SIMD throughput.
