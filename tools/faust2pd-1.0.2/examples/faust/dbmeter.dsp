declare name 		"dbmeter";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

//-------------------------------------------------
// A dB Vumeter
//-------------------------------------------------

import("math.lib");
import("music.lib");


vmeter(x)		= attach(x, envelop(x) : vbargraph("dB", -96, 10));
hmeter(x)		= attach(x, envelop(x) : hbargraph("dB", -96, 10));

envelop			= abs : max(db2linear(-96)) : linear2db : min(10)  : max ~ -(96.0/SR);

process 		= vmeter;