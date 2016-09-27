# Faust Libraries

NOTE: this documentation was automatically generated.

This page provides information on how to use the Faust libraries. 

The `/libraries` folder contains the different Faust libraries. If you wish to add your own functions to this library collection, you can refer to the "Contributing" section providing a set of coding conventions.

WARNING: These libraries replace the "old" Faust libraries. They are still being beta tested so you might encounter bugs while using them. If you find a bug, please report it at rmichon_at_ccrma_dot_stanford_dot_edu. Thanks ;)!

## Using the Faust Libraries

The easiest and most standard way to use the Faust libraries is to import `stdfaust.lib` in your Faust code:

```
import("stdfaust.lib");
```

This will give you access to all the Faust libraries through a series of environments:

* `ma`: `math.lib`
* `ba`: `basic.lib`
* `de`: `delay.lib`
* `en`: `envelope.lib`
* `ro`: `route.lib`
* `si`: `signal.lib`
* `an`: `analyzer.lib`
* `fi`: `filter.lib`
* `os`: `miscoscillator.lib`
* `no`: `noise.lib`
* `ho`: `hoa.lib`
* `sp`: `spat.lib`
* `sy`: `synth.lib`
* `ef`: `misceffect.lib`
* `ve`: `vaeffect.lib`
* `co`: `compressor.lib`
* `pf`: `phafla.lib`
* `re`: `reverb.lib`
* `de`: `demo.lib`

Environments can then be used as follows in your Faust code:

```
import("stdfaust.lib");
process = os.osc(440);
```

In this case, we're calling the `osc` function from `miscoscillator.lib`.

Alternatively, environments can be created by hand:

```
os = library("miscoscillator.lib");
process = os.osc(440);
```

Finally, libraries can be simply imported in the Faust code (not recommended):

```
import("miscoscillator.lib");
process = osc(440);
```

## Contributing

If you wish to add a function to any of these libraries or if you plan to add a new library, make sure that you follow the following conventions:

### New Functions

* All functions must be preceded by a markdown documentation header respecting the following format (open the source code of any of the libraries for an example):

```
//-----------------functionName--------------------
// Description
// 
// #### Usage
// 
// ```
// Usage Example
// ```
//
// Where:
//
// * argument1: argument 1 descirption
//-------------------------------------------------
```

* Every time a new function is added, the documentation should be updated simply by running `make doclib`.
* The environment system (e.g. `os.osc`) should be used when calling a function declared in another library (see the section on *Using the Faust Libraries*).
* Try to reuse exisiting functions as much as possible.
* If you have any question, send an e-mail to rmichon_at_ccrma_dot_stanford_dot_edu.

### New Libraries

* Any new "standard" library should be declared in `stdfaust.lib` with its own environment (2 letters - see `stdfaust.lib`).
* Any new "standard" library must be added to `generateDoc`.
* Functions must be organized by sections.
* Any new library should at least `declare` a `name` and a `version`. 
* The comment based markdown documentation of each library must respect the following format (open the source code of any of the libraries for an example):

```
//############### libraryName ##################
// Description
// 
// * Section Name 1
// * Section Name 2
// * ...
//
// It should be used using the `[...]` environment:
//
// ```
// [...] = library("libraryName");
// process = [...].functionCall;
// ```
//
// Another option is to import `stdfaust.lib` which already contains the `[...]`
// environment:
//
// ```
// import("stdfaust.lib");
// process = [...].functionCall;
// ```
//##############################################

//================= Section Name ===============
// Description
//==============================================
```
* If you have any question, send an e-mail to rmichon_at_ccrma_dot_stanford_dot_edu.

## General Organization

Only the libraries that are considered to be "standard" are documented:

* `analyzer.lib` 
* `basic.lib` 
* `delay.lib`
* `misceffect.lib`
* `compressor.lib`
* `vaeffect.lib`
* `phafla.lib`
* `reverb.lib`
* `envelope.lib`
* `filter.lib`
* `miscoscillator.lib`
* `noise.lib`
* `hoa.lib`
* `math.lib`
* `pm.lib`
* `route.lib`
* `signal.lib`
* `spat.lib`
* `synth.lib`
* `demo.lib`
* `tonestack.lib` (not documented but example in `/examples/misc`)
* `tube.lib` (not documented but example in `/examples/misc`)

Other deprecated libraries such as `music.lib`, etc. are present but are not documented to not confuse new users. 

The doumentation of each library can be found in `/documentation/library.html` or in `/documentation/library.pdf`.

The `/examples` directory contains all the examples from the `/examples` folder of the Faust distribution as well as new ones. Most of them were updated to reflect the coding conventions described in the next section. Examples are organized by types in different folders. The `/old` folder contains examples that are fully deprecated, probably because they were integrated to the libraries and fully rewritten (see `freeverb.dsp` for example). Examples using deprecated libraries were integrated to the general tree but a warning comment was added at their beginning to point readers to the right library and function. 

## Coding Conventions

In order to have a uniformized library system, we established the following conventions (that hopefully will be followed by others when making modifications to them :-) ).

### Documentation

* All the functions that we want to be "public" are documented.
* We used the `faust2md` "standards" for each library: `//###` for main title (library name - equivalent to `#` in markdown), `//===` for section declarations (equivalent to `##` in markdown) and `//---` for function declarations (equivalent to `####` in markdown - see `basic.lib` for an example).
* Sections in function documentation should be declared as `####` markdown title.
* Each function documentation provides a "Usage" section (see `basic.lib`). 

### Library Import

To prevent cross-references between libraries we generalized the use of the `library("")` system for function calls in all the libraries. This means that everytime a function declared in another library is called, the environment corresponding to this library needs to be called too. To make things easier, a `stdfaust.lib` library was created and is imported by all the libraries:

```
ma = library("math.lib");
ba = library("basic.lib");
de = library("delay.lib");
en = library("envelope.lib");
ro = library("route.lib");
si = library("signal.lib");
an = library("analyzer.lib");
fi = library("filter.lib");
os = library("miscoscillator.lib");
no = library("noise.lib");
ho = library("hoa.lib");
sp = library("spat.lib");
sy = library("synth.lib");
ef = library("misceffect.lib");
ve = library("vaeffect.lib");
co = library("compressor.lib");
pf = library("phafla.lib");
re = library("reverb.lib");
```

For example, if we wanted to use the `smooth` function which is now declared in `signal.lib`, we would do the following:

```
import("stdfaust.lib");

process = si.smooth(0.999);
```

This standard is only used within the libraries: nothing prevents coders to still import `signal.lib` directly and call `smooth` without `ro.`, etc.

### "Demo" Functions

All the functions that were present in the libraries and that contained any kind of UI elements declaration (mostly JOS "`demo`" functions) were turned into independant `.dsp` files that were placed in the `/examples` folder. Thus, Faust libraries now only contain "pure" function declarations which should make them more legible. Also, "`demo`" functions make great examples... 

For practicality, the "`demo`" functions are still declared and are available in `demo.lib` as "components" pointing at the `/examples` folder (which is why that folder will have to be installed on the system during the installation process of the Faust distribution).

## The question of licensing/authoring/copyrigth

Now that Faust libraries are not author specific, each function will be able to have its own licence/author declaration. This means that some libraries wont have a global licence/author/copyright declaration like it used to be the case.