// The power of two integers is the product of its factors wrapping on 32 bits, in
// every backend, as the folding of a constant power computes it (issue #1421) :
// 10^10 is 1410065408 and 2^31 is -2147483648, whether folded or computed.
// The 15 bases and 111 exponents of tests/compile-tests/defined-integer-operations.py,
// one pair per sample (1665 samples, then again), through the paths of a power :
// - pow(b, kp), kp proven >= 0 : an integer
// - pow(b, 3), pow(b, 13) : constant exponents, within and beyond the products of 8
// - the constants 10^10 and 2^31, folded by the compiler
// - pow(b, k), k of unknown sign : a real, the inverse of the wrapped product for k < 0,
//   bounded to [-1, 1] since a product wrapped to 0 gives +inf
// An integer is written as its two halves of 16 bits, each exact in single precision and
// printed with 6 decimals : every bit of the power is compared.

n  = (+(1) ~ _) - 1;
b  = rdtable(waveform{0, 1, -1, 2, -2, 3, -3, 7, 25, 46340, 46341, -46341, 65536, 69999, -70000}, (n / 111) % 15);
k  = n % 111 - 40;
kp = max(0, n % 71);

halves(p) = float(p >> 16) / 32768.0, float(p & 65535) / 65536.0;

process = halves(pow(b, kp)), halves(pow(b, 3)), halves(pow(b, 13)),
          halves(10^10), halves(2^31),
          max(-1.0, min(1.0, pow(b, k) / 2147483648.0));
