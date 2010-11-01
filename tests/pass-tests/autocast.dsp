// An automatic int cast should be generated
smooth(c) = *(1-c) : +~*(c);
process = @(hslider("delay", 0, 0, 10000, 1) : smooth(0.9999) : int : &(16535)); 
