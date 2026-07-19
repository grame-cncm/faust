import("stdfaust.lib");

// Parameterized random_bernoulli with probability parameter
random_bernoulli = ffunction(float random_bernoulli(float), <math.h>, "");

// Use slider to control probability (p=0.7 means 70% chance of 1)
prob = hslider("probability", 0.5, 0.0, 1.0, 0.01);
process = random_bernoulli(prob);
