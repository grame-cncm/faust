declare name "ftz_bounded_rec";
// Regression for issue #1371: with -ftz 2, the flush-to-zero test of a real
// recursion, (bits(x) & exponent mask) ? x : 0, must not fold to false when
// the interval of x is bounded. The bits of a float are not its value (0.5f
// is 0x3F000000): when the interval of the bitcast was the numeric range of
// x, every range that truncates to {0, 1} gave a mask test proven 0, and the
// recursion output 0 for ever. The first two outputs were affected, the third
// one, whose range reaches -1, is the control.
// Hermetic on purpose: no library. Every value is a multiple of 1/128, exact
// in float as in double, so every precision leg compares at the default tolerance.

n = +(1) ~ _;                                    // integer recursion, untouched by -ftz
x = max(-1.0, min(1.0, float(n % 128) / 64 - 1));  // sawtooth, the clamp bounds it to [-1, 1]
trig = (n % 48) == 0;
hold = select2(trig) ~ _;                        // sample-and-hold every 48 samples, as ba.sAndH

process = (0.5 * x : + ~ *(0)),                  // feedback cancelled: in [-0.5, 0.5]
          (0.5 + 0.5 * x : hold),                // held: in [0, 1]
          (x : hold);                            // held: in [-1, 1]
