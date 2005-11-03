//-------------------------------------------------
// Simple vumeter
//-------------------------------------------------

import("math.lib");


vmeter(x)		= attach(x, envelop(x) : vbargraph("meter", 0, 1));
hmeter(x)		= attach(x, envelop(x) : hbargraph("meter", 0, 1));

envelop			= abs : min(0.99) : max ~ -(1.0/SR);

process 		= vmeter;