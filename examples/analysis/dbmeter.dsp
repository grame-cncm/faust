declare name 		"dbmeter";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

//-------------------------------------------------
// A dB Vumeter
//-------------------------------------------------

import("stdfaust.lib");

process = hgroup("8 channels dB meter", par(i,8, vgroup("%i", vmeter(i) : null)))
with {
	null(x) = attach(0,x);
	envelop = abs : max(ba.db2linear(-70)) : ba.linear2db : min(10)  : max ~ -(80.0/ma.SR);
	vmeter(i, x) = attach(x, envelop(x) : vbargraph("chan %i[unit:dB]", -70, 10));
	hmeter(i, x) = attach(x, envelop(x) : hbargraph("chan %i[unit:dB]", -70, 10));
};
