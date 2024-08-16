declare name "flanger";
declare version "0.0";
declare author "JOS, revised by RM";
declare description "Flanger effect application.";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = dm.flanger_demo;
