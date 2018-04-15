declare name 		"panpot";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

//-------------------------------------------------
// Stereo panpot
//-------------------------------------------------

panpot(x) 	= sqrt(c)*x, sqrt(1-c)*x
			with {
				c=(nentry("[1]pan[style:knob]",0,-90,90,1)-90.0)/-180.0;
			};

process		= panpot;

