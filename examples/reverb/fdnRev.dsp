declare name "fdnRev";
declare version "0.0";
declare author "JOS, Revised by RM";
declare description "A feedback delay network reverb.";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = dm.fdnrev0_demo(16,5,3);
