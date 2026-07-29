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
- ✅ State save/restore (parameters recalled properly)  
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
Build the dynamic hot-reload plugin
```bash
cd architecture/clap
make -f Makefile.simple
```
Install to system plugin directories

```bash
make -f Makefile.simple install
```
The dynamic plugin (FaustDynamic.clap) will be installed to:
```bash
~/Library/Audio/Plug-Ins/CLAP/
~/.clap/plugins/
```

Clean build artifacts
```bash
make -f Makefile.simple clean
```

Once installed, use the GUI to load DSP files for hot-reloading:
Run the hot-reload GUI controller
```bash
cd architecture/clap
python faust-hot-reload.py
```
The GUI allows you to:
- Browse and load .dsp files
- View currently loaded DSP
- Access your history of used DSP files chronologically which can also be cleared
- Hot-reload DSP code while the plugin is running in your DAW


The dynamic plugin watches bash `/tmp/faust-current-dsp.txt`  for DSP file paths and automatically recompiles when the file changes.

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
- Some DSPs hot reload parameters correctly and process audio, but the desired effect from the DSP done in Faust can't be heard unless plugin is re-instantiated.  
- All quad-channel and some analysis DSP's currently crash Reaper (specifically quadEcho,fourSourcesToOcto and vumeter.dsp). These crashes stem from lower-priority design areas.

---

## 🔐 Broader Limitations
- The 12 fixed-parameter ceiling applies to the **dynamic** hot-reload plugin
  only (`architecture/clap/simple-faust.cpp`), where fixed slots are what lets
  a host keep its parameter assignments across a reload. The static path
  (`clap-arch.cpp`) uses `fUI.getParamsCount()` and has no such limit.
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


