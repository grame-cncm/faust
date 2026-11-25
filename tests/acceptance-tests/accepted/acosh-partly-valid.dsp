// acosh of a value within [0, 2] : invalid below 1, valid above, the signal has valid values
h = ffunction(float acoshf|acosh|acoshl (float), <math.h>, "");
process = h(hslider("x", 1, 0, 2, 0.01));
