

# Rust architecture files 

[Rust](https://www.rust-lang.org) is a blazingly fast and memory-efficient language with no runtime or garbage collector, it can power performance-critical services, run on embedded devices, and easily integrate with other languages.

A [Rust backend](https://github.com/grame-cncm/faust/tree/master-dev/compiler/generator/rust) allows to generate Rust code from the DSP program as a data structure (subtype of a `dsp` type) and a set of methods using this type. Several architecture files have been developed to use the resulting Rust code. [Additional projects](https://faustdoc.grame.fr/manual/architectures/#rust-tools) can be used to ease integration in the Rust ecosystem. 

## faust2portaudiorust

The **faust2portaudiorust** tool transforms a Faust DSP program into a ready-to-use Rust project which uses the [PortAudio library](http://portaudio.com) for real-time audio rendering. 

`faust2portaudiorust [-source] [Faust options] <file.dsp>` 

Here are the available options:

- `-source : only generates the source project`
- `-help or -h : shows the different options` 

By default, it will create a `file-portaudiorust` folder with the Rust project and compile it using cargo. 

As usual with faust2xx tools, other Faust compiler specific options can be given to **faust2portaudiorust**, like `-vec -lv 1` to compile in vector mode.etc.

## faust2jackrust

The **faust2jackrust** tool transforms a Faust DSP program into a ready-to-use Rust project which uses [JACK](https://jackaudio.org) for real-time audio rendering.

`faust2jackrust [-source] [Faust options] <file.dsp>` 

Here are the available options:

- `-source : only generates the source project.`
- `-help or -h : shows the different options` 

By default, it will create a `file-jackrust` folder with the Rust project and compile it using cargo. 

As usual with faust2xx tools, other Faust compiler specific options can be given to **faust2portaudiorust**, like `-vec -lv 1` to compile in vector mode.etc.
