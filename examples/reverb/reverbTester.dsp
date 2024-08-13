declare name "reverbTester";
declare version "0.0";
declare author "RM";
declare description "Handy test inputs for reverberator demos below.";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = dm.stereo_reverb_tester;
