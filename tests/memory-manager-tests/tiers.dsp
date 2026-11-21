// Test program for tiered-memory-test.cpp: delay lines of several sizes.
// Each delays another signal (FAUST shares one line among delays of the
// same signal) and rounds its length up to a power of two.
import("stdfaust.lib");
process = _ <: (abs : de.delay(64, 50)), (max(0) : de.delay(4096, 3000)),
               (min(0) : de.delay(16384, 12000)), (sin : de.delay(65536, 40000)),
               (cos : de.delay(262144, 200000)) :> _;
