declare name "reverbDesigner";
declare version "0.1";
declare author "JOS";
declare description "Workbench for building a custom Feedback Delay Network (FDN) Reverebator";

import("stdfaust.lib");

N = 16; 	// Feedback Delay Network (FDN) order (power of 2, 2 to 16)
NB = 5; 	// Number of T60-controlled frequency-bands (3 or more)
BSO = 3;	// Order of each lowpass/highpass bandsplit (odd positive integer)

process = dm.fdnrev0_demo(N,NB,BSO);
