declare name "ChurchBell";
declare description "Generic church bell physical model.";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("stdfaust.lib");

process = pm.churchBell_ui <: _,_;
