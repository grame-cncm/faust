import("stdfaust.lib");

// Test JAX random beta distribution (parameterized)
random_beta = ffunction(float random_beta(float, float), <math.h>, "");

// Generate stereo random values in [0, 1] with beta(2, 2) distribution
process = random_beta(2.0, 2.0), random_beta(2.0, 2.0);
