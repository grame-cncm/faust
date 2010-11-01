 // example of not very explicit error message
 

 foo(x,y,y) = y*2;
 foo(x,y,z) = y*3;

 //process = 2:foo(1,2);

//process = foo(1,1,1), ((1,1) : (foo(1,1), foo(1,2)));

process = foo(1,1), foo(1,2);

