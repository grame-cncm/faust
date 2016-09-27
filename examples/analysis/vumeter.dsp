declare name 		"vumeter";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

//-------------------------------------------------
// Simple vumeter
//-------------------------------------------------

import("stdfaust.lib");


vmeter(x)		= attach(x, envelop(x) : vbargraph("[2][unit:dB]", -70, +5));
hmeter(x)		= attach(x, envelop(x) : hbargraph("[2][unit:dB]", -70, +5));

envelop         = abs : max ~ -(1.0/ma.SR) : max(ba.db2linear(-70)) : ba.linear2db;

process 		= hmeter,hmeter;
