import("stdfaust.lib");

// Test JAX random normal distribution (Gaussian noise)
random_normal = ffunction(float random_normal(), <math.h>, "");

// Generate stereo Gaussian noise
process = random_normal, random_normal;
