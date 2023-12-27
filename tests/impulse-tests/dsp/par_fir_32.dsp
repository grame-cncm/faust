import("stdfaust.lib");

N = 32; // FIR filter length set very large for test
M = 1; // Number of FIR filters in parallel
coeffs(j) = par(i,N,1.0/float(i*j+1));
filter(j) = fi.fir(coeffs(j));
filterbank = par(j,M,filter(j+1));
process = filterbank;
