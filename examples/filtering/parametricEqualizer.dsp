declare name "parametricEqualizer";
declare description "Exercise and compare Parametric Equalizer sections on test signals";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = dm.parametric_eq_demo;
