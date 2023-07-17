declare name "Differentiable gain + DC";
declare description "A basic multivariate automatic differentiation example.";

gain = hslider("gain [diff:1]", .5, 0, 1, .001);
dc = hslider("dc [diff:1]", 0, -.5, .5, .001);

process = _*(gain),dc : +;
