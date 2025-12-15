# Faust language support in Atom

1) Add _syntax highlighting_ and _snippets_ for `.dsp` and `.lib`
files by copying the folder `../language-faust` into
`~/.atom/packages/`.

2) Select the Atom menu-item `Packages / Settings View / Install
Packages/Themes` and install the package `process-palette`.

3) Add a palette of Faust-related commands by copying the _renamed_
file `./process-palette.json` into `~/.atom/` (i.e., rename by
removing the platform extension `.osx` or `.linux`).

Once this is done you can start coding in Faust using _snippets_ for
all functions defined in the standard libraries. For example, the
prefix `lowp` expands to `fi.lowpass`. Next, selecting `lowpass` and
pressing `ctrl-alt-cmd-d` brings up the documentation of the function
`lowpass` in a browser window.

You can open the svg block-diagram by pressing `ctrl-alt-cmd-g` and
the C++ code by pressing `ctrl-alt-cmd-c`.

## Regenerating snippets

If you update the standard libraries, rebuild the Atom snippets with the Faust helper `faust2atomsnippets`:

```
faust2atomsnippets <lib1.lib> <lib2.lib> ... > atom/language-faust/snippets/faust-library.cson
```

Provide the list of libraries you want snippets for (for example the set included in `stdfaust.lib`). Redirect the output to `snippets/faust-library.cson` in this package.

For help, run:

```
faust2atomsnippets -h
```
