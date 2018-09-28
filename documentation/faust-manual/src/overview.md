# Overview of the Faust Universe

While in its most *primitive* form, Faust is distributed as a command-line 
compiler, a wide range of tools have been developed around it in the course of 
the past few years. Their variety and their function might be hard to grab at 
first. This sort chapter provides an overview of their role and will hopefully 
help you decide which one is better suited for your personal use. 

<!-- TODO: it'd be nice to have some kind of figure here summarizing everything -->

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
