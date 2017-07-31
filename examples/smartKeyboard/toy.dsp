//##################################### toy.dsp #######################################
// Faust sound toy specifically designed for `faust2smartkeyb` where a funny
// synth can be controlled using several fingers on the screen and the built-in
// accelerometer.
//
// ## `SmartKeyboard` Use Strategy
//
// We just want a blank screen where the position of the different fingers on
// the screen can be tracked and retrieved in the Faust object. For that, we
// create one keyboard with one key, that should fill the screen. We ask the
// interface to not compute the `freq` and `bend` parameters to save
// computation by setting `'Keyboard 0 - Send Freq':'0'`. We don't want the
// color of the key to change when it is touched so we deactivate the
// `Piano Keyboard` mode. Fingers should be numbered to be able to use the
// numbered `x` and `y` parameters (`x0`, `y0`, `x1`, etc.), so `Count Fingers`
// is enabled. Finally, by setting `Max Keyboard Polyphony` to 0, we deactivate
// the voice allocation system and we automatically start a voice when the app
// is launched. This means that fingers are no longer associated to specific voices.
//
// ## Compilation Instructions
//
// This Faust code will compile fine with any of the standard Faust targets. However
// it was specifically designed to be used with `faust2smartkeyb`. For best results,
// we recommend to use the following parameters to compile it:
//
// ```
// faust2smartkeyb [-ios/-android] toy.dsp
// ```
//
// ## Version/Licence
//
// Version 0.0, Feb. 2017
// Copyright Romain Michon CCRMA (Stanford University)/GRAME 2017:
// https://ccrma.stanford.edu/~rmichon
// MIT Licence: https://opensource.org/licenses/MIT
//########################################################################################

// X/Y interface: one keyboard with one key
// freq and bend are not computed
// fingers are counted
// voice is launched on startup
declare interface "SmartKeyboard{
	'Number of Keyboards':'1',
	'Max Keyboard Polyphony':'0',
	'Keyboard 0 - Number of Keys':'1',
	'Keyboard 0 - Send Freq':'0',
	'Keyboard 0 - Static Mode':'1',
	'Keyboard 0 - Piano Keyboard':'0',
	'Keyboard 0 - Send Numbered X':'1',
	'Keyboard 0 - Send Numbered Y':'1'
}";

import("stdfaust.lib");

// parameters
x0 = hslider("x0",0.5,0,1,0.01) : si.smoo;
y0 = hslider("y0",0.5,0,1,0.01) : si.smoo;
y1 = hslider("y1",0,0,1,0.01) : si.smoo;
q = hslider("q[acc: 0 0 -10 0 10]",30,10,50,0.01) : si.smoo;
del = hslider("del[acc: 0 0 -10 0 10]",0.5,0.01,1,0.01) : si.smoo;
fb = hslider("fb[acc: 1 0 -10 0 10]",0.5,0,1,0.01) : si.smoo;

// mapping
impFreq = 2 + x0*20;
resFreq = y0*3000+300;

// simple echo effect
echo = +~(de.delay(65536,del*ma.SR)*fb);

// putting it together
process = os.lf_imptrain(impFreq) : fi.resonlp(resFreq,q,1) : echo : ef.cubicnl(y1,0)*0.95 <: _,_;
