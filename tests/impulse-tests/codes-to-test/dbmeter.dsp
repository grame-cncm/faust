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


vmeter(x)		= attach(x, envelop(x) : vbargraph("[unit:dB]", -70, 10));
hmeter(x)		= attach(x, envelop(x) : hbargraph("[unit:dB]", -70, 10));

envelop			= abs : max(db2linear(-70)) : linear2db : min(10)  : max ~ -(80.0/SR);
null(x)         = attach(0,x);
process 		= hgroup("8 channels dB meter", par(i,8, vgroup("%i", vmeter : null)));