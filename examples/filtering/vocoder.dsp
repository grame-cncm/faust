declare name "Vocoder";
declare version "0.0";
declare author "RM";
declare description "Use example of the vocoder function where an impulse train is used as excitation.";

import("stdfaust.lib");

process = dm.vocoder_demo;
