declare name "VirtualAnalog";
declare version "0.0";
declare author "JOS, revised by RM";
declare description "Virtual analog oscillator demo application.";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = dm.virtual_analog_oscillator_demo;
