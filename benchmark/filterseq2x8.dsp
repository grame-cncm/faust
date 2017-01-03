fi = library("filters.lib");

// two sequences of 8 lowpass filters
process = par(j, 2, seq(i, 8, fi.lowpass(3,1000)));
