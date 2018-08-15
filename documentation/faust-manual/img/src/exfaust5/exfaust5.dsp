
import("stdfaust.lib");
duplicate(1,x) = x;
duplicate(n,x) = x, duplicate(n-1,x);
process = duplicate(5,no.noise);

