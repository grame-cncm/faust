 import("music.lib");
 freq		= hslider("freq", 440, 20, 20000, 0.1);
 partial(i)	= osc(i*freq);
 process	= par(i, 5, partial(i));


 
