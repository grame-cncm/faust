//-----------------------------------------------
// 			Volume Fader in dB
//-----------------------------------------------

smooth(c)	= *(1-c) : +~*(c);
level		= hslider("level (db)", 0, -96, 4, 0.1) : db2linear : smooth(0.999);

process		= vgroup("Fader", *(level));
