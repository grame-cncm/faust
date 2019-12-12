//################################### multiSynth.dsp ######################################
// Faust instrument specifically designed for `faust2smartkeyb` where 4 keyboards
// are used to control 4 independent synths.
//
// ## `SmartKeyboard` Use Strategy
//
// The `SmartKeyboard` configuration is relatively simple for this example and
// only consists in four polyphonic keyboards in parallel. The `keyboard` standard
// parameter is used to activate specific elements of the synthesizer.
//
// ## Compilation Instructions
//
// This Faust code will compile fine with any of the standard Faust targets. However
// it was specifically designed to be used with `faust2smartkeyb`. For best results,
// we recommend to use the following parameters to compile it:
//
// ```
// faust2smartkeyb [-ios/-android] -effect reverb.dsp multiSynth.dsp
// ```
//
// ## Version/Licence
//
// Version 0.0, Feb. 2017
// Copyright Romain Michon CCRMA (Stanford University)/GRAME 2017
// MIT Licence: https://opensource.org/licenses/MIT
//########################################################################################

// Interface with 4 polyphnic keyboards of 13 keys with the same config
declare interface "SmartKeyboard{
	'Number of Keyboards':'4',
	'Rounding Mode':'2',
	'Inter-Keyboard Slide':'0',
	'Keyboard 0 - Number of Keys':'13',
	'Keyboard 1 - Number of Keys':'13',
	'Keyboard 2 - Number of Keys':'13',
	'Keyboard 3 - Number of Keys':'13',
	'Keyboard 0 - Lowest Key':'60',
	'Keyboard 1 - Lowest Key':'60',
	'Keyboard 2 - Lowest Key':'60',
	'Keyboard 3 - Lowest Key':'60',
	'Keyboard 0 - Send Y':'1',
	'Keyboard 1 - Send Y':'1',
	'Keyboard 2 - Send Y':'1',
	'Keyboard 3 - Send Y':'1'
}";

import("stdfaust.lib");

// standard parameters
f = hslider("freq",300,50,2000,0.01);
bend = ba.semi2ratio(hslider("bend[midi:pitchwheel]",0,-2,2,0.001)) : si.polySmooth(gate,0.999,1);
gain = hslider("gain",1,0,1,0.01);
s = hslider("sustain[midi:ctrl 64]",0,0,1,1); // for sustain pedal
t = button("gate");
y = hslider("y[midi:ctrl 1]",1,0,1,0.001) : si.smoo;
keyboard = hslider("keyboard",0,0,3,1) : int;

// fomating parameters
gate = t+s : min(1);
freq = f*bend;
cutoff = y*4000+50;

// oscillators
oscilators(0) = os.sawtooth(freq);
oscilators(1) = os.triangle(freq);
oscilators(2) = os.square(freq);
oscilators(3) = os.osc(freq);

// oscs are selected in function of the current keyboard
synths = par(i,4,select2(keyboard == i,0,oscilators(i))) :> fi.lowpass(3,cutoff) : *(envelope)
with{
	envelope = gate*gain : si.smoo;
};

process = synths <: _,_;
