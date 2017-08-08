//################################### frog.dsp #####################################
// A simple smart phone abstract instrument than can be controlled using the touch
// screen and the accelerometers of the device.
//
// ## `SmartKeyboard` Use Strategy
//
// The idea here is to use the `SmartKeyboard` interface as an X/Y control pad by just
// creating one keyboard with on key and by retrieving the X and Y position on that single
// key using the `x` and `y` standard parameters. Keyboard mode is deactivated so that
// the color of the pad doesn't change when it is pressed.
//
// ## Compilation Instructions
//
// This Faust code will compile fine with any of the standard Faust targets. However
// it was specifically designed to be used with `faust2smartkeyb`. For best results,
// we recommend to use the following parameters to compile it:
//
// ```
// faust2smartkeyb [-ios/-android] frog.dsp
// ```
//
// ## Version/Licence
//
// Version 0.0, Feb. 2017
// Copyright Romain Michon CCRMA (Stanford University)/GRAME 2017
// MIT Licence: https://opensource.org/licenses/MIT
//########################################################################################

declare name "frog";

import("stdfaust.lib");

//========================= Smart Keyboard Configuration =================================
// (1 keyboards with 1 key configured as a pad.
//========================================================================================

declare interface "SmartKeyboard{
	'Number of Keyboards':'1',
	'Keyboard 0 - Number of Keys':'1',
	'Keyboard 0 - Piano Keyboard':'0',
	'Keyboard 0 - Static Mode':'1',
	'Keyboard 0 - Send X':'1',
	'Keyboard 0 - Send Y':'1'
}";

//================================ Instrument Parameters =================================
// Creates the connection between the synth and the mobile device
//========================================================================================

// SmartKeyboard X parameter
x = hslider("x",0,0,1,0.01);
// SmartKeyboard Y parameter
y = hslider("y",0,0,1,0.01);
// SmartKeyboard gate parameter
gate = button("gate");
// the cutoff frequency of the filter is controlled with the x axis of the accelerometer
cutoff = hslider("cutoff[acc: 0 0 -10 0 10]",2500,50,5000,0.01);

//=================================== Parameters Mapping =================================
//========================================================================================

maxFreq = 100;
minFreq = 1;
freq = x*(maxFreq-minFreq) + minFreq : si.polySmooth(gate,0.999,1);

maxQ = 40;
minQ = 1;
q = (1-y)*(maxQ-minQ) + minQ : si.smoo;
filterCutoff = cutoff : si.smoo;

//============================================ DSP =======================================
//========================================================================================

process = sy.dubDub(freq,filterCutoff,q,gate) <: _,_;
