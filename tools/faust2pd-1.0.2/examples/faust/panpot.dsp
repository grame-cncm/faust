declare name 		"panpot";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

//-------------------------------------------------
// Stereo panpot
//-------------------------------------------------

panpot(x) 	= (1-c)*x, c*x
			with {
				c=(nentry("",0,-8,8,1)-8)/-16;
			};

process		= vgroup("panpot", panpot);

