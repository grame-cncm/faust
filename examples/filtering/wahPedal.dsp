declare name "wahPedal";
declare description "Demonstrate the Fourth-Order Wah pedal (similar to the Moog VCF)";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = dm.wah4_demo;
