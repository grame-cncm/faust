# FAUST - Programming Language for Audio Applications and Plugins

## Grame, Centre National de Creation Musicale: <http://www.grame.fr>

[![Build Status](https://travis-ci.org/grame-cncm/faust.svg?branch=master-dev)](https://travis-ci.org/grame-cncm/faust)

## Introduction

FAUST (Functional Audio Stream) is a functional programming language specifically designed for real-time signal processing and synthesis. A distinctive characteristic of FAUST is to be fully compiled. 

The FAUST compiler translates DSP specifications into very efficient code for various languages (C++, C, JAVA, JavaScript, etc) that works at sample level. It targets high-performance signal processing applications, libraries and audio plug-ins for a variety of audio platforms and standards. A same FAUST specification can be used to easily generate various kinds of native standalone applications, iOS and Android apps, as well as CSOUND, LADSPA, MAX/MSP, PD, Q, SuperCollider, VST, AU plugins, etc. (see the section on [Faust Architectures](#faust-architectures) for an exhaustive list).

While there are Faust contributors everywhere across the globe, Faust is mainly being developed at Grame, Centre National de Creation Musicale (<http://www.grame.fr>), its birthplace.

## Versions and Branches

The FAUST distribution can be downloaded on the FAUST Github repository: <https://github.com/grame-cncm/faust>. Official releases packages are also available here: <https://sourceforge.net/projects/faudiostream/files/?source=navbar>.

There are currently 2 different versions of the Faust compiler: "FAUST0" and "FAUST2". They are available in two separate branches: `master` (FAUST0) and `faust2` (FAUST2). The main difference between these 2 versions lies in the FAUST compiler. `master` and `faust2` are merged multiple times a week, so features that are not related to the FAUST compiler should be synchronized. 

In the following subsections, details about the differences between these 2 versions of FAUST are provided as well as information on other branches of the repository.

### `master` (FAUST0)

`master` is the main Faust branch hosting FAUST0. FAUST0 is the "original" version of the Faust compiler. Unlike FAUST2, it can only generate C++ code and it doesn't have any dependencies, making it extremely easy to compile and install. FAUST0 will suit the needs of most users and is the recommended version of FAUST.

### `master-dev` (FAUST0 - Preferred Development Branch)

`master-dev` is the development sub-branch of `master`, thus it is also based on FAUST0. It is used by FAUST developers to commit their changes and can be considered as "the main development branch." The goal is to make sure that `master` is always functional. Merges between `master-dev` and `master` are carried out multiple times a week by the GRAME team. 

### `faust2` (FAUST2)

`faust2` is the home of FAUST2. As mentioned previously, most of the differences between FAUST0 and FAUST2 lie in the FAUST compiler. Unlike FAUST0, FAUST2 can generate code in different languages: C, C++, JAVA, JavaScript, LLVM bit code, etc. It also implements experimental features such as multi-rate capabilities, etc. Thanks to its ability to generate LLVM bit code and to `lib-llvm`, FAUST2 is "embeddable" in any C++ program through a library called `libfaust`. Compiling FAUST2 is slightly more complex than FAUST0 since it relies on LLVM and OpenSSL. Finally, FAUST2 is needed by some sister projects of FAUST such as FaustLive, FaucK, Faust-GEM, etc.

More experimental branches are also available but are not documented here.

## Organization of the Distribution

It's organization is the following :

	architecture/          : the architecture files and libraries currently supported
	benchmark/             : tools to measure the impact of various compiler options
	compiler/              : sources of the Faust compiler
	documentation/         : Faust developer's documentation
	debian/                : files for Debian installation
	examples/              : examples of Faust programs with makefiles for various audio targets
	installer/             : various instalers for Linux distribution
	libraries/             : DSP libraries
	syntax-highlighting/   : support for syntax highlighting for several editors
	test/                  : various tests
	tools/                 : additional easy-to-use scripts to produce binaries and plugins
	windows/               : Windows projects


## Compilation and installation

### To compile and install the Faust compiler on Linux and MacOSX : 

	make
	su
	make install

or

	sudo make install

It could be also useful to install additional tools, for example :

	cd tools/faust2appls/
	sudo make install

	
### On Windows :

The first option is to use the Visual Studio 2008 solution
`/faust/compiler/windows/faust_vs2008.sln`. Open the solution with
the Visual Studio 2008 environment and run Build. Both
Debug/Release targets are supported.

The second solution is to download and install the QT4.6 SDK : 
	[QT4.6 SDK](http://qt.nokia.com/downloads/sdk-windows-cpp)
and use the project file 'compiler.pro' in the compiler folder.

### Build & Use FAUST with Docker :

	docker build -t faust
	docker run faust [args...]

For example to display the help:

	docker run faust -h

To use an additional tool, for example faust2pdf:

	docker run --entrypoint faust2pdf faust [args...]

### Compilation of the examples

Several FAUST examples are provided in the example folder. To
compile and test the examples with Jack/GTK do :

	cd examples
	make jackgtk

This will create a subfolder jackgtkdir with all the jack
applications. You can also create alsa applications (make alsagtk)
as well as other formats.

In order to compile your own applications, you can simply place you
files in the example folder and use the existing makefiles.

To list for possible audio targets :

	make help


About 20 different audio platforms are supported : 

- Action Script
- Alsa
- ChucK
- CoreAudio
- CSOUND
- iPhone
- Jack
- LADSPA
- Matlab
- MaxMSP
- Octave
- OSS
- PortAudio
- Pure
- PureData
- Q
- Sndfile
- Snd-RT
- SuperCollider
- SynthFile
- VST
- VSTi (mono)

For all these audio platforms you may have to install the related
SDK and/or development libraries.

## Faust Architectures (Targets)

TODO

## Acknowledgments

Many persons have been contributing to the FAUST project by
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
