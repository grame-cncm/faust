import("stdfaust.lib");

mytable = rdtable(waveform{0, 1, 0, -1});
mytable_tabulated(x) = ba.tabulate(1, mytable, 4, 0, 4, x).lin;
process = mytable_tabulated;
