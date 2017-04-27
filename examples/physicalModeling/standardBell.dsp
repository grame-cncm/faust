declare name "StandardChurchBell";
declare description "Standard church bell physical model.";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("stdfaust.lib");

process = pm.standardBell_ui <: _,_;
