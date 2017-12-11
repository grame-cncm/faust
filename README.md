# Faust - Programming Language for Audio Applications and Plugins

## Grame, Centre National de Creation Musicale: <http://www.grame.fr>

master : [![Build Status](https://travis-ci.org/grame-cncm/faust.svg?branch=master)](https://travis-ci.org/grame-cncm/faust) 
master-dev : [![Build Status](https://travis-ci.org/grame-cncm/faust.svg?branch=master-dev)](https://travis-ci.org/grame-cncm/faust) 

## Introduction

Faust (Functional Audio Stream) is a functional programming language specifically designed for real-time signal processing and synthesis. A distinctive characteristic of Faust is to be fully compiled. 

The Faust compiler translates DSP specifications into very efficient code for various languages (C++, C, JAVA, JavaScript, ASM JavaScript, LLVM IR, WebAssembly etc.) working at sample level. It targets high-performance signal processing applications, libraries and audio plug-ins for a variety of audio platforms and standards. A same Faust specification can be used to easily generate various kinds of native standalone applications, iOS and Android apps, as well as CSOUND, LADSPA, MAX/MSP, PD, Q, SuperCollider, VST, AU plugins, etc. (see the README in the `/architecture` folder for an exhaustive list).

While there are Faust contributors everywhere across the globe, Faust is mainly being developed at Grame, Centre National de Creation Musicale (<http://www.grame.fr>), its birthplace.

## Versions and Branches

The Faust distribution can be downloaded on the Faust Github repository: <https://github.com/grame-cncm/faust>. Official releases packages are also available here: <https://sourceforge.net/projects/faudiostream/files/?source=navbar>.

In the following subsections, details about the differences between these 2 versions of Faust are provided as well as information on other branches of the repository.

### `master` 

`master` is the main Faust branch. It can compile in different languages: C, C++, JAVA, JavaScript, ASM JavaScript, LLVM IR, WebAssembly etc. It also implements experimental features such as multi-rate capabilities, etc. Thanks to its ability to generate LLVM IR and by using LLVM JIT, Faust is "embeddable" in any C++ program through a library called `libfaust`. Compiling Faust relies on LLVM and OpenSSL. Finally, Faust is needed by some sister projects of Faust such as FaustLive, FaucK, faustgen~, etc. This branch also cotiaons the old Faust1 C++ backend.

### `master-dev` (Preferred Development Branch)

`master-dev` is the development sub-branch of `master`. It is used by Faust developers to commit their changes and can be considered as "the main development branch." The goal is to make sure that `master` is always functional. Merges between `master-dev` and `master` are carried out multiple times a week by the GRAME team. 

More experimental branches are also available but are not documented here.

## Overview of the Faust Distribution

This is an overview of the content of the top-level folders of the Faust distribution. Most of these folders contain their own README describing their content in more details.

	architecture/          : the architecture files currently supported
	benchmark/             : tools to measure the impact of various compiler options
	compiler/              : sources of the Faust compiler
	debian/                : files for Debian installation
	documentation/         : Faust developer's documentation
	examples/              : Faust programs examples organized by categories
	installer/             : various instalers for Linux distribution
	libraries/             : DSP libraries
	syntax-highlighting/   : support for syntax highlighting for several editors
	test/                  : various tests
	tools/                 : additional easy-to-use scripts (faust2...) to produce binaries and plugins
	windows/               : Windows projects

## Compilation and Installation

The following elements are required to build Faust:

* `llvm/clang` (>= 3.8 / <= 5.0. Note that a 'universal' makefile target can be used to create 32/64 bits binaries. In this case LLVM has to be installed in universal mode [32/64 bits], so  for instance on OSX using MacPorts, using : `sudo port install llvm-3.xx +universal`)
* `openssl` (has to be installed in universal mode [32/64 bits] if *make universal* is to be used).

### Getting the source code

In order to compile Faust on your machine you can either download the latest release of the source code <https://github.com/grame-cncm/faust/releases> or clone the git repository. In order to clone the git repository you will have to do the following steps:

	git clone https://github.com/grame-cncm/faust.git 
	cd faust
	git submodule update --init
	
The last step `git submodule update --init` is a new one. This is due to the fact that the Faust libraries have been moved to an independent github repository <https://github.com/grame-cncm/faustlibraries.git>. This repository is a submodule of the Faust repository (as well as some other Faust related projects).

### Linux and MacOSX 

To build Faust on MacOSX or Linux, just run the following commands from the root of the distribution:

	make
	sudo make install

### Windows

#### Using Visual Studio

Open the Faust Visual Studio solution in `/faust/windows/faust_vs2012.sln` with Visual Studio 2012 or greater and run "Build". Both Debug/Release targets are supported.

#### Using Qt

The Faust compiler can be built with [Qt](https://www.qt.io/) using `/compiler/compiler.pro`.

### Build & Use Faust with Docker :

	docker build -t faust
	docker run faust [args...]

For example to display the help:

	docker run faust -h

To use an additional tool, for example faust2pdf:

	docker run --entrypoint faust2pdf faust [args...]

## Using the Faust Examples

The `/examples` folder contains dozen of example Faust codes organized by categories. There are many options to use them.

### FaustPlayground

[FaustPlayground](http://faust.grame.fr/faustplayground/) is an online tool to compile and use Faust code directly in a web browser. To use a Faust example from the `/examples` folder, just drag-and-drop it in the work space and it should work right away!

### FaustLive

[FaustLive](https://sourceforge.net/p/faudiostream/faustlive/ci/master/tree/) is a program that was designed to facilitate the prototyping of Faust codes. It embeds the LLVM on-the-fly compiler of Faust2 allowing you to very rapidly compile Faust codes on your computer. Binaries and installation packages of FaustLive are available for [Linux, Windows and OSX](https://sourceforge.net/projects/faudiostream/files/).

### Faust Online Compiler

The [Faust Online Compiler](http://faust.grame.fr/onlinecompiler/) allows to write and compile Faust codes for a wide range of targets and platforms. Unlike, the Faust playground presented above, it doesn't permit to run a Faust program in a web browser.

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
    faust2asmjs             : asmjs WebAudio code
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
    faust2webaudioasm       : WebAudio web HTML app
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
* The Faust website: <http://faust.grame.fr> contains useful resources around Faust.
* The [Faust online course](https://ccrma.stanford.edu/~rmichon/faustWorkshops/course2015/) or the [Faust Hero in 2 Hours tutorial](https://ccrma.stanford.edu/~rmichon/faustTutorials/#faust-hero-in-2-hours) might be good starting points for beginners.
* [Julius Smith's website](https://ccrma.stanford.edu/~jos) is an incredible resource on various topics around DSP and Faust.

## Acknowledgments

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
