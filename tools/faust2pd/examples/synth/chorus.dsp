
/* Stereo chorus. */

declare name "chorus -- stereo chorus effect";
declare author "Albert Graef";
declare version "1.0";

import("music.lib");

level	= hslider("level", 0.5, 0, 1, 0.01);
freq	= hslider("freq", 3, 0, 10, 0.01);
dtime	= hslider("delay", 0.025, 0, 0.2, 0.001);
depth	= hslider("depth", 0.02, 0, 1, 0.001);

tblosc(n,f,freq,mod)	= (1-d)*rdtable(n,wave,i&(n-1)) +
			  d*rdtable(n,wave,(i+1)&(n-1))
with {
	wave	 	= time*(2.0*PI)/n : f;
	phase		= freq/SR : (+ : decimal) ~ _;
	modphase	= decimal(phase+mod/(2*PI))*n;
	i		= int(floor(modphase));
	d		= decimal(modphase);
};

chorus(dtime,freq,depth,phase,x)
			= x+level*fdelay(1<<16, t, x)
with {
	t		= SR*dtime/2*(1+depth*tblosc(1<<16, sin, freq, phase));
};

process			= vgroup("chorus", (left, right))
with {
	left		= chorus(dtime,freq,depth,0);
	right		= chorus(dtime,freq,depth,PI/2);
};
