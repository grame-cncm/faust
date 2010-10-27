//ERROR : inconsistent number of parameters in pattern-matching rule: (x,y) => y; 
 
 foo = case { (x,y) => y; (x,x) => x+1; };
 foo(x,y) = y;
 process = foo(1,1), foo(3,4);

