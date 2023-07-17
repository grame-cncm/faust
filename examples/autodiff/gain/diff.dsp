declare name "Differentiable gain";
declare description "A basic automatic differentiation example consisting of a learnable gain
control";

gain = hslider("gain [diff:1]", .5, 0, 1, .001);

process = _*gain;
