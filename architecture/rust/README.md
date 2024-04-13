

# Rust architecture files 

[Rust](https://www.rust-lang.org) is a blazingly fast and memory-efficient language with no runtime or garbage collector, it can power performance-critical services, run on embedded devices, and easily integrate with other languages.

A [Rust backend](https://github.com/grame-cncm/faust/tree/master-dev/compiler/generator/rust) allows to generate Rust code from the DSP program as a data structure (subtype of a `dsp` type) and a set of methods using this type. Several architecture files have been developed to use the resulting Rust code. [Additional projects](https://faustdoc.grame.fr/manual/architectures/#rust-tools) can be used to ease integration in the Rust ecosystem. 

## faust2portaudiorust

The **faust2portaudiorust** tool transforms a Faust DSP program into a ready-to-use Rust project which uses the [PortAudio library](http://portaudio.com) for real-time audio rendering. 

`faust2portaudiorust [-source] [Faust options] <file.dsp>` 

Here are the available options:

- `-source : only generates the source project`
- `-help or -h : shows the different options` 

By default, it will create a `file-portaudiorust` folder with the Rust project and compile it using *cargo*. 

As usual with faust2xx tools, other Faust compiler specific options can be given to **faust2portaudiorust**, like `-vec -lv 1` to compile in vector mode.etc.

## faust2jackrust

The **faust2jackrust** tool transforms a Faust DSP program into a ready-to-use Rust project which uses [JACK](https://jackaudio.org) for real-time audio rendering.

`faust2jackrust [-source] [Faust options] <file.dsp>` 

Here are the available options:

- `-source : only generates the source project.`
- `-help or -h : shows the different options` 

By default, it will create a `file-jackrust` folder with the Rust project and compile it using *cargo*. 

As usual with faust2xx tools, other Faust compiler specific options can be given to **faust2jackrust**, like `-vec -lv 1` to compile in vector mode.etc.

## Memory allocation issues

A DSP can be large in memory and allocating it on the heap by using [Box](https://doc.rust-lang.org/std/boxed/struct.Box.html) is often necessary to avoid stack overflows. Unfortunately, Rust does not have a native way to directly allocate on the heap, and `let dsp = Box::new(Dsp::new())` will only solve the problem in release build where the intermediary stack allocation will be optimized away.

Faust fixes this problem with the help of the crate [default-boxed](https://docs.rs/default-boxed/latest/default_boxed/) that generates a method that allocates a struct on the heap. When using the generated architecture files, the project is already configured to use this crate and directly allocate on the heap. If you are not using the generated architecture files, ensure that the `Cargo.toml` file building the generated code contains the dependency to `default-boxed` and the feature `default-boxed`:

```toml
[dependencies]
default-boxed = { version = "0.2.0", optional = true }

[features]
default = ["default-boxed"]
default-boxed = ["dep:default-boxed"]
```

Then, allocate the DSP with `let dsp = Dsp::default_boxed()` instead of `let dsp = Box::new(Dsp::new())`.

This feature can be opted out by building without the `default-boxed` feature, for example with `--no-default-features`. This removes both the `default-boxed` dependency and the `::default_boxed()` method.
