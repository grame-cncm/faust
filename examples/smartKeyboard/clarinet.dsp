//############################### clarinet.dsp #################################
// Faust instrument specifically designed for `faust2smartkeyb` where a
// clarinet physical model is controlled by an interface implementing
// fingerings similar to that of a the real instrument. The pressure of the
// breath in the mouthpiece of the clarinet is controlled by blowing on the
// built-in microphone of the device.
//
// ## `SmartKeyboard` Use Strategy
//
// The device is meant to be held with 2 hands vertically in order to put all
// fingers on the screen at the same time. Key combinations determine the
// pitch of the instrument. A single voice is constantly ran.
//
// ## Compilation Instructions
//
// This Faust code will compile fine with any of the standard Faust targets.
// However it was specifically designed to be used with `faust2smartkeyb`. For
// best results, we recommend to use the following parameters to compile it:
//
// ```
// faust2smartkeyb [-ios/-android] clarinet.dsp
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
	'Keyboard 0 - Number of Keys':'4',
  'Keyboard 1 - Number of Keys':'5',
	'Keyboard 0 - Send Freq':'0',
  'Keyboard 1 - Send Freq':'0',
	'Keyboard 0 - Piano Keyboard':'0',
  'Keyboard 1 - Piano Keyboard':'0',
	'Keyboard 0 - Send Key Status':'1',
	'Keyboard 1 - Send Key Status':'1',
	'Keyboard 0 - Key 3 - Label':'O+',
	'Keyboard 1 - Key 4 - Label':'O-'
}";

import("stdfaust.lib");

// SMARTKEYBOARD PARAMS
kb0k0status = hslider("kb0k0status",0,0,1,1) : min(1) : int;
kb0k1status = hslider("kb0k1status",0,0,1,1) : min(1) : int;
kb0k2status = hslider("kb0k2status",0,0,1,1) : min(1) : int;
kb0k3status = hslider("kb0k3status",0,0,1,1) : min(1) : int;
kb1k0status = hslider("kb1k0status",0,0,1,1) : min(1) : int;
kb1k1status = hslider("kb1k1status",0,0,1,1) : min(1) : int;
kb1k2status = hslider("kb1k2status",0,0,1,1) : min(1) : int;
kb1k3status = hslider("kb1k3status",0,0,1,1) : min(1) : int;
kb1k4status = hslider("kb1k4status",0,0,1,1) : min(1) : int;

// MODEL PARAMETERS
reedStiffness = hslider("reedStiffness[acc: 1 1 -10 0 10]",0,0,1,0.01) : si.smoo;
basePitch = 73; // C#4
pitchShift = // calculate pitch shfit in function of "keys" combination
  ((kb0k0status == 0) & (kb0k1status == 1) & (kb0k2status == 0) &
		(kb1k0status == 0) & (kb1k1status == 0) & (kb1k2status == 0) &
		(kb1k3status == 0))*(-1) + // C
	((kb0k0status == 1) & (kb0k1status == 0) & (kb0k2status == 0) &
		(kb1k0status == 0) & (kb1k1status == 0) & (kb1k2status == 0) &
		(kb1k3status == 0))*(-2) + // B
	((kb0k0status == 1) & (kb0k1status == 0) & (kb0k2status == 1) &
		(kb1k0status == 0) & (kb1k1status == 0) & (kb1k2status == 0) &
		(kb1k3status == 0))*(-3) + // Bb
	((kb0k0status == 1) & (kb0k1status == 1) & (kb0k2status == 0) &
		(kb1k0status == 0) & (kb1k1status == 0) & (kb1k2status == 0) &
		(kb1k3status == 0))*(-4) + // A
	((kb0k0status == 1) & (kb0k1status == 1) & (kb0k2status == 0) &
		(kb1k0status == 1) & (kb1k1status == 0) & (kb1k2status == 0) &
		(kb1k3status == 0))*(-5) + // G#
	((kb0k0status == 1) & (kb0k1status == 1) & (kb0k2status == 1) &
		(kb1k0status == 0) & (kb1k1status == 0) & (kb1k2status == 0) &
		(kb1k3status == 0))*(-6) + // G
	((kb0k0status == 1) & (kb0k1status == 1) & (kb0k2status == 1) &
		(kb1k0status == 0) & (kb1k1status == 1) & (kb1k2status == 0) &
		(kb1k3status == 0))*(-7) + // F#
	((kb0k0status == 1) & (kb0k1status == 1) & (kb0k2status == 1) &
		(kb1k0status == 1) & (kb1k1status == 0) & (kb1k2status == 0) &
		(kb1k3status == 0))*(-8) + // F
	((kb0k0status == 1) & (kb0k1status == 1) & (kb0k2status == 1) &
		(kb1k0status == 1) & (kb1k1status == 1) & (kb1k2status == 0) &
		(kb1k3status == 0))*(-9) + // E
	((kb0k0status == 1) & (kb0k1status == 1) & (kb0k2status == 1) &
		(kb1k0status == 1) & (kb1k1status == 1) & (kb1k2status == 0) &
		(kb1k3status == 1))*(-10) + // Eb
	((kb0k0status == 1) & (kb0k1status == 1) & (kb0k2status == 1) &
		(kb1k0status == 1) & (kb1k1status == 1) & (kb1k2status == 1) &
		(kb1k3status == 0))*(-11) + // D
	((kb0k0status == 0) & (kb0k1status == 0) & (kb0k2status == 0) &
		(kb1k0status == 0) & (kb1k1status == 0) & (kb1k2status == 0) &
		(kb1k3status == 1))*(-12) + // C#
	((kb0k0status == 1) & (kb0k1status == 1) & (kb0k2status == 1) &
		(kb1k0status == 1) & (kb1k1status == 1) & (kb1k2status == 1) &
		(kb1k3status == 1))*(-13); // C
octaveShiftUp = +(kb0k3status : ba.impulsify)~_; // counting up
octaveShiftDown = +(kb1k4status : ba.impulsify)~_; // counting down
octaveShift = (octaveShiftUp-octaveShiftDown)*(12);
// tube length is just smoothed: could be improved
tubeLength = basePitch+pitchShift+octaveShift : ba.midikey2hz : pm.f2l : si.smoo;
bellOpening = 0.5;

// ASSEMBLING MODEL
model(pressure) = pm.clarinetModel(tubeLength,pressure,reedStiffness,bellOpening);

// pressure is estimated from mic signal
process = an.amp_follower_ud(0.02,0.02)*0.7 : model <: _,_;
