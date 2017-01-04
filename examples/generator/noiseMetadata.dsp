// WARNING: This a "legacy example based on a deprecated library". Check noises.lib
// for more accurate examples of noise functions

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

declare name 		"noiseMetadata"; // avoid same name as in noise.dsp
declare version 	"1.1";
declare author 		"Grame";
declare author 		"Yghe";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2009";

<mdoc>
\section{Presentation of the "noise.dsp" Faust program}
This program describes a white noise generator with an interactive volume, using a random function.

\subsection{The random function}
</mdoc>

random  = +(12345)~*(1103515245);

<mdoc>
The \texttt{random} function describes a generator of random numbers, which equation follows. You should notice hereby the use of an integer arithmetic on 32 bits, relying on integer wrapping for big numbers.
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
Endly, the sound level of this program is controlled by a user slider, which gives the following equation: 
<equation>process</equation>

\section{Block-diagram schema of process}
This process is illustrated on figure 1.
<diagram>process</diagram>

\section{Notice of this documentation}
You might be careful of certain information and naming conventions used in this documentation:
<notice />

\section{Listing of the input code}
The following listing shows the input Faust code, parsed to compile this mathematical documentation.
<listing mdoctags="false" dependencies="false" distributed="false" />
</mdoc>
