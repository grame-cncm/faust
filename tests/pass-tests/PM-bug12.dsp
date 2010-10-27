 // example of partially applied rules
 // transformed into a symbolic box
 
 foo(x,x,z) = z*2;
 foo(x,y,z) = z*3;
 process = foo(1,1), foo(2,1);

