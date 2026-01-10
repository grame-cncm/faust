import("stdfaust.lib");

outer = checkbox("outer") == 0;
inner = checkbox("inner") == 0;
delaySamps = 240;

process = outer : ondemand(inner : ondemand(os.osc(440) : @(delaySamps)));
