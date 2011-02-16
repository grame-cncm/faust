up2 = vectorize(1) <: # : serialize;

dw2 = vectorize(2) : [0];

filter = _<:_,@(1):+:*(0.5);

process = up2:exp:filter:dw2;
