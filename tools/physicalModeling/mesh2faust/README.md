# `mesh2faust`

`mesh2faust` is an open-source modal physical model generator for the Faust
programming language. `mesh2faust` takes a volumetric mesh of a 3D object as
its main argument, carries out a finite element analysis, and generates the
corresponding Faust modal physical model. A wide range of parameters can be
configured to fine-tune the analysis as well as the behavior of the generated
object.

`mesh2faust` is based on [Vega FEM](http://run.usc.edu/vega/) and should work
both on Linux and OSX.

`mesh2faust` is part of the
[Faust Physical Modeling Toolkit](https://ccrma.stanford.edu/~rmichon/pmFaust).
Tutorials on how to make
physical models of musical instruments can be found
[here](https://ccrma.stanford.edu/~rmichon/faustTutorials/#making-physical-models-of-musical-instruments-with-faust).

## Build/Installation

`mesh2faust` relies on [Vega FEM](http://run.usc.edu/vega/) to turn the
provided volumetric mesh into a 3D mesh and to carry out the finite element
analysis on it. A lightweight adapted version of this library is part of this
repository.

Vega itself relies on some libraries that must be installed on your system in
order to compile `mesh2faust`. This section walks you through the different
steps to build and install `mesh2faust` on your system.

### Linux

* First, install the Intel MKL Library (<https://software.intel.com/en-us/intel-mkl>).
Unfortunately, this library is not open source (but it's free), so you wont find
it in your usual package manager.
* Get `libarpack` with your package manager (`libarpack2-dev` in Ubuntu).
* Go in `/vega/Makefile-headers/` and run "`selectLinux`", this will update the
dynamic link of `Makefile-header` to the right Makefile for your system.
* You might have to make some adjustments in
`/vega/Makefile-headers/Makefile-header.linux` in the "MKL Paths" section
(Intel tends to change the organization of this lib pretty often).
* Run: `make`
* Run: `sudo make install`
* NOTE: Additional adjustments might have to be made to `Makefile-header.linux`
(compilation was only tested on Linux Mint)

### OSX

* First, install the Intel MKL Library (<https://software.intel.com/en-us/intel-mkl>).
Unfortunately, this library is not open source (but it's free), so you wont find
it in your usual package manager.
* Get `arpack`. The `mesh2faust` makefiles were configured to work with the MacPort
version of `arpack`, so we advise you to use this package manager to get it
(e.g., `port install arpack`).
* Go in `/vega/Makefile-headers/` and run "`selectMacOSX`", this will update the
dynamic link of `Makefile-header` to the right Makefile for your system.
* You might have to make some adjustments in
`/vega/Makefile-headers/Makefile-header.osx` in the "MKL Paths" and "ARPACK" sections
depending on how you installed these 2 packages.
* Run: `make`
* Run: `sudo make install`
* NOTE: Additional adjustments might have to be made to `Makefile-header.osx`
(that's where you want to look at if you get some linker errors, etc.)

### Windows

Ever thought about using Linux? We heard it's great! :)

## Using `mesh2faust`

`mesh2faust` works as a command line program. The detailed list of options of
`mesh2faust` can be printed at any time by running:

```
mesh2faust --help
```

This will print the following list of options:

```
--help: prints this help
--debug: verboses the output of mesh2faust
--showfreqs: prints the list of frequencies of the calculated modes
--infile: specifies the path to the volumetric mesh file. Dimensions of the mesh should be in meters. E.g.: --infile file.obj
--freqcontrol: adds frequency control to the generated model by adding a freq parameter to it
--name: specifies the name of the generated model (no spaces or special characters). E.g.: --name modelName
--minmode: specifies the minimum frequency of the lowest mode. E.g.: --minmode 30
--maxmode: specifies the maximum frequency of the highest mode. E.g.: --maxmode 9000
--lmexpos: specifies the maximum number of excitation positions in the model. E.g.: --lmexpos 10
--expos: specifies excitation positions as a list of vertex IDs. E.g.: --expos 89 63 45
--nfemmodes: specifies the number of modes to be computed for the finite element analysis. E.g.: --nfemmodes 300
--nsynthmodes: specifies the max number of modes to be added to the physical model and synthesized. E.g.: --nsynthmodes 50
```

The only required argument of `mesh2faust` is the
path to a volumetric mesh saved as an `.obj` file (the "world unit" of this file
should be in meter). This path must be provided using the `--infile` flag. E.g.:

```
mesh2faust --infile 3dObject.obj
```

This will create a Faust library file (`.lib`) called `modalModel.lib` in the
current folder, implementing the modal physical model corresponding to
`3dObject.obj`, and using the default parameters of `mesh2faust`.

The complexity of the object to analyze (mostly determined by its number of
  vertices) will greatly impact the duration of this process. For complex objects
  (e.g., > 3E4 vertices), this can easily take more than 30 mins on a "regular"
  laptop.

### Physical Model Name

The default name of the Faust physical model generated by `mesh2faust` is
`modalModel`. This name can be changed using the `--name` flag:

```
mesh2faust --infile 3dObject.obj --name toneBar
```

will generate a model called `toneBar` saved in a file named `toneBar.lib`.

### Material Properties

The material of the object to turn into a physical model can be configured by
providing its Young's modulus (in N/m^2), Poisson's ratio (no unit), and
density (in kg/m^3), in that order, using the `--material` flag as follows:

```
mesh2faust --material 70E9 0.35 2700 --infile 3dObject.obj
```

These values correspond to the default material (aluminum) used by `mesh2faust`,
so providing `--material 70E9 0.35 2700` will not change anything.

### Excitation Positions

After the finite element analysis, the number of excitation position (the
  place where energy is introduced) in the
physical model is the same as the number of vertices in the provided volumetric
mesh. Thus, the more vertices, the more excitation positions. The gain of each
mode in the model is different for each excitation position, so the amount of
data to be included in the generated Faust file exponentially increases with
the number of vertices in the mesh.

`mesh2faust` allows to limit the number of excitation positions in the model
either by providing a maximum number of positions using the `--lmexpos` flag
followed by an integer number, or by giving a list of vertices ID using the
`--expos` flag.

```
mesh2faust --infile 3dObject.obj --lmexpos 10
```

will generate a physical model with 10 selectable randomly distributed
excitation positions.

```
mesh2faust --infile 3dObject.obj --expos 236 589
```

will generate a physical model with 2 excitation positions corresponding to
vertex ID 236 and 589.
[Vertex IDs can be easily retrieved using meshlab.](https://ccrma.stanford.edu/~rmichon/faustTutorials/#making-physical-models-of-musical-instruments-with-faust)     

### Limiting the Number of Modes

In most cases, it is necessary to limit the number of modes of the physical
model generated by `mesh2faust`, either because they might be outside the
human hearing range (or above Nyquist) or too many (the more modes in the
model, the more computation). Several options allow to tune mode selection
in `mesh2faust` and are presented in this section.

* `--nfemmodes` controls the number of modes computed during the finite
element analysis. By default, 200 modes are computed (unless the provided mesh
has less than 200 vertices, in which case the number of computed modes will be
the same as the number of vertices in the mesh). Modes are computed by frequency,
so in this case, "200" corresponds to the first 200 modes. The more modes will
be computed during the analysis, the more time it will take.
* `--minmode` sets the minimum frequency of the lowest mode to be synthesized.
Any mode below this frequency will be discarded (default is 20Hz).  
* `--maxmode` sets the maximum frequency of the highest mode to be synthesized.
Any mode above this frequency will be discarded (default is 10KHz).
* `--nsynthmodes` controls the number of modes to be synthesized (default is 20).
Modes are selected by frequency starting at `--minmode`. `--nsynthmodes` is
adjusted (clipped) to the number of modes available between `--minmode` and
`-maxmode`.

Typically, `-nfemmodes` should be greater than `--nsynthmodes` since some of the
modes computed during the finite element analysis will be discarded depending
on the value of the `--minmode` and `--maxmode`.

```
mesh2faust --infile 3dObject.obj --nsynthmodes 50 --nfemmodes 200 --maxmode 12000
```

will generate a model with a maximum number of 50 modes and will discard modes
below 20Hz and above 12KHz.

### Making a Transposable Model

By default, `mesh2faust` generates a "static" model where the frequency of each
mode is expressed as a frequency in Hz. However, it is possible to generate a
model where mode frequencies are dynamically calculated in function of a given
fundamental frequency (mode 0) simply by providing the `--freqcontrol` flag.

Obviously, this will increase the amount of computation of the model and change
its number of arguments (see [Using Generated Models](#using-generated-models)).

### Debugging

"Debug" mode can be activated simply by providing the `--debug` flag when
calling `mesh2faust`. This will just make the process more verbose.

Additionally, `--showfreqs` will display the frequency of the computed modes
in the terminal.

## Using the Generated Models

Faust physical models generated by `mesh2faust` rely on some functions declared
in the Faust libraries, thus they all import `stdfaust.lib`.

Faust functions implementing the physical models generated by `mesh2faust` look
like:

```
_ : modalModel(exPos,t60,t60DecayRatio,t60DecaySlope) : _
```

The single audio input of the function can be used to provide an excitation
signal to the model.

### Excitation Position

`exPos` is the excitation position expressed as an integer. For example, if the
model has 5 excitation positions (e.g., configured using
[`--expos`](#excitation-positions)), the range of `exPos` will be 0-4 .

### Resonance Duration (t60)

`mesh2faust` currently doesn't allow to the estimate the time of resonance of
each mode (t60) in function of each other. While this feature will be added
in a future version, the t60 of the modes of the generated models can be
configured with 3 different parameters: `t60`, `t60DecayRatio`, and
`t60DecaySlope` where:

* `t60`: resonance duration of the lowest mode in seconds.
* `t60DecayRatio`: decay of modes t60s in function of their frequency. The
range of this parameter is 0-1. If 1, the t60 of the highest mode will be
close to 0 second.
* `t60DecaySlope`: controls the slope of the function used to compute the decay
of modes t60 in function of their frequency. It essentially controls the power
of this function. So if 1, decay will be linear, if 2, decay will be a power of
2, etc.

### Dynamic F0 Model

The [Making a Transposable Model](making-a-transposable-model) section shows how to
make a model with a dynamic fundamental frequency. Models generated using this
option look like:

```
_ : modalModel(freq,exPos,t60,t60DecayRatio,t60DecaySlope) : _
```

Where `freq` is the fundamental frequency ("f0") of the model.

## Extra Help

Feel free to contact Romain Michon if you need extra help:
rmichon AT ccrma DOT stanford DOT edu.

## License

Copyright 2017, Romain Michon and Sara R. Martin. GRAME - Centre National
de Creation Musicale (Lyon, France), CCRMA - Stanford University (USA) and
Norwegian Technical University of Trondheim (Norway).

Project partly funded by Research Council of Norway et NTNU (Norwegian Technical
University of Trondheim).

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
