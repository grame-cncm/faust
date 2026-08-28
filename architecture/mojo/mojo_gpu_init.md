# Mojo GPU architecture prototype

## Purpose

The current prototype separates the system into three layers:

- `probe.mojo` defines the temporary application and hardcoded DSP shape.
- `audio/portaudio/gpu.mojo` connects PortAudio to GPU processing.
- `gpu/device.mojo` owns GPU resources and launches kernels.

The goal is to validate the GPU-oriented DSP shape in `probe.mojo` before
implementing it in the FAUST generator.

## Complete audio-block flow

For every PortAudio callback:

```text
PortAudio inputs
    -> GPU input buffers
    -> GPU DSP kernel
    -> GPU output buffers
    -> PortAudio outputs
    -> synchronization
```

The callback returns only after the GPU output has been copied back.

## `probe.mojo`

This is the experimental frontend.

It currently:

1. verifies that a supported accelerator exists;
2. creates and initializes `ProtoDsp`;
3. creates `PortAudioGpu` with the grid and block dimensions;
4. initializes and starts the driver;
5. waits on standard input;
6. stops the driver and frees the DSP.

`ProtoDsp` will be replaced by a manually written GPU-oriented DSP. Once that
shape works correctly, the compiler can be modified to generate it.

`portaudio-gpu.mojo` remains the reference architecture; experimentation belongs
in `probe.mojo`.

## `PortAudioGpu`

`PortAudioGpu` owns the PortAudio lifecycle and a pointer to `FaustGpuDevice`.
It also stores the GPU grid and block dimensions selected by the frontend.

### Initialization

`init` initializes PortAudio and returns an explicit error code.

### Starting

`start`:

1. reads the DSP input/output counts;
2. obtains the required default PortAudio devices and latencies;
3. allocates a `FaustGpuDevice`;
4. creates its GPU context and buffers;
5. opens the PortAudio stream;
6. passes the GPU state pointer to the callback;
7. starts audio processing.

### Callback

For each audio block, `gpu_callback`:

1. recovers `FaustGpuDevice` from PortAudio's `data` pointer;
2. verifies the buffer size;
3. enqueues one host-to-GPU copy for every input channel;
4. enqueues the DSP kernel;
5. enqueues one GPU-to-host copy for every output channel;
6. synchronizes the GPU;
7. returns `PA_CONTINUE`, or `PA_ABORT` on error.

PortAudio uses non-interleaved buffers, so each channel is handled through a
separate pointer.

### Stopping

`stop` stops and closes the PortAudio stream, destroys the GPU state, and
terminates PortAudio. The stream must stop before its callback state is freed.

## `FaustGpuDevice`

`FaustGpuDevice` owns the persistent GPU resources:

- `ctx`: GPU device context;
- `dsp_buf`: raw device copy of the DSP object;
- `input_buf` and `output_buf`: contiguous audio storage;
- `input_streams` and `output_streams`: device-side channel-pointer tables;
- `input_channels` and `output_channels`: reusable channel sub-buffer views;
- buffer size, channel counts, and kernel launch dimensions.

The DSP state lives in `dsp_buf` across callbacks. Oscillator phases, delay
lines, and other state modified by `compute` therefore persist on the GPU.

## GPU runtime creation

`create_gpu_runtime`:

1. reads the DSP channel counts;
2. allocates the DSP, audio, and pointer-table buffers;
3. copies the initialized host DSP into `dsp_buf`;
4. launches `init_streams` to build the channel-pointer tables;
5. creates persistent sub-buffer views for channel transfers;
6. constructs `FaustGpuDevice` in the supplied host allocation.

Zero-channel DSPs receive minimum one-element placeholder allocations. Those
elements are never accessed when the corresponding channel count is zero.

## `init_streams`

`init_streams` is an initialization kernel. Each thread handles one channel and
writes its device address into the appropriate FAUST stream table.

The resulting layout is equivalent to:

```text
inputs  -> [input channel 0 pointer, input channel 1 pointer, ...]
outputs -> [output channel 0 pointer, output channel 1 pointer, ...]
```

These are the `ImmStreams` and `MutStreams` layouts expected by `Dsp.compute`.

## `compute_gpu`

`compute_gpu` is a free GPU-launchable wrapper around the DSP instance method.
It reconstructs the DSP and stream pointers from their raw buffers, then calls:

```mojo
dsp[].compute(count, inputs, outputs)
```

The wrapper is necessary because `enqueue_function` cannot directly launch the
instance method `Dsp.compute`.

## What the probe must validate

The existing infrastructure already moves audio through PortAudio and the GPU.
The next experiment must validate the shape inside `compute`:

- how `thread_idx` maps threads to oscillators or independent DSP units;
- how per-thread state is laid out and indexed;
- how thousands of oscillators write or mix their outputs safely;
- which grid and block dimensions match that shape;
- whether state remains correct across consecutive audio callbacks.

Only after this shape works should the FAUST generator be changed to emit it.

## Current frontend issue

The committed `probe.mojo` and `portaudio-gpu.mojo` contain `print(e)` in a
non-raising error branch. It should be `print(err)`. The following repeated
`if err` block is also redundant.
