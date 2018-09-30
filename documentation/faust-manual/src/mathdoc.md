# Mathematical Documentation

The Faust compiler provides a mechanism to produce a self-describing 
documentation of the mathematical semantic of a Faust program, essentially as a 
pdf file. The corresponding options are 
[`-mdoc` (short) or `--mathdoc`](#compilation-options) (long).

## Goals of the Mathdoc

There are three main goals, or uses, of the Faust mathematical documentation 
generator:

* to preserve signal processors, independently from any computer language but 
only under a mathematical form;
* to bring some help for debugging tasks, by showing the formulas as they are 
really computed after the compilation stage;
* to give a new teaching support, as a bridge between code and formulas for 
signal processing.

## Installation Requirements

* `faust`, of course!
* `svg2pdf` (from the Cairo 2D graphics library), to convert block-diagrams, 
as Latex doesn't embed SVG directly,
* `breqn`, a Latex package to handle automatic breaking of long equations,
* `pdflatex`, to compile the Latex output file.

## Generating the Mathdoc

The easiest way to generate the complete mathematical documentation is to call 
the `faust2mathdoc` script on a Faust file, as the `-mdoc` option leaves the 
process of generating the documentation unfinished (only the source 
is produced).

### Invoking the `-mdoc` Option

Calling directly `faust -mdoc` does only the first part of the work, generating:

* a top-level directory, suffixed with `-mdoc`,
* 5 subdirectories (`cpp/`, `pdf/`, `src/`, `svg/`, `tex/`),
* a Latex file containing the formulas,
* SVG files for block-diagrams.

At this stage:

* `cpp/` remains empty,
* `pdf/` remains empty,
* `src/` contains all the used Faust sources (even libraries),
* `svg/` contains SVG block-diagram files,
* `tex/` contains the generated Latex file.

### Invoking `faust2mathdoc`

The `faust2mathdoc` script calls `faust --mathdoc` first, then it finishes the 
work:

* moving the output C++ file into `cpp/`,
* converting all SVG files into pdf files (you must have `svg2pdf` installed, 
from the Cairo 2D graphics library),
* launching `pdflatex` on the Latex file (you must have both `pdflatex` and the 
`breqn` package installed),
* moving the resulting pdf file into `pdf/`.

### Online Examples

To get an idea of the results of this mathematical documentation, which 
captures the mathematical semantic of Faust programs, you can look at two pdf 
files online:

* <http://faust.grame.fr/pdf/karplus.pdf> (automatic documentation),
* <http://faust.grame.fr/pdf/noise.pdf> (manual documentation).

You can also generate all *mdoc* pdfs at once, simply invoking the `make 
mathdoc` command inside the `examples/` directory: 

* for each `%.dsp` file, a complete `%-mdoc` directory will be generated,
* a single `allmathpdfs/` directory will gather all the generated pdf files.

## Automatic Documentation

By default, when no `<mdoc>` tag can be found in the input Faust file, the 
`-mdoc` option automatically generates a Latex file with four sections:

* **Equations of process**, gathering all formulas needed for `process`,
* **Block-diagram schema of process**, showing the top-level block-diagram of 
`process`,
* **Notice of this documentation**, summing up generation and conventions 
information,
* **Complete listing of the input code**, listing all needed input files 
(including libraries).

## Manual Documentation

You can specify yourself the documentation instead of using the automatic mode, 
with five xml-like tags. That allows you to modify the presentation and to 
add your own comments, not only on `process`, but also about any expression 
you'd like to. Note that as soon as you declare an `<mdoc>` tag inside your 
Faust file, the default structure of the automatic mode is ignored, and all the 
Latex stuff becomes up to you!

### Six Tags

Here are the six specific tags:

* `<mdoc></mdoc>`, to open a documentation field in the Faust code,
  * `<equation></equation>`, to get equations of a Faust expression,
  * `<diagram></diagram>`, to get the top-level block-diagram of a Faust 
  expression,
  * `<metadata></metadata>`, to reference Faust metadatas (cf. declarations), 
  calling the corresponding keyword,
  * `<notice />`, to insert the "adaptive" notice all formulas actually 
  printed,
  * `<listing [attributes] />`, to insert the listing of Faust files called.

The `<listing />` tag can have up to three boolean attributes (set to `true` by 
default):

* `mdoctags` for `<mdoc>` tags;
* `dependencies` for other files dependencies;
* `distributed` for the distribution of interleaved Faust code between `<mdoc>` 
sections.

### The `mdoc` Top-Level Tags

The `<mdoc></mdoc>` tags are the top-level delimiters for Faust mathematical 
documentation sections. This means that the four other documentation tags can't 
be used outside these pairs.

In addition of the four inner tags, `<mdoc></mdoc>` tags accept free Latex text, 
including its standard macros (like `\section`, `\emph`, etc.). This allows to 
manage the presentation of resulting tex file directly from within the input 
Faust file. 

The complete list of the Latex packages included by Faust can be found in the 
file `architecture/latexheader.tex`.

## An Example of Manual Mathdoc

```
<mdoc>
\title{<metadata>name</metadata>}
\author{<metadata>author</metadata>}
\date{\today}
\maketitle

\begin{tabular}{ll}
	\hline
	\textbf{name}		& <metadata>name</metadata> \\
	\textbf{version} 	& <metadata>version</metadata> \\
	\textbf{author} 	& <metadata>author</metadata> \\
	\textbf{license} 	& <metadata>license</metadata> \\
	\textbf{copyright} 	& <metadata>copyright</metadata> \\
	\hline
\end{tabular}
\bigskip
</mdoc>
//-----------------------------------------------------------------
// Noise generator and demo file for the Faust math documentation
//-----------------------------------------------------------------

declare name 		"Noise";
declare version 	"1.1";
declare author 		"Grame";
declare author 		"Yghe";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2009";

<mdoc>
\section{Presentation of the "noise.dsp" Faust program}
This program describes a white noise generator with an interactive volume, 
using a random function.

\subsection{The random function}
</mdoc>

random  = +(12345)~*(1103515245);

<mdoc>
The \texttt{random} function describes a generator of random numbers, which 
equation follows. You should notice hereby the use of an integer arithmetic on 
32 bits, relying on integer wrapping for big numbers.
<equation>random</equation>

\subsection{The noise function}
</mdoc>

noise   = random/2147483647.0;

<mdoc>
The white noise then corresponds to:
<equation>noise</equation>

\subsection{Just add a user interface element to play volume!}
</mdoc>

process = noise * vslider("Volume[style:knob]", 0, 0, 1, 0.1);

<mdoc>
Endly, the sound level of this program is controlled by a user slider, which 
gives the following equation: 
<equation>process</equation>

\section{Block-diagram schema of process}
This process is illustrated on figure 1.
<diagram>process</diagram>

\section{Notice of this documentation}
You might be careful of certain information and naming conventions used in this 
documentation:
<notice />

\section{Listing of the input code}
The following listing shows the input Faust code, parsed to compile this
mathematical documentation.
<listing mdoctags="false" dependencies="false" distributed="true" />
</mdoc>
```

### The `-stripmdoc` Option

The listing of the input code contains all the mathdoc text. As it may be 
useless in certain cases, we provide an option to strip mathdoc contents 
directly at compilation stage: `-stripmdoc` (short) or `--strip-mdoc-tags` 
(long).

## Localization of Mathdoc Files

By default, texts used by the documentator are in English, but you can specify 
another language (French, German and Italian at the moment), using the `-mdlang` 
(or `--mathdoc-lang`) option with a two-letters argument (`en`, `fr`, `it`, 
etc.).

The `faust2mathdoc` script also supports this option, plus a third short form 
with `-l`:

```
faust2mathdoc -l fr myfaustfile.dsp
```

If you would like to contribute to the localization effort, feel free to 
translate the mathdoc texts from any of the `mathdoctexts-*.txt` files, that 
are in the `architecture` directory (`mathdoctexts-fr.txt`, 
`mathdoctexts-it.txt`, etc.). As these files are dynamically loaded, just 
adding a new file with an appropriate name should work.

## Summary of the Mathdoc Generation Steps

* First, to get the full mathematical documentation done on your Faust file, 
call `faust2mathdoc myfaustfile.dsp`.
* Then, open the pdf file `myfaustfile-mdoc/pdf/myfaustfile.pdf`.
* That's all !
