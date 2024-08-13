declare name "Violin";
declare description "Simple violin physical model controlled with continuous parameters.";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = pm.violin_ui <: _,_;
