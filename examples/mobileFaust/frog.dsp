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
// Author: Romain Michon (rmichon_at_ccrma_dot_stanford_dot_edu)
// 06/17/2016
//########################################################################################

import("stdfaust.lib");


//========================= Smart Keyboard Configuration ================================= 
// (1 keyboards with 1 key configured as a pad.
//========================================================================================

declare interface "SmartKeyboard{
	'nKeyb':'1',
	'keyb0_nKeys':'1',
	'keyb0_keybMode':'0'
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
freq = x*(maxFreq-minFreq) + minFreq : si.polySmooth(gate,0.999,2);

maxQ = 40;
minQ = 1;
q = (1-y)*(maxQ-minQ) + minQ : si.smoo;
filterCutoff = cutoff : si.smoo; 


//============================================ DSP =======================================
//========================================================================================

process = sy.dubDub(freq,filterCutoff,q,gate);