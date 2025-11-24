import("stdfaust.lib");

freq = hgroup("FREQ", vslider("Freq", 200, 200, 1000, 0.01));

process = hgroup("/h:Foo/v:Faa", os.osc(freq)), hgroup("/h:Foo/v:Faa", os.osc(freq));
