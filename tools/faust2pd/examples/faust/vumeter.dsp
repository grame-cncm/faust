declare name 		"vumeter";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

//-------------------------------------------------
// Simple vumeter
//-------------------------------------------------

import("math.lib");


vmeter(x)		= attach(x, envelop(x) : vbargraph("meter", 0, 1));
hmeter(x)		= attach(x, envelop(x) : hbargraph("meter", 0, 1));

envelop			= abs : min(0.99) : max ~ -(1.0/SR);

process 		= vgroup("vu meter", vmeter);