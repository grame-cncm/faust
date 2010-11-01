 // additional arguments of pm rule where thrown away
 
cond(1,x,y) = x;
cond(b,x,y) = y;

fact(n) = cond(n>0, \(n).(n*fact(n-1)), \(n).(1)) (n);

fact2(n) = cond(n>0, \(n).(n*fact2(n-1)), \(n).(1), n);
 
process = fact(10), fact(-10), fact2(10);


