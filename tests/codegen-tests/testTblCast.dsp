import("stdfaust.lib");
//process = rdtable(5, 0, int(2.5*(1+os.osc(440))));
//process = rdtable(5, 0, float(2.5*(1+os.osc(440)))); // OK Now
//process(x) = rwtable(5, 0.1, float(2.5*(1+os.osc(440))), x, float(2.5*(1+os.osc(110))) ); // 

process = 5.5, 3.3, 1.2  : rdtable; // example stepl


