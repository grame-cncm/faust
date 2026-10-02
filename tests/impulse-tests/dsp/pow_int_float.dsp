// Regression for PR #1326: integer and floating-point power helpers must
// keep separate argument types, regardless of their declaration order.
// 50000^2 wraps to -1794967296 as int32; 0.6^2 must remain 0.36.
n = int(hslider("n", 50000, 0, 50000, 1));
x = hslider("x", 0.6, 0, 1, 0.01);

process = float(n * n), x * x;
