import("stdfaust.lib");

// Test JAX random exponential distribution (parameterized)
random_exponential = ffunction(float random_exponential(float), <math.h>, "");

// Generate stereo exponential random values with rate=1.0 (mean=1.0)
process = random_exponential(1.0), random_exponential(1.0);
