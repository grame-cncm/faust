declare name "GermanChurchBell";
declare description "German church bell physical model.";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("stdfaust.lib");

process = pm.germanBell_ui <: _,_;
