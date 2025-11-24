import("stdfaust.lib");

// Shared slider declared in a root group.
base = vgroup("Root", vslider("shared", 440, 100, 1000, 1));

// Nested groups climb back to Root using a relative group label.
nested = vgroup("Outer", hgroup("../Root", vslider("shared", 220, 100, 1000, 1)));

process = os.osc(base), os.osc(nested);  // two outputs driven by the shared slider
