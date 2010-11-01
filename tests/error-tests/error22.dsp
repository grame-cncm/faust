// can't compute interval of recursive signal
filter = *(0.01) : +~*(0.99);
d = hslider("delay", 0, 0, 1000, 1) : filter : int;
process = @(d);
