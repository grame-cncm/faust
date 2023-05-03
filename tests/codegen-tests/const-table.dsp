import("stdfaust.lib");
process = par(i, 4, 4) : ro.interleave(2,2) : (si.bus(3),!) : rdtable;
