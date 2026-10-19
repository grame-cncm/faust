// the sine of a bounded slider, shifted into [0, 8], used as a delay
process = @(_, int(4*sin(hslider("x", 0, 0, 6.28, 0.01))+4));
