
/* Compressor unit. */

declare name "compressor -- compressor/limiter unit";
declare author "Albert Graef";
declare version "1.0";

import("music.lib");

/* Controls. */

// partition the controls into these three groups
comp_group(x)	= hgroup("1-compression", x);
env_group(x)	= vgroup("2-envelop", x);
gain_group(x)	= vgroup("3-gain", x);

// compressor controls: ratio, threshold and knee size
ratio		= comp_group(nentry("ratio", 2, 1, 20, 0.1));
threshold	= comp_group(nentry("threshold", -20, -96, 10, 0.1));
knee		= comp_group(nentry("knee", 3, 0, 20, 0.1));

// attack and release controls; clamped to a minimum of 1 sample
attack		= env_group(hslider("attack", 0.002, 0, 1, 0.001)) : max(1/SR);
release		= env_group(hslider("release", 0.5, 0, 10, 0.01)) : max(1/SR);

// gain controls: make-up gain, compression gain meter
makeup_gain	= gain_group(hslider("makeup gain", 0, -96, 96, 0.1));
gain(x)		= attach(x, x : gain_group(hbargraph("gain", -96, 0)));

/* Envelop detector. This is basically the same as in amp.dsp. */

t		= 0.1;
g		= exp(-1/(SR*t));
env		= abs : *(1-g) : + ~ *(g);
rms		= sqr : *(1-g) : + ~ *(g) : sqrt;
sqr(x)		= x*x;

/* Compute the envelop of a stereo signal. Replace env with rms if you want to
   use the RMS value instead. */

env2(x,y)	= max(env(x),env(y));

/* Compute the compression factor for the current input level. The gain is
   always 0 dB if we're below the reduced threshold, threshold-knee. Beyond
   the real threshold value the level is scaled by 1/ratio. Between these two
   extremes we return a convex combination of those factors. This is also
   known as "soft-knee" compression: the compression kicks in gradually at
   threshold-knee and reaches its full value at threshold. For special
   effects, you can also achieve old-school "hard-knee" compression by setting
   the knee value to zero. Also note that, before computing the gain, the
   input level is first smoothed out using a 1 pole IIR to prevent clicks when
   the input level changes abruptly. The attack and release times of this
   filter are configured with the corresponding envelop controls of the
   compressor. */

compress(env)	= level*(1-r)/r
with {
	// the (filtered) input level above the threshold
	level	= env : h ~ _ : linear2db : (_-threshold+knee) : max(0)
	with {
		h(x,y)	= f*x+(1-f)*y with { f = (x<y)*ga+(x>=y)*gr; };
		ga	= exp(-1/(SR*attack));
		gr	= exp(-1/(SR*release));
	};
	// the knee factor, clamped to 0..1; we add a small perturbation in
	// the denominator to prevent infinities and nan when knee<<1
	p	= level/(knee+eps) : max(0) : min(1) with { eps = 0.001; };
	// the actual compression ratio
	r	= 1-p+p*ratio;
};

process(x,y)	= (g*x,g*y)
with {
	g	= env2(x,y) : compress : gain : +(makeup_gain) : db2linear;
};
