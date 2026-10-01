# Soundfile channel wrap tests

A soundfile read with more channels than it actually has reads channel `chan % fChannels`
(see the contract in `architecture/faust/gui/Soundfile.h`). `wrap.dsp` reads a 3 channels file
with 70 outputs, more than the former `MAX_CHAN` (64) limit, in several compilation modes.

The file is loaded with `SoundUI` and `LibsndfileReader`, which only allocate the real channel
buffers: the test is built with AddressSanitizer, so a generated code still indexing past
`fChannels` is reported, not only a wrong value.

```
make check                       # uses ../../build/bin/faust
make check FAUST=<faust binary>
```

Needs libsndfile (found with `pkg-config`). The impulse tests (`tests/impulse-tests`, `sound.dsp`)
cover the same rule on the other backends (interp, LLVM, JAX), with 2 channels read as 4.
