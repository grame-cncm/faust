// Test program for tiered-memory-test.cpp: an 8 kB table (made in
// classInit) and a 16 kB delay line, both sized for the arena tier.
import("stdfaust.lib");
tsize = 2048;
tab = rdtable(tsize, os.sinwaveform(tsize));
process = _ <: (abs : de.delay(4096, 3000)), (*(1000) : int : abs : %(tsize) : tab) :> _;
