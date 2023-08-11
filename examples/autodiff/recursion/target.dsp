declare description "Differentiating a one-pole filter should yield the
following algorithm. Compile this and compare its normal form with that of
`faust -diff diff.dsp`.";

process = dy
with {
    alpha = hslider("alpha", .99, 0, .99, .01);

    // This is the one-pole filter.
    y = + ~(alpha,_ : *);
    // This is the derivative of y, which, due to recursivity, also depends on y.
    dy = y' : + ~(alpha,_ : *);
};
