declare name 		"Noise";
declare version 	"1.1";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2009";

//-----------------------------------------------------------------
// Noise generator and demo file for the Faust math documentation
//-----------------------------------------------------------------

random  = +(12345)~*(1103515245);
noise   = random/2147483647.0;

process = noise : abs;
