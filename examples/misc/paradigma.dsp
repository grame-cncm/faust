// Modulation synthesis with sparse convolution filter and distortions.
// ---------------------------------------------------------------------
//
// A "3D" oscillator oscillating on x,y,z axis, with the radius of x,y used as waveform,
// very similar and related to FM / AM.
//
// The y axis oscillation is set by MIDI pitch, x and z are detuned by simple just tuned ratios.
// Feedback acts on the individual sine oscillations (giving a sawtooth like waveform).
//
// Three weighted copies with time varying shifts are summed in a lossy integrator
// (sparse convolution), followed by a peak resonance filter and shaped by
// an internal pick-up like distortion and an asymmetric polynomial.
//
// The convolution tabs give a (variyng) triangle impulse response if integrated twice,
// with a -12 dB/octave rolloff and regular notches.
// Here only one integrator is used.
//
// The envelope is hard wired to the oscillation amplitudes and the rise time of the filter.
//
// An LFO is wired to pitch.
//
// A resonant EQ and the Dattoro Reverb from the Faust libary are added as effect on the sum.
//
// Inspired by the history of sound synthesis, namely Trautonium, Mini Moog, Phase Modulation Synthesis,
// Variophon Wind Instrument Synthesizer, Physical Modeling, and the work of Thomas D. Rossing.
//
// References:
// Kot, Vitezslav. (2006). DIGITAL SOUND EFFECTS ECHO AND REVERB BASED ON NON EXPONENTIALLY DECAYING COMB FILTER.
// https://en.wikipedia.org/wiki/Variophon
// Parker, Julian & Zavalishin, Vadim & Le Bivic, Efflam. (2016). Reducing The Aliasing Of Nonlinear Waveshaping Using Continuous-TimeConvolution.
// Nicholas G. Horton, Thomas R. Moore. (2008). Modelling The Magnetic Pickup Of An Electric Guitar.
// https://www.musicdsp.org/en/latest/Effects/86-waveshaper-gloubi-boulga.html, see comment from 2005-09-22 01:07:58
// Frei, Beat. Digital Sound Generation I & II, ICST Zurich University of the Arts
// Smith, J.O. Physical Audio Signal Processing,http://ccrma.stanford.edu/~jos/pasp/, online book, 2010 edition

declare options "[midi:on][nvoices:8]";
declare name "Paradigma_9";
declare version "1.0";
declare author "gabriel";

import("stdfaust.lib");

// Frequency Ratios table
frtonum = waveform{1, 16, 9, 6, 5, 4, 7, 3, 8, 5, 7, 15};
frtodiv = waveform{1, 15, 8, 5, 4, 3, 5, 2, 5, 3, 4, 8};

// MIDI
// minimum velocity
minvelo = 1/32;
midigrp(x) = hgroup("[1]MIDI", x);
f = nentry("freq[hidden:1]", 200, 40, 2000, 0.1);
kmidi = nentry("key[hidden:1]", 69, 0, 127, 1);
bend = ba.semi2ratio(hslider("bend[hidden:1][midi:pitchwheel][style:
knob]", 0, -2, 2, 0.01));
gain = nentry("gain[hidden:1]", 0.6, 0, 1, 0.01)<:*:_*(1-minvelo):_+minvelo;
master = hslider("volume[midi:ctrl 7]", 0.6, 0, 1, 0.01);
gate = button("gate[hidden:1]");

// Oscillator Parameter
rtogrp(x) = hgroup("[2]Oscillator", x);
rto1sel = rtogrp(hslider("[1]x[style:knob]", -12, -36, 36, 1));
rto2sel = rtogrp(hslider("[2]z[style:knob]", 19, -36, 36, 1));
fbka = rtogrp(hslider("[3]Feedback[style:knob]", 0.15, 0, 1, 0.01)<:*:*(1/ma.PI));
detune = rtogrp(hslider("[4]Detune[style:knob]", 0.125, 0, 0.5, 0.005)/ma.SR);

// LFO and Envelope Parameter
lfogrp(x) = hgroup("[3]Envelope & LFO", x);
enva = (lfogrp(ba.db2linear(hslider("[1]A[style:knob]", 20, 15, 66, 1))/1000));
envd = (lfogrp(ba.db2linear(hslider("[2]D[style:knob]", 74, 26, 100, 1))/1000)*envpscal);
envs = (lfogrp(hslider("[3]S[style:knob]", 0, 0, 1, 0.01)));
envr = (lfogrp(ba.db2linear(hslider("[4]R[style:knob]", 50, 26, 100, 1))/1000)*envpscal);
lfof = lfogrp(hslider("[5]LFO Hz[style:knob]", 3, 0.1, 12, 0.1));
lfvibra = lfogrp(hslider("[6]Vibrato[style:knob]", 0.125, 0, 1, 0.01))<:*;

env = en.adsre(enva, envd*envpscal, envs, envr*envpscal, gate);
envg = env:_*gain;

lfosn = qsin(mphasor(lfof/ma.SR));

// Triangular Filter Parameter
fltgrp(x) = hgroup("[4]Filter", x);
wid = fltgrp(hslider("[1]Rise[style:knob]", 3, 1, 9, 0.001)):2^_:1/_;
edge = fltgrp(hslider("[2]Fall[style:knob]", 6, 1, 9, 0.001)):2^_:1/_;
fiq = fltgrp(hslider("[3]Q[style:knob]", 1, 0.5, 3.87, 0.01))<:*;
drive = fltgrp(hslider("[4]Drive[style:knob]", -12, -12, 30, 0.1)):_/20.0:10^_;

// Modulation Frequency Ratios
rto1oct = rto1sel/12:floor;
rto1semi = rto1sel+36:_%12;
rto1a = frtonum, rto1semi:rdtable;
rto1b = frtodiv, rto1semi:rdtable;
rto1 = (rto1a/rto1b)*(2^rto1oct);
rto1r = min((1/rto1), 1);

rto2oct = rto2sel/12:floor;
rto2semi = rto2sel+36:_%12;
rto2a = frtonum, rto2semi:rdtable;
rto2b = frtodiv, rto2semi:rdtable;
rto2 = rto1*(rto2a/rto2b)*(2^rto2oct);
rto2r = min((1/rto2), 1);

// Pitch
lg2f = ma.log2(f/440);
stretch = 0.0333*lg2f;
envpscal = (-3*lg2f):ba.db2linear;
fplus = f*bend+lfosn*lfvibra*f*0.5/12*envg+stretch;

w = f/ma.SR;
w2 = rto1*w;
w3 = rto2*w;
wplus = fplus/ma.SR;

fbk1 = fbka*(0.5-w)^4;
fbk2 = fbka*(0.5-w2)^4*rto1r;
fbk3 = fbka*(0.5-w3)^4*rto2r;

// Modulation Reduction Per Frequency
redux1 = ((3.3-((rto1+1)*w))/3.3), 0:max:_^3;
redux2 = ((3.3-((rto2+1)*w))/3.3), 0:max:_^3;
modep = envg;
modep1 = envg*redux1*rto1r*gain;
modep2 = envg*redux2*rto2r*gain;

// Sine Oscillator
wrap(n) = n-(floor(n+0.5));
// Bhaskara I based approximate sine curve
qsincurve(x) = 1-((x*x)<:*(1.2253517*16), (_<:*:*(-3.60562732*16)):>_);
qsin(x) = x+(0.5):wrap<:(abs:-(0.25):qsincurve), _:ma.copysign;
// Feedback Depth Reduction Curve
fbcurve(x) = x:abs:-(1)<:^(3):_, (x):ma.copysign;

// Oscillator
mphasor(fw) = (+(fw)~(wrap));
oscsn(fw, off) = mphasor(fw)+off:qsin:+~*(0.5);
osc1(fw, off) = ((fw), +(off):(oscsn))~(*(fbk2):fi.pole(0.5):_*fbcurve(fw));

// 3D to 2D radius
oscy(fw, off) = (osc1(fw, off)*osc1(fw*rto2+2*detune, 0.75+off)*modep2)*modep;
oscx(fw, off) = (osc1(fw*rto1+detune,
    0.25+off)*osc1(fw*rto2+2*detune, 0.25+off)*modep2)*modep1;
oscxy(fw, off) = (oscy(fw, off)<:*), (oscx(fw, off)<:*):+:sqrt;

// Pick-Up like Distortion
// distance :
pickd = 0.25;
pickup(x, pickd) = x, // normal for in < 1.2e-4
(x, (x^2:_+pickd:_^(3/2)):/), // ILO:
(pickd^(3/2)/(sqrt(x*x+1)):ma.neg:_+pickd^(3/2)):// select
ba.if((_:abs:_<=1.2e-4), _, _):_*(pickd^(4/3));

// Basic Synthvoice, modulated Oscillations
synthvox(fw, ph2, ph3, g1, g2, g3) = (oscxy(fw, 0):_*g1), (oscxy(fw,
    ph2):_*g2), (oscxy(fw, ph3):_*g3):>_:fi.zero(1.0)<:_, (pickd):pickup;

// Triangle
// reduce width with frequency
widredux = w<:+:_^3:1.0-_;
// diff to max f in octaves, reduced for higher octaves
dwo = (0.25/wid):max(_, 1):ma.log2:ma.inv:_*widredux:ma.inv;
// falling edge
egderto = edge/wid;
wid2 = wid*(2^(dwo*(1-envg))):_*(2^(dwo*(1-gain))):min(_, 0.25):max(_, 4/(ma.SR/fplus));
wid2e = edge:min(_, 0.25):max(_, 4/(ma.SR/fplus));

fiw = wplus/wid2;
fiwtail = wplus/wid2e;
// triangle coefficients
apg0 = fiw;
apg1 = -apg0-fiwtail;
apg2 = fiwtail;
// integration freq
igpole = 1.0-5.0/ma.SR;
resf = (fplus/(wid2+wid2e)):min(_, (0.249*ma.SR));

// Asymmetric Shaper x - 0.15x^2-0.15x^3
tubicclip = _:min(_, (1.19419)):max(_, (-1.86086));
tubicilo(x) = x, // normal for in < 1.2e-4
(x-0.15*(x^2)-0.15*(x^3)), // ILO:
((0.5*(x^2)-0.05*(x^3)-0.0375*(x^4)), (x<:_, _':-:_<:(abs:max(_, 1.2e-4)), (ma.signum):ma.copysign):/):// select
ba.if((_:abs:_<=1.2e-4), _, _):fi.dcblockerat(10.0);

// Sound
process = synthvox(wplus, wid2, wid2e, apg0, apg1, apg2):fi.dcblockerat(10.0):fi.pole(igpole):fi.svf.peak(resf, fiq):_*drive:tubicclip:tubicilo:_*(1/drive);
effect = _*master:preeq(lsf,
    lsgain,
    b1f,
    eqq2,
    eqg2,
    b2f,
    eqq3,
    eqg3,
    hsf,
    hsgain)<:_, _:re.dattorro_rev_default;

// ---------------------------------------------------------------------------------------------------------------
// Resonant EQ for instrument corpus, based on SVF
eqgrp(x) = hgroup("[5]EQ", x);
lsgain = eqgrp(hslider("[1]Low Gain[style:knob]", 3, -18, 18, 0.25));
b1f = eqgrp(hslider("[2]Split F Low[style:knob]", -0.5, -1, 1, 0.05)):(2.0)^_:_*360;
b1gain = eqgrp(hslider("[3]Band 1 Gain[style:knob]", 4.5, -18, 18, 0.25));
b2f = eqgrp(hslider("[4]Split F Hi[style:knob]", -0.5, -1, 1, 0.05)):(2.0)^_:_*720;
b2gain = eqgrp(hslider("[5]Band 2 Gain[style:knob]", 4.5, -18, 18, 0.25));
hsgain = eqgrp(hslider("[6]Hi Gain[style:knob]", -3, -18, 18, 0.25));

// Q and gain of middle bands are scaled simultanously, with saturation curveongain,
// max gain is reduced from the output. Bands are spaced in octaves by default.
lsf = b1f*0.5;
hsf = b2f*2;
gcurve(gain, gainrange) = abs(gain/gainrange)<:*:1-_:_+1:_*0.5;
qscal(gain, gainrange) = 1.414*(abs(gain/gainrange)):_+1.414;
eqq2 = qscal(b1gain, 18.0);
eqg2 = b1gain*gcurve(b1gain, 18.0);
eqq3 = qscal(b2gain, 18.0);
eqg3 = b2gain*gcurve(b2gain, 18.0);
eqredux = max(lsgain, eqg2):max(_, eqg3):max(_, hsgain):ba.db2linear:ma.inv;

preeq(f1, g1, f2, q2, g2, f3, q3, g3, f4, g4) = _*eqredux:fi.svf.bell(f1,
    1.414,
    g1):fi.svf.bell(f2, q2, g2):fi.svf.bell(f3,
    q3,
    g3):fi.svf.hs(f4, 1.414, g4);
