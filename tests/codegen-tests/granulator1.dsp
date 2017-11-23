//-----------------------------------------------
//
// Parabolic Grain Envelop : from Ross Bencina
//
//-----------------------------------------------

import("music.lib");

//----------------------------------------------------------------------
// RINTEGRATE : Resetable integrator
// It integrates the values of x : 0, x(0), x(0)+x(1), x(0)+x(1)+x(2),...
// The integration is controled by a boolean <onoff> signal. When
// <onoff> is 1, values are integrated. When <onoff> is 0, the integration
// is stopped and the output value is reset to 0
//----------------------------------------------------------------------

rintegrate(onoff) 	= (+:*(onoff))~_ : mem;

//----------------------------------------------------------------------
// INTEGRATE : signal integrator
// It integrates the values of x : 0, x(0), x(0)+x(1), x(0)+x(1)+x(2),...
// The implementation is based on rintegrate with an onoff signal always
// on (i.e. 1).
//----------------------------------------------------------------------

integrate 		= rintegrate(1);

//----------------------------------------------------------------------
// Trigable Parabolic Grain Envelop :
// Multiply the incoming signal <sig> with a parabolic envelop of duration
// <sdur> samples and of amplitude <gamp>. The envelop is controled by a
// trigger boolean signal <trig>. An envelop is trigged when the <trig>
// become 1. Once trigged the envelop will continue until the end before
// being retriggable
//----------------------------------------------------------------------

grainenv(sdur, gamp, trig, sig) = (_|trig|trig' : amplitude : max(0)) ~ >(0) : *(sig)
	with {
		rdur 			= 1.0/sdur;
		rdur2 			= rdur*rdur;
		curve 			= -8.0 * gamp * rdur2;

		slope(on) 		= 4 * gamp * (rdur - rdur2) + rintegrate(on,curve);
		amplitude(on) 	= rintegrate(on, slope(on));
	};

//----------------------------------------------------------------------
// A grain
// <id> is the value that must be used by sel to trig the grain
// <po> is the delay (in samples) on the input signal
// <gdur> is the duration of the grain (in samples)
// <gamp> is the amplitude of the grain
// <sel> is the selection signal used to trig the grain. The grain is
// trigged when <sel> == <id>
// <sig> is the audio signal to process
//----------------------------------------------------------------------

grain(id, pos, gdur, gamp, sel, sig)
	= sig : delay10s(pos) : grainenv(gdur, gamp, (sel==id));

//----------------------------------------------------------------------
// A multi grain with a stereo output
// <num> the number of grains
// <tdur> the total duration over which the grains are distributed
// <gdur> is the duration of the grain (in samples)
// <gamp> is the amplitude of the grain
// <sel> is the selection signal used to trig the grains.
// <sig> is the audio signal to process
//----------------------------------------------------------------------

multigrain2(num, tdur, gdur, gamp, sel, sig)
	= sel, sig <: par(i,num, grain(i, tdur*i/num, gdur, gamp)) :> _,_;

//----------------------------------------------------------------------
//integer random numbers
// Generates integer random numbers between two values <lo> and <hi>
//----------------------------------------------------------------------

irnd(lo,hi) = int( (lo+hi)/2 + noise*(hi-lo)/2 );

//----------------------------------------------------------------------
// Sample and hold : the value is sampled when <t> is 1
// and hold when <t> is 0
//----------------------------------------------------------------------

SH(t) = *(t): +~*(1-t);

trig = (integrate(1) % 7 == 3);
selector_ = irnd(0, 20);

//process 	= integrate(1), slope(trig), max(0.0,bidule(trig));
//process 	= integrate(1), trig, grainenv(10, 2.8, trig, 1);
//process 	= integrate(1), selector, multigrain2(4, 100, 10, 1, selector, integrate(1));

//process = integrate(1), pulse(10), irnd(0,100), (irnd(0,100) : SH(pulse(10)));

vol = hslider("vol", 0, 0, 1, 0.01);
lim1 = hslider("lim1", 0, 0, 10000, 1);
lim2 = hslider("lim2", 0, 0, 10000, 1);

process = *(vol) : multigrain2( 32, 5*SR, SR/20, 1, (irnd(lim1,lim2) : SH(pulse(SR/137))) );

