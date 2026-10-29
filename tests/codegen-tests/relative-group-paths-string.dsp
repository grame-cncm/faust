// Companion test for relative-group-paths.dsp
// This uses the string literal form that was already working
// Both tests should produce identical UI structure

import("stdfaust.lib");

// Using explicit path in slider string (already working)
freq = vslider("../h:FREQ/Freq",200,200,1000,0.01);

// The freq slider should be shared between V1 and V2
process = hgroup("V1", os.osc(freq)), hgroup("V2", os.osc(freq));
