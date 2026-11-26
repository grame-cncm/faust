// The sum and the difference of two integers wrap on 32 bits both ways, in every backend :
// below -2147483648 as above 2147483647. JSFX computes them as reals brought back to
// 32 bits, and brought back only the sums above 2^31 - 1 and the differences below 0.
// Operands near both ends, read from tables so that nothing folds, one pair per sample.
// An integer is written as its two halves of 16 bits : every bit is compared.

n = (+(1) ~ _) - 1;
a = rdtable(waveform{-2147483000, -1500000000, 2147483000, 1500000000, 7}, n % 5);
b = rdtable(waveform{-1000000000, -700000000, 1000000000, 700000000, -3}, (n >> 2) % 5);

halves(p) = float(p >> 16) / 32768.0, float(p & 65535) / 65536.0;

process = halves(a + b), halves(a - b), halves(b - a + n), halves(a + n - b);
