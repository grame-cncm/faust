
declare name "karplus -- Karplus-Strong string synth";
declare author "Yann Orlarey";
declare version "1.0";

import("music.lib");

// control variables

// master volume and pan
vol	= hslider("vol", 0.3, 0, 10, 0.01);	// %
pan	= hslider("pan", 0.5, 0, 1, 0.01);	// %

// excitator and resonator parameters
size	= hslider("samples", 512, 1, 1024, 1);	// #samples
dtime	= hslider("decay time", 4, 0, 10, 0.01);// -60db decay time

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

/* Karplus-Strong string synthesizer: */

process	= vgroup("1-excitator", noise*gain : *(gate : excitator))
	: vgroup("2-resonator", resonator(SR/freq)) : dcblocker
        : vgroup("3-master", *(vol) : panner(pan));
