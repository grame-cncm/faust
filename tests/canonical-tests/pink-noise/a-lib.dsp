// the pink noise of the library
import("stdfaust.lib");
r = (+(12345) ~ *(1103515245)) : float; // the generator of no.noise, before its scaling
R = 2147483647.0;
process = no.pink_noise;
