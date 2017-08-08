//################################### midiOnly.dsp ######################################
// Faust instrument specifically designed for `faust2smartkeyb` implementing a MIDI
// controllable app where the mobile device's touch screen is used to control
// specific parameters of the synth continuously using two separate X/Y control surfaces.
//
// ## `SmartKeyboard` Use Strategy
//
// The `SmartKeyboard` configuration for this instrument consists in a single keyboard
// with two keys. Each key implements a control surface. `Piano Keyboard` mode is
// disabled so that key names are not displayed and that keys don't change color when
// touched. Finally, `Send Freq` is set to 0 so that new voices are not allocated by
// the touch screen and that the `freq` and `bend` parameters are not computed.
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

// Interface with 4 polyphnic keyboards of 13 keys with the same config
declare interface "SmartKeyboard{
	'Number of Keyboards':'1',
	'Keyboard 0 - Number of Keys':'2',
	'Keyboard 0 - Send Freq':'0',
	'Keyboard 0 - Piano Keyboard':'0',
	'Keyboard 0 - Static Mode':'1',
	'Keyboard 0 - Send Key X':'1',
	'Keyboard 0 - Key 0 - Label':'Mod Index',
	'Keyboard 0 - Key 1 - Label':'Mod Freq'
}";

import("stdfaust.lib");

f = hslider("freq",300,50,2000,0.01);
bend = hslider("bend[midi:pitchwheel]",1,0,10,0.01) : si.polySmooth(gate,0.999,1);
gain = hslider("gain",1,0,1,0.01);
key = hslider("key",0,0,1,1) : int;
kb0k0x = hslider("kb0k0x[midi:ctrl 1]",0.5,0,1,0.01) : si.smoo;
kb0k1x = hslider("kb0k1x[midi:ctrl 1]",0.5,0,1,0.01) : si.smoo;
s = hslider("sustain[midi:ctrl 64]",0,0,1,1);
t = button("gate");

// fomating parameters
gate = t+s : min(1);
freq = f*bend;
index = kb0k0x*1000;
modFreqRatio = kb0k1x;

envelope = gain*gate : si.smoo;

process = sy.fm((freq,freq + freq*modFreqRatio),index*envelope)*envelope <: _,_;
