//-----------------------------------------------
// 			Sinusoidal Oscillator
//-----------------------------------------------


// User interface
//----------------
vol 			= hslider("volume", 0, 0, 1, 0.001);
freq 			= hslider("freq", 1000, 0, 24000, 0.1);


process 		= osc(freq) * vol;
