// exemple de schema illisible

 import("music.lib");
 freq		= hslider("freq", 440, 20, 20000, 0.1);
 partial(i)	= osc(i*freq);
 partial0	= osc(0*freq);
 partial1	= osc(1*freq);
 partial2	= osc(2*freq);
 process	= partial(0), partial1, partial(2);

