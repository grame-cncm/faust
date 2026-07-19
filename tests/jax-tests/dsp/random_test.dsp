// Test JAX native random number generation
// Verifies that random_uniform foreign function works with JAX PRNG

import("stdfaust.lib");

// Declare JAX's random uniform function as a foreign function
random_uniform = ffunction(float random_uniform(), <math.h>, "");

// Generate mono noise to test basic functionality
process = random_uniform;