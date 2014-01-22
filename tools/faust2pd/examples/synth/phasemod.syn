
declare name "phasemod -- phase modulation synth";
declare author "Albert Graef";
declare version "1.0";

import("music.lib");

// control variables

// master volume and pan
vol	= hslider("vol", 0.3, 0, 10, 0.01);	// %
pan	= hslider("pan", 0.5, 0, 1, 0.01);	// %

// ADSR envelop
attack	= hslider("attack", 0.01, 0, 1, 0.001);	// sec
decay	= hslider("decay", 0.3, 0, 1, 0.001);	// sec
sustain = hslider("sustain", 0.5, 0, 1, 0.01);	// %
release = hslider("release", 0.2, 0, 1, 0.001);	// sec

// voice parameters
freq	= nentry("freq", 440, 20, 20000, 1);	// Hz
gain	= nentry("gain", 1, 0, 10, 0.01);	// %
gate	= button("gate");			// 0/1

// generic table-driven oscillator with phase modulation

// n	= the size of the table, must be a power of 2
// f	= the wave function, must be defined on the range [0,2*PI]
// freq	= the desired frequency in Hz
// mod	= the phase modulation signal, in radians

tblosc(n,f,freq,mod)	= (1-d)*rdtable(n,wave,i&(n-1)) +
			  d*rdtable(n,wave,(i+1)&(n-1))
with {
	wave	 	= time*(2.0*PI)/n : f;
	phase		= freq/SR : (+ : decimal) ~ _;
	modphase	= decimal(phase+mod/(2*PI))*n;
	i		= int(floor(modphase));
	d		= decimal(modphase);
};

// phase modulation synth (sine modulated by another sine)

smooth(c) = *(1-c) : +~*(c);

process	= tblosc(1<<16, sin, freq, mod) * env * (gain:smooth(0.999))
  :  vgroup("2-master", *(vol) : panner(pan))
with {
	env = gate : vgroup("1-adsr", adsr(attack, decay, sustain, release));
	mod = 2*PI*tblosc(1<<16, sin, freq, 0)*env;
};
