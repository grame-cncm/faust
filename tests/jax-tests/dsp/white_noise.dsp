import("stdfaust.lib");

// Standard uniform [0, 1]
random_uniform = ffunction(float random_uniform(), <math.h>, "");

// Utility: rescale to [-1, 1] for white noise
uneg1to1 = 2 * random_uniform - 1;

// Stereo white noise in [-1, 1]
process = uneg1to1, uneg1to1;
