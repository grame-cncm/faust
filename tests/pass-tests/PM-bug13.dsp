foo = abs,abs;
x = 666;
n = 18;



fact(0) = 1;
fact(n) = n*fact(n-1);

map(foo, (x,xs)) = foo(x), map(foo,xs);
map(foo, x) = foo(x);


process = map(fact, (10,11,12,13));


