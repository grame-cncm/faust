import("stdfaust.lib");

gate = checkbox("gate") == 0;

process = (gate, _) : ondemand(fi.lowpass(2, 800));
