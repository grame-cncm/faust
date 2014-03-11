
/* Stereo flanger with feedback. */

/* This is basically just a chorus with a different kind of LFO (triangle wave
   instead of sine), smaller delay times (typically 1-10 ms instead of 20-30
   ms) and (much) larger sweep depth, which makes this unit sound more like a
   time-varying filter (in fact, that's just what it is), in contrast to the
   gentle pitch modulation produced by a chorus.

   There's also an additional feedback loop which can be used to produce
   metallic sounds, and a stereo control which allows you to change the
   stereo spread (a.k.a. phase difference between left and right LFO).

   Note that you can actually make this unit sound pretty much like a chorus
   by cranking up the delay time while setting the feedback to zero and
   reducing level and depth (the latter by at least an order of magnitude). */

declare name "flanger -- stereo flanger with feedback";
declare author "Albert Graef";
declare version "1.0";

import("music.lib");

level			= hslider("level", 1, 0, 1, 0.01);
freq			= hslider("freq", 2, 0, 10, 0.01);
dtime			= hslider("delay", 0.002, 0, 0.04, 0.001);
depth			= hslider("depth", 0.5, 0, 1, 0.001);
feedback		= hslider("feedback", 0.1, 0, 1, 0.001);
stereo			= hslider("stereo", 1, 0, 1, 0.001);

tblosc(n,f,freq,mod)	= (1-d)*rdtable(n,wave,i&(n-1)) +
			  d*rdtable(n,wave,(i+1)&(n-1))
with {
	wave		= time*(2.0*PI)/n : f;
	phase		= freq/SR : (+ : decimal) ~ _;
	modphase	= decimal(phase+mod/(2*PI))*n;
	i		= int(floor(modphase));
	d		= decimal(modphase);
};

triangle(t)		= ((0<=t) & (t<=PI))*((2*t-PI)/PI) +
			  ((PI<t) & (t<=2*PI))*((3*PI-2*t)/PI);

flanger(dtime,freq,level,feedback,depth,phase,x)
			= (x+(loop(x)*level))/(1+level)
with {
	t	= SR*dtime/2*(1+depth*tblosc(1<<16, triangle, freq, phase));
	loop	= (+ : fdelay(1<<16, t)) ~ *(feedback);
};

process			= vgroup("flanger", (left, right))
with {
	left	= flanger(dtime,freq,level,feedback,depth,0);
	right	= flanger(dtime,freq,level,feedback,depth,stereo*PI);
};
