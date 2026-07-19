import("stdfaust.lib");

// Parameterized random_beta with alpha and beta parameters
random_beta = ffunction(float random_beta(float, float), <math.h>, "");

// Test with different parameter values
alpha = hslider("alpha", 2.0, 0.1, 10.0, 0.1);
beta = hslider("beta", 2.0, 0.1, 10.0, 0.1);
process = random_beta(alpha, beta);
