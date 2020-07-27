declare name 		"vumeter";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

//-------------------------------------------------
// Simple vumeter
//-------------------------------------------------

import("stdfaust.lib");

process = hmeter(0), hmeter(1)
with {
	vmeter(i, x) = attach(x, envelop(x) : vbargraph("chan %i[2][unit:dB]", -70, +5));
	hmeter(i, x) = attach(x, envelop(x) : hbargraph("chan %i[2][unit:dB]", -70, +5));
	envelop = abs : max ~ -(1.0/ma.SR) : max(ba.db2linear(-70)) : ba.linear2db;
};
