//-----------------------------------------------
// 			Sinusoidal Oscillator 
//		(with linear interpolation)
//-----------------------------------------------

smooth(c)		= *(1-c) : +~*(c);
vol 			= hslider("volume (db)", 0, -96, 0, 0.1) : db2linear : smooth(0.999) ;
freq 			= hslider("freq", 1000, 0, 24000, 0.1);


process 		= vgroup("Oscillator", osci(freq) * vol);
