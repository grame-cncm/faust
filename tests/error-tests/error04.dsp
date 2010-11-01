//ERROR : inconsistent number of parameters in pattern-matching rule: (x,y) => -; previous rule was: (5) => +;

// Faust should complain about inconsistent number of patterns
// between the foo rules

foo (5) = +;
foo (x,y) = -;

process = foo(3,2);
