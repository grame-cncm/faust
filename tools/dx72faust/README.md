# `dx72faust`

`dx72faust` is a simple program to convert Yamaha DX7 `.syx` preset files into
Faust libraries.

## Compilation and Installation

Compilation:

```
make
```

Installation:

```
sudo make install
```

## Using `mesh2faust`

The only argument of `dx72faust` is a `.syx` DX7 preset file:

```
dx72faust presetFile.syx
```

Which will create a `dx7_presetFile.syx.lib` file in the current folder.

DX7 files can be easily found on the web. One great resource is Dave Benson's
website: <https://homepages.abdn.ac.uk/mth192/pages/html/dx7.html>

## Using the Generated Faust Libraries

Faust libraries generated with `dx72faust` rely on `dx7.lib` which is available
in the `libraries` folder of the Faust distribution. Each library will contain
32 functions corresponding to the 32 voices contained in the preset file. These
functions all have a name starting with `dx7_` and have 3 arguments: `freq`,
`gain`, and `gate`. They can be used as such:

```
import("dx7_brass.syx.lib");

freq = hslider("freq",440,50,2000,0.01);
gain = hslider("gain",1,0,1,0.01);
gate = button("gate");

process = dx7_BRASS1(freq,gain,gate);
```

NOTE: The output signal of `dx7_*` functions might need to be scaled in some cases.

Example of libraries generated with `dx7faust` can be found in the
`libraries/dx7presets` folder of the Faust distribution.
