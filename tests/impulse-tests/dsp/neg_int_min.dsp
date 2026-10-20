// The negation of an int that may be INT_MIN wraps : -INT_MIN is INT_MIN, computed
// without a signed overflow (the slider, -3e9 by default, converts to INT_MIN).
process = 0 - int(hslider("x", -3e9, -3e9, 0, 1)), 0 - int(_);
