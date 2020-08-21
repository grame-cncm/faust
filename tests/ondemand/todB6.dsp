// verification des problèmes éventuels de "capture"
import("stdfaust.lib");

// test imbrication de ondemands
clock(n) = 1 : (+,n:%)~_  : ==(1); 

time = +(1)~_ ;
foo = (clock(2), time : ondemand(_)); 

//process = foo;
process = clock(3) : ondemand(foo);  // Doesn't work as expected