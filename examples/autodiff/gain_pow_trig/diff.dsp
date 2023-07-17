declare name "Differentiable gain";
declare description "An automatic differentiation example that facilitates testing a somewhat
convoluted logarithmic differentiation scenario.";

gain = hslider("gain [diff:1]", .5, 0, 1, .001);

process = _*(gain,cos(gain) : ^);

// This version fails to converge for target gain < ~.7,
// because autodiff attempts to set negative gain; in this scenario,
// log(gain) returns a non-number.
//process = _*(gain,sin(gain) : ^);
