// Modulation synthesis with sparse convolution filter and IR matched noise
// ========================================================================
//
// A "3D" oscillator oscillating on x,y,z axis, with the radius differential of x,y going 
// into a triangular filter along with optional IR matched synched noise, followed by magnetic distortion.
//
// Good for a variety of semi-natural sounds and very quick sound dialing due to few and meaningful parameters.
//
// The y axis oscillation is set by MIDI pitch, x and z are detuned by just ratios.
// The oscillator is retuned if x-ratio is negative.
// Feedback acts on the individual oscillations.
//  
//
// Three weighted (differentiated) copies with time varying shifts are summed in a lossy integrator
// ( sparse convolution ), followed by a peak resonance filter.
//
// The convolution tabs would give a (variyng) triangle impulse response if integrated twice,
// with a -12 dB/octave rolloff and varying regular notches.
// Here only one integrator is used. 
// The changeing filter shape gives pseudo naturally moving notches with a spectral tilt,
// and spreads the phases anti-causal in respect to the time response peak.
// This resembles a spreading waveform or changing excitation in several accoustic instruments.
//
// The symmetry parameter controls the falling edge between nearly immediate steep edge 
// and symmetric triangle pulse for different excitations / timbres.
//
// The "adaptive" parameter steers how the filter follows pitch and envelope.
// Q adds an additional peak resonance, followed by an additional high pass and magnetic pickup shaper.
// An additional one pole lowpass is hard wired to velocity 8and pitch).
//
// The envelope is hard wired to the oscillations amplitudes and the rise time of the filter.
//
// LFO is wired to pitch.
//
// Inspired by the history of sound synthesis, namely Trautonium, Mini Moog, Roland Juno, Phase Modulation Synthesis,
// Variophon Wind Instrument Synthesizer, Physical Modeling, and the work of Thomas D. Rossing.
//
// gm 2020, 2026-8-24 (this version)
//
//
//
// References:
// Kot, Vítězslav. (2006). DIGITAL SOUND EFFECTS ECHO AND REVERB BASED ON NON EXPONENTIALLY DECAYING COMB FILTER. 
// https://en.wikipedia.org/wiki/Variophon 
// Parker, Julian & Zavalishin, Vadim & Le Bivic, Efflam. (2016). 
//      Reducing The Aliasing Of Nonlinear Waveshaping Using Continuous-Time Convolution. 
// Nicholas G. Horton, Thomas R. Moore. (2008). Modelling The Magnetic Pickup Of An Electric Guitar.
// Frei, Beat. Digital Sound Generation I & II, ICST Zurich University of the Arts
// Smith, J.O. Physical Audio Signal Processing,http://ccrma.stanford.edu/~jos/pasp/, online book, 2010 edition

declare options "[midi:on][nvoices:16]";
declare options "[-vec]";
declare name "Paradigma v0145";
declare version "0.1.45";
declare author "gabriel | vox angelica";

import("stdfaust.lib");

// Frequency ratios table
frtonum = waveform{1, 16, 9, 6, 5, 4, 7, 3, 8, 5, 7, 15};
frtodiv = waveform{1, 15, 8, 5, 4, 3, 5, 2, 5, 3, 4, 8};

// Impulse response matched noise seeds: Piano, Cello, Guitar
// The seeds, when synched, generate aproximate sequences of the impulse responses differentiated twice
// ( this could be further refined by giving more wight to the onsets of the IRs, or spectral matching)
seeds = waveform{560098197, 478917317, 82993751};

// MIDI 
// minimum velocity
minvelo = 1/32;
midigrp(x) = hgroup("[1]MIDI", x);
f = nentry("freq[hidden:1]", 200, 40, 2000, 0.1);
kmidi = nentry("key[hidden:1]", 69, 0, 127, 1);
bend = ba.semi2ratio(hslider("bend[hidden:1][midi:pitchwheel][style: knob]", 0, -2, 2, 0.01));
gain = nentry("gain[hidden:1]", 0.4, 0, 1, 0.01)<:*:_*(1-minvelo):_+minvelo;
master = hslider("volume[midi:ctrl 7]", 0.6, 0, 1, 0.01);
gate = button("gate[hidden:1]");

// Oscillator Parameter
oscgrp(x) = hgroup("[2]Oscillator", x);
rto1sel = oscgrp(hslider("[1]x[style:knob]", -12, -36, 36, 1));
rto2sel = oscgrp(hslider("[2]z[style:knob]", 7, -36, 36, 1));
fbka = oscgrp(hslider("[3]Feedback[style:knob]", 0, 0, 1, 0.01)<:*:*(0.5/ma.PI));
detune = oscgrp(hslider("[4]Detune[style:knob]", 0.1, 0, 0.5, 0.005)/ma.SR);
nxamnt = oscgrp(hslider("[5]Osc / Noise[style:knob]", 0.7, 0, 1, 0.005)<:*);
constnx = oscgrp(checkbox("[6]continous"));
nxselect = oscgrp(hslider("[7]NoiseColor[style:knob]", 0, 0, 2, 1));

nxseed = seeds, nxselect:rdtable;

// LFO and Envelope Parameter
lfogrp(x) = hgroup("[3]Envelope & LFO", x);
enva = (lfogrp(ba.db2linear(hslider("[1]A[style:knob]", 20, 15, 66, 1))/1000));
envd = (lfogrp(ba.db2linear(hslider("[2]D[style:knob]", 71, 26, 100, 1))/1000)*envpscal);
envs = (lfogrp(hslider("[3]S[style:knob]", 0, 0, 1, 0.01)));
envr = (lfogrp(ba.db2linear(hslider("[4]R[style:knob]", 42, 26, 100, 1))/1000)*envpscal);
lfof = lfogrp(hslider("[5]LFO Hz[style:knob]", 3.5, 0.1, 12, 0.1));
lfvibra = lfogrp(hslider("[6]Vibrato[style:knob]", 0.05, 0, 1, 0.01))<:*;

env = en.adsre(enva, envd*envpscal, envs, envr*envpscal, gate);
envlfo = en.adsre(enva, 0, 1, envr*envpscal, gate);
envg = env*gain;
envgr3 = env*(gain^(1/3));

lfosn = qsin(mphasor(lfof/ma.SR))*envlfo;

// Triangular Filter Parameter
fltgrp(x) = hgroup("[4]Filter", x);
wid = fltgrp(hslider("[1]RisingEdge[style:knob]", 1.67, 1, 2.64, 0.001))<:_, _:*:_*(-1):2^_;
widsym = fltgrp(hslider("[2]Symmetry[style:knob]", 0, 0, 1, 0.01));
fiq = fltgrp(hslider("[3]Q[style:knob]", 1.25, 0.5, 3.87, 0.01))<:*;
fiadapt = fltgrp(hslider("[4]Adaption[style:knob]", 2.5, 1, 3, 0.25));

hpoffs = fltgrp(hslider("[5]HighPass[style:knob]", -2, -2, 2, 0.03125)):2^_;
pickupdrive = fltgrp(hslider("[6]Pickup[style:knob]", -2, -2, 2, 0.03125)):2^_;

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
rto2 = (rto2a/rto2b)*(2^rto2oct);
rto2r = min((1/rto2), 1);

// retunes the oscillator if x-oscillation is below fundamental
retune = ba.if((rto1oct+rto1semi)<0, rto1, 1);

// Pitch
lg2f = ma.log2(f/440);
// slight detune per pitch
stretch = 0.003*lg2f;
// scaling per pitch
envpscal = (-1.5*lg2f):ba.db2linear;
// f with modulation and detuning
fplus = f*bend+lfosn*lfvibra*f*0.5/12*envg+stretch;

w = retune*f/ma.SR;
w2 = rto1*w;
w3 = rto2*w;
wplus = retune*fplus/ma.SR;

// Feedback scaling
fbk1 = fbka*(0.5-w)^4;
fbk2 = fbka*(0.5-w2)^4*rto1r;
fbk3 = fbka*(0.5-w3)^4*rto2r;

// Modulation Reduction Per Frequency
redux = octcurve(w);
redux1 = octcurve(rto1*w);
redux2 = octcurve(rto2*w);
modep = envgr3*redux;
modep1 = envgr3*redux1;
modep2 = envgr3*redux2;

// Oscillator
// ==========
// wraps bewtween -0.5 and 0.5
wrap(n) = n-(floor(n+0.5));
// Bhaskara I based approximate cosine curve
qsincurve(x) = 1-((x*x)<:*(1.2253517*16), (_<:*:*(-3.60562732*16)):>_);
// cosine like half circle
qsin(x) = x+(0.5):wrap<:(abs:-(0.25):qsincurve), _:ma.copysign;
// full sine wave, input -0.5...0.5
// Feedback and modulation depth reduction curves
fbcurve(x) = 1/x<:_, 1:max:ma.log2:_-6<:_, 0:max:_*(1/10);
octcurve(x) = 1/x<:_, 1:max:ma.log2:_-2<:_, 0:max:_*(1/6)<:*;
// basic phasor -0.5...0.5
mphasor(fw) = (+(fw)~(wrap));
// basic sine oscillator
oscsn(fw, off) = mphasor(fw)+off:qsin;
// oscillator with feedback and IIR feedback filter
osc1(fw, off) = ((fw), +(off):(oscsn))~(*(fbka):fi.pole(0.5):_*fbcurve(fw));

// 3D modulation 
// a point rotates around 3 axis, the differntial of the radius of x,y is then used as signal
oscy(fw, off) = (osc1(fw, off)*osc1(fw*rto2+2*detune, 0.75+off)*modep2)*modep;
oscx(fw, off) = (osc1(fw*rto1+detune, 0.25+off)*osc1(fw*rto2+2*detune, 0.25+off)*modep2)*modep1;
// 2D radius,-> differentiator since the signal is integrated later, plus (synched) noise
oscxy(fw, off) = (oscy(fw, off)<:*), (oscx(fw, off)<:*):+:sqrt<:_-_':_*(1-nxamnt)+sncnx(fw, off)*envg*nxamnt;

// synched noise waveform
// xor random, recursive if global constnx flag is 1, otherwise only nxseed + step are used as seed
xornx(step) = (*(constnx):+(nxseed+step):int<:_, (_<<13):xor<:_, (_>>17):xor<:_, (_<<5):xor:_&536870911<:_, (float:_*(1/2147483648):wrap))~_:!, _*(1/(constnx+1));
sncwin(ph) = ba.if((abs(ph)<4*w), (abs(ph)/(4*w))-0.25:qsin*(0.5)+0.5, 1);
//synched or continous noise, not alias free due to simple transition ( 8 sample cosine fade to zero )
sncnx(fw, off) = mphasor(fw):_+off:wrap<:(_<:_+0.5<:_, _+fw<:_/fw, _/fw<:(_<:_, _), _:_, floor, floor<:_, (_<:_, _), _:(_-_, xornx, xornx):(_<:_, _), _, _:route(4, 4, 1, 1, 3, 2, 2, 3, 4, 4):(1-_)*_, _*_:>_*5), sncwin:_, ba.if(constnx, 1, _):*;

// Triangle filter with changeing rising edge, relative falling edge
// =================================================================
octavesfromtop = 1/w<:_, 1:max:ma.log2;
widbrighten = octavesfromtop-4<:_, 0:max:1/(2^_);
// curve to brighten ( == reduce triangle width) low notes
widredux = octavesfromtop-4<:_, 0:max:// curve to fade brightness ( == increase width) for top notes
_*(1/6)<:_, 1:min:sqrt*widbrighten;

// diff to max. width in octaves, reduced for higher octaves
dwo = (0.25/wid):max(_, 1):ma.log2:_*widredux;

minwid = 4/(ma.SR/f);
// minimum triangle edge time
maxwid = 0.5;
// maximum triangle edge time

// scale with envelope
// 1. rising edge
wid2 = wid*(fiadapt^(dwo*(1-envg))):min(_, maxwid):max(_, minwid);
// 2. falling edge relative to rising edge
wid2e = (1/512+wid2*widsym):min(_, maxwid):max(_, minwid);
fiw = w/wid2;
//  t increment for rising edge
fiwtail = w/wid2e;
//  t increment for falling edge

fiwcompens = 0.25*wid2e/(2/512);
// gain compensation

// triangle coefficients
apg0 = fiw*fiwcompens;
apg1 = -apg0-fiwtail*fiwcompens;
apg2 = fiwtail*fiwcompens;

// integration freq. ~ 25 Hz
igpole = 1.0-25.0/ma.SR;
// resonance frequency  
resf = (fplus/(wid2+wid2e)):min(_, (0.166*ma.SR));

// additional pitch and velocity dependend 1-pole low pass and global voice level
lpfw = w+(5000/ma.SR-w)*gain*gain;
lpp = ma.E^(-2*ma.PI*lpfw);
lpa = 1.5*(1-lpp);

// Pick-up like distortion 
// =======================
// ( x-distance = 0.25 )
pickup(x) = x, // normal for in < 1.2e-4
(x, (x^2:_+0.25:_^(3/2)):/), // ILO anti aliasing:
(0.25^(3/2)/(sqrt(x*x+1)):ma.neg:_+0.25^(3/2)):// select
ba.if((_:abs:_<=1.2e-4), _, _):_*(0.25^(4/3));

// Basic synth voice, 3 phase shifted weighted copies, velocity dependend lowpass, integration
synthvox(fw, ph2, ph3, g1, g2, g3) = (oscxy(fw, 0):_*g1), (oscxy(fw, ph2):_*g2), (oscxy(fw, ph3):_*g3):>_:_*lpa:fi.pole(lpp):fi.pole(igpole);

// Sound 
// =====
process = synthvox(wplus, wid2, wid2e, apg0, apg1, apg2):fi.svf.peak(resf, fiq):fi.svf.hp(hpoffs*fplus/(wid2+wid2e):min(_, ma.SR*0.166), 0.707):_*pickupdrive:pickup*(min(1/pickupdrive, 1))<:_, _;

effect = re.dattorro_rev_default;
