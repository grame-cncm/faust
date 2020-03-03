import("stdfaust.lib");

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// A very simple subtractive synthesizer with 1 VCO 1 VCF.
// The VCO Waveform is variable between Saw and Square
// The frequency is modulated by an LFO
// The envelope control volum and filter frequency
//
///////////////////////////////////////////////////////////////////////////////////////////////////
// MIDI IMPLEMENTATION:
//
// CC 70 : waveform (Saw to square)
// CC 71 : Filter resonance (Q)
// CC 74 : Filter Cutoff frequency
// CC 79 : Filter keyboard tracking (0 to X2, default 1)
// CC 75 : Filter Envelope Modulation
//
// Envelope
// CC 73 : Attack
// CC 76 : Decay
// CC 77 : Sustain
// CC 72 : Release
//
// CC 78 : LFO frequency (0.001Hz to 10Hz)
// CC 1 : LFO Amplitude (Modulation)
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
// HUI //////////////////////////////////////////////////
// Keyboard
midigate = button("gate");
midifreq = nentry("freq[unit:Hz]", 440, 20, 20000, 1);
midigain = nentry("gain", 0.5, 0, 0.5, 0.01);// MIDI KEYBOARD

// pitchwheel
bend = ba.semi2ratio(hslider("bend [midi:pitchwheel]",0,-2,2,0.01));

// VCO
wfFade = hslider("waveform[midi:ctrl 70]",0.5,0,1,0.001):si.smoo;

// VCF
res = hslider("resonnance[midi:ctrl 71]",0.5,0,1,0.001):si.smoo;
fr = hslider("fc[midi:ctrl 74]", 15, 15, 12000, 0.001):si.smoo;
track = hslider("tracking[midi:ctrl 79]", 1, 0, 2, 0.001);
envMod = hslider("envMod[midi:ctrl 75]",50,0,100,0.01):si.smoo; 

// ENV
att = 0.01 * (hslider("attack[midi:ctrl 73]",0.1,0.1,400,0.001));
dec = 0.01 * (hslider("decay[midi:ctrl 76]",60,0.1,400,0.001));
sust = hslider("sustain[midi:ctrl 77]",0.1,0,1,0.001);
rel = 0.01 * (hslider("release[midi:ctrl 72]",100,0.1,400,0.001));

// LFO
lfoFreq = hslider("lfoFreq[midi:ctrl 78]",6,0.001,10,0.001):si.smoo;
modwheel = hslider("modwheel[midi:ctrl 1]",0,0,0.5,0.001):si.smoo;

// PROCESS /////////////////////////////////////////////
allfreq = (midifreq * bend) + LFO;
// VCF
cutoff = ((allfreq * track) + fr + (envMod * midigain * env)) : min(ma.SR/8);

// VCO
oscillo(f) = (os.sawtooth(f)*(1-wfFade))+(os.square(f)*wfFade);

// VCA
volume = midigain * env;

// Enveloppe
env = en.adsre(att,dec,sust,rel,midigate);

// LFO
LFO = os.lf_triangle(lfoFreq)*modwheel*10;

// SYNTH ////////////////////////////////////////////////
synth = (oscillo(allfreq) : ve.moog_vcf(res,cutoff)) * volume;

// PROCESS /////////////////////////////////////////////
process = synth;
