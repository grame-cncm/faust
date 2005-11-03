//-----------------------------------------------
// Audio tester : send a sinus to a loudspeaker
//-----------------------------------------------

import("music.lib");



// User interface
//----------------
smooth(c)		= *(1-c) : +~*(c);
vol 			= hslider("2-volume", -96, -96, 0, 0.1): db2linear : smooth(0.999);
freq 			= hslider("1-freq", 1000, 0, 24000, 0.1);
dest 			= hslider("3-destination", 0, 0, 8, 1);


process 		= vgroup( "Audio Tester", osc(freq) <: par(i,8, *(vol*(dest==i))) );
  
