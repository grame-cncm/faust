// Regression: a real value whose interval had an lsb >= 0 (a constant from 2^32 on, rint,
// round) was taken for an int32 by the interval rules, which wrapped the product to
// [INT_MIN, INT_MAX]: both comparisons below were folded to the constant 0. x and y are 0
// at the first sample and 1 after, so each output is 0 then 1. They are two signals, so that
// the second product is not normalized into a square, which another rule types.
t = float(+(1) ~ _ : -(1));
x = max(0.0, min(1.0, t));
y = max(0.0, min(1.0, 2.0 * t));

process = x * 5e9 >= 3e9, rint(x * 1e5) * rint(y * 1e5) >= 3e9;
