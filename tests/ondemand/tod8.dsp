// Like tod7 but with real ondemand
//foo(h) = +(1)~sampling(_,h) : log : upsampling(_,h);
//foo(h) = h,1:ondemand(+~_ : log);
foo(h) = h,1:ondemand(+~_);

//process = foo(1); // semble OK
clock(n) = 1 : (+,n:%)~_  : ==(1); 
process = foo(1), foo(clock(3)), foo(clock(4)); // semble OK


