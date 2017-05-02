// Radix 2 FFT, decimation in time, interleaved complex signals and spectra

declare name    "FFT";
declare author  "JOS";
declare license "STK-4.3";

import("stdfaust.lib");

N = 8;
input = par(i,N,float(i==1),0.0); // delayed impulse
output = input : an.fft(N); // Sliding FFT of input, rectangular window
outputMagSq = output : an.cSumSq(N); // Sliding power spectrum
inputHat = output : an.ifft(N); // Inverse FFT = input signal to within roundoff error
error = input, (inputHat : par(i,2*N,*(-1))) :>  an.cSumSq(N) : par(i,N,sqrt); // L2 norm of error
process = error; // see also: input, output, outputMagSq, inputHat;

// USAGE:
//
// > faust FFT.dsp
//   ...
//   output0[i] = (FAUSTFLOAT)2.92209e-17f;
//   output1[i] = (FAUSTFLOAT)3.081488e-33f;
//   output2[i] = (FAUSTFLOAT)4.127506e-17f;
//   output3[i] = (FAUSTFLOAT)7.273337e-17f;
//   output4[i] = (FAUSTFLOAT)2.92209e-17f;
//   output5[i] = (FAUSTFLOAT)5.551115e-17f;
//   output6[i] = (FAUSTFLOAT)2.0227457e-18f;
//   output7[i] = (FAUSTFLOAT)7.273337e-17f;
//   ...
