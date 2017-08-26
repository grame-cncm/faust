//##################################### drums.dsp ########################################
// Faust instrument specifically designed for `faust2smartkeyb` where 3 drums can
// be controlled using pads. The X/Y postion of fingers is detected on each key
// and use to control the strike postion on the virtual membrane.
//
// ## `SmartKeyboard` Use Strategy
//
// The drum physical model used here is implemented to be generic so that its
// fundamental frequency can be changed for each voice. `SmartKeyboard` is used
// in polyphonic mode so each new strike on the interface corresponds to a new
// new voice.
//
// ## Compilation Instructions
//
// This Faust code will compile fine with any of the standard Faust targets. However
// it was specifically designed to be used with `faust2smartkeyb`. For best results,
// we recommend to use the following parameters to compile it:
//
// ```
// faust2smartkeyb [-ios/-android] -effect reverb.dsp drums.dsp
// ```
//
// ## Version/Licence
//
// Version 0.0, Feb. 2017
// Copyright Romain Michon CCRMA (Stanford University)/GRAME 2017
// MIT Licence: https://opensource.org/licenses/MIT
//########################################################################################

// Interface with 2 keyboards of 2 and 1 keys (3 pads)
// Static mode is used so that keys don't change color when touched
// Note labels are hidden
// Piano Keyboard mode is deactivated so all the keys look the same
declare interface "SmartKeyboard{
	'Number of Keyboards':'2',
	'Keyboard 0 - Number of Keys':'2',
	'Keyboard 1 - Number of Keys':'1',
	'Keyboard 0 - Static Mode':'1',
	'Keyboard 1 - Static Mode':'1',
	'Keyboard 0 - Send X':'1',
	'Keyboard 0 - Send Y':'1',
	'Keyboard 1 - Send X':'1',
	'Keyboard 1 - Send Y':'1',
	'Keyboard 0 - Piano Keyboard':'0',
	'Keyboard 1 - Piano Keyboard':'0',
	'Keyboard 0 - Key 0 - Label':'High',
	'Keyboard 0 - Key 1 - Label':'Mid',
	'Keyboard 1 - Key 0 - Label':'Low'
}";

import("stdfaust.lib");

// standard parameters
gate = button("gate");
x = hslider("x",1,0,1,0.001);
y = hslider("y",1,0,1,0.001);
keyboard = hslider("keyboard",0,0,1,1) : int;
key = hslider("key",0,0,1,1) : int;

drumModel = pm.djembe(rootFreq,exPos,strikeSharpness,gain,gate)
with{
	// frequency of the lowest drum
	bFreq = 60;
	// retrieving pad ID (0-2)
	padID = 2-(keyboard*2+key);
	// drum root freq is computed in function of pad number
	rootFreq = bFreq*(padID+1);
	// excitation position
	exPos = min((x*2-1 : abs),(y*2-1 : abs));
	strikeSharpness = 0.5;
	gain = 2;
};

process = drumModel <: _,_;
