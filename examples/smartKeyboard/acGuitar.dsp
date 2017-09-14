//############################### acGuitar.dsp #################################
// Faust instrument specifically designed for `faust2smartkeyb` where 6 virtual
// nylon strings can be strummed and plucked using a dedicated keyboard. The
// extra "strumming keyboard" could be easily replaced by an external strumming
// interface while the touch screen could keep being used to change the pitch
// of the strings.
//
// ## `SmartKeyboard` Use Strategy
//
// The first 6 keyboards implement each individual string of the instrument. A
// seventh keybaord is used a strumming/plucking interface. As mentionned
// previously, it could be easily replaced by an external interface.
//
// ## Compilation Instructions
//
// This Faust code will compile fine with any of the standard Faust targets.
// However it was specifically designed to be used with `faust2smartkeyb`. For
// best results, we recommend to use the following parameters to compile it:
//
// ```
// faust2smartkeyb [-ios/-android] -effect reverb.dsp acGuitar.dsp
// ```
//
// ## Version/Licence
//
// Version 0.0, Aug. 2017
// Copyright Romain Michon CCRMA (Stanford University)/GRAME 2017
// MIT Licence: https://opensource.org/licenses/MIT
//##############################################################################

declare interface "SmartKeyboard{
	'Number of Keyboards':'7',
	'Max Keyboard Polyphony':'0',
	'Rounding Mode':'2',
	'Keyboard 0 - Number of Keys':'14',
  'Keyboard 1 - Number of Keys':'14',
	'Keyboard 2 - Number of Keys':'14',
	'Keyboard 3 - Number of Keys':'14',
	'Keyboard 4 - Number of Keys':'14',
	'Keyboard 5 - Number of Keys':'14',
	'Keyboard 6 - Number of Keys':'6',
	'Keyboard 0 - Lowest Key':'52',
	'Keyboard 1 - Lowest Key':'57',
	'Keyboard 2 - Lowest Key':'62',
	'Keyboard 3 - Lowest Key':'67',
	'Keyboard 4 - Lowest Key':'71',
	'Keyboard 5 - Lowest Key':'76',
	'Keyboard 0 - Send Keyboard Freq':'1',
	'Keyboard 1 - Send Keyboard Freq':'1',
	'Keyboard 2 - Send Keyboard Freq':'1',
	'Keyboard 3 - Send Keyboard Freq':'1',
	'Keyboard 4 - Send Keyboard Freq':'1',
	'Keyboard 5 - Send Keyboard Freq':'1',
	'Keyboard 6 - Piano Keyboard':'0',
	'Keyboard 6 - Send Key Status':'1',
	'Keyboard 6 - Key 0 - Label':'S0',
	'Keyboard 6 - Key 1 - Label':'S1',
	'Keyboard 6 - Key 2 - Label':'S2',
	'Keyboard 6 - Key 3 - Label':'S3',
	'Keyboard 6 - Key 4 - Label':'S4',
	'Keyboard 6 - Key 5 - Label':'S5'
}";

import("stdfaust.lib");

// SMARTKEYBOARD PARAMS
kbfreq(0) = hslider("kb0freq",164.8,20,10000,0.01);
kbbend(0) = hslider("kb0bend",1,0,10,0.01);
kbfreq(1) = hslider("kb1freq",220,20,10000,0.01);
kbbend(1) = hslider("kb1bend",1,0,10,0.01);
kbfreq(2) = hslider("kb2freq",293.7,20,10000,0.01);
kbbend(2) = hslider("kb2bend",1,0,10,0.01);
kbfreq(3) = hslider("kb3freq",392,20,10000,0.01);
kbbend(3) = hslider("kb3bend",1,0,10,0.01);
kbfreq(4) = hslider("kb4freq",493.9,20,10000,0.01);
kbbend(4) = hslider("kb4bend",1,0,10,0.01);
kbfreq(5) = hslider("kb5freq",659.2,20,10000,0.01);
kbbend(5) = hslider("kb5bend",1,0,10,0.01);
kb6kstatus(0) = hslider("kb6k0status",0,0,1,1) <: ==(1) | ==(4) : int;
kb6kstatus(1) = hslider("kb6k1status",0,0,1,1) <: ==(1) | ==(4) : int;
kb6kstatus(2) = hslider("kb6k2status",0,0,1,1) <: ==(1) | ==(4) : int;
kb6kstatus(3) = hslider("kb6k3status",0,0,1,1) <: ==(1) | ==(4) : int;
kb6kstatus(4) = hslider("kb6k4status",0,0,1,1) <: ==(1) | ==(4) : int;
kb6kstatus(5) = hslider("kb6k5status",0,0,1,1) <: ==(1) | ==(4) : int;

// MODEL PARAMETERS
// strings length
sl(i) = kbfreq(i)*kbbend(i) : pm.f2l : si.smoo;
// pluck position is controlled by the x axis of the accel
pluckPosition =
	hslider("pluckPosition[acc: 1 0 -10 0 10]",0.5,0,1,0.01) : si.smoo;

// ASSEMBLING MODELS
// number of strings
nStrings = 6;
guitar = par(i,nStrings,
	kb6kstatus(i) : ba.impulsify : // using "raw" impulses to drive the models
	pm.nylonGuitarModel(sl(i),pluckPosition)) :> _;

process = guitar <: _,_;
