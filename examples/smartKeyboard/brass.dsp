//############################### brass.dsp ###################################
// Faust instrument specifically designed for `faust2smartkeyb` where a
// trumpet physical model is controlled using some of the built-in sensors of
// the device and the touchscreen. Some of these elements could be replaced by
// external controllers (e.g., breath/mouth piece controller).
//
// ## `SmartKeyboard` Use Strategy
//
// 1 keyboard is used to implement the pistons of the trumpet (3 keys) and the
// other allows to control the lips tension.
//
// ## Compilation Instructions
//
// This Faust code will compile fine with any of the standard Faust targets.
// However it was specifically designed to be used with `faust2smartkeyb`. For
// best results, we recommend to use the following parameters to compile it:
//
// ```
// faust2smartkeyb [-ios/-android] -effect reverb.dsp brass.dsp
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
	'Keyboard 0 - Number of Keys':'1',
  'Keyboard 1 - Number of Keys':'3',
	'Keyboard 0 - Send Freq':'0',
  'Keyboard 1 - Send Freq':'0',
	'Keyboard 0 - Piano Keyboard':'0',
  'Keyboard 1 - Piano Keyboard':'0',
	'Keyboard 0 - Send Key X':'1',
	'Keyboard 1 - Send Key Status':'1',
	'Keyboard 0 - Static Mode':'1',
	'Keyboard 0 - Key 0 - Label':'Lips Tension',
	'Keyboard 1 - Key 0 - Label':'P1',
	'Keyboard 1 - Key 1 - Label':'P2',
	'Keyboard 1 - Key 2 - Label':'P3'
}";

import("stdfaust.lib");

// SMARTKEYBOARD PARAMS
kb0k0x = hslider("kb0k0x",0,0,1,1);
kb1k0status = hslider("kb1k0status",0,0,1,1) : min(1) : int;
kb1k1status = hslider("kb1k1status",0,0,1,1) : min(1) : int;
kb1k2status = hslider("kb1k2status",0,0,1,1) : min(1) : int;

// MODEL PARAMETERS
// pressure is controlled by accelerometer
pressure = hslider("pressure[acc: 1 1 -10 0 10]",0,0,1,0.01) : si.smoo;
breathGain = 0.005; breathCutoff = 2000;
vibratoFreq = 5; vibratoGain = 0;
//pitch when no pistons are pushed
basePitch = 48; // C4
// calculate pitch shift in function of piston combination
pitchShift =
  ((kb1k0status == 0) & (kb1k1status == 1) & (kb1k2status == 0))*(1) +
  ((kb1k0status == 1) & (kb1k1status == 0) & (kb1k2status == 0))*(2) +
  ((kb1k0status == 1) & (kb1k1status == 1) & (kb1k2status == 0))*(3) +
  ((kb1k0status == 0) & (kb1k1status == 1) & (kb1k2status == 1))*(4) +
  ((kb1k0status == 1) & (kb1k1status == 0) & (kb1k2status == 1))*(5) +
  ((kb1k0status == 1) & (kb1k1status == 1) & (kb1k2status == 1))*(6);
// tube length is calculated based on piston combination
tubeLength = basePitch-pitchShift : ba.midikey2hz : pm.f2l : si.smoo;
// lips tension is controlled using pad on screen
lipsTension = kb0k0x : si.smoo;
// default mute value
mute = 0.5;

// ASSEMBLING MODEL
model =
	pm.blower(pressure,breathGain,breathCutoff,vibratoFreq,vibratoGain) :
  pm.brassModel(tubeLength,lipsTension,mute);

process = model <: _,_;
