<h1 align="center">faust2clap</h1>



<p align="center"><em>by Facundo Franchino, under the mentorship of Stéphane Letz and Jatin Chowdhury</em></p>

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

## Prerequisites

Before using faust2clap, make sure you have:

- **Faust** (version 2.54.0 or later) - See [official installation guide](https://faust.grame.fr/downloads/)
- **Python 3.7+** for the build script
- **Tkinter** (required for the hot-reload GUI)
  - macOS: `brew install python-tk`
  - Linux: `sudo apt-get install python3-tk`
- **uv** (recommended for dependency management)
- **C++ compiler** with C++17 support (Clang/GCC/MSVC)
- **CMake 3.16+** for building plugins
- **libfaust** with interpreter support (required for dynamic mode only)

### Installation

Since faust2clap is now integrated into Faust, simply install Faust from source:

```bash
git clone https://github.com/grame-cncm/faust.git
cd faust
make
sudo make install
```

After installation, faust2clap will be available in:
- Build script: `tools/faust2clap/faust2clap.py`
- Architecture files: `architecture/clap/`

## 💻 Usage

### 🛠️ Static build 
Generate and build a static CLAP plugin from your DSP file

```python
python tools/faust2clap/faust2clap.py your_file.dsp
```
```shell
optional flags:
  -mono          generate monophonic plugin
  -poly          generate polyphonic plugin (default)
  -nvoices N     set number of polyphonic voices (default: 16)
  -o, --output   specify output build directory (default: ./build/<plugin_name>)
```

The plugin will be automatically built and installed to:
```shell
~/Library/Audio/Plug-Ins/CLAP/your_file.clap
```

###  Dynamic (Interpreter) mode
Build the dynamic hot-reload plugin:

```bash
git submodule update --init external/efsw
cd architecture/clap
make -f Makefile.simple
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
- Design choice of a 12 fixed-parameter system places a limitation on dsp designs requiring more parameters (e.g a complex synthesiser), one could say this is a tool targeted towards effects processing, mainly.
- No "friendly" UI, yet. I will be working on a JUCE implementation for the GUI and a on-display preset management system which will end the need for an external python script that runs the .dsp selector.
- Although notably fast, utilising LLVM instead of the Interpreter could make it 3 to 10 times faster.

---

## Testing

The faust2clap tool has been tested with various DSP examples from the Faust distribution:

### Manual Testing
To verify functionality:
1. Build a static plugin: `python tools/faust2clap/faust2clap.py examples/reverb/dattorro.dsp`
2. Build the dynamic plugin: `cd architecture/clap && make -f Makefile.simple`
3. Load generated plugins in a CLAP-compatible DAW (Reaper, Bitwig, etc.)
4. Test audio processing, parameter changes, and state save/restore

### Test Coverage
- ✅ Effects processing (reverbs, filters, delays)
- ✅ Synthesisers with MIDI input
- ✅ Polyphonic voice management
- ✅ Parameter automation
- ✅ State persistence
- ✅ Hot-reload functionality

### Known Test Issues
See "Known Issues" section above for DSPs that currently have issues.

## Next Steps
- [ ] Simplify UI management (remove redundant classes)  
- [ ] Fix static build I/O conversion (investigate `dsp_sample_adapter`)  
- [ ] Add automated test suite for CI/CD  

---

## References
- [Faust Documentation](https://faustdoc.grame.fr/manual/architectures/)  
- [CLAP Plugin Standard](https://github.com/free-audio/clap)  
- Faust 2018 Paper – *An overview of the faust developer ecosystem*  

---

## Contributing

We welcome contributions to faust2clap! Here's how you can help:

### Reporting Issues
- **Bug reports**: Open an issue on [GitHub Issues](https://github.com/grame-cncm/faust/issues) with the `faust2clap` tag
- **Feature requests**: Discuss new features by opening an issue first
- **Questions**: For general questions, use GitHub Discussions or the Faust Discord server

### Making Contributions
- Fork the repository and create a feature branch from `master-dev`
- Make your changes and make sure tests pass
- Submit a pull request with a clear description of your changes
- Follow the existing code style and conventions

### Getting Support
- **Documentation**: Check the README and Faust documentation
- **Community**: Join the [Faust Discord](https://discord.gg/N29N8CVN) or [CLAP Discord](https://discord.gg/5EHpsbNR)
- **Email me**: [Reach me here](facundo@gauchodsp.com)

## Authors
- **Facundo Franchino**, under the mentorship of **Stéphane Letz** and **Jatin Chowdhury**
- Based on Faust (GRAME) and CLAP 


## Acknowledgements
- **Stéphane Letz** for choosing me to take on this project, and giving me the opportunity to contribute to the Faust ecosystem, as well as the constant support and feedback throughout the whole process.
- **Jatin Chowdhury** for the extensive CLAP knowledge and mentorship.
- **CLAP Discord community**, for all the discussions, feedback, and support (too many names to list!).


