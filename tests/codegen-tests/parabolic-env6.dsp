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
// <sdur> is the duration of the grain (in samples)
// <gamp> is the amplitude of the grain
// <sel> is the selection signal used to trig the grain. The grain is
// trigged when <sel> == <id>
// <sig> is the audio signal to process
//----------------------------------------------------------------------

grain(id, pos, sdur, gamp, sel, sig)
	= sig : delay10s(pos) : grainenv(sdur, gamp, (sel==id));

trig = (integrate(1) % 7 == 3);
selector_ = integrate(1) % 7;

//process 	= integrate(1), slope(trig), max(0.0,bidule(trig));
//process 	= integrate(1), trig, grainenv(10, 2.8, trig, 1);
process 	= integrate(1), trig, grain(3, 2, 10, 1, selector_, integrate(1));
