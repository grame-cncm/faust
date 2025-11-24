import("stdfaust.lib");

// Slider defined under a deep nesting.
deep = vgroup("Top", hgroup("Mid", tgroup("Tab", vslider("gain", 0.5, 0, 1, 0.01))));

// Another branch climbs two levels up to reach Tab and reuse the same slider.
reuse = vgroup("Sibling", vgroup("Child", tgroup("../../Top/Mid/Tab", vslider("gain", 0.5, 0, 1, 0.01))));

process = os.osc(440) * deep, os.osc(660) * reuse;
