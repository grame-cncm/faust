up2 = vectorize(1) <: # : serialize;
dw2 = vectorize(2) : [0];

up4 = up2:up2;
dw4 = vectorize(4) : [0];

process = up2 ~ ( (up4~dw2) : dw2);