// OK: faust -svg tests/ondemand/tod1.dsp
// test rewriting of ondemand code
clock(n) = 1 : (+,n:%)~_  : ==(1); 

process = clock(5) : ondemand(+(1)~_), clock(5) : ondemand(+(1)~_);

