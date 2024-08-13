declare name "noiseGate";
declare version "0.0";
declare author "JOS, revised by RM";
declare description "Gate demo application.";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = dm.gate_demo;
