import("stdfaust.lib");

// Slider defined under a tab group.
tabbed = tgroup("Tab", hgroup("Row", vgroup("Col", vslider("gain", 0.5, 0, 1, 0.01))));

// Another hierarchy reuses the same slider by targeting the tab group relatively.
reuse = vgroup("Alt", tgroup("../Tab", vslider("gain", 0.5, 0, 1, 0.01)));

process = os.osc(440) * tabbed, os.osc(660) * reuse;
