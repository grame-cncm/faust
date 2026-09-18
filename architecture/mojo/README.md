# Faust to Mojo architectures

This directory contains the architectures and support components used by the FAUST Mojo backend to turn
generated DSP code into an executable program.

A FAUST backend has two main parts:

- the *generator*, which translates the FAUST intermediate representation into the target language;
- the *architecture system*, which supplies the environment required to use the generated DSP.

The Mojo generator produces `struct mydsp`: its state, initialization, metadata, user interface
description, and processing methods. An architecture supplies the application entry point, audio driver,
GUI, memory management, and other support code. The CPU path calls `compute`; the experimental GPU path
also generates the device operations required by `FaustDspGpu`.

## FAUST architectures

A FAUST architecture is a Mojo template selected with `-a`. The compiler inserts the generated DSP between
the architecture's first section (imports and definitions) and second section (application entry point):

```
    architecture-provided imports and definitions
    <<includeIntrinsic>>
    <<includeclass>>
    architecture-provided main and lifecycle
```

`<<includeclass>>` receives the DSP class emitted by `MojoCodeContainer.produceClass()`;
`<<includeIntrinsic>>` remains in the template for the compiler's architecture expansion. The top-level
templates use matching section comments to mark these boundaries.

`portaudio.mojo`, `portaudio-terminal.mojo`, `portaudio-proto.mojo`,
`portaudio-terminal-gpu.mojo`, `bench.mojo`, `inspect.mojo`, and `impulse.mojo` follow this structure.
The packages below contain their reusable implementations; the templates compose those packages around
the generated DSP.

## DSP interface

The `FaustDsp` trait in `dsp/dsp.mojo` specifies the common CPU architecture contract. It includes input
and output counts, the sample rate, initialization and reset, metadata and JSON, UI construction, and
block processing:

```
    dsp.compute(count, inputs, outputs)
```

The generated `mydsp` conforms to this contract, so the PortAudio callback can process a DSP without
knowing its concrete fields. The CPU architecture and benchmark and impulse tools use this interface.

The GPU variant also conforms to `FaustDspGpu` in `dsp/gpu.mojo`. This trait adds static
`gpu_work_size(count)` and `gpu_compute(ctx, dsp_raw, in_buf, out_buf, work_buf, count)` operations. Its
default `compute` body is empty: GPU audio passes an `AdapterDsp[mydsp]` to PortAudio so the callback
invokes the adapter's `compute`, which forwards the block to `GpuDevice`. Directly passing the GPU DSP to
PortAudio would not execute GPU processing.


<!-- NOTE:(Ari) devi parlare in termini generali delle interazioni delle parti, non devi citare esplicitamente -->
<!-- portaudio o terminal gui, le si spiega dopo esplictiamente, non ha senso citarle qui che stai spiegando il -->
<!-- sitema in generale. Inoltre tutta la parte della gpu essendo atipica la fai alla fine, faciamo un capitolo -->
<!-- separato di gpu processing dove spieghi tutta quella roba li. -->


The generator and the selected architecture meet in the complete Mojo file:

```
    FAUST program                 architecture template (-a)
          |                                  |
    Mojo generator                  imports and application main
          |                                  |
          +------------ mydsp ---------------+
                           |
                     Mojo compiler
                           |
                       application
```

## Organization into Mojo modules and packages

A `.mojo` file is a module. A directory containing `__init__.mojo` is a package whose initializer can
re-export its public API. The current layout is:

```
    architecture/mojo/
    ├── audio/                          FaustAudio, PortAudio, PortAudio FFI
    ├── bench/                          benchmark runner and reports
    ├── conf/                           prelude, type aliases, compile-time definitions
    ├── dsp/                            FaustDsp, FaustDspGpu, AdapterDsp
    ├── gpu/                            GpuDevice and GPU helpers
    ├── gui/                            FaustGui, ControlGui, ProtoGui, TerminalGui, MapGui
    │   └── terminal/native/            C11 terminal library and Makefile
    ├── help/                           mathematical, SIMD, and I/O helpers
    ├── mem/                            buffer allocation helpers
    ├── meta/                           FaustMeta
    ├── pulse/                          impulse test runner
    ├── test/                           test .dsp FAUSt sources
    ├── portaudio.mojo
    ├── portaudio-terminal.mojo
    ├── portaudio-proto.mojo
    ├── portaudio-terminal-gpu.mojo
    ├── bench.mojo
    ├── inspect.mojo
    └── impulse.mojo
```

Templates import from package entry points, never from their implementation submodules. They always
import the full prelude with `from conf import *`; other imports reflect the template's actual needs.
For example, the impulse template uses `from pulse import *` and
`from gui import FaustGui, ControlGui`. The GPU terminal template obtains `AdapterDsp` from `dsp`,
`GpuDevice` and `has_accelerator` from `gpu`, `TerminalGui` and the control map from `gui`, and
`PortAudio` from `audio`.

Implementation modules may import a concrete sibling or leaf module to avoid circular package imports.
The `__init__.mojo` files define the public surface used by architecture templates.

### Location of generated files

The generated Mojo file imports these packages. Supply the `architecture/mojo` directory to Mojo with
`-I`, whether the generated file is inside or outside that directory:

```
    mojo build -I architecture/mojo path/to/generated_dsp.mojo -o generated_dsp
```

When building from `architecture/mojo`, use `-I .` instead.

## Pixi environment

This directory is a Pixi workspace. `pixi.toml` uses `max-nightly` and `conda-forge`, depends on
development versions of `modular` and `mojo`, and targets `osx-arm64`. `pixi.lock` records the resolved
environment. From this directory:

```
    pixi install
    pixi shell
```

Commands may also be run through `pixi run`.

## Common components

### Configuration

`conf/prelude.mojo` exports arithmetic and SIMD aliases, pointer and stream types, memory and alignment
constants, and the architecture's external sample type. `conf/__init__.mojo` re-exports the full prelude.
The prelude imports the common standard library and GPU host definitions with `*`.

```
    comptime dfaust = get_defined_dtype["DFAUST", f32]()
    comptime FaustFloat = Scalar[dfaust]
```

`DFAUST` defaults to `f32` and can be set with `-D DFAUST=DType.float32`. It describes the external
sample and UI-zone type; it is distinct from FAUST's internal precision setting (`-single` or `-double`).
The PortAudio and current GPU templates require 32-bit external samples. The current Mojo GPU generator
also requires `-single` internal precision.

### DSP

<!-- NOTE(Ari): non initiare mai le cazo di frasi don minuscola o con il nome di una classe struttura o modulo. -->
<!-- ad esempio qui dovresi dire 'Il modulo dsp esporta....' -->

`dsp` publicly exports `FaustDsp`, `FaustDspGpu`, and `AdapterDsp`. The adapter holds pointers to the
generated DSP and a prepared GPU device, delegates initialization, metadata, and UI construction to the
DSP, and implements the `FaustDsp.compute` call by invoking `GpuDevice.process`.

### Audio

`audio` exports `FaustAudio`, `PortAudio`, `SAMP_RATE`, and `BUFF_SIZE`. The `FaustAudio` contract has
`init`, `start`, `stop`, and `is_alive`. `audio/portaudio/ffi.mojo` contains the C bindings; the PortAudio
implementation opens a non-interleaved `float32` stream and registers a callback that calls the DSP's
`compute`. The same driver accepts a generated CPU DSP or the GPU adapter.

PortAudio defines `SAMP_RATE` as a value in kHz multiplied by 1,000: the default `96` means 96 kHz.
Its default `BUFF_SIZE` is 256 frames. Thus use `-D SAMP_RATE=48` for 48 kHz in PortAudio templates.

### GUI

`gui` exports the `FaustGui` trait, `ControlGui`, `ProtoGui`, `TerminalGui`, and GPU control-map helpers.
The generated `build_user_interface` describes nested groups, controls, bargraphs, and metadata through
the `FaustGui` methods. `run()` is the blocking GUI call on the main thread; methods for unsupported
widget kinds may use the trait's default empty implementation.

- `ControlGui` operates buttons for impulse tests.
- `ProtoGui` is a small text-input prototype.
- `TerminalGui` builds a stack-based widget hierarchy and runs the native C11 terminal interface.

The terminal interface supports sliders, number entries, buttons, checkboxes, bargraphs, mouse interaction,
and numerical entry. `gui/terminal/ffi.mojo` bridges Mojo to
`gui/terminal/native/termgui.c`. Build the static library before linking a terminal architecture:

```
    make -C gui/terminal/native release
```

The resulting library is `gui/terminal/native/build/libtermgui.a`.

### GPU

`gpu` exports `GpuDevice`, GPU error codes, kernel indices, and `has_accelerator`. `GpuDevice.prepare`
allocates the device DSP, channel buffers, and work storage. `MapGui` visits the DSP UI to record
active control zones and passive meter zones. On each block, the device transfers changed controls and
input samples, enqueues the generated kernels, copies output samples and meters back, and synchronizes.
The DSP state stays on the device between blocks. `get_error` reports callback errors after playback,
and `release` frees the device state when processing has stopped.

This is the current prototype GPU path; the generated GPU DSP uses `FaustDspGpu` and the ordinary
`FaustAudio`/`PortAudio` integration through composition with `AdapterDsp`.

### Metadata

`meta` provides `FaustMeta`, the interface used by generated code to report FAUST metadata.

### Helpers

`help` contains math, SIMD load/store, and input-wait helpers used by the generated code and templates.

### Memory

`mem` supplies explicit buffer allocation and release for benchmark, inspection, and impulse programs.

### Benchmark and Test

`bench` implements the benchmark runner and reporting used by `bench.mojo` and `inspect.mojo`.
`pulse` implements the impulse test runner used by `impulse.mojo`. Their top-level templates allocate
the DSP and buffers, then invoke the corresponding package functions.

## Available architectures

The top-level `.mojo` templates are selected with FAUST's `-a` option.

```
portaudio.mojo
```

Allocates and initializes a CPU DSP, starts PortAudio, waits for standard input on the main thread,
stops the stream, and releases the DSP. PortAudio calls its `compute` from the audio callback.

```
portaudio-terminal.mojo
```

Builds a `TerminalGui` from the CPU DSP, starts PortAudio, and enters the blocking terminal GUI loop.
The GUI edits the DSP's host control zones; the callback reads them during processing.
Requires PortAudio and `libtermgui.a` when linking.

```
portaudio-proto.mojo
```

Builds `ProtoGui()` from a CPU DSP and runs its simple text loop while PortAudio processes audio.
This template is intended for prototypes; the native terminal architecture provides the richer UI.

```
portaudio-terminal-gpu.mojo
```

Builds `TerminalGui`, `MapGui`, `GpuDevice[mydsp]`, `AdapterDsp[mydsp]`, and the normal `PortAudio`
driver. After preparing the device, it gives the adapter to PortAudio and runs the GUI on the main thread.
On shutdown, it stops the audio stream before releasing GPU and DSP storage. Requires a GPU-capable DSP,
a supported accelerator, PortAudio, and `libtermgui.a`.

```
bench.mojo
```

Allocates buffers, warms up the CPU DSP, measures repeated `compute` calls, and reports results without
starting an audio driver. The benchmark package controls optional CSV output.

```
inspect.mojo
```

Runs the CPU DSP through an exported, non-inlined `inspect_compute` function. `keep` and
`clobber_memory` make the generated low-level code easier to locate and examine.

```
impulse.mojo
```

Initializes the CPU DSP and `ControlGui`, then uses `pulse` to print an impulse response in the format
expected by the FAUST impulse tests.

<!-- NOTE:(Ari) questa parte la devi spiegare all'inizio nella sezione del disegno generale, e non citare -->
<!-- esplictamente portaudio, parla di callback del driver audio ad esempio, non di cose specifiche. -->

## Audio execution flow

For CPU templates, `main` initializes `mydsp`, optionally builds a GUI, and passes the DSP to
`PortAudio.start`. PortAudio's callback calls `mydsp.compute`. The main thread waits in the GUI's `run`
or the architecture's input loop, then stops PortAudio and releases the DSP.

```
    main                             PortAudio callback
      |                                      |
      +--> mydsp.init                        |
      +--> build_user_interface (optional)  |
      +--> PortAudio.start(mydsp) ---------> mydsp.compute
      +--> GUI.run / input wait              |
      +--> PortAudio.stop <------------------+
      +--> release mydsp
```

For the GPU terminal template, `main` also creates the control map and device before calling
`PortAudio.start(adapter)`. The callback calls `AdapterDsp.compute`, which invokes
`GpuDevice.process`: host controls and inputs move to the device, generated GPU kernels run, then audio
outputs and meters return to the host. The callback finishes the block after GPU synchronization.

## Compile-time configuration

Mojo `-D` definitions specialize the architecture when building the generated file:

```
    -D DFAUST=DType.float32 -D SAMP_RATE=48 -D BUFF_SIZE=128
```

For PortAudio, `SAMP_RATE=48` means 48 kHz. Benchmark code defines its sample rate directly in Hz
(default 96,000); `pulse` also uses Hz (default 44,100). `BUFF_SIZE` is in frames. Benchmark and
inspection components have additional definitions such as `COMPUTE_ITERS`.

FAUST's `-single`/`-double` flags select *internal* DSP precision. `-gpu` selects the experimental Mojo
GPU generator; it currently accepts `-single` and requires `FaustDspGpu` at the architecture boundary.

## Essential workflow

NOTE:(Ari) anche qui non ha senso fare i riferimenti ai nomi dei file sorgenti.


From `architecture/mojo`, generate a CPU DSP with the terminal template:

```
    make -C gui/terminal/native release
    /path/to/faust -lang mojo -single -a portaudio-terminal.mojo \
        -o program.mojo test/phasorsine.dsp
```

Compile it with the architecture packages and native libraries available to the linker:

```
    mojo build -O3 -I . -D DFAUST=DType.float32 -D SAMP_RATE=48 -D BUFF_SIZE=128 \
        -Xlinker -L/opt/homebrew/opt/portaudio/lib -Xlinker -lportaudio \
        -Xlinker gui/terminal/native/build/libtermgui.a -Xlinker -lm \
        -o program program.mojo
```

For GPU processing, select the GPU generator and GPU terminal template, then build with the same
PortAudio and terminal link options:

```
    /path/to/faust -lang mojo -gpu -single -a portaudio-terminal-gpu.mojo \
        -o program_gpu.mojo test/phasorsine.dsp
    mojo build -O3 -I . -D DFAUST=DType.float32 -D SAMP_RATE=48 -D BUFF_SIZE=128 \
        -Xlinker -L/opt/homebrew/opt/portaudio/lib -Xlinker -lportaudio \
        -Xlinker gui/terminal/native/build/libtermgui.a -Xlinker -lm \
        -o program_gpu program_gpu.mojo
```

Adjust the PortAudio library search path for the local installation. To use `portaudio.mojo`,
`portaudio-proto.mojo`, `bench.mojo`, `inspect.mojo`, or `impulse.mojo`, change the template passed to
`-a` and provide the libraries required by that template.
