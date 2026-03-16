// WARNING : numeric stability analysis should detect this recursive near-unity gain loop when -nsa is enabled.

process = loop
with {
    loop = +(1.0) ~ (*(0.99995));
};
