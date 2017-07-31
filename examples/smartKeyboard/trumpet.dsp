//################################### trumpet.dsp #####################################
// A simple trumpet app... (for large screens).
//
// ## Compilation Instructions
//
// This Faust code will compile fine with any of the standard Faust targets. However
// it was specifically designed to be used with `faust2smartkeyb`. For best results,
// we recommend to use the following parameters to compile it:
//
// ```
// faust2smartkeyb [-ios/-android] -effect reverb.dsp trumpet.dsp
// ```
//
// ## Version/Licence
//
// Version 0.0, Feb. 2017
// Copyright Romain Michon CCRMA (Stanford University)/GRAME 2017
// MIT Licence: https://opensource.org/licenses/MIT
//########################################################################################

import("stdfaust.lib");

declare interface "SmartKeyboard{
	'Number of Keyboards':'5',
	'Max Keyboard Polyphony':'1',
	'Mono Mode':'1',
	'Keyboard 0 - Number of Keys':'13',
	'Keyboard 1 - Number of Keys':'13',
	'Keyboard 2 - Number of Keys':'13',
	'Keyboard 3 - Number of Keys':'13',
	'Keyboard 4 - Number of Keys':'13',
	'Keyboard 0 - Lowest Key':'77',
	'Keyboard 1 - Lowest Key':'72',
	'Keyboard 2 - Lowest Key':'67',
	'Keyboard 3 - Lowest Key':'62',
	'Keyboard 4 - Lowest Key':'57',
	'Rounding Mode':'2',
	'Keyboard 0 - Send Y':'1',
	'Keyboard 1 - Send Y':'1',
	'Keyboard 2 - Send Y':'1',
	'Keyboard 3 - Send Y':'1',
	'Keyboard 4 - Send Y':'1',
}";

// standard parameters
f = hslider("freq",300,50,2000,0.01);
bend = hslider("bend[midi:pitchwheel]",1,0,10,0.01) : si.polySmooth(gate,0.999,1);
gain = hslider("gain",1,0,1,0.01);
s = hslider("sustain[midi:ctrl 64]",0,0,1,1); // for sustain pedal
t = button("gate");
y = hslider("y[midi:ctrl 1]",1,0,1,0.001) : si.smoo;

// fomating parameters
gate = t+s : min(1);
freq = f*bend;
cutoff = y*4000+50;
envelope = gate*gain : si.smoo;

process = os.sawtooth(freq)*envelope : fi.lowpass(3,cutoff) <: _,_;
