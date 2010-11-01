 // pattern matching doesn't go inside groups
 

 foo(hgroup("", x)) = x*2;
 
 foo(x) = x*3;


process = foo(hgroup("", 10));

