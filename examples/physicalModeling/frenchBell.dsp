declare name "FrenchChurchBell";
declare description "French church bell physical model.";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("stdfaust.lib");

process = pm.frenchBell_ui <: _,_;
