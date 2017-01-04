# Faust Libraries

NOTE: this documentation was automatically generated.

This page provides information on how to use the Faust libraries. 

The `/libraries` folder contains the different Faust libraries. If you wish to add your own functions to this library collection, you can refer to the "Contributing" section providing a set of coding conventions.

WARNING: These libraries replace the "old" Faust libraries. They are still being beta tested so you might encounter bugs while using them. If your codes still use the "old" Faust libraries, you might want to try to use Bart Brouns' script that automatically makes an old Faust code compatible with the new libraries: <https://github.com/magnetophon/faustCompressors/blob/master/newlib.sh>. If you find a bug, please report it at rmichon_at_ccrma_dot_stanford_dot_edu. Thanks ;)!

## Using the Faust Libraries

The easiest and most standard way to use the Faust libraries is to import `stdfaust.lib` in your Faust code:

```
import("stdfaust.lib");
```

This will give you access to all the Faust libraries through a series of environments:

* `sf`: `all.lib`
* `an`: `analyzers.lib`
* `ba`: `basics.lib`
* `co`: `compressors.lib`
* `de`: `delays.lib`
* `dm`: `demos.lib`
* `en`: `envelopes.lib`
* `fi`: `filters.lib`
* `ho`: `hoa.lib`
* `ma`: `maths.lib`
* `ef`: `misceffects.lib`
* `os`: `oscillators.lib`
* `no`: `noises.lib`
* `pf`: `phaflangers.lib`
* `pm`: `physmodels.lib`
* `re`: `reverbs.lib`
* `ro`: `routes.lib`
* `si`: `signals.lib`
* `sp`: `spats.lib`
* `sy`: `synths.lib`
* `ve`: `vaeffects.lib`

Environments can then be used as follows in your Faust code:

```
import("stdfaust.lib");
process = os.osc(440);
```

In this case, we're calling the `osc` function from `oscillators.lib`.

You can also access all the functions of all the libraries directly using the `sf` environment:

```
import("stdfaust.lib");
process = sf.osc(440);
```

Alternatively, environments can be created by hand:

```
os = library("oscillators.lib");
process = os.osc(440);
```

Finally, libraries can be simply imported in the Faust code (not recommended):

```
import("oscillators.lib");
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
// * argument1: argument 1 description
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

* `analyzers.lib` 
* `basics.lib` 
* `compressors.lib`
* `delays.lib`
* `demos.lib`
* `envelopes.lib`
* `filters.lib`
* `hoa.lib`
* `maths.lib`
* `misceffects.lib`
* `oscillators.lib`
* `noises.lib`
* `phaflangers.lib`
* `physmodels.lib`
* `reverbs.lib`
* `routes.lib`
* `signals.lib`
* `spats.lib`
* `synths.lib`
* `tonestacks.lib` (not documented but example in `/examples/misc`)
* `tubes.lib` (not documented but example in `/examples/misc`)
* `vaeffects.lib`

Other deprecated libraries such as `music.lib`, etc. are present but are not documented to not confuse new users. 

The doumentation of each library can be found in `/documentation/library.html` or in `/documentation/library.pdf`.

The `/examples` directory contains all the examples from the `/examples` folder of the Faust distribution as well as new ones. Most of them were updated to reflect the coding conventions described in the next section. Examples are organized by types in different folders. The `/old` folder contains examples that are fully deprecated, probably because they were integrated to the libraries and fully rewritten (see `freeverb.dsp` for example). Examples using deprecated libraries were integrated to the general tree but a warning comment was added at their beginning to point readers to the right library and function. 

## Coding Conventions

In order to have a uniformized library system, we established the following conventions (that hopefully will be followed by others when making modifications to them :-) ).

### Documentation

* All the functions that we want to be "public" are documented.
* We used the `faust2md` "standards" for each library: `//###` for main title (library name - equivalent to `#` in markdown), `//===` for section declarations (equivalent to `##` in markdown) and `//---` for function declarations (equivalent to `####` in markdown - see `basics.lib` for an example).
* Sections in function documentation should be declared as `####` markdown title.
* Each function documentation provides a "Usage" section (see `basics.lib`). 

### Library Import

To prevent cross-references between libraries we generalized the use of the `library("")` system for function calls in all the libraries. This means that everytime a function declared in another library is called, the environment corresponding to this library needs to be called too. To make things easier, a `stdfaust.lib` library was created and is imported by all the libraries:

```
an = library("analyzers.lib");
ba = library("basics.lib");
co = library("compressors.lib");
de = library("delays.lib");
dm = library("demos.lib");
en = library("envelopes.lib");
fi = library("filters.lib");
ho = library("hoa.lib");
ma = library("maths.lib");
ef = library("misceffects.lib");
os = library("oscillators.lib");
no = library("noises.lib");
pf = library("phaflangers.lib");
pm = library("physmodels.lib");
re = library("reverbs.lib");
ro = library("routes.lib");
sp = library("spats.lib");
si = library("signals.lib");
sy = library("synths.lib");
ve = library("vaeffects.lib");
```

For example, if we wanted to use the `smooth` function which is now declared in `signals.lib`, we would do the following:

```
import("stdfaust.lib");

process = si.smooth(0.999);
```

This standard is only used within the libraries: nothing prevents coders to still import `signals.lib` directly and call `smooth` without `ro.`, etc.

### "Demo" Functions

"Demo" functions are placed in `demos.lib` and have a built-in user interface (UI). Their name ends with the `_demo` suffix. Each of these function have a `.dsp` file associated to them in the `/examples` folder. 

Any function containing UI elements should be placed in this library and respect these standards.

### "Standard" Functions

"Standard" functions are here to simplify the life of new (or not so new) Faust coders. They are declared in `/libraries/doc/standardFunctions.md` and allow to point programmers to preferred functions to carry out a specific task. For example, there are many different types of lowpass filters declared in `filters.lib` and only one of them is considered to be standard, etc.

## The question of licensing/authoring/copyrigth

Now that Faust libraries are not author specific, each function will be able to have its own licence/author declaration. This means that some libraries wont have a global licence/author/copyright declaration like it used to be the case.
