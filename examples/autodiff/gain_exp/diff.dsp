declare name "Differentiable gain";
declare description "A learnable gain control, whose squared value is used to test differentiation
of the exponential function.";

g = hslider("g [diff:1]", -.5, -2, 0, .001);

// y = x(e^{-(g^2)})
process = _*((g,2 : ^),-1 : * : exp);
// dy/dg = -2gxe^{-(g^2)}
