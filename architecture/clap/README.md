# faust2clap 
#### by Facundo Franchino, under the mentorship of Stéphane Letz and Jatin Chowdhury

## Overview

`faust2clap` is a tool which connects  **Faust DSP code** with the **CLAP plugin standard**. It allows a developer to take a Faust .dsp file and produce a working CLever Audio Plugin with little extra work.
This tool supports both **statically compiled** and **dynamically reloaded (hot reload)** DSP implementations.

In addition to this static mode, a dynamic implementation has been added. In this form, a single plugin can compile and reload any .dsp program while it is running. The user does not need to build a new binary or close and reopen the plugin in the host. The code may be altered and hot-reloaded directly, while the host continues without interruption. This approach makes testing and development faster, and allows experiments to be carried out in the same environment in which the final plugin will be used, for example in a DAW such as Reaper.

---

## Features
- ✅ Generate CLAP plugins directly from Faust (.dsp file) code  
- ✅ Hot-reloading of DSP: update `.dsp` files without restarting the host or closing the plugin
- ✅ Parameter discovery and synchronisation with host  
- ✅ MIDI and polyphonic support via Faust’s `mydsp_poly`  
- ✅ State save/restore, parameters recalled properly (static mode; see Known Issues for the dynamic one)  
- ✅ 32f/64f audio I/O support  

---

## 💻 Usage

### 🛠️ Static build 
Generate and build a static CLAP plugin from your DSP file

```shell
faust2clap your_file.dsp
```
```shell
optional flags:
  -nvoices N   build a polyphonic instrument with N voices
  -midi        accepted for consistency; CLAP plugins always receive host MIDI
  --clap-sdk DIR   directory holding clap-sdk/ and clap-helpers/
  --no-install     build only, do not copy into the user CLAP directory
```

Polyphony follows the same convention as the other `faust2xx` tools:
`-nvoices N` requests it, otherwise the DSP's own `declare nvoices "N";` is
used, otherwise the plugin is monophonic. There is no flag to force mono —
no sibling tool has one, and a `declare nvoices` is the DSP saying what it is. Unrecognised options are passed
through to the Faust compiler, so `-vec -lv 0 -I /path/to/lib` behave as
elsewhere.

A DSP with no audio input is declared to hosts as an **instrument**
(`[instrument]`, plus `[synthesizer]` when it is polyphonic); anything else is
an `[audio-effect]`. The arity comes from the `-uim` macros, which the tool asks
Faust for. This matters for more than tidiness: REAPER records the kind in its
plugin cache, so a synthesiser announced as an effect never appears where a
musician looks for one. After rebuilding a plugin whose kind changed, rescan in
**Options → Preferences → Plug-ins → CLAP → Re-scan**.

`-osc` and `-soundfile` are refused rather than ignored: the CLAP architecture
builds neither interface, so accepting them would produce a plugin silently
missing what was asked for.

Generated sources and the build tree are written beside the input `.dsp`, in a
`<name>-clap/` directory. The `-clap` suffix matters: `<name>` on its own is
what `faust2caqt`, `faust2jaqt` and other siblings call the executable they
build from the same program, so an unsuffixed directory would collide with it.

The plugin is built and installed into the per-user CLAP directory for the
platform, as listed in the CLAP specification (`clap/entry.h`):

| Platform | Destination |
|---|---|
| macOS | `~/Library/Audio/Plug-Ins/CLAP` |
| Linux | `~/.clap` |
| Windows | `%LOCALAPPDATA%\Programs\Common\CLAP` |

Setting `CLAP_PATH` overrides this — its first entry is used, so builds land
wherever your hosts already look. `--no-install` builds without copying.

On macOS the plugin is a `.clap` bundle; elsewhere it is a `.clap` shared
object. Only the macOS path has been exercised so far.

###  Dynamic (Interpreter) mode

Unlike the static mode there is no `faust2xx` script here: the dynamic plugin
is one binary, built once, that compiles `.dsp` programs itself at runtime.
Build it by hand from `architecture/clap`.

#### 1. Prerequisites

**The CLAP submodules**, from the root of the Faust checkout:

```bash
git submodule update --init external/clap-sdk external/clap-helpers
```

**A `libfaust` carrying the interpreter backend.** This is what the plugin
links against, and it is the only Faust library it needs — the interpreter
compiles and runs the DSP without LLVM. From the root of the Faust checkout:

```bash
make interp
sudo make install
```

That installs a `libfaust` (about 12 MB) with the interpreter backend alone. A
`libfaust` built the usual way also carries the LLVM backend and then needs the
LLVM libraries at link time; see the troubleshooting notes below.

#### 2. Build

```bash
cd architecture/clap
make
```

This produces `FaustDynamic.clap` (about 5 MB) in place. `make help` prints the toolchain, the Faust paths it resolved and the
install directory it would use — the first thing to look at if something is
wrong.

`CXX`, `CXXFLAGS`, `LDFLAGS` and `ARCHFLAGS` are honoured, so a distribution
build can impose its own toolchain:

```bash
make CXX=clang++ CXXFLAGS="-O3 -Wall"
```

#### 3. Install

```bash
make install
```

`FaustDynamic.clap` goes into the per-user CLAP directory named by the
specification: `~/Library/Audio/Plug-Ins/CLAP` on macOS, `~/.clap` on Linux.
`make clean` removes the build output.

On macOS the result is a bundle whose `Info.plist` declares
`CFBundlePackageType BNDL`. A host inspects that before loading anything and
refuses a bundle that claims to be an application, which is what a plain shared
library copied into place looks like.

#### Troubleshooting the build

**Undefined LLVM symbols at link time** — your `libfaust` carries the LLVM
backend. Either rebuild it with `make interp`, or pass LLVM in:

```bash
make LLVM_LIBS="$(llvm-config --ldflags --libs --system-libs)"
```

**The plugin does not appear in your DAW (macOS)** — check that the host is not
running under Rosetta. The build is native-only by default, because it can only
be as universal as the `libfaust` and LLVM it links; an `x86_64` host cannot
load an `arm64` plugin, scans a different cache and reports nothing. With a
universal `libfaust` available:

```bash
make ARCHFLAGS="-arch arm64 -arch x86_64"
```

**`cannot find clap/clap.h`** — the submodules of step 1 are not checked out.

#### 4. Choose the DSP you are working on

The plugin does not embed a DSP. It reads a **control file** naming the `.dsp`
to load, and then watches both that file and the DSP it names.

| Platform | Control file |
|---|---|
| macOS | `~/Library/Application Support/faust-clap/current-dsp.txt` |
| Linux | `$XDG_RUNTIME_DIR/faust-clap/`, else `$XDG_CONFIG_HOME/faust-clap/`, else `~/.config/faust-clap/` — file `current-dsp.txt` |
| Windows | `%LOCALAPPDATA%\faust-clap\current-dsp.txt` |

It holds one line: the absolute path of the DSP. The directory is created
private to you (mode `0700`), because the file names a program the plugin will
compile and run.

**Point it at your DSP** — writing this file switches the plugin over within a
fraction of a second, with the host still playing:

```bash
echo ~/my-dsp/reverb.dsp > ~/Library/Application\ Support/faust-clap/current-dsp.txt
```

**Or use the GUI** ([below](#the-hot-reload-gui)), which writes the same file
and keeps a history of the programs you have used:

```bash
cd architecture/clap
python3 faust-hot-reload.py
```

**Or name it before the host starts**, with `FAUST_DSP_FILE`. This is only read
at instantiation, and the control file wins over it if both are set:

```bash
export FAUST_DSP_FILE=~/my-dsp/reverb.dsp
```

**One DSP per plugin instance.** By default every instance follows the same
control file. Give an instance its own with `FAUST_CLAP_CONTROL`, and two
plugins in one session can work on two different programs:

```bash
export FAUST_CLAP_CONTROL=~/my-dsp/instance-a.txt
```

##### Working on it

From then on, just edit and save. The plugin notices the change, compiles on a
worker thread and swaps the result in — playback is not interrupted, and
controls that survived the edit keep the values you had set. Values are matched
by Faust address, so they carry across an edit of the same file; switching to a
*different* file starts from that program's own defaults, since the address of a
control includes the name of the program it belongs to.

**When it does not compile, nothing breaks.** The DSP that is playing keeps
playing, the failed one is simply not installed, and the error goes to standard
error. The plugin keeps watching the file, so fixing the mistake and saving
again is enough — no need to reload the plugin. The same is true at startup: a
DSP that fails then leaves the plugin passing audio through, still watching.

**So run your DAW from a terminal**, or you will not see why a reload did
nothing:

```bash
/Applications/REAPER.app/Contents/MacOS/REAPER
```

A successful load prints what was loaded; a failure prints the Faust compiler's
own message:

```
[Faust Dynamic] loaded /Users/you/my-dsp/reverb.dsp: 2 in, 2 out, 3 parameters
[Faust Dynamic] reload failed, keeping the current DSP: /Users/you/my-dsp/reverb.dsp:5 :
ERROR : init = 4 outside of [0.1 3] range in 'hslider("rate",4.0f,0.1f,3.0f,0.01f)'
```

##### Environment variables

| Variable | Effect |
|---|---|
| `FAUST_CLAP_CONTROL` | Control file to watch, per instance. Overrides the default path above |
| `FAUST_DSP_FILE` | DSP loaded at instantiation, used only when the control file names nothing |
| `FAUST_CLAP_PARAM_SLOTS` | Number of CLAP parameter slots (default 32) |

##### About the parameters

The host sees a fixed number of slots, each announced as a plain `0..1` range —
CLAP only lets a plugin change a parameter's range while it is deactivated, so a
fixed range is what allows the UI to follow a reload without interrupting audio.
The value displayed is the control's real one, in the DSP's own units. Slots are
keyed by Faust address and kept across a reload, so a control that survives an
edit stays on the same slot and keeps its automation.

###  The hot-reload GUI

`architecture/clap/faust-hot-reload.py` is a small companion window for the
dynamic plugin. It does exactly one thing to the system: **it writes the control
file**. Everything else it offers is convenience around that one write, so
nothing depends on it — the plugin never talks to it, and `echo` into the
control file achieves the same result.

```bash
cd architecture/clap
python3 faust-hot-reload.py
```

It needs Python 3 and `tkinter`, which ships with most Python installations. It
resolves the control file exactly as the plugin does, `FAUST_CLAP_CONTROL`
included, so pointing an instance at its own file also points the GUI at it.

What the window gives you:

- **Currently loaded** — reads the control file back and shows which program the
  plugin is on. Useful when several instances are in play, or after a session
  where you switched around.
- **Browse for a DSP file** — a file chooser that opens in your Faust examples
  directory when it can find one. Picking a file writes the control file, so the
  plugin switches immediately.
- **Recently used** — the last 20 programs, most recent first. Double-click one
  to load it. This is what makes A/B-ing two DSPs quick. The list is kept in
  `~/.faust-hot-reload-history.json` and prunes entries whose file has since
  disappeared.
- **Clear history** — empties that list.

It warns before writing if the path does not exist or does not end in `.dsp`,
but it does not compile anything and cannot tell you whether a program is
valid — only the plugin does that, and it reports through the terminal (see
above). A file loaded here that fails to compile will leave the previously
loaded DSP playing, exactly as if you had written the control file by hand.

---

## 🏛️ Architecture 

- **CLAPMapUI**: Custom UI wrapper to expose Faust parameters to CLAP.  
- **Interpreter backend**: Uses `libfaust`’s interpreter VM (`interpreter-dsp.h`) to enable hot-reloading.  
- **Static backend**: Uses statically compiled `mydsp` class.  
- **Audio handling**: Converts between host’s float/double and `FAUSTFLOAT` using temporary buffers or `dsp_sample_adapter`.  

###  Workflow

```text
        ┌──────────────┐
        │   Faust DSP  │   (your .dsp file)
        └──────┬───────┘
               │
               ▼
        ┌──────────────┐
        │  faust2clap  │   (static or dynamic)
        └──────┬───────┘
               │
               ▼
        ┌──────────────┐
        │   CLAP .so   │   (plugin binary)
        └──────┬───────┘
               │
               ▼
        ┌──────────────┐
        │   Host/DAW   │   (Reaper, Bitwig, etc.)
        └──────────────┘
```

---

## 🛑 Known Issues
- The dynamic plugin does not implement the CLAP state extension, so a saved
  session does not remember which DSP was loaded.
- Its ports are fixed stereo, because CLAP requires a stable port description
  while the DSP behind it changes. A mono DSP feeds both channels; a DSP with
  more than two outputs is truncated to two, with a warning. One with more than
  eight channels either way is refused rather than loaded.

---

## 🔐 Broader Limitations
- The **dynamic** plugin exposes a fixed number of parameter slots
  (`architecture/clap/dynamic-faust.cpp`), because a host cannot be told the
  parameter count changed on every edit. Slots are keyed by Faust address and
  kept across a reload, so automation survives an edit. The count defaults to 32
  and is set with `FAUST_CLAP_PARAM_SLOTS`; a control that finds no free slot is
  reported by name rather than silently dropped. The static path
  (`clap-arch.cpp`) has no such limit.
- The CLAP headers are installed with Faust (`share/faust/clap/include`), so
  the tool works from a plain installation. It falls back to the `external/`
  submodules in a source checkout, and `--clap-sdk DIR` / `CLAP_SDK_DIR`
  override both. A Faust built without the submodules checked out will not
  carry the headers, and `--clap-sdk` is then required.
- No "friendly" UI, yet. I will be working on a JUCE implementation for the GUI and a on-display preset management system which will end the need for an external python script that runs the .dsp selector.
- Although notably fast, utilising LLVM instead of the Interpreter could make it 3 to 10 times faster.

---

## Next Steps
- [ ] Simplify UI management (remove redundant classes)  
- [ ] Fix static build I/O conversion (investigate `dsp_sample_adapter`)  
- [ ] Add test suite for hot reload with various DSPs  
- [ ] Test with measure_dsp and dsp_optimizer classes to measure CPU consumption

---

## References
- [Faust Documentation](https://faustdoc.grame.fr/manual/architectures/)  
- [CLAP Plugin Standard](https://github.com/free-audio/clap)  
- Faust 2018 Paper – *An overview of the faust developer ecosystem*  

---

## Authors
- **Facundo Franchino**, under the mentorship of **Stéphane Letz** and **Jatin Chowdhury**
- Based on Faust (GRAME) and CLAP 

## Acknowledgements
- **Stéphane Letz** for choosing me to take on this project, and giving me the opportunity to contribute to the Faust ecosystem, as well as the constant support and feedback throughout the whole process.
- **Jatin Chowdhury** for the extensive CLAP knowledge and mentorship.
- **CLAP Discord community**, for all the discussions, feedback, and support (too many names to list!).


