//######################################## vocal.dsp #####################################
// A funny vocal synth app...
//
// ## Compilation Instructions
//
// This Faust code will compile fine with any of the standard Faust targets. However
// it was specifically designed to be used with `faust2smartkeyb`. For best results,
// we recommend to use the following parameters to compile it:
//
// ```
// faust2smartkeyb [-ios/-android] vocal.dsp
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
	'Number of Keyboards':'1',
	'Max Keyboard Polyphony':'0',
	'Keyboard 0 - Number of Keys':'1',
	'Keyboard 0 - Send Freq':'0',
	'Keyboard 0 - Static Mode':'1',
	'Keyboard 0 - Send X':'1',
	'Keyboard 0 - Piano Keyboard':'0'
}";

// standard parameters
vowel = hslider("vowel[acc: 0 0 -10 0 10]",2,0,4,0.01) : si.smoo;
x = hslider("x",0.5,0,1,0.01) : si.smoo;
vibrato = hslider("vibrato[acc: 1 0 -10 0 10]",0.05,0,0.1,0.01);
gain = hslider("gain",0.25,0,1,0.01);

// fomating parameters
freq = x*200 + 50;
voiceFreq = freq*(os.osc(6)*vibrato+1);

process = pm.SFFormantModelBP(1,vowel,0,voiceFreq,gain) <: _,_;
