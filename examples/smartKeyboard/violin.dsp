//############################### violin.dsp ###################################
// Faust instrument specifically designed for `faust2smartkeyb` where a
// complete violin physical model can be played using the touch sceen
// interface. While the 4 virtual strings can be bowed using a control
// surface on the screen, it could be easily substituted with an external
// interface.
//
// ## `SmartKeyboard` Use Strategy
//
// 4 keyboards are used to control the pitch of the 4 bowed strings. Strings
// are connected to the virtual bow when they are touched. A pad created from
// a keybaord with a single key can be used to control the bow velocity and
// pressure on the selected strings.
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
	'Number of Keyboards':'5',
	'Max Keyboard Polyphony':'0',
	'Rounding Mode':'2',
	'Send Fingers Count':'1',
	'Keyboard 0 - Number of Keys':'19',
	'Keyboard 1 - Number of Keys':'19',
	'Keyboard 2 - Number of Keys':'19',
	'Keyboard 3 - Number of Keys':'19',
	'Keyboard 4 - Number of Keys':'1',
	'Keyboard 0 - Lowest Key':'55',
	'Keyboard 1 - Lowest Key':'62',
	'Keyboard 2 - Lowest Key':'69',
	'Keyboard 3 - Lowest Key':'76',
	'Keyboard 0 - Send Keyboard Freq':'1',
	'Keyboard 1 - Send Keyboard Freq':'1',
	'Keyboard 2 - Send Keyboard Freq':'1',
	'Keyboard 3 - Send Keyboard Freq':'1',
	'Keyboard 4 - Send Freq':'0',
	'Keyboard 4 - Send Key X':'1',
	'Keyboard 4 - Send Key Y':'1',
	'Keyboard 4 - Key 0 - Label':'Bow',
	'Keyboard 4 - Static Mode':'1'
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
kb4k0x = hslider("kb4k0x",0,0,1,1) : si.smoo;
kb4k0y = hslider("kb4k0y",0,0,1,1) : si.smoo;
kbfingers(0) = hslider("kb0fingers",0,0,10,1) : int;
kbfingers(1) = hslider("kb1fingers",0,0,10,1) : int;
kbfingers(2) = hslider("kb2fingers",0,0,10,1) : int;
kbfingers(3) = hslider("kb3fingers",0,0,10,1) : int;

// MODEL PARAMETERS
// strings lengths
sl(i) = kbfreq(i)*kbbend(i) : pm.f2l : si.smoo;
// string active only if fingers are touching the keyboard
as(i) = kbfingers(i)>0;
// bow pressure could also be controlled by an external parameter
bowPress = kb4k0y;
// retrieving finger displacement on screen (dirt simple)
bowVel = kb4k0x-kb4k0x' : abs : *(8000) : min(1) : si.smoo;
// bow position is constant but could be ontrolled by an external interface
bowPos = 0.7;

// ASSEMBLING MODELS
// essentially 4 parallel violin strings
model = par(i,4,pm.violinModel(sl(i),bowPress,bowVel*as(i),bowPos)) :> _;

process = model <: _,_;
