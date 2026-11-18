// the delay of a foreign function, converted then masked : NaN converts to 0, and the mask
// bounds the amount
h = ffunction(float hypotf|hypot|hypotl (float, float), <math.h>, "");
process = @(int(h(2, hslider("y", 4, 0, 8, 0.01))) & 511);
