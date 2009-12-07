declare name 		"select3";
declare version 	"0.1";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2009";

//-----------------------------------------------
// Three noises compared
//-----------------------------------------------


RANDMAX = 2147483647;
random1 = ffunction(int random (), <stdlib.h>, "");
noise1 = (random1 << 1) * (1.0/RANDMAX);
random2 = (*(1103515245)+12345) ~ _ ; 
noise2 = random2 * (1.0/RANDMAX);
noise3 = 0;

process = select3(button("Switch"), noise1, noise2, noise3) * hslider("volume", 0, 0, 1, 0.01) <: _,_ ;
