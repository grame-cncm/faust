// delay with negative values
filter = *(0.01) : +~*(0.99);
d = hslider("delay", 0, -10, 1000, 1)  : int;
process = @(d);
