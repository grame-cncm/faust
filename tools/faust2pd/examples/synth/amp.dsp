
/* Stereo amplifier stage with bass, treble, gain and balance controls and a
   dB meter. */

declare name "amp -- stereo amplifier stage";
declare author "Albert Graef";
declare version "1.0";

import("math.lib");
import("music.lib");

/* Fixed bass and treble frequencies. You might want to tune these for your
   setup. */

bass_freq	= 300;
treble_freq	= 1200;

/* Bass and treble gain controls in dB. The range of +/-20 corresponds to a
   boost/cut factor of 10. */

bass_gain	= nentry("bass", 0, -20, 20, 0.1);
treble_gain	= nentry("treble", 0, -20, 20, 0.1);

/* Gain and balance controls. */

gain		= db2linear(nentry("gain", 0, -96, 96, 0.1));
bal		= hslider("balance", 0, -1, 1, 0.001);

/* Balance a stereo signal by attenuating the left channel if balance is on
   the right and vice versa. I found that a linear control works best here. */

balance		= *(1-max(0,bal)), *(1-max(0,0-bal));

/* Generic biquad filter. */

filter(b0,b1,b2,a0,a1,a2)	= f : (+ ~ g)
with {
	f(x)	= (b0/a0)*x+(b1/a0)*x'+(b2/a0)*x'';
	g(y)	= 0-(a1/a0)*y-(a2/a0)*y';
};

/* Low and high shelf filters, straight from Robert Bristow-Johnson's "Audio
   EQ Cookbook", see http://www.musicdsp.org/files/Audio-EQ-Cookbook.txt. f0
   is the shelf midpoint frequency, g the desired gain in dB. S is the shelf
   slope parameter, we always set that to 1 here. */

low_shelf(f0,g)		= filter(b0,b1,b2,a0,a1,a2)
with {
	S  = 1;
	A  = pow(10,g/40);
	w0 = 2*PI*f0/SR;
	alpha = sin(w0)/2 * sqrt( (A + 1/A)*(1/S - 1) + 2 );

	b0 =    A*( (A+1) - (A-1)*cos(w0) + 2*sqrt(A)*alpha );
	b1 =  2*A*( (A-1) - (A+1)*cos(w0)                   );
	b2 =    A*( (A+1) - (A-1)*cos(w0) - 2*sqrt(A)*alpha );
	a0 =        (A+1) + (A-1)*cos(w0) + 2*sqrt(A)*alpha;
	a1 =   -2*( (A-1) + (A+1)*cos(w0)                   );
	a2 =        (A+1) + (A-1)*cos(w0) - 2*sqrt(A)*alpha;
};

high_shelf(f0,g)	= filter(b0,b1,b2,a0,a1,a2)
with {
	S  = 1;
	A  = pow(10,g/40);
	w0 = 2*PI*f0/SR;
	alpha = sin(w0)/2 * sqrt( (A + 1/A)*(1/S - 1) + 2 );

	b0 =    A*( (A+1) + (A-1)*cos(w0) + 2*sqrt(A)*alpha );
	b1 = -2*A*( (A-1) + (A+1)*cos(w0)                   );
	b2 =    A*( (A+1) + (A-1)*cos(w0) - 2*sqrt(A)*alpha );
	a0 =        (A+1) - (A-1)*cos(w0) + 2*sqrt(A)*alpha;
	a1 =    2*( (A-1) - (A+1)*cos(w0)                   );
	a2 =        (A+1) - (A-1)*cos(w0) - 2*sqrt(A)*alpha;
};

/* The tone control. We simply run a low and a high shelf in series here. */

tone		= low_shelf(bass_freq,bass_gain)
		: high_shelf(treble_freq,treble_gain);

/* Envelop follower. This is basically a 1 pole LP with configurable attack/
   release time. The result is converted to dB. You have to set the desired
   attack/release time in seconds using the t parameter below. */

t		= 0.1;			// attack/release time in seconds
g		= exp(-1/(SR*t));	// corresponding gain factor

env		= abs : *(1-g) : + ~ *(g) : linear2db;

/* Use this if you want the RMS instead. Note that this doesn't really
   calculate an RMS value (you'd need an FIR for that), but in practice our
   simple 1 pole IIR filter works just as well. */

rms		= sqr : *(1-g) : + ~ *(g) : sqrt : linear2db;
sqr(x)		= x*x;

/* The dB meters for left and right channel. These are passive controls. */

left_meter(x)	= attach(x, env(x) : hbargraph("left", -96, 10));
right_meter(x)	= attach(x, env(x) : hbargraph("right", -96, 10));

/* The main program. */

process		= hgroup("0-amp", hgroup("1-tone", tone, tone) :
				  hgroup("2-gain", (_*gain, _*gain)))
		: vgroup("3-balance", balance)
		: vgroup("4-meter", (left_meter, right_meter));
