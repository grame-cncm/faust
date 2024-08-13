declare name "RussianChurchBell";
declare description "Russian church bell physical model.";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = pm.russianBell_ui <: _,_;
