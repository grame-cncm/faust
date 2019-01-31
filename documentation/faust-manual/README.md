# New Faust Manual / Documentation

This folder contains the prototype of the future Faust documentation/manual.
It is currently all written in markdown in `faustManual.html`. Running
`build` will convert this file into the corresponding html page: `index.html`.
It will automatically add the header, navbar, footer, etc. of the future
Faust website. If you wish to generate a standalone html doc. You comment the
last line of the `build` script and un-comment the following one.

## Standards

### Latex Math

Latex Math can be used in Markdown and will be interpreted accordingly (see
`faustManual.md` for examples).


### Runnable Faust Code

Any runnable Faust code can be surrounded the `<!-- faust-run -->` and 
`<!-- /faust-run -->` tags (see `faustManual.md` for examples).

## Compiling the Old Rail Figures

All the rail figures from the old faust-quick-reference are placed in individual
files that can be found in `img/src`. Running `pdflatex` will place the
corresponding figure in an individual pdf file. Pdf files were then converted
to `svg` using Inkscape and placed in `img`.
