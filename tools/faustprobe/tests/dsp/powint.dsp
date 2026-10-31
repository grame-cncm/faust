// A base known to the compiler and an exponent that is not: with fast math,
// LLVM computes this as exp2(log2(53) * k), just under 53.
k = hslider("k", 1, 0, 8, 1);
process = pow(53.0, floor(k)), int(pow(53.0, floor(k)));
