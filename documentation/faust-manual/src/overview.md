# Overview of the Faust Universe

While in its most *primitive* form, Faust is distributed as a command-line 
compiler, a wide range of tools have been developed around it in the course of 
the past few years. Their variety and their function might be hard to grab at 
first. This sort chapter provides an overview of their role and will hopefully 
help you decide which one is better suited for your personal use. 

<!-- TODO: it'd be nice to have some kind of figure here summarizing everything
the various Faust branches should appear in this figure: we want something
as complete as possible. -->

TODO: here say a few words about the philosophy behind the disto: the online
editor is the way to go for most users, then various pre-compiled packages
of the compiler can be found, then source, then git. Finally other external
tools for development.   

## The Faust Distribution

The Faust distribution hosts the source of the Faust compiler (both in its 
command line and library version), the source of the Faust *architectures*
(targets), the various Faust compilation scripts, a wide range of 
Faust-related-tools, the [Faust DSP Libraries](TODO) (which in practice
are hosted a separate Git submodule), etc.

The latest stable release of the Faust distribution can be found here:
<https://github.com/grame-cncm/faust/releases>. It is recommended for most
Faust users willing to compile the Faust compiler and `libfaust` from scratch.

To have the latest stable development version, you can use the `master`
branch of the Faust git repository which is hosted on GitHub: 
<https://github.com/grame-cncm/faust/tree/master>.

For something even more bleeding edge (to be used at your own risks), you might
use the `master-dev` branch of the Faust git repository: 
<https://github.com/grame-cncm/faust/tree/master-dev>. `master-dev` is the 
development sub-branch of `master`. It is used by Faust developers to commit 
their changes and can be considered as "the main development branch." The goal 
is to make sure that `master` is always functional. Merges between `master-dev` 
and `master` are carried out multiple times a week by the GRAME team.

> Also, note that pre-compiled packages of the Faust compiler and of `libfaust`
for various platforms can be found on the [Download Page](__FAUST_DOMAIN__/download)
of the Faust website.

The Faust distribution is organized as follows:

```
architecture/          : the source of the architecture files
benchmark/             : tools to measure the efficiency of the generated code
build/                 : the various makefiles and build folders
compiler/              : sources of the Faust compiler
COPYING                : license information
debian/                : files for Debian installation
Dockerfile             : docker file
documentation/         : Faust's documentations
examples/              : Faust programs examples organized by categories
installer/             : various installers for Linux distribution
libraries/             : Faust DSP libraries
Makefile               : makefile used to build and install Faust
README.md              : instructions on how to build and install Faust
syntax-highlighting/   : support for syntax highlighting for several editors
tests/                 : various tests
tools/                 : tools to produce audio applications and plugins
windows/               : Windows related ressources
```

The following subsections present some of the main components of the Faust 
distribution.

### Command-Line Compiler

* Link to precompiled version versions (download page)
* What is the Faust compiler? (Quickly)
* Link to [Using the Faust Compiler](#using-the-faust-compiler)

### `libfaust`

* Link to precompiled version versions (download page)
* What is it? (Quickly)
* Link to tutorial 
[Embedding the Faust Compiler Using `libfaust`](__FAUST_DOMAIN__/learn/embedding-faust)

### `faust2...` Scripts

## Web Tools

### The Online Editor

### The FaustPlayground

### The Faust Online Compiler

### Web Services

## Development Tools

### FaustLive

### FaustWorks

## A Quick Tour of the Faust Targets

TODO: say something about the fact that faust2 scripts only works on the Mac
and Linux and that web services can help Windows users.

### `faust2alqt`

`faust2alqt` converts a Faust program into a standalone application with an 
[ALSA](https://www.alsa-project.org) audio engine and a [Qt](https://www.qt.io)
interface.

**Platforms**

* Linux only (because of ALSA)

**Dependencies**

* ASLA development libraries
* Qt development libraries 

**Usage**

```
faust2alqt [OPTIONS] faustFile.dsp
```

Run:

```
faust2alqt -h
```

for additional help and options.

### `faust2alsa`

`faust2alsa` converts a Faust program into a standalone application with an 
[ALSA](https://www.alsa-project.org) audio engine and a 
[GTK](https://www.gtk.org/) interface.

**Platforms**

* Linux only (because of ALSA)

**Dependencies**

* ASLA development libraries
* GTK development libraries 

**Usage**

```
faust2alsa [OPTIONS] faustFile.dsp
```

Run:

```
faust2alsa -h
```

for additional help and options.

### `faust2alsaconsole`

`faust2alsaconsole` converts a Faust program into a command line application with 
an [ALSA](https://www.alsa-project.org) audio engine.

**Platforms**

* Linux only (because of ALSA)

**Dependencies**

* ASLA development libraries

**Usage**

```
faust2alsaconsole [OPTIONS] faustFile.dsp
```

Run:

```
faust2alsaconsole -h
```

for additional help and options.

### `faust2android`

`faust2android` converts a Faust program into a ready-to-use Android application.
Additional information about this Faust target can be found on 
[the corresponding website](https://ccrma.stanford.edu/~rmichon/faust2android/). 

**Platforms**

* Android only

**Dependencies**

* Android SDK and development tools (i.e., Android studio, etc.)
* Android NDK

**Usage**

```
faust2android [OPTIONS] faustFile.dsp
```

Run:

```
faust2android -h
```

for additional help and options.

### `faust2androidunity`

`faust2android` converts a Faust program into an android library (`armeabi-v7a` 
and `x86`) for the [Faust unity plugin](TODO).

<!-- TODO: there might a webpage about this project -->

**Platforms**

* Android only (within [Unity](https://unity3d.com/))

**Dependencies**

* Android SDK and development tools (i.e., Android studio, etc.)
* Android NDK

**Usage**

```
faust2androidunity [OPTIONS] faustFile.dsp
```

Run:

```
faust2androidunity -h
```

for additional help and options.

### `faust2api`

`faust2api` converts a Faust program into a C++ library that can be used with a
simple API. It supports most of Faust's target platforms (i.e., Android, iOS,
ALSA, CoreAudio, JUCE, Jack, etc.).

Additional information about `faust2api` can be found on 
[the corresponding website](https://ccrma.stanford.edu/~rmichon/faust2api/).

**Platforms**

* Android
* iOS
* Windows
* Linux
* MacOS

**Dependencies**

Dependencies varies in functions of the target platform.

**Usage**

```
faust2api [TARGET] [OPTIONS] faustFile.dsp
```

Run:

```
faust2api -h
```

for additional help and options.

### `faust2asmjs`

`faust2asmjs` converts a Faust program into an [AMS JavaScript](TODO) object to
be used in a web-app.

**Platforms**

* Web

**Usage**

```
faust2asmjs [OPTIONS] faustFile.dsp
```

Run:

```
faust2asmjs -h
```

for additional help and options.

<!-- NOTE: skipping faust2atomsnippets here -->

### `faust2au`

`faust2au` converts a Faust program into an [Audio Unit](TODO) plug-in.

> Note that Audio Unit plug-ins can also be generated in Faust using 
[`faust2juce`](#faust2juce). In fact, this option might lead to better results
in many cases.

**Platforms**

* MacOS

**Usage**

```
faust2au [OPTIONS] faustFile.dsp
```

Run:

```
faust2au -h
```

for additional help and options.

### `faust2bela`

`faust2bela` converts a Faust program into a [BELA](TODO) plug-in.

**Platforms**

* BELA

**Usage**

```
faust2bela [OPTIONS] faustFile.dsp
```

Run:

```
faust2bela -h
```

for additional help and options.

### `faust2caqt`

`faust2caqt` converts a Faust program into a standalone application with an 
[CoreAudio](TODO) audio engine and a [Qt](https://www.qt.io) interface.

**Platforms**

* MacOS only (because of CoreAudio)

**Usage**

```
faust2caqt [OPTIONS] faustFile.dsp
```

Run:

```
faust2caqt -h
```

for additional help and options.

### `faust2caqtios`

`faust2caqtios` converts a Faust program into an iOS app with a 
[Qt](https://www.qt.io) interface.

**Platforms**

* iOS

**Usage**

```
faust2caqtios [OPTIONS] faustFile.dsp
```

Run:

```
faust2caqtios -h
```

for additional help and options.

### `faust2ck`

`faust2ck` converts a Faust program into a Chugin ([ChucK](TODO) plug-in). This
tools was developed by Spencer Salazar.

<!-- TODO: may be add a link to the project. -->

**Platforms**

* MacOS
* Linux
* Windows

**Usage**

```
faust2ck [OPTIONS] faustFile.dsp
```

### `faust2csound`

`faust2csound` converts a Faust program into a [CSOUND](TODO) opcode. 

**Platforms**

* MacOS
* Linux
* Windows

**Usage**

```
faust2csound [OPTIONS] faustFile.dsp
```

### `faust2dssi`

TODO 

### `faust2dummy`

TODO

### `faust2dummymem`

TODO

### `faust2eps`

`faust2eps` converts a Faust program into a diagram in EPS format. 

**Usage**

```
faust2eps faustFile.dsp
```

### `faust2faustvst`

`faust2faustvst` converts a Faust program into a [VST plug-in](TODO). This
tool was developed by Albert Gräf.

> Note that VST plug-ins can also be generated in Faust using 
[`faust2vst`](#faust2vst) and [`faust2juce`](#faust2juce). The former was
developed prior to `faust2faustvst` by another author and provides less 
features. Hence `faust2faustvst` should be preferred to it. `faust2juce` is
also a good option.   

**Platforms**

* MacOS
* Windows
* Linux

**Dependencies**

* VST SDK

**Usage**

```
faust2faustvst [OPTIONS] faustFile.dsp
```

Run:

```
faust2faustvst -h
```

for additional help and options.

### `faust2firefox`

`faust2faustvst` converts a Faust program into a block diagram and opens it
in the default web browser of the system. It can be seen as a subset of
[`faust2svg`](#faust2svg)

**Platforms**

* MacOS
* Linux

**Usage**

```
faust2firefox faustFile.dsp
```

### `faust2gen`

`faust2gen` compiles a Faust program to a `faustgen~` patch for 
[MaxMSP](https://cycling74.com/products/max/).

**Platforms**

* MacOS
* Windows

**Dependencies**

* MaxMSP SDK

**Usage**

```
faust2gen [OPTIONS] faustFile.dsp
```

Run:

```
faust2gen -h
```

for additional help and options.

### `faust2graph`

`faust2graph` simply calls `faust` with the 
[`-tg` option](#compilation-options) which generates the corresponding graph of
internal computational loops.

**Platforms**

* MacOS
* Linux

**Usage**

```
faust2graph [OPTIONS] faustFile.dsp
```

### `faust2graphviewer`

`faust2graphviewer` simply calls [`faust2graph`](#faust2graph) and then opens
the generated file in the default viewer.

**Platforms**

* MacOS
* Linux

**Usage**

```
faust2graphviewer [OPTIONS] faustFile.dsp
```

### `faust2ios`

`faust2ios` turns a Faust program into a ready-to-use iOS application. While
the app might be compiled directly from the command line calling this script,
it will be necessary in most cases to generate an Xcode project to fix the 
bundle identifier of the app, etc.

**Platforms**

* iOS

**Dependencies**

* iOS SDK / development tools

**Usage**

```
faust2ios [OPTIONS] faustFile.dsp
```

Run:

```
faust2ios -h
```

for additional help and options.

### `faust2jack`

`faust2jack` turns a Faust program into a standalone application with a 
[Jack audio engine](http://jackaudio.org/) and a [GTK](https://www.gtk.org/) 
interface.

**Platforms**

* Linux
* MacOS

**Dependencies**

* Jack development libraries
* GTK development libraries

**Usage**

```
faust2jack [OPTIONS] faustFile.dsp
```

Run:

```
faust2jack -h
```

for additional help and options.

### `faust2jackconsole`

`faust2jackconsole` turns a Faust program into a command-line application with a 
[Jack audio engine](http://jackaudio.org/).

**Platforms**

* Linux
* MacOS

**Dependencies**

* Jack development libraries

**Usage**

```
faust2jackconsole [OPTIONS] faustFile.dsp
```

Run:

```
faust2jackconsole -h
```

for additional help and options.

### `faust2jackinternal`

TODO

### `faust2jackrust`

TODO 

### `faust2jackserver`

`faust2jackserver` turns a Faust program into a standalone application with a 
[Jack audio engine](http://jackaudio.org/) and a [Qt](https://www.qt.io/)
interface in server mode (similar to [`faust2jaqt`](#faust2jaqt)).

**Platforms**

* Linux
* MacOS
* Windows

**Dependencies**

* Jack development libraries
* Qt development libraries

**Usage**

```
faust2jackserver [OPTIONS] faustFile.dsp
```

### `faust2jaqt`

`faust2jaqt` turns a Faust program into a standalone application with a 
[Jack audio engine](http://jackaudio.org/) and a [Qt](https://www.qt.io/).

**Platforms**

* Linux
* MacOS
* Windows

**Dependencies**

* Jack development libraries
* Qt development libraries

**Usage**

```
faust2jaqt [OPTIONS] faustFile.dsp
```

Run:

```
faust2jaqt -h
```

for additional help and options.

### `faust2jaqtchain`

`faust2jaqtchain` is the same as [`faust2jaqt`](#faust2jaqt) but it will work
with multiple files (that will be compiled as multiple independent applications).

**Platforms**

* Linux
* MacOS
* Windows

**Dependencies**

* Jack development libraries
* Qt development libraries

**Usage**

```
faust2jaqtchain [OPTIONS] faustFile0.dsp faustFile1.dsp etc.
```

Run:

```
faust2jaqtchain -h
```

for additional help and options.

### `faust2javaswing`

`faust2javaswing` will compile a Faust program as a JAVA standalone application
with a Swing interface. 

**Platforms**

* Linux
* MacOS
* Windows

**Dependencies**

* JAVA

**Usage**

```
faust2javaswing [OPTIONS] faustFile.dsp
```

### `faust2juce`

<!-- TODO -->

### `faust2ladspa`

<!-- TODO -->

### `faust2linuxunity`

<!-- TODO -->

### `faust2lv2`

<!-- TODO -->

### `faust2mathdoc`

<!-- TODO -->

### `faust2mathviewer`

<!-- TODO -->

### `faust2jmax6`

<!-- TODO -->

### `faust2md`

<!-- TODO -->

### `faust2msp`

<!-- TODO -->

### `faust2netjackconsole`

<!-- TODO -->

### `faust2netjackqt`

<!-- TODO -->

### `faust2nodejs`

<!-- TODO -->

### `faust2octave`

<!-- TODO -->

### `faust2osxiosunity`

<!-- TODO -->

### `faust2owl`

<!-- TODO -->

### `faust2paqt`

<!-- TODO -->

### `faust2pdf`

<!-- TODO -->

### `faust2plot`

<!-- TODO -->

### `faust2png`

<!-- TODO -->

### `faust2portaudiorust`

<!-- TODO -->

### `faust2pure`

<!-- TODO -->

### `faust2puredata`

<!-- TODO -->

### `faust2raqt`

<!-- TODO -->

### `faust2ros`

<!-- TODO -->

### `faust2rosgtk`

<!-- TODO -->

### `faust2rpialsaconsole`

<!-- TODO -->

### `faust2rpinetjackconsole`

<!-- TODO -->

### `faust2sam`

<!-- TODO -->

### `faust2sig`

<!-- TODO -->

### `faust2sigviewer`

<!-- TODO -->

### `faust2smartkeyb`

<!-- TODO -->

### `faust2sndfile`

<!-- TODO -->

### `faust2supercollider`

<!-- TODO -->

### `faust2svg`

<!-- TODO -->

### `faust2unity`

<!-- TODO -->

### `faust2unitywin`

<!-- TODO -->

### `faust2vst`

<!-- TODO -->

### `faust2vsti`

<!-- TODO -->

### `faust2w32max6`

<!-- TODO -->

### `faust2w32msp`

<!-- TODO -->

### `faust2w32puredata`

<!-- TODO -->

### `faust2w32vst`

<!-- TODO -->

### `faust2w64max6`

<!-- TODO -->

### `faust2wasm`

<!-- TODO -->

### `faust2webaudio`

<!-- TODO -->

### `faust2webaudioasm`

<!-- TODO -->

### `faust2webaudiowasm`

<!-- TODO -->

### `faust2webaudiowast`

<!-- TODO -->

### `faust2winunity`

<!-- TODO -->
