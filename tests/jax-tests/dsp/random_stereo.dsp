// Test JAX native random number generation with independent channels
// This test verifies that each random_uniform call gets a fresh RNG key

import("stdfaust.lib");

// Declare JAX's random uniform function as a foreign function
random_uniform = ffunction(float random_uniform(), <math.h>, "");

// Generate stereo noise with independent channels
// Using different expressions to prevent compiler optimization
left = random_uniform;
right = random_uniform * 1.0;  // Force separate evaluation

process = left, right;