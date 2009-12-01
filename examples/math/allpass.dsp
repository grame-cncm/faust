declare name 		"allpass";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";



allpassfeed	= 0.5;
allpasstuningL4	= 225;

// Comb and Allpass filters
//-------------------------

allpass(dt,fb) = (_,_ <: (*(fb),_:+:@(dt)), -) ~ _ : (!,_);


process = allpass (allpasstuningL4, allpassfeed);
