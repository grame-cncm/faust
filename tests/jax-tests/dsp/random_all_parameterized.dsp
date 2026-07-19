import("stdfaust.lib");

// Comprehensive test of parameterized random functions
random_exponential = ffunction(float random_exponential(float), <math.h>, "");
random_bernoulli = ffunction(float random_bernoulli(float), <math.h>, "");
random_beta = ffunction(float random_beta(float, float), <math.h>, "");

// Test with different parameter values
exp_rate = hslider("exp_rate", 1.0, 0.1, 10.0, 0.1);
bern_prob = hslider("bern_prob", 0.5, 0.0, 1.0, 0.01);
beta_alpha = hslider("beta_alpha", 2.0, 0.1, 10.0, 0.1);
beta_beta = hslider("beta_beta", 2.0, 0.1, 10.0, 0.1);

// Mix all three parameterized distributions
process =
    random_exponential(exp_rate) * 0.1 +
    random_bernoulli(bern_prob) * 0.3 +
    random_beta(beta_alpha, beta_beta) * 0.6;
