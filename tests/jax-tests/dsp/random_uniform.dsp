// Test JAX native random number generation using foreign function
// This test verifies that the JAX backend properly handles random_uniform
// foreign function calls and generates appropriate JAX PRNG code

import("stdfaust.lib");

// Declare JAX's random uniform function as a foreign function
// This should generate calls to self.random_uniform(rngs())
// which uses JAX's PRNG for proper random generation
random_uniform = ffunction(float random_uniform(), <math.h>, "");

// Generate stereo white noise using JAX random
// Each channel should get independent random values
process = random_uniform, random_uniform;