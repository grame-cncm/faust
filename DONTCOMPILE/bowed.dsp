//##################################### bowed.dsp ########################################
// Faust instrument specifically designed for `faust2smartkeyb` implementing a
// non-polyphonic synthesizer (e.g., physical model; etc.) using a combination of
// different types of UI elements.
//
// ## `SmartKeyboard` Use Strategy
//
// 5 keyboards are declared (4 actual keyboards and 1 control surface). We want to
// disable the voice allocation system and we want to activate a voice on start-up
// so that all strings are constantly running so we set `Max Keyboard Polyphony` to
// 0. Since we don't want the first 4 keyboards to send the X and Y position of
// fingers on the screen, we set `Send X` and `Send Y` to 0 for all these keyboards.
// Similarly, we don't want the fifth keyboard to send pitch information to the synth
// so we set `Send Freq` to 0 for that keyboard. Finally, we deactivate piano keyboard
// mode for the fifth keyboard to make sure that color doesn't change when the key is
// touch and that note names are not displayed.
//
// ## Compilation Instructions
//
// This Faust code will compile fine with any of the standard Faust targets. However
// it was specifically designed to be used with `faust2smartkeyb`. For best results,
// we recommend to use the following parameters to compile it:
//
// ```
// faust2smartkeyb [-ios/-android] -effect reverb.dsp midiOnly.dsp
// ```
//
// ## Version/Licence
//
// Version 0.0, Feb. 2017
// Copyright Romain Michon CCRMA (Stanford University)/GRAME 2017
// MIT Licence: https://opensource.org/licenses/MIT
//########################################################################################

declare interface "SmartKeyboard{
	'Number of Keyboards':'5',
	'Max Keyboard Polyphony':'0',
	'Rounding Mode':'1',
	'Keyboard 0 - Number of Keys':'19',
	'Keyboard 1 - Number of Keys':'19',
	'Keyboard 2 - Number of Keys':'19',
	'Keyboard 3 - Number of Keys':'19',
	'Keyboard 4 - Number of Keys':'1',
	'Keyboard 4 - Send Freq':'0',
	'Keyboard 0 - Send X':'0',
	'Keyboard 1 - Send X':'0',
	'Keyboard 2 - Send X':'0',
	'Keyboard 3 - Send X':'0',
	'Keyboard 0 - Send Y':'0',
	'Keyboard 1 - Send Y':'0',
	'Keyboard 2 - Send Y':'0',
	'Keyboard 3 - Send Y':'0',
	'Keyboard 0 - Lowest Key':'55',
	'Keyboard 1 - Lowest Key':'62',
	'Keyboard 2 - Lowest Key':'69',
	'Keyboard 3 - Lowest Key':'76',
	'Keyboard 4 - Piano Keyboard':'0',
	'Keyboard 4 - Key 0 - Label':'Bow'
}";

import("stdfaust.lib");

// parameters
f = hslider("freq",400,50,2000,0.01);
bend = hslider("bend",1,0,10,0.01);
keyboard = hslider("keyboard",0,0,5,1) : int;
key = hslider("key",0,0,18,1) : int;
x = hslider("x",0.5,0,1,0.01) : si.smoo;
y = hslider("y",0,0,1,0.01) : si.smoo;

// mapping
freq = f*bend;
// dirty motion tracker
velocity = x-x' : abs : an.amp_follower_ar(0.1,1) : *(8000) : min(1);

// 4 "strings"
synthSet = par(i,4,synth(localFreq(i),velocity)) :> _
with{
	localFreq(i) = freq : ba.sAndH(keyboard == i) : si.smoo;
	synth(freq,velocity) = sy.fm((freq,freq + freq*modFreqRatio),index*velocity)*velocity
	with{
		index = 1000;
		modFreqRatio = y*0.3;
	};
};

process = synthSet <: _,_;