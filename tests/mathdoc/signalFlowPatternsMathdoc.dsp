declare name "Signal Flow Patterns Mathdoc";
declare version "0.1";
declare author "oneilltomhq";
declare license "BSD";
declare description "Mathdoc tour of selected Faust example signal-flow patterns.";

import("stdfaust.lib");

<mdoc>
\section{Signal-flow patterns in Faust examples}
This document extracts small versions of three patterns used throughout the
Faust examples:
\begin{itemize}
\item feedback delay networks and diffusers, as in \texttt{examples/reverb/freeverb.dsp}
and \texttt{examples/reverb/fdnRev.dsp};
\item crossfaded variable delay pitch shifting, as in
\texttt{examples/pitchShifting/pitchShifter.dsp};
\item mono-to-many spatial fan-out, as in \texttt{examples/spat/spat.dsp}.
\end{itemize}
</mdoc>

// Freeverb-style feedback comb and allpass diffuser, copied in reduced form
// from examples/SAM/freeverb/freeverb.dsp.
comb(dt, fb, damp) = (+:@(dt)) ~ (*(1-damp) : (+ ~ *(damp)) : *(fb));
allpass(dt, fb) = (_,_ <: (*(fb),_:+:@(dt)), -) ~ _ : (!,_);

comb_a = comb(1116, 0.78, 0.18);
comb_b = comb(1277, 0.76, 0.20);
comb_c = comb(1422, 0.74, 0.17);
comb_d = comb(1617, 0.72, 0.21);

parallel_tank = _ <: comb_a, comb_b, comb_c, comb_d :> _;
diffuser = allpass(556, 0.5) : allpass(441, 0.5);
reverb_core = parallel_tank : diffuser;

<mdoc>
\section{Parallel resonators plus serial diffusion}
Freeverb-style reverbs put several feedback comb filters in parallel, then run
their sum through allpass diffusers. Different delay lengths avoid one obvious
resonance grid; allpasses smear transients without changing broadband energy
as much as another comb stage.

\subsection{Feedback comb}
The comb filter is a one-pole feedback loop around a delay. The damping section
inside the loop is a low-pass smoother, so high frequencies decay faster than
low frequencies.
<equation>comb_a</equation>

\subsection{Parallel tank}
The tank copies one input to four combs and sums the outputs.
<equation>parallel_tank</equation>
<diagram>parallel_tank</diagram>

\subsection{Diffuser}
Two allpass stages make the response denser without being a simple echo sum.
<equation>diffuser</equation>
<diagram>diffuser</diagram>
</mdoc>

// Reduced view of the pitch shifter example: the real implementation lives in
// effects.lib as ef.transpose and uses moving readers. This static version keeps
// the same two-tap/crossfade topology so mathdoc can render stable equations.
pitch_window = hslider("pitch/window[samples]", 1000, 50, 10000, 1);
pitch_offset = hslider("pitch/tapOffset[samples]", 20, 1, 2000, 1);
pitch_fade = hslider("pitch/fade", 0.5, 0, 1, 0.01);
pitch_tap_a = de.fdelay(20000, pitch_window);
pitch_tap_b = de.fdelay(20000, pitch_window + pitch_offset);
pitch_pattern = _ <: (pitch_tap_a : *(1-pitch_fade)), (pitch_tap_b : *(pitch_fade)) :> _;

<mdoc>
\section{Crossfaded variable-delay pitch shifting}
The pitch shifter in \texttt{examples/pitchShifting/pitchShifter.dsp} delegates
to \texttt{ef.transpose}. Its signal-flow trick is two delay taps with
complementary fades. In the full effect the readers move and reset; this reduced
form freezes the readers but keeps the crossfade topology visible.
<equation>pitch_pattern</equation>
<diagram>pitch_pattern</diagram>
</mdoc>

pan_angle = hslider("spat/angle", 0.25, 0, 1, 0.01);
pan_distance = hslider("spat/distance", 0.6, 0, 1, 0.01);
spat_pattern = sp.spat(4, pan_angle, pan_distance);

<mdoc>
\section{Spatial fan-out}
The spatializer in \texttt{examples/spat/spat.dsp} takes one source and spreads
it over an output ring. Angle chooses neighboring speakers; distance changes
direct and ambient weight. In Faust terms, this is fan-out plus per-output gain
law.
<equation>spat_pattern</equation>
<diagram>spat_pattern</diagram>
</mdoc>

dry = hslider("mix/dry", 0.35, 0, 1, 0.01);
wet = hslider("mix/wet", 0.65, 0, 1, 0.01);

demo_voice = _ <: *(dry), (reverb_core : pitch_pattern : *(wet)) :> _;
process = demo_voice : spat_pattern;

<mdoc>
\section{Full demonstration process}
The demonstration combines the patterns: dry/wet split, feedback/diffusion,
moving delay pitch shift, then spatial fan-out.
<equation>process</equation>
<diagram>process</diagram>

\section{Listing}
<listing mdoctags="false" dependencies="false" distributed="false" />
</mdoc>
