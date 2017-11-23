// WARNING : shadowed pattern-matching rule: (x) => x,3:*; previous rule was: (x) => x,2:*;

foo(x) = x*2;
foo(x) = x*3;
process = foo(10);

