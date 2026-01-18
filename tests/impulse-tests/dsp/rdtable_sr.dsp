// Test case for fSampleRate initialization in SubContainers

import("stdfaust.lib");
process = rdtable(100, ma.SR, ba.time % 100);
