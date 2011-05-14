
/* A simple "chimes" patch, using a bank of resonz filters (cf. Steiglitz, DSP
   Primer, pp. 89f.). */

declare name "chimes -- chimes synth using a bank of resonz filters";
declare author "Albert Graef";
declare version "2.0";

import("music.lib");

/* Control variables: */

// master volume, pan
vol		= hslider("vol", 0.5, 0, 10, 0.01);		// %
pan		= hslider("pan", 0.5, 0, 1, 0.01);		// %

// excitator and resonator parameters

// excitator decay time [sec]
xdecay		= nentry("decay", 0.01, 0, 1, 0.001);

// resonator #0
hrm0		= nentry("harmonic0", 1, 0, 50, 0.001);		// harmonic
amp0		= nentry("amplitude0", 0.167, 0, 1, 0.001);	// amplitude
decay0		= nentry("decay0", 3.693, 0, 10, 0.001);	// decay time
rq0		= nentry("rq0", 0.002, 0, 1, 0.0001);		// filter 1/Q
// resonator #1
hrm1		= nentry("harmonic1", 3.007, 0, 50, 0.001);	// harmonic
amp1		= nentry("amplitude1", 0.083, 0, 1, 0.001);	// amplitude
decay1		= nentry("decay1", 2.248, 0, 10, 0.001);	// decay time
rq1		= nentry("rq1", 0.002, 0, 1, 0.0001);		// filter 1/Q
// resonator #2
hrm2		= nentry("harmonic2", 4.968, 0, 50, 0.001);	// harmonic
amp2		= nentry("amplitude2", 0.087, 0, 1, 0.001);	// amplitude
decay2		= nentry("decay2", 2.828, 0, 10, 0.001);	// decay time
rq2		= nentry("rq2", 0.002, 0, 1, 0.0001);		// filter 1/Q
// resonator #3
hrm3		= nentry("harmonic3", 8.994, 0, 50, 0.001);	// harmonic
amp3		= nentry("amplitude3", 0.053, 0, 1, 0.001);	// amplitude
decay3		= nentry("decay3", 3.364, 0, 10, 0.001);	// decay time
rq3		= nentry("rq3", 0.002, 0, 1, 0.0001);		// filter 1/Q
// resonator #4
hrm4		= nentry("harmonic4", 12.006, 0, 50, 0.001);	// harmonic
amp4		= nentry("amplitude4", 0.053, 0, 1, 0.001);	// amplitude
decay4		= nentry("decay4", 2.488, 0, 10, 0.001);	// decay time
rq4		= nentry("rq4", 0.002, 0, 1, 0.0001);		// filter 1/Q

// frequency, gain, gate
freq		= nentry("freq", 440, 20, 20000, 1);		// Hz
gain		= nentry("gain", 1, 0, 10, 0.01);		// %
gate		= button("gate");				// 0/1

/* Definition of the resonz filter. This is basically a biquad filter with
   pairs of poles near the desired resonance frequency and zeroes at -1 and
   +1. See Steiglitz for details. */

resonz(R,freq)	= f : (+ ~ g)
with {
	f(x)	= a*(x-x');		// feedforward function (two zeros)
	g(y)	= 2*R*c*y - R*R*y';	// feedback function (two poles)
	w	= 2*PI*freq/SR;		// freq in rad per sample period
	c	= 2*R/(1+R*R)*cos(w);	// cosine of pole angle
	s	= sqrt (1-c*c);		// sine of pole angle
	a	= (1-R*R)*s;		// factor to normalize resonance
};

/* The excitator, a short burst of noise. */

excitator(t)	= t : hgroup("1-excitator", adsr(0, xdecay, 0, 0) : *(noise));

/* Bank of 5 resonators. */

resonator(f,t,i,hrm,amp,decay,rq)
		= (f,t,_) : hgroup("2-resonator-%i", g)
with {
	g(f,t)	= resonz(R,h)*(amp*b*env)
	with {
		h	= hrm*f;	// harmonic
		B	= rq*f/SR;	// bandwidth, as fraction of sample rate
		R	= 1-PI*B;	// resonance (pole radius)
		b	= 1/(2*B);	// boost factor = Nyquist/bandwidth
		env	= adsr(0, decay, 0, 0, t);	// envelop
	};
};

resonators(f,t)	= resonator(f,t,0,hrm0,amp0,decay0,rq0)
		+ resonator(f,t,1,hrm1,amp1,decay1,rq1)
		+ resonator(f,t,2,hrm2,amp2,decay2,rq2)
		+ resonator(f,t,3,hrm3,amp3,decay3,rq3)
		+ resonator(f,t,4,hrm4,amp4,decay4,rq4);

/* The synth. */

process		= excitator(gate)*gain <: resonators(freq, gate)
		: vgroup("3-master", *(vol) : panner(pan));
