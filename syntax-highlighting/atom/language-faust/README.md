# Faust language support in Atom

1) First add _syntax highlighting_ and _snippets_ for `.dsp` and `.lib` files:

- copy the folder `language-faust/` into `~/.atom/packages/`

2) Then add a palette of Faust-related commands:
 
- install the package `process-palette`
- copy the file `process-palette.json` into `~/.atom/` (don't forget to remove the plateform extension `.osx` or `.linux`)

Once this is done you can start coding in Faust with snippets for all functions defined in the standard libraries. For example from the prefix `lowp` you will get `fi.lowpass`. Then by selecting `lowpass` and pressing `ctrl-alt-cmd-d` you will get the documentation of the function `lowpass`.

You can get the svg block-diagram by pressing `ctrl-alt-cmd-g` and the C++ code by pressing `ctrl-alt-cmd-c`.