up2 = vectorize(1) <: # : serialize;
up4 = up2:up2;

dw2 = vectorize(2) : [0];
dw4 = vectorize(4) : [0];

process = (up2,up4) ~ (dw2,dw4);