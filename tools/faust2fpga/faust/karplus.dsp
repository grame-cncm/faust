import("stdfaust.lib");

// Karplus Strong (1/2)
process = ba.pulse(10000) :
        + ~ transformation;

transformation = @(50) : moyenne : *(0.99);

moyenne(x) = (x+x')/2;
