// the delay of a foreign function held within [0, 100] : NaN converts to 0, every number
// lies within the bounds
h = ffunction(float erff|erf|erfl (float), <math.h>, "");
process = @(int(min(100, max(0, 50 + 50 * h(hslider("x", 0, -4, 4, 0.01))))));
