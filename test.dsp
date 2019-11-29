import("stdfaust.lib");

t1 = rdtable(100, (1:+~_));
t2 = rdtable(50, t1(2:(+,100:%)~_));

//process = t2(3:(+,50:%)~_);

process = ba.automat(120, 15, 0.0);