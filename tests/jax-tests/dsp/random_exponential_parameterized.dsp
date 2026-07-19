import("stdfaust.lib");

// Parameterized random_exponential with rate parameter
random_exponential = ffunction(float random_exponential(float), <math.h>, "");

// Use slider to control rate (higher rate = shorter mean decay time)
rate = hslider("rate", 1.0, 0.1, 10.0, 0.1);
process = random_exponential(rate);
