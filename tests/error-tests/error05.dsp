//ERROR : inconsistent number of parameters in pattern-matching rule: (x,z) => z; previous rule was: (x,x,z) => x;
// test for unconsistent pattern matching rules
fuu (x,x,z) = x;
fuu (x,z) = z;

process = fuu(1,1), fuu(1,2);
