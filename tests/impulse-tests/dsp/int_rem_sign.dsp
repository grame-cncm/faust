// The remainder of two integers has the sign of the dividend, as in C, in every backend :
// -7 % 3 is -1 and 7 % -3 is 1. JSFX builds it on EEL2's '%', which gives the remainder of
// the absolute values. Dividends from -50 to 14949 (then again), divisors of both signs,
// constant or not (never 0).

n = (+(1) ~ _) - 1;
m = n - 50;
d = n % 9 - 4;
v = select2(d == 0, d, 5);

process = float(m % 7), float(m % -7), float((0 - m) % 7), float((0 - m) % -7), float(m % v);
