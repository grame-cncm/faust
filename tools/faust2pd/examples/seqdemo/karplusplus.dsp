
declare name "karplusplus -- Karplus-Strong + Fuzz";
declare author "Yann Orlarey, Albert Graef";
declare version "1.0";

import("music.lib");

// control variables

// master volume and pan
vol	= hslider("vol", 0.3, 0, 10, 0.01);	// %
pan	= hslider("pan", 0.5, 0, 1, 0.01);	// %

// excitator and resonator parameters
size	= hslider("samples", 512, 1, 1024, 1);	// #samples
dtime	= hslider("decay time", 4, 0, 10, 0.01);// -60db decay time

// fuzz parameters
drive	= hslider("drive", 0, 0, 50, 0.1);	// overdrive factor
res	= hslider("res", 0, 0, 20, 0.1);	// filter resonance
tone	= hslider("tone", 20, 1, 20, 0.1);	// filter cutoff harmonic
level	= hslider("level", 1, 0, 10, 0.01);	// output gain (%)

// voice parameters
freq	= nentry("freq", 440, 20, 20000, 1);	// Hz
gain	= nentry("gain", 1, 0, 10, 0.01);	// %
gate	= button("gate");			// 0/1

/* The excitator: */

upfront(x) 	= (x-x') > 0.0;
decay(n,x)	= x - (x>0)/n;
release(n)	= + ~ decay(n);
trigger(n) 	= upfront : release(n) : >(0.0) : +(leak);
leak		= 1.0/65536.0; // avoid denormals on Pentium
excitator	= trigger(size);

/* The resonator: */

average(x)	= (x+x')/2;
att(d,t)	= 1-1/pow(db2linear(60), d/(SR*t));
comb(d,a)	= (+ : fdelay(4096, d-1.5)) ~ (average : *(1.0-a));
resonator(d)	= comb(d,att(d,dtime));

/* DC blocker (see http://ccrma.stanford.edu/~jos/filters/DC_Blocker.html): */

dcblocker(x)	= (x-x') : (+ ~ *(0.995));

// resonant lowpass

// This is a tweaked Butterworth filter by David Werner and Patrice Tarrabia,
// see http://www.musicdsp.org and http://www.experimentalscene.com for
// details.

// res = resonance in dB above DC gain
// freq = cutoff frequency

lowpass(res,freq)	= f : (+ ~ g) : *(a)
with {
	f(x)	= a0*x+a1*x'+a2*x'';
	g(y)	= 0-b1*y-b2*y';
	a	= 1/db2linear(0.5*res);

	c	= 1.0/tan(PI*(freq/SR));
	c2	= c*c;
	r	= 1/db2linear(2.0*res);
	q	= sqrt(2.0)*r;
	a0	= 1.0/(1.0+(q*c)+(c2));
	a1	= 2.0*a0;
	a2	= a0;
	b1	= 2.0*a0*(1.0-c2);
	b2	= a0*(1.0-q*c+c2);
};

/* Fuzz effect. */

clip(x)		= f*x+1-f with { f = abs(drive*x)<=1; };
fuzz(freq)	= clip : lowpass(res,tone*freq) : *(level);

/* Karplus-Strong string synthesizer: */

process	= vgroup("1-excitator", noise*gain : *(gate : excitator))
	: vgroup("2-resonator", resonator(SR/freq)) : dcblocker
        : vgroup("3-fuzz", fuzz(freq))
        : vgroup("4-master", *(vol) : panner(pan));
