//################################ bells.dsp ###################################
// Faust instrument specifically designed for `faust2smartkeyb` where the
// physical models of 4 different bells can be played using screen pads. The
// models are taken from `physmodels.lib`.
//
// ## `SmartKeyboard` Use Strategy
//
// The `SmartKeyboard` interface is used to implement percussion pads where
// the X/Y position of fingers is retrieved to control the strike position on
// the bells.
//
// ## Compilation Instructions
//
// This Faust code will compile fine with any of the standard Faust targets.
// However it was specifically designed to be used with `faust2smartkeyb`. For
// best results, we recommend to use the following parameters to compile it:
//
// ```
// faust2smartkeyb [-ios/-android] -effect reverb.dsp bells.dsp
// ```
//
// ## Version/Licence
//
// Version 0.0, Aug. 2017
// Copyright Romain Michon CCRMA (Stanford University)/GRAME 2017
// MIT Licence: https://opensource.org/licenses/MIT
//##############################################################################

declare interface "SmartKeyboard{
	'Number of Keyboards':'2',
	'Max Keyboard Polyphony':'0',
	'Keyboard 0 - Number of Keys':'2',
  'Keyboard 1 - Number of Keys':'2',
	'Keyboard 0 - Send Freq':'0',
  'Keyboard 1 - Send Freq':'0',
	'Keyboard 0 - Piano Keyboard':'0',
  'Keyboard 1 - Piano Keyboard':'0',
	'Keyboard 0 - Send Key Status':'1',
	'Keyboard 1 - Send Key Status':'1',
	'Keyboard 0 - Send X':'1',
	'Keyboard 0 - Send Y':'1',
	'Keyboard 1 - Send X':'1',
	'Keyboard 1 - Send Y':'1',
	'Keyboard 0 - Key 0 - Label':'English Bell',
	'Keyboard 0 - Key 1 - Label':'French Bell',
	'Keyboard 1 - Key 0 - Label':'German Bell',
	'Keyboard 1 - Key 1 - Label':'Russian Bell'
}";

import("stdfaust.lib");

// SMARTKEYBOARD PARAMS
kb0k0status = hslider("kb0k0status",0,0,1,1) : min(1) : int;
kb0k1status = hslider("kb0k1status",0,0,1,1) : min(1) : int;
kb1k0status = hslider("kb1k0status",0,0,1,1) : min(1) : int;
kb1k1status = hslider("kb1k1status",0,0,1,1) : min(1) : int;
x = hslider("x",1,0,1,0.001);
y = hslider("y",1,0,1,0.001);

// MODEL PARAMETERS
strikeCutoff = 6500;
strikeSharpness = 0.5;
strikeGain = 1;
// synthesize 10 modes out of 50
nModes = 10;
// resonance duration is 30s
t60 = 30;
// number of excitation pos (retrieved from model)
nExPos = 7;
// computing excitation position from X and Y
exPos = min((x*2-1 : abs),(y*2-1 : abs))*(nExPos-1) : int;

// ASSEMBLING MODELS
bells =
	(kb0k0status : pm.strikeModel(10,strikeCutoff,strikeSharpness,strikeGain) : pm.englishBellModel(nModes,exPos,t60,1,3)) +
	(kb0k1status : pm.strikeModel(10,strikeCutoff,strikeSharpness,strikeGain) : pm.frenchBellModel(nModes,exPos,t60,1,3)) +
	(kb1k0status : pm.strikeModel(10,strikeCutoff,strikeSharpness,strikeGain) : pm.germanBellModel(nModes,exPos,t60,1,2.5)) +
	(kb1k1status : pm.strikeModel(10,strikeCutoff,strikeSharpness,strikeGain) : pm.russianBellModel(nModes,exPos,t60,1,3)) :> *(0.2);

process = bells <: _,_;
