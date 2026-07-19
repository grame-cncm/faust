import("stdfaust.lib");

// Parameterized random_beta with constant parameters
random_beta = ffunction(float random_beta(float, float), <math.h>, "");

// Use constant values for alpha and beta
process = random_beta(5.0, 1.0);
