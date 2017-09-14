//############################### violin2.dsp ##################################
// Faust instrument specifically designed for `faust2smartkeyb` where a
// complete violin physical model can be played using the touch sceen
// interface. Bowing is carried out by constantly moving a finger on the
// y axis of a key.
//
// ## `SmartKeyboard` Use Strategy
//
// 4 keyboards are used to control the pitch of the 4 bowed strings. Strings
// are connected to the virtual bow when they are touched.
//
// ## Compilation Instructions
//
// This Faust code will compile fine with any of the standard Faust targets.
// However it was specifically designed to be used with `faust2smartkeyb`. For
// best results, we recommend to use the following parameters to compile it:
//
// ```
// faust2smartkeyb [-ios/-android] -effect reverb.dsp violin.dsp
// ```
//
// ## Version/Licence
//
// Version 0.0, Aug. 2017
// Copyright Romain Michon CCRMA (Stanford University)/GRAME 2017
// MIT Licence: https://opensource.org/licenses/MIT
//##############################################################################

declare interface "SmartKeyboard{
	'Number of Keyboards':'4',
	'Max Keyboard Polyphony':'0',
	'Rounding Mode':'2',
	'Send Fingers Count':'1',
	'Keyboard 0 - Number of Keys':'12',
	'Keyboard 1 - Number of Keys':'12',
	'Keyboard 2 - Number of Keys':'12',
	'Keyboard 3 - Number of Keys':'12',
	'Keyboard 0 - Lowest Key':'55',
	'Keyboard 1 - Lowest Key':'62',
	'Keyboard 2 - Lowest Key':'69',
	'Keyboard 3 - Lowest Key':'76',
	'Keyboard 0 - Send Keyboard Freq':'1',
	'Keyboard 1 - Send Keyboard Freq':'1',
	'Keyboard 2 - Send Keyboard Freq':'1',
	'Keyboard 3 - Send Keyboard Freq':'1',
	'Keyboard 0 - Send Y':'1',
	'Keyboard 1 - Send Y':'1',
	'Keyboard 2 - Send Y':'1',
	'Keyboard 3 - Send Y':'1'
}";

import("stdfaust.lib");

// SMARTKEYBOARD PARAMS
kbfreq(0) = hslider("kb0freq",220,20,10000,0.01);
kbbend(0) = hslider("kb0bend",1,0,10,0.01);
kbfreq(1) = hslider("kb1freq",330,20,10000,0.01);
kbbend(1) = hslider("kb1bend",1,0,10,0.01);
kbfreq(2) = hslider("kb2freq",440,20,10000,0.01);
kbbend(2) = hslider("kb2bend",1,0,10,0.01);
kbfreq(3) = hslider("kb3freq",550,20,10000,0.01);
kbbend(3) = hslider("kb3bend",1,0,10,0.01);
kbfingers(0) = hslider("kb0fingers",0,0,10,1) : int;
kbfingers(1) = hslider("kb1fingers",0,0,10,1) : int;
kbfingers(2) = hslider("kb2fingers",0,0,10,1) : int;
kbfingers(3) = hslider("kb3fingers",0,0,10,1) : int;
y = hslider("y",0,0,1,1) : si.smoo;

// MODEL PARAMETERS
// strings lengths
sl(i) = kbfreq(i)*kbbend(i) : pm.f2l : si.smoo;
// string active only if fingers are touching the keyboard
as(i) = kbfingers(i)>0;
// retrieving finger displacement on screen (dirt simple)
bowVel = y-y' : abs : *(3000) : min(1) : si.smoo;
// bow position is constant but could be ontrolled by an external interface
bowPos = 0.7;
bowPress = 0.5;

// ASSEMBLING MODELS
// essentially 4 parallel violin strings
model = par(i,4,pm.violinModel(sl(i),bowPress,bowVel*as(i),bowPos)) :> _;

process = model <: _,_;
