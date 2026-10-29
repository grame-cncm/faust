// A short delay whose amount comes from the input (as in impulse-tests/dsp/norm3.dsp): a NaN input
process(x) = x @ (10 * min(abs(x), 1));
