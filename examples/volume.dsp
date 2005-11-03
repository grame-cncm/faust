//-----------------------------------------------
// 			Volume control in dB
//-----------------------------------------------

import("music.lib");

smooth(c)	= *(1-c) : +~*(c);
gain		= vslider("gain", 0, -96, 4, 0.1) : db2linear : smooth(0.999);

process		= *(gain);
