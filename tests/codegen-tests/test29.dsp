import("stdfaust.lib");

// Interval computation issue, which is now fixed in ba.tabulate with : wf = r0 + float(rid(ba.time, 1))*(r1-r0)/float(mid) : FX;
// Use rid(ba.time, 0) to reproduce the issue.

note = 1 : qu.quantize(523.25, qu.dorian);
lead2 = os.square(note) : ve.moog_vcf(0.9, 1000);

process = lead2;
