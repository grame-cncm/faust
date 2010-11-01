//ERROR : pattern matching failed, no rule of case {(z,y,x,x) => (x,(10,y:*):+),(100,z:*):+; } matches argument list (4,7,2,#1)
 
 foo(x,x,y,z) = x+10*y+100*z;
 process = foo(4,7,2);

