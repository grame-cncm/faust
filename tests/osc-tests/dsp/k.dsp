declare name 		"k";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2009";


vol 			= hslider("volume", 0.1, 0, 1, 0.1);
process 		= 1 * vol; 
