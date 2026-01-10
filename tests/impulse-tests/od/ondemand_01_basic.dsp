import("stdfaust.lib");

gate = checkbox("gate") == 0;

process = gate : ondemand(os.osc(440));
