// Generate incorrect code where itbl1mydspSIG0 is read without being initialized (use interp-tracer -trace 7 table1.dsp)

t1 = rdtable(100, (1:+~_));
t2 = rdtable(50, t1(2:+~_));

process = t2(3:(+,50:%)~_);