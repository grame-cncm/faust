// A comparison with NaN is false : sqrt(x) >= 0 is false for x < 0. It must not be
// decided (and folded) at compile time : the index is 1 for x < 0.
process(x) = rdtable(2, (+(1)~_), 1 - (sqrt(x) >= 0));
