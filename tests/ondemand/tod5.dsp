// Simulation of ondemand
foo(h) = +(1)~sampling(_,h) : control(_,h);

//process = foo(1); // semble OK
clock(n) = 1 : (+,n:%)~_ : ==(1); 
process = foo(1), foo(clock(3)), foo(clock(4)); // semble OK


