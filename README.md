# Faust - Programming Language for Audio Applications and Plugins

## Grame, Centre National de Creation Musicale: <https://www.grame.fr>

<!-- 
master : [![Build Status](https://travis-ci.org/grame-cncm/faust.svg?branch=master)](https://travis-ci.org/grame-cncm/faust)
master-dev : [![Build Status](https://travis-ci.org/grame-cncm/faust.svg?branch=master-dev)](https://travis-ci.org/grame-cncm/faust)![C/C++ CI](https://github.com/grame-cncm/faust/workflows/C/C++%20CI/badge.svg)
 -->

Build status: [![Ubuntu](https://github.com/grame-cncm/faust/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/grame-cncm/faust/actions/workflows/ubuntu.yml) [![MacOS](https://github.com/grame-cncm/faust/actions/workflows/macos.yml/badge.svg)](https://github.com/grame-cncm/faust/actions/workflows/macos.yml) [![Windows](https://github.com/grame-cncm/faust/actions/workflows/windows.yml/badge.svg)](https://github.com/grame-cncm/faust/actions/workflows/windows.yml)

## Introduction

Faust (Functional Audio Stream) is a functional programming language specifically designed for real-time signal processing and synthesis. A distinctive characteristic of Faust is that it is fully compiled.

The Faust compiler translates DSP specifications into very efficient code for various languages (C++, C, JAVA, LLVM IR, WebAssembly etc.) working at sample level. It targets high-performance signal processing applications, libraries, and audio plug-ins for a variety of audio platforms and standards. A same Faust specification can be used to easily generate various kinds of native standalone applications, iOS and Android apps, as well as Csound, LADSPA, Max/MSP, PD, Q, SuperCollider, VST, AU plugins, etc. (see the README in the `/architecture` folder for an exhaustive list).

While there are Faust contributors everywhere across the globe, Faust is mainly being developed at Grame, Centre National de Creation Musicale (<https://www.grame.fr>), its birthplace.

## Versions and Branches

The Faust distribution can be downloaded on the Faust Github repository: <https://github.com/grame-cncm/faust>. Official release packages are also available here: <https://github.com/grame-cncm/faust/releases>.

In the following subsections, details about the branches of the repository are given.

### `master`

`master` is the main Faust branch. It can compile in different languages: C, C++, JAVA, LLVM IR, WebAssembly etc. Thanks to its ability to generate LLVM IR and by using LLVM JIT, Faust is "embeddable" in any C++ program through a library called `libfaust`. Faust is needed by some sister projects of Faust such as FaustLive, FaucK, faustgen~, etc.

### `master-dev` (Preferred Development Branch)

`master-dev` is the development sub-branch of `master`. It is used by Faust developers to commit their changes and can be considered as "the main development branch." The goal is to make sure that `master` is always functional. Merges between `master-dev` and `master` are carried out typically where doing a release.

More experimental branches are also available but are not documented here.

## Overview of the Faust Distribution

This is an overview of the content of the top-level folders of the Faust distribution. Most of these folders contain their own README describing their content in more details.

	architecture/          : the architecture files currently supported
	build/                 : build tools and scripts (cmake based)
	benchmark/             : tools to measure the impact of various compiler options
	compiler/              : sources of the Faust compiler
	debian/                : files for Debian installation
	documentation/         : Faust developer's documentation
	examples/              : Faust programs examples organized by categories
	installer/             : various installers for Linux distribution
	libraries/             : DSP libraries
	syntax-highlighting/   : support for syntax highlighting for several editors
	tests/                 : various tests
	tools/                 : additional easy-to-use scripts (faust2...) to produce binaries and plugins
	windows/               : Windows related resources

## Libraries

Faust libraries are now in a [separated project](https://github.com/grame-cncm/faustlibraries) and included as a git submodule. The [oboe](https://github.com/google/oboe) project is also included as submodule in two different places: `architecture/android/app/oboe` and `architecture/smartkeyboard/app/oboe`. The [faust2ck](https://github.com/ccrma/faust2ck) project is also included as submodule in `tools/faust2ck`. These submodules are synchronized from time to time in the main Faust repository using the following commands:

    git submodule update --remote --merge
    git add libraries tools/faust2ck architecture/android/app/oboe architecture/smartKeyboard/android/app/oboe
    git commit -m "Faust updated to the latest version of the libraries, faust2ck, and oboe"
    git push

Or to synchronize the *libraries* folder only:

    git submodule update --remote --merge libraries
    git add libraries 
    git commit -m "Faust updated to the latest version of libraries."
    git push
    
Or to synchronize the *faust2ck* folder only:

    git submodule update --remote --merge tools/faust2ck
    git add tools/faust2ck 
    git commit -m "Faust updated to the latest version of faust2ck."
    git push
    
Or to synchronize the *py2max* folder only:

    git submodule update --remote --merge architecture/max-msp/py2max
    git add architecture/max-msp/py2max 
    git commit -m "Faust updated to the latest version of py2max."
    git push

## Compilation and Installation

Since release 2.5.18, Faust compilation and installation is based on [CMake](https://cmake.org/). For details about compilation, you should look at the [Faust wiki pages](https://github.com/grame-cncm/faust/wiki) or go directly to the [simple tutorial](https://github.com/grame-cncm/faust/wiki/BuildingSimple) to compile and install.

## Using the Faust Examples

The `/examples` folder contains dozen of example Faust codes organized by categories. There are many options to use them.

### Online Faust Editor

The [Online Faust Editor](https://fausteditor.grame.fr) is a zero-conf tool that provides all the compilation services, including binaries generation for all the supported platforms and architectures.

### Online Faust IDE

The [Online Faust IDE](https://faustide.grame.fr)  is a zero-conf tool that provides all the compilation services, including binaries generation for all the supported platforms and architectures, but also various utilities for signal processing development.

### Faust Playground

[Faust Playground](https://faustplayground.grame.fr/) is an online tool to compile and use Faust code directly in a web browser. To use a Faust example from the `/examples` folder, just drag-and-drop it in the work space and it should work right away!

### FaustLive

[FaustLive](https://github.com/grame-cncm/faustlive) is a program that was designed to facilitate the prototyping of Faust codes. It embeds the LLVM on-the-fly compiler of Faust2 allowing you to very rapidly compile Faust codes on your computer. Binaries and installation packages of FaustLive are available for [Linux, Windows and OSX](https://github.com/grame-cncm/faustlive/releases).

### `faust2...` Scripts and Programs

The `faust2...` scripts and programs are command line tools allowing to compile Faust codes to any of the supported Faust targets ("architectures"). They are placed on your system during the Faust installation process. The fastest way to get an exhaustive list of all of them is to open a terminal window, type `faust2`, and then press the Tab key for auto-completion. For example, to compile a Faust code as a JACK application with a Qt interface, run:

	faust2jaqt yourCode.dsp

The most commonly used `faust2` scripts are:

    faust2alqt              : ALSA application with Qt UI
    faust2ladspa            : LADSPA plug-in
    faust2pdf               : pdf block diagram
    faust2supercollider     : SuperCollider external
    faust2alsa              : ALSA application with GTK UI
    faust2faustvst          : VST plug-in
    faust2lv2               : LV2 plug-in
    faust2plot              : command line program to debug DSP (sample plotting, etc.)
    faust2svg               : SVG block diagram
    faust2alsaconsole       : ALSA command line program
    faust2mathdoc           : automatic pdf mathematical documentation
    faust2png               : png block diagram
    faust2android           : Android app
    faust2graph             : svg graph
    faust2puredata          : PureData external
    faust2api               : API generator
    faust2msp               : MaxMSP 5 external and patch
    faust2max6              : MaxMSP 6 (and later) external and patch
    faust2ios               : iOS app
    faust2ros               : ROS app
    faust2au                : Audio Unit plugin
    faust2rosgtk            : ROS app with GTK UI
    faust2bela              : BELA program
    faust2jack              : JACK application with GTK UI
    faust2netjackconsole    : NetJack command line program
    faust2rpialsaconsole    : Raspberry Pi ALSA command line program
    faust2caqt              : CoreAudio application with Qt UI
    faust2jackconsole       : JACK command line program
    faust2netjackqt         : NetJack application with Qt UI
    faust2rpinetjackconsole : Raspberry Pi JACK command line program
    faust2caqtios           : iOS app with Qt UI
    faust2octave            : Octave script
    faust2csound            : CSOUND Opcode
    faust2owl               : OWL Program
    faust2sig               : SVG signal
    faust2jaqt              : JACK application with Qt UI

Obviously, the corresponding dependencies for each of them must be installed on your system for compilation to be successful. For example, if you use `faust2jaqt`, JACK and Qt libraries must be installed.

## Documentation and Resources

* `/documentation/faust-quick-reference.pdf` contains the most up-to-date documentation of Faust.
* `/documentation/library.pdf` contains the documentation of the Faust DSP libraries.
* The [Faust website](https://faust.grame.fr) contains useful resources around Faust.
* The [Faust online course](https://ccrma.stanford.edu/~rmichon/faustWorkshops/course2015/) or the [Faust Hero in 2 Hours tutorial](https://ccrma.stanford.edu/~rmichon/faustTutorials/#faust-hero-in-2-hours) might be good starting points for beginners.
* [Julius Smith's website](https://ccrma.stanford.edu/~jos) is an incredible resource on various topics around DSP and Faust.

## Acknowledgements

Many persons have been contributing to the Faust project by
providing code for the compiler, architecture files, libraries,
examples, documentation, scripts, bug reports, ideas, etc.

I would like to thank them and especially: Fons Adriaensen, Tiziano
Bole, Baktery Chanka, Thomas Charbonnel, Damien Cramet, Etienne
Gaudrin, Albert Graef, Stefan Kersten, Victor Lazzarini, Matthieu
Leberre, Mathieu Leroi, Kjetil Matheussen, Remy Muller, Sampo
Savolainen, Nicolas Scaringella, Stephen Sinclair, Travis Skare,
Julius Smith, as well as my colleagues at GRAME, in particular :
Dominique Fober, Stephane Letz and Karim Barkati, and from the
ASTREE project : Jerome Barthelemy (IRCAM), Alain Bonardi (IRCAM),
Raffaele Ciavarella (IRCAM), Pierre Jouvelot (Ecole des
Mines/ParisTech), Laurent Pottier (U. Saint-Etienne)

## Questions and suggestions

If you have questions suggestions and comments, or if you want to
contribute to the project, two mailing lists are available:
- [Development List](https://lists.sourceforge.net/lists/listinfo/faudiostream-devel)
- [Users List](https://lists.sourceforge.net/lists/listinfo/faudiostream-users)

[Yann Orlarey](https://github.com/orlarey)
