declare name "freeverb";
declare version "0.0";
declare author "RM";
declare description "Freeverb demo application.";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = dm.freeverb_demo;
