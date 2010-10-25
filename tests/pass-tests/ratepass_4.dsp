up2 = vectorize(1) <: # : serialize;

dw2 = vectorize(2) : [0];

process = (up2,up2:+) ~ dw2;