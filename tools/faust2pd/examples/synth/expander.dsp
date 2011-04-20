
/* Expander unit. */

/* This is pretty much the same as compressor.dsp, but here the given ratio is
   applied to *attenuate* levels *below* the threshold. */

declare name "expander -- expander/noise gate unit";
declare author "Albert Graef";
declare version "1.0";

import("music.lib");

/* Controls. */

exp_group(x)	= hgroup("1-expander", x);
env_group(x)	= vgroup("2-envelop", x);
gain_group(x)	= vgroup("3-gain", x);

ratio		= exp_group(nentry("ratio", 2, 1, 20, 0.1));
threshold	= exp_group(nentry("threshold", -40, -96, 10, 0.1));
knee		= exp_group(nentry("knee", 3, 0, 20, 0.1));

attack		= env_group(hslider("attack", 0.001, 0, 1, 0.001)) : max(1/SR);
release		= env_group(hslider("release", 0.1, 0, 10, 0.01)) : max(1/SR);

gain(x)		= attach(x, x : gain_group(hbargraph("gain", -96, 0)));

t		= 0.1;
g		= exp(-1/(SR*t));
env		= abs : *(1-g) : + ~ *(g);
rms		= sqr : *(1-g) : + ~ *(g) : sqrt;
sqr(x)		= x*x;

env2(x,y)	= max(env(x),env(y));

expand(env)	= level*(1-r)
with {
	level	= env : h ~ _ : linear2db : (threshold+knee-_) : max(0)
	with {
		h(x,y)	= f*x+(1-f)*y with { f = (x<y)*ga+(x>=y)*gr; };
		ga	= exp(-1/(SR*attack));
		gr	= exp(-1/(SR*release));
	};
	p	= level/(knee+eps) : max(0) : min(1) with { eps = 0.001; };
	r	= 1-p+p*ratio;
};

process(x,y)	= (g*x,g*y)
with {
	g	= env2(x,y) : expand : gain : db2linear;
};
