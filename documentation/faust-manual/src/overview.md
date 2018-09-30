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

### `faust2alqt`

`faust2alqt` converts a Faust code into a standalone application with an 
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

`faust2alsa` converts a Faust code into a standalone application with an 
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

`faust2alsaconsole` converts a Faust code into a command line application with 
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

`faust2android` converts a Faust code into a ready-to-use Android application.
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

`faust2android` converts a Faust code into an android library (`armeabi-v7a` 
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

`faust2api` converts a Faust code into a C++ library that can be used with a
simple API. It supports most of Faust's target platforms (i.e., Android, iOS,
ALSA, CoreAudio, JUCE, Jack, etc.).

Additional information about `faust2api` can be found on 
[the corresponding website](https://ccrma.stanford.edu/~rmichon/faust2api/).

**Platforms**

* Android
* iOS
* Windows
* Linux
* OSX

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


