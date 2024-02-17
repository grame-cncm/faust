

# Julia architecture files 

[Julia](https://julialang.org) is a high-level, high-performance, dynamic programming language. While it is a general-purpose language and can be used to write any application, many of its features are well suited for numerical analysis and computational science.

A [Julia backend](https://github.com/grame-cncm/faust/tree/master-dev/compiler/generator/julia) allows to generate Julia code from the DSP program as a data structure (subtype of a `dsp` type) and a set of methods using this type. Several architecture files have been developed to use the resulting Julia code:

- `gui/meta.jl`: contains the base Meta type definition and associated method
- `gui/UI.jl`: contains the base UI type definition and associated methods
- `gui/MapUI.jl`: establishes a mapping beween UI items and their paths, and offers a `setParamValue/getParamValue `API to set and get their values. It uses an helper PathBuilder type to create complete pathnames to the leaves in the UI hierarchy. Note that the item path encodes the UI hierarchy in the form of a /group1/group2/.../label string and is the way to distinguish control that may have the same label, but different localisation in the UI tree. The `setParamValue/getParamValue` API takes either labels or paths as the way to describe the control, but using path is the safer way to use it
- `gui/GTKUI.jl`: contains a basic GUI generator developed using the [GtkObservables.jl](https://github.com/JuliaGizmos/GtkObservables.jl) package
- `gui/OSCUI.jl`: allows to control the DSP parameters using the Open Sound Control (OSC) protocol with the [OSC.jl](https://github.com/fundamental/OpenSoundControl.jl) package
- `dsp/dsp.jl`: contains the base DSP type definition and associated methods
- `audio/audio.jl`: defines the base type and methods for audio drivers
- `audio/portaudio.jl`: allows to use the [PortAudio library](http://portaudio.com) for real-time audio rendering
- `minimal.jl`: shows how the generated Julia code can be used in a minimal program which allocates and instantiate the DSP, and call the `compute` function. The `MapUI.jl` file is used to possibly control the DSP.  Use  `faust -lang julia -a julia/minimal.jl foo.dsp -o foo.jl ` to create a ready to test  `foo.jl` file
- `minimal-control.jl`: test the `compute!`method with all controllers min/max range
- `portaudio-gtk.jl`: an architecture file used by the **faust2portaudiojulia** tool that combines the PortAudio driver and GTK and OSC controllers

With a fresh Julia install, all required packages can be installed with the `julia packages.jl` command done in the architecture/julia folder.

## faust2portaudiojulia

The **faust2portaudiojulia** tool transforms a Faust DSP program into a fully working Julia source file which uses the [PortAudio library](http://portaudio.com) for real-time audio rendering, and can be controlled with OSC messages. By default it starts with the GTK based Graphical User Interface. It uses the `MapUI.jl`, `OSCUI.jl` and `GTKUI.jl` architecture files. 

`faust2portaudiojulia [-osc] [-oscc] [-play <num>] [additional Faust options (-vec -vs 8...)] file.dsp` 

Here are the available options:

- `-osc : to activate OSC control on 5000 and 5001 ports`
- `-oscc : to activate OSC control on 5000 and 5001 ports and automatically start the faust-osc-controller application`
- `-play <num> : to start the 'Julia' runtime with <num> threads and the generated file.jl`

By default, it will create a `file.jl` to be executed with the `julia file.jl` command, or in an interactive session. Using the `-play <num>` option allows to directly start the Julia executable.

- `-help or -h : shows the different options` 

As usual with faust2xx tools, other Faust compiler specific options can be given to **faust2portaudiojulia**, like `-vec -lv 1` to compile in vector mode.etc.

