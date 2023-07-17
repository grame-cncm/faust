declare name "Differentiable gain";
declare description "A learnable gain control, whose squared value is used to test logarithmic
differentiation";

gain = hslider("gain [diff:1]", .5, 0, 1, .001);

process = _*(gain,2 : ^);
