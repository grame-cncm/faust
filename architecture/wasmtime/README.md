# Faust Wasmtime Tools

This repository provides tools to run and benchmark Faust DSP programs compiled to WebAssembly using the [Wasmtime](https://github.com/bytecodealliance/wasmtime) runtime.

## faustwasmtime

The **faustwasmtime** tool can compile and run a Faust `.dsp` file or load and run a `.wasm` precompiled file using the Wasmtime runtime. It connects the DSP to a JACK (or dummy) audio backend and serves a control UI over HTTP:

```bash
faustwasmtime <foo.dsp/foo.wasm>
```

Once running, an HTTP interface is available at:

```
http://127.0.0.1:5510
```

- Starts audio processing with JACK
- Enables real-time web-based control
- Press `q` in the terminal to quit

## faustbench-wasmtime

The **faustbench-wasmtime** tool can compile a Faust `.dsp` file or load `.wasm` precompiled file and benchmark them using the Wasmtime engine. It reports performance stats such as bandwidth and CPU usage:

```bash
faustbench-wasmtime <foo.dsp/foo.wasm>
```

Typical output:

```
myeffect.wasm : 89.32 MBytes/sec, SD : 3.14% (DSP CPU % : 27.5)
```

- Measures over 5 seconds using a 512-sample buffer
- Useful for profiling and comparing backends

