declare name 		"rms";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2009";


// Root Mean Square of n consecutive samples
RMS(n) = square : mean(n) : sqrt ;

// the square of a signal
square(x) = x * x ;

// the mean of n consecutive samples of a signal
// uses fixpoint to avoid the accumulation of
// rounding errors 
mean(n) = float2fix : integrate(n) : fix2float : /(n); 

// the sliding sum of n consecutive samples of a signal
integrate(n,x) = x - x@n : +~_ ;

// convertion between float and fix point
float2fix(x) = int(x*(1<<20));      
fix2float(x) = float(x)/(1<<20);    

// Root Mean Square of 1000 consecutive samples
process = RMS(1000) ;
