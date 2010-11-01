 // WARNING : shadowed pattern-matching rule: (x,x) => x,1:+; previous rule was: (x,y) => y;
 
 foo(x,y) = y;
 foo(x,x) = x+1;
 process = foo(1,1), foo(3,4);

