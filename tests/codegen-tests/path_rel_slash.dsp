import("stdfaust.lib");

// Group label with an embedded slash is split into nested folders, and a relative lookup finds it.
shared = vgroup("Parent/Child", vslider("mix", 0.5, 0, 1, 0.01));
reuse = hgroup("Sibling", vgroup("../Parent/Child", vslider("mix", 0.5, 0, 1, 0.01)));

process = os.osc(440) * shared, os.osc(660) * reuse;
