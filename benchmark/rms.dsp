integrate(n,x) = x - x@n : +~_ ;   // the sum of n successive values of a signal
mean(n) = float2fix : integrate(n) : fix2float : /(n); // the mean of n successive values of a signal
square(x) = x * x ;                 // the square of a signal
float2fix(x) = int(x*(1<<20));      // convert to fixpoint
fix2float(x) = float(x)/(1<<20);    // convert from fixpoint
RMS(n) = square : mean(n) : sqrt ;  // the Root Mean Square of a signal

process = RMS(1000) ;
