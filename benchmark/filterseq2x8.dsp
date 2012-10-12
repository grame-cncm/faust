import("filter.lib");

// two sequences of 8 lowpass filters
process = par(j, 2, seq(i, 8, lowpass(3,1000)));
