declare name "filterOSC";
declare version "0.0";
declare author "JOS, revised by RM";
declare description "Simple application demoing filter based oscillators.";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = dm.oscrs_demo;
