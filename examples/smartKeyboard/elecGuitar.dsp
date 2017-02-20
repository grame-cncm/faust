//################################### elecGuitar.dsp #####################################
// Faust instruments specifically designed for `faust2smartkeyb` where an electric
// guitar physical model is controlled using an isomorphic keyboard. Rock on! 
//
// ## `SmartKeyboard` Use Strategy
//
// we want to create an isomorphic keyboard where each keyboard is monophonic and
// implements a "string". Keyboards should be one fourth apart from each other
// (more or less like on a guitar). We want to be able to slide between keyboards
// (strum) to trigger a new note (voice) and we want new fingers on a keyboard to
// "steal" the pitch from the previous finger (sort of hammer on).
//
// ## Compilation Instructions
//
// This Faust code will compile fine with any of the standard Faust targets. However
// it was specifically designed to be used with `faust2smartkeyb`. For best results,
// we recommend to use the following parameters to compile it:
//
// ```
// faust2smartkeyb [-ios/-android] -effect elecGuitarEffecr.dsp elecGuitar.dsp
// ```
//
// ## Version/Licence
//
// Version 0.0, Feb. 2017
// Copyright Romain Michon CCRMA (Stanford University)/GRAME 2017:
// https://ccrma.stanford.edu/~rmichon
// MIT Licence: https://opensource.org/licenses/MIT
//########################################################################################

// Interface with 6 monophonic keyboards one fourth apart from each other 
declare interface "SmartKeyboard{
	'Number of Keyboards':'6',
	'Max Keyboard Polyphony':'1',
	'Keyboard 0 - Number of Keys':'13',
	'Keyboard 1 - Number of Keys':'13',
	'Keyboard 2 - Number of Keys':'13',
	'Keyboard 3 - Number of Keys':'13',
	'Keyboard 4 - Number of Keys':'13',
	'Keyboard 5 - Number of Keys':'13',
	'Keyboard 0 - Lowest Key':'72',
	'Keyboard 1 - Lowest Key':'67',
	'Keyboard 2 - Lowest Key':'62',
	'Keyboard 3 - Lowest Key':'57',
	'Keyboard 4 - Lowest Key':'52',
	'Keyboard 5 - Lowest Key':'47',
	'Rounding Mode':'2'
}";

import("stdfaust.lib");

// standard parameters
f = hslider("freq",300,50,2000,0.01);
bend = hslider("bend[midi:pitchwheel]",1,0,10,0.01) : si.polySmooth(gate,0.999,1);
gain = hslider("gain",1,0,1,0.01);
s = hslider("sustain[midi:ctrl 64]",0,0,1,1); // for sustain pedal
t = button("gate");

// mapping params
gate = t+s : min(1);
freq = f*bend : max(60); // min freq is 60 Hz

// noise excitation triggered by gate, the excitation duration is controlled
// by breq
noiseburst = no.noise : *(gate : ba.impulsify : trigger(P))
with {
	 P = ma.SR/(freq+300);
  	 diffgtz(x) = x != x';
  	 decay(n,x) = x - (x>0)/n;
  	 release(n) = + ~ decay(n);
  	 trigger(n) = diffgtz : release(n) : > (0.0);
};

// string waveguide with fractional delay
string = +~(de.fdelay4(2048,n) : bridge(brightness,resDuration))
with{
	// string parameters
	brightness = 0.3; // (0-1)
	resDuration = 8*(gate : si.smoo); // in secs
	n = ma.SR/freq;

	// bridge reflection filter
	bridge(B,t60,x) = dampingFilter(rho,h0,h1,x)
	with{
		dampingFilter(rho,h0,h1,x) = rho * (h0 * x' + h1*(x+x''));
		h0 = (1.0 + B)/2;
		h1 = (1.0 - B)/4;
		rho = pow(0.001,1.0/(freq*t60));
	};
};

// putting it all together
process = noiseburst : fi.lowpass(2,freq*5) : string <: _,_;
