import("stdfaust.lib");

// Test JAX random bernoulli (binary random, parameterized)
random_bernoulli = ffunction(float random_bernoulli(float), <math.h>, "");

// Generate stereo random gates (0 or 1) with p=0.5
process = random_bernoulli(0.5), random_bernoulli(0.5);
