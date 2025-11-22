// Regression test for issue #1063: relative paths in group labels
// https://github.com/grame-cncm/faust/issues/1063
//
// This test verifies that relative path components (.., .) in group labels
// are resolved correctly against the parent path context.
//
// Both forms should produce the same resolved label for the slider:
// 1. Using explicit path in slider: vslider("../h:FREQ/Freq", ...)
// 2. Using hgroup with relative path: hgroup("../FREQ", vslider("Freq", ...))
//
// Expected behavior: In both cases, the slider should be shared between
// V1 and V2 groups, appearing in a FREQ group at the same level as V1/V2.

import("stdfaust.lib");

// Using hgroup with relative path (previously broken, now fixed)
freq = hgroup("../FREQ", vslider("Freq",200,200,1000,0.01));

// The freq slider should be shared between V1 and V2
process = hgroup("V1", os.osc(freq)), hgroup("V2", os.osc(freq));
