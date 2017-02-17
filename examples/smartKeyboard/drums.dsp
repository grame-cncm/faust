//##################################### drums.dsp ########################################
// Faust instrument specifically designed for `faust2smartkeyb` where 3 drums can
// be controlled using pads. The X/Y postion of fingers is detected on each key
// and use to control the strike postion on the virtual membrane.
//
// ## `SmartKeyboard` Use Strategy
//
// The drum physical model used here is implemented to be generic so that its
// fundamental frequency can be changed for each voice. `SamrtKeyboard` is used
// in polyphonic mode so each new strike on the interface corresponds to a new
// new voice.
//
// ## Compilation Instructions
//
// This Faust code will compile fine with any of the standard Faust targets. However
// it was specifically designed to be used with `faust2smartkeyb`. For best results,
// we recommend to use the following parameters to compile it:
//
// ```
// faust2smartkeyb [-ios/-android] -effect reverb.dsp drums.dsp
// ```
//
// ## Version/Licence
//
// Version 0.0, Feb. 2017
// Copyright Romain Michon CCRMA (Stanford University)/GRAME 2017
// MIT Licence: https://opensource.org/licenses/MIT
//########################################################################################

// Interface with 2 keyboards of 2 and 1 keys (3 pads)
// Static mode is used so that keys don't change color when touched
// Note labels are hidden
// Piano Keyboard mode is deactivated so all the keys look the same
declare interface "SmartKeyboard{
	'Number of Keyboards':'2',
	'Keyboard 0 - Number of Keys':'2',
	'Keyboard 1 - Number of Keys':'1',
	'Keyboard 0 - Static Mode':'1',
	'Keyboard 1 - Static Mode':'1',
	'Keyboard 0 - Piano Keyboard':'0',
	'Keyboard 1 - Piano Keyboard':'0',
	'Keyboard 0 - Key 0 - Label':'High',
	'Keyboard 0 - Key 1 - Label':'Mid',
	'Keyboard 1 - Key 0 - Label':'Low'
}";

import("stdfaust.lib");

// standard parameters
gate = button("gate");
x = hslider("x",1,0,1,0.001);
y = hslider("y",1,0,1,0.001);
keyboard = hslider("keyboard",0,0,1,1) : int;
key = hslider("key",0,0,1,1) : int;

// drum modal physical model
drum = excitation <: par(i,N,mode(i,baseFreq,t60Scaler)) :> *(outGain)
with{
	// number of modes
	N = 20;
	// angle
	theta = 0;
	// resonance duration
	t60Scaler = 1;
	// frequency of the lowest drum
	bFreq = 60;
	// output gain (should be changed in function of the number of drums and modes)
	outGain = 0.1;
	// excitation position
	exPos = min((x*2-1 : abs),(y*2-1 : abs));
	// retrieving pad number (0-2)
	j = 2-(keyboard*2+key);
	// drum root freq is computed in function of pad number
	baseFreq = bFreq*(j+1);
	// computing the gain of each filter
	inGains(i) = cos((i+1)*theta)/float(i+1);
	// computing each modes, why is this done like this, cus it sounds goooood...
	mode(i,baseFreq,t60) = *(inGains(i)) : modeFilter(baseFreq+(200*i),(N-i)*t60*0.03)*(1/(i+1))
	with{
		// biquad taking freq and t60 as arguments
		modeFilter(f,t60) = fi.tf2(b0,b1,b2,a1,a2)
		with{
			b0 = 1;
			b1 = 0;
			b2 = -1;
			w = 2*ma.PI*f/ma.SR;
			r = pow(0.001,1/float(t60*ma.SR));
			a1 = -2*r*cos(w);
			a2 = r^2;
		};
	};

	// excitation: filtered noise burst. filters change in function of x/y position
	excitation = noiseburst : fi.highpass(2,40+exPos*500) : fi.lowpass(2,500+exPos*15000)
	with{
		// noise excitation
		noiseburst = no.noise : *(gate : ba.impulsify : trigger(P))
		with {
			 P = ma.SR/300;
  		 	 diffgtz(x) = x != x';
  		 	 decay(n,x) = x - (x>0)/n;
  		 	 release(n) = + ~ decay(n);
  		 	 trigger(n) = diffgtz : release(n) : > (0.0);
		};
	};
};

process = drum <: _,_;
