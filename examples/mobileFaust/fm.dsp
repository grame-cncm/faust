//###################################### fm.dsp ##########################################
// A simple smart phone percussion abstract sound toy based on an FM synth.
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
// mode resonance duration is controlled with the x axis of the accelerometer
modFreqRatio = hslider("res[acc: 0 0 -10 0 10]",1,0,2,0.01);


//=================================== Parameters Mapping =================================
//========================================================================================

// carrier frequency
minFreq = 80;
maxFreq = 500;
cFreq = x*(maxFreq-minFreq) + minFreq : si.polySmooth(gate,0.999,2);

// modulator frequency
modFreq = cFreq*modFreqRatio : si.smoo;

// modulation index
modIndex = y*100 : si.smoo;


//============================================ DSP =======================================
//========================================================================================

// since the generated sound is pretty chaotic, there is no need for an envelope generator
fmSynth = sy.fm((cFreq,modFreq),(modIndex))*gate;

process = fmSynth;