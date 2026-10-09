# LLVM API regressions

`check-opt-cache` tests the LLVM JIT optimization level and factory cache.
Build Faust and libfaust with LLVM enabled at the repository root, then select
the compiler and library from that same build explicitly:

```sh
make -C tests/llvm-tests check-opt-cache -k \
  FAUST="$(pwd)/build/bin/faust" \
  OPT_CACHE_LIB="$(pwd)/build/lib/libfaust.dylib" \
  OPT_CACHE_INC="$(pwd)/architecture"
```

Use `libfaust.so` on Linux. The test requires the shared library's LLVM runtime
to be discoverable by the loader. `LLVM_TEST_MAX_LEVEL` defaults to 3 for
LLVM >= 17; set it to 5 when testing the legacy pipeline of LLVM < 17.
The gate prints the compiler source commit and C++ compiler version before
compiling the test with `-ffp-contract=off`.

The test keeps factories alive while requesting the same DSP and class name
with different parameters; changing `-cn` would hide cache collisions.
It checks:

- String O0/O3 requests in both orders, repeat-request pointer reuse, distinct
  factory SHA keys and post-JIT IR, and lookup by the factory's own SHA.
- Default/native target aliases, a triple without a CPU (host CPU), and
  isolation between native and generic CPU targets (or reuse if the host
  already reports a generic CPU).
- Equivalent maximum levels (`-1` and the backend's effective maximum).
- Identical serialized IR or bitcode requested at different levels/targets.
- Signals O0/O3 post-JIT IR, maximum-level execution, and rejection of invalid
  levels below -1 before either optimization or cache lookup.

Every audio check evaluates 128 samples of input plus its one-sample delay,
using two compute calls and an independent exact arithmetic oracle. The test
compares optimized IR as well as audio: correct audio alone cannot establish
that the requested optimization pipeline ran. It does not assert timing ratios.

## Cache identity

String factories use the existing SHA of the application name, DSP source and
normalized compiler options as their input identity. IR/bitcode readers use
the SHA of their serialized input. The cache then combines that input identity
with the canonical target (`triple:CPU`) and effective IR optimization level.

A default target is resolved to the host triple/CPU; a target containing only
a triple gets the host CPU. Optimization normalization mirrors the actual
pipeline: `-1` selects the maximum; LLVM >= 17 caps levels at O3, while older
LLVM keeps its extended levels. Equivalent parameters reuse a factory;
different effective targets or levels do not.

For source/IR/bitcode factories the SHA published by `getSHAKey()` /
`getCSHAKey()` identifies this complete
factory configuration. It is not the source-only SHA returned by DSP expansion.
Use the factory's own SHA with `getDSPFactoryFromSHAKey()` or its C wrapper.
Each cache hit still adds a reference, requiring a matching `deleteDSPFactory()`.

Signal/Box factories are registered for lifetime management but do not perform
a source/serialization cache lookup. Unlike the String path, these entry points
receive in-memory trees without computing a content identity; Box lowers to
Signal. Tree addresses cannot identify equivalent computations across contexts.
Adding reuse would require a stable content key, for example a hash of the
generated IR before optimization, combined with target and optimization level.
That approach could avoid repeated optimization and JIT compilation, but would
still generate the initial IR on every request.
They still set target and optimization level before `initJIT()`.
The precompiled machine-code reader is unchanged:
it restores already-generated machine code and has no IR optimization parameter.
