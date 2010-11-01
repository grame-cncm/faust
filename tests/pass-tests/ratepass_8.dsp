up2 = vectorize(1) <: # : serialize;

dw3 = vectorize(3) : [0];
dw2 = vectorize(2) : [0];

process = up2 <: (dw3,dw2);