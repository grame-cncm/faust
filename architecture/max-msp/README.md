# faust2max6

The **faust2max6** tool transforms a Faust DSP program into a compiled Max/MSP external, and a ready-to-use patch to load and use it, containing the control GUI. Polyphonic and MIDI controllable instruments can be created. It compiles 64 bits externals for Max6 and newer versions.

## How to use

**faust2max6** is used with the following options: 

`faust2max6 [-osc] [-midi] [-soundfile/-soundfile-static] [-opt native|generic] [-nvoices <num>] [-us <factor>] [-ds <factor>] [-filter <filter>] [-effect <effect.dsp>] [-mc] [-native] [-arch auto|arm64|x86_64|universal] [-universal] [-nopatch] [-nopost] [additional Faust options (-vec -vs 8...)] <file.dsp>`

By default it will create the *file~.mxo* external along with a *file.maxpat* patch file and a *ui.js* helper file, that will load the external and automatically create a User Interface (with sliders, buttons...) ready to control it. To be fully functional, the object still has to be connected to audio inputs/outputs or other elements in the patch. **Double-click** on the object allow to display its controls with their **range**, **label**, **shortname** and **complete path**. Note that  *-double* compilation mode is used by default in **faust2max6**.

Attributes can be used at object creation time, for instance the following DSP code:

```
import("stdfaust.lib");
freq = hslider("freq", 200, 50, 1000, 0.01);
gain = hslider("gain", 0.5, 0, 1, 0.01);
process = os.sawtooth(freq) * gain;
```
can be started with the following `@freq 700` and `@gain 0.6` attributes to configure parameters at creation time. Note that labels containing whitespace (like "freq Hz") cannot be used as attributes, they will have to be renamed.

#### Regular or multi-channels inputs/outputs

By default, and depending of the number of audio inputs and outputs described in the DSP source code, the compiled .xmo/.xme object has:
- N inlets, the first one being an audio inlet combined with the message control inlet, and all other audio inlets
- M outlets, audio outs from 1 to M-1 (or 2 if MIDI outlet is created)
- an output messages outlet 
- the right most outlet is used to send MIDI messages if MIDI metadata are used in the DSP UI items, and is only created when the `-midi` option is used

If compiled with the `-mc` option, the compiled .xmo/.xme object has: 
- one multi-channels audio inlet combined with the message control inlet
- one multi-channels audio outlet
- an output messages outlet 
- the right most outlet is used to send MIDI messages if MIDI metadata are used in the DSP UI items, and is only created when the `-midi` option is used

### Controlling

The compiled .xmo/.xme object can be controlled with the following messages, which can be used depending of the parameters used at compilation time:

- `polyphony <nvoices>` : to set the DSP in polyphonic mode with *nvoices* (note that the DSP code has to follow the [polyphonic convention](https://faustdoc.grame.fr/manual/midi/))
- `osc <IP inport outport xmit[0|1] bundle[0|1]>`: to activate OSC control in input and output mode, possibly generating messages when *xmit = 1*, and in bundle mode when *bundle = 1* 
- `midievent <midi message>`: to receive and decode MIDI messages
- `init`: to generate all inputs and outputs control messages as a message list *[path, init, min, max]* that will be sent on the output messages outlet
- `dump`: to generate all inputs and outputs control messages as a message list *[path, cur, min, max]* that will be sent on the output messages outlet 
- `mute`: to mute audio rendering

When the object has bargraphs, their values are sent in the right most outlet as a message list *[path, cur, min, max]*.

#### Input controllers 

All control messages are received in the left most inlet (the signal + message inlet) with the `<label|shortname|path> <number>` syntax. Their number and exact syntax obviously depend of the actual Faust DSP code. `Label` is the simple name of the controller (like `freq` of `gain`), the `shortname` is the smallest unique name that can be used, and `path` is the complete path following the OSC convention (like `osc/freq` of `osc/gain` kind of path). The `shortname` or `path` syntax has to be used to be sure all controllers are distincts. The `number` parameter is the actual float value for the controller. 

#### Output controllers

When the object has bargraphs, their values are sent on the output messages outlet as a message list *[path, cur, min, max]*.

## Options

Here are the available options:

  - `-opt native` : to activate the best compilation options for the native CPU
  - `-opt generic` : to activate the best compilation options for a generic CPU 
  - `-native` to compile for the native CPU (otherwise the 'generic' mode is used by default)
  - `-nvoices <num>` : to produce a polyphonic self-contained DSP with <num> voices, ready to be used with MIDI
  - `-effect <effect.dsp>` : to produce a polyphonic DSP connected to a global output effect, ready to be used with MIDI
  - `-midi` : to activate MIDI control
  - `-osc` : to activate OSC control
  - `-us <factor>` : upsample the DSP by a factor
  - `-ds <factor>` : downsample the DSP by a factor
  - `-filter <filter>` : use a filter for upsampling or downsampling [0..4]
  - `-arch arm64` : to generate an ARM64-only external on macOS (`x86_64` and `universal` are also accepted)
  - `-universal` : to generate a 64 bits x86/ARM universal external on macOS 
  - `-nopatch` : to deactivate patch generation
  - `-nopost` : to disable Faust messages to Max console
  - `-soundfile`: when compiling DSP using 'soundfile' primitive, to add the needed resources (soundfiles) in the produced .mxo file, and have the required libsndfile library statically linked
  - `-soundfile-dynamic` : when compiling DSP using 'soundfile' primitive, to add the needed resources (soundfiles) in the produced .mxo file, and use the installed libsndfile library (so possibly using dynamic link)
  - `-help or -h` : shows the different options 
 
## Configuration

If you plan to use **faust2max6** on your own machine, you will have to:

- install [Max/MSP SDK](https://cycling74.com/downloads/sdk)
- edit the `faust/tools/faust2appls/faustpath` script to properly setup the $MAXSDK variable, then re-install the scripts again using `sudo make install`
- alternatively you can locally change the $MAXSDK variable in a terminal using `export MAXSDK=/your/alternate/path`, then use **faust2max6** in this terminal.

## Misc

- the original DSP file as well as the compiled self-contained C++ file are kept in the compiled `.mxo` external, in `Contents/Resources`, to be accessed using the *Show Package Contents* option. Soundfiles added with `-soundfile` are copied there too, so that the external can be code signed.

# faust2gen

The **faust2gen** tool transforms a Faust DSP program into a ready-to-use patch containing a **faustgen~/mc.faustgen~** object to compile it. Polyphonic and MIDI controllable patches can be created. The `read` message with the given DSP filename is added in the patch, so that the DSP code can be read and compiled. The control GUI is automatically created and connected to the **faustgen~/mc.faustgen~** object after the compilation step. The DSP code can be edited with an external editor. After the DSP code has been changed externally, the `read` message has to be used again to trigger compilation and GUI update.   

## How to use

**faust2gen** is used with the following options: `faust2gen [-nvoices <num>] [-mc] <file.dsp>` 

## Options

Here are the available options:

 - `-nvoices <num>` : to produce a polyphonic ready patch to be used with MIDI events
 - `-mc` : to use a mc.faustgen~ object

# faust2rnbo

The **faust2rnbo** tool transforms a Faust DSP program into a RNBO patch including the generated codebox code. Polyphonic and MIDI controllable instruments can be created. The `-sp` option allows to generate as a reusable rnbopat file. Two rnbopat files will always be generated in polyphonic mode with an effect, since using abstractions is the appropriate model to combine the DSP and effect in a single `rnbo~`object. Additional options are used to generate a special version of the RNBO patch used in the testing infrastructure. 

## How to use

**faust2rnbo** is used with the following options: 

`faust2rnbo [options] [additional Faust options] <file.dsp>`

The Codebox backend used by RNBO does not support Faust's `-vec` option; do
not combine it with `faust2rnbo`.

## Options

Here are the available options:

  - `-midi` : activates MIDI control
  - `-nvoices <num>` : produces a polyphonic DSP with <num> voices, ready to be used with MIDI events
  - `-effect <effect.dsp>` : generates a polyphonic DSP connected to a global output effect, ready to be used with MIDI or OSC
  - `-effect auto` : generates a polyphonic DSP connected to a global output effect defined as 'effect' in <file.dsp>, ready to be used with MIDI or OSC
  - `-compile` : to trigger C++ compilation at load time
  - `-test` : to generate special 'RB_XX' prefix for parameters (for testing)
  - `-sp` : to generate codebox subpatchers as a file.rnbopat file
  - `-cpp_path <path>` : to set C++ export folder 
  - `-cpp_filename <filename>` : to set C++ export filename
 
By default it will create the *file.maxpat* patch file. 

# faustgen2max

`faustgen2max.py` turns Max prototypes that use `faustgen~` or `mc.faustgen~`
into distributable patches backed by native externals compiled with
`faust2max6`. It uses py2max to read and rewrite the complete patch hierarchy,
including embedded subpatchers.

For each faustgen box the converter:

1. extracts the Faust program from its `sourcecode` property;
2. infers the required compilation features from the source and the patch;
3. compiles the program as a Max `.mxo` external with `faust2max6`;
4. changes the box text to the compiled external name; and
5. removes the faustgen source and machine-code properties from the output.

The replacement is performed in place in the py2max model. Box ids, positions,
scripting names, other attributes, and patch cords are therefore preserved.
The input `.maxpat` is read-only and is never modified.

## Requirements

- Python 3.9 or newer;
- py2max, either installed as a Python package or present in the adjacent
  `architecture/max-msp/py2max` checkout;
- Faust and the tools used by `faust2max6` available on `PATH`;
- the Max SDK configured as described in the **Configuration** section above;
- a `sourcecode` property containing the Faust program in every converted box.

When run from a Faust source checkout, the converter automatically prefers that
checkout's `tools/faust2appls/faust2max6` and matching `architecture/` directory.
This prevents an older installed architecture from being used accidentally.
Existing `FAUSTARCH` and `FAUST_ARCH_PATH` environment variables remain
authoritative. Use `--faust2max6` to select another compiler wrapper explicitly.

## Basic conversion

```bash
python3 architecture/max-msp/faustgen2max.py my-prototype.maxpat
```

By default, a patch named `my-prototype.maxpat` produces the sibling directory
`my-prototype-compiled/` with this layout:

```text
my-prototype-compiled/
├── my-prototype-compiled.maxpat
├── my-prototype-compiled.json
├── external_name.dsp
└── external_name~.mxo/
```

There is one `.dsp` and `.mxo` pair per distinct Faust source and compilation
configuration. Identical boxes share the same external. The JSON manifest
records the input/output paths, analysis of every box, compiler arguments,
include directories, generated bundles, source lengths and source SHA-256
hashes. It deliberately does not duplicate the Faust source text.

Use `--output-dir` to choose the output directory for exactly one input patch:

```bash
python3 architecture/max-msp/faustgen2max.py \
    --output-dir /tmp/compiled \
    my-prototype.maxpat
```

Multiple files may be supplied. A directory input is searched recursively for
`.maxpat` files. With multiple patches, `--output-root` creates one
`<patch>-compiled` child directory per patch:

```bash
python3 architecture/max-msp/faustgen2max.py \
    patches/ another-patch.maxpat \
    --output-root compiled/
```

Without `--output-root`, every result is placed beside its input patch.
`--output-dir` and `--output-root` are mutually exclusive.

## Analysis mode

`--analyze` prints the detected objects and compilation decisions as JSON. It
does not invoke `faust2max6`, create directories, or write files:

```bash
python3 architecture/max-msp/faustgen2max.py \
    --analyze \
    my-prototype.maxpat
```

Nested objects have stable locations such as `root/obj-20/obj-2`. These
locations, along with `object_id`, `varname`, and the one-based `index`, can be
used to identify an object when overriding its generated name.

## Feature inference and overrides

The converter chooses the default `faust2max6` arguments as follows:

- `mc.faustgen~` adds `-mc`;
- a faustgen MIDI outlet layout, a detected voice count, `[midi:...]` Faust
  metadata, or incoming MIDI/MPE objects and messages adds `-midi`;
- an incoming `osc ...` message adds `-osc`;
- use of the Faust `soundfile(...)` primitive adds `-soundfile`;
- `declare nvoices "N";` in the source or an incoming constant `polyphony N`
  message records the intended number of voices and enables MIDI inference;
  when there is no declaration, the value is also passed as `-nvoices N`.

MIDI, OSC, and soundfile detection can each be kept automatic, forced on, or
forced off:

```bash
python3 architecture/max-msp/faustgen2max.py \
    --midi always \
    --osc never \
    --soundfile auto \
    my-prototype.maxpat
```

The accepted values are `auto`, `always`, and `never` (the French aliases
`oui`, `non`, `toujours`, and `jamais` are also accepted). `--nvoices N`
replaces the detected voice count for all faustgen boxes in the selected
patches.

Incoming prototype messages and their patch cords are preserved. The converter
warns about `read`, `write`, `compileoptions`, and `librarypath`, because those
faustgen-specific messages do not configure a compiled external.

## External names

The default name is selected in this order:

1. the Faust `declare name "...";` metadata;
2. the Max scripting name (`varname`), unless it is an automatically generated
   `faustgen-N` name;
3. the input patch filename and, when needed, the object id.

Names are converted to portable lowercase C++ identifiers. Collisions receive
a numeric suffix. Override a name with a repeatable `--name` assignment:

```bash
python3 architecture/max-msp/faustgen2max.py \
    --name synth=poly_synth \
    --name root/obj-20/obj-2=filter_bank \
    my-prototype.maxpat
```

The selector before `=` may be the full nested location, Max box id, scripting
name, or one-based occurrence number. If several selectors match one box, they
must assign the same name.

## Target architecture

`--arch` controls the Mach-O architecture produced by `faust2max6` on macOS:

- `auto` keeps the historical behavior: universal on Apple Silicon and
  `x86_64` on Intel;
- `arm64` produces a thin Apple Silicon external;
- `x86_64` produces a thin Intel external;
- `universal` combines both slices.

An ARM64-only build is useful when an optional static dependency, such as an
OSC or soundfile library, is only available for Apple Silicon:

```bash
python3 architecture/max-msp/faustgen2max.py \
    --arch arm64 \
    /Users/letz/Developpements/faust/embedded/faustgen/Faustgen-poly-midi.maxpat
```

An explicitly selected non-`auto` architecture and all inferred flags appear
in the manifest's `args` arrays. The generated bundle can be checked with:

```bash
lipo -archs external_name~.mxo/Contents/MacOS/external_name~
```

## Additional compiler options

`--compiler-arg` is repeatable and passes arguments directly to `faust2max6`.
Use the `--compiler-arg=VALUE` form when a value begins with `-`:

```bash
python3 architecture/max-msp/faustgen2max.py \
    --compiler-arg=-vec \
    --compiler-arg=-lv=1 \
    my-prototype.maxpat
```

These options apply to every compilation unit. `-nopatch` is always added so
that `faust2max6` creates only the external; `faustgen2max.py` itself creates
the final rewritten patch.

## Python API

The module can also be imported by tests or other conversion tools. Its two
public workflow functions are:

```python
patcher, infos = analyze_patch(patch_path, **analysis_options)

output_patch, manifest, infos = convert_patch(
    patch_path,
    output_dir,
    faust2max6="faust2max6",
    force=False,
    **analysis_options,
)
```

`analyze_patch` returns the mutable py2max `Patcher` and a `FaustgenInfo` for
each object without writing files. `convert_patch` performs the analysis,
compilation, rewrite, and manifest generation. It raises `ConversionError` for
conversion failures. A custom `compile_runner(command, cwd)` may be injected by
tests or embedding applications.

## Existing outputs, paths, and exit status

Existing generated products are protected by default. `--force` allows their
replacement. It does not modify the input patch or remove unrelated files from
the output directory.

Input and output paths may contain spaces. To accommodate the internal shell
handling in `faust2max6`, compilation takes place in a temporary directory with
short symlinks to the original Faust include directories, after which the
finished bundles are copied to the requested output directory.

Exit status is `0` on success, `1` when analysis finds an input patch with no
faustgen object, and `2` for invalid arguments, missing sources, existing
outputs, compilation failures, or file errors.

Run the built-in help for the complete option summary:

```bash
python3 architecture/max-msp/faustgen2max.py --help
```
