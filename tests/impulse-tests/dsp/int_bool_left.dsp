// An int operation whose left operand is a comparison (a bool) wraps : (x > 0) - x is
// 0 - INT_MIN, INT_MIN, computed without a signed overflow (the slider, -3e9 by default,
// converts to INT_MIN).
x = int(hslider("x", -3e9, -3e9, 3e9, 1));
process = (x > 0) - x, (x < 0) + x - 1;
