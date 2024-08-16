declare name "sawtoothLab";
declare version "0.0";
declare author "JOS, revised by RM";
declare description "An application demonstrating the different sawtooth oscillators of Faust.";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = dm.sawtooth_demo;
