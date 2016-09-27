//################################### trumpet.dsp #######################################
// A simple smart phone trumpet where pitch is controlled on the screen of the device,
// vibrato with the x axis of the accelerometer and amplitude with the y axis.
//
// ## `SmartKeyboard` Use Strategy
//
// The `SmartKeyboard` interface is used here to create to parallel keyboards in order
// for the performer to hold his device like a wind instruments (4 finges on each side
// of the screen and the 2 thumbs on the back of the device). The orientation of the 
// left (top) keyboard is inverted so that the lowest pitch is on the bottom right 
// corner of the screen (index finger of the right hand) and that the highest pitch
// is on the bottom left corner (index finger of the left hand).
//
// Author: Romain Michon (rmichon_at_ccrma_dot_stanford_dot_edu)
// 06/17/2016
//########################################################################################

import("stdfaust.lib");


//========================= Smart Keyboard Configuration ================================= 
// (2 keyboards, each has 7 keys, lowest key of top 
// keyboard is G3, lowest key of top keyboard is C3, both keyboards use a chromatic 
// scale, the orientation of the top keyboard is inverted, keys are quantized on both
// keyboards (integer only))
//========================================================================================

declare interface "SmartKeyboard{
	'nKeyb':'2',
	'keyb0_nKeys':'7',
	'keyb1_nKeys':'7',
	'keyb0_lowestKey':'67',
	'keyb1_lowestKey':'60',
	'keyb0_scale':'0',
	'keyb1_scale':'0',
	'keyb0_orientation':'1',
	'quantizationMode':'0'
}";


//================================ Instrument Parameters =================================
// Creates the connection between the synth and the mobile device
//========================================================================================

// smart keyboard frequency parameter
freq = hslider("freq",300,50,2000,0.01);
// vibrato controlled by accelerometer x axis
vibrato = hslider("vibrato[acc: 0 0 -10 0 10]",0,-1,1,0.01);
// smart keyboard gain parameter controlled by accelerometer y axis
gain = hslider("gain[acc: 1 0 -2 -2 10]",0,0,1,0.01);
// smart keyboard gate parameter
gate = button("gate");


//=================================== Parameters Mapping =================================
//========================================================================================

// As a ratio of freq...
vibratoAmplitude = 0.1;
// freq is modulated by vibrato and then smoothed to prevent clicks
synthFreq = freq+(vibrato*freq*vibratoAmplitude) : si.polySmooth(gate,0.999,2);

synthGain = gain : ba.lin2LogGain : si.smoo;


//============================================ DSP =======================================
//========================================================================================

process = sy.sawTrombone(synthFreq,synthGain,gate);