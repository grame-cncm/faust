import("stdfaust.lib");

// OK: faust -svg tests/ondemand/tod1.dsp
// test rewriting of ondemand code
clock(n) = 1 : (+,n:%)~_  : ==(1); 


process = 
	(1 : ondemand(no.noise)), 
	(clock(2) : ondemand(no.noise));

