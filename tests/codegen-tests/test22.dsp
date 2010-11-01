//Bug discovered by julius smith
 
SR = fconstant(int fSamplingFreq, <math.h>);
R = 1.0-4410.0/SR;
process = (1-1') / (1-R*R);
