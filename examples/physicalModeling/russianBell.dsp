declare name "RussianChurchBell";
declare description "Russian church bell physical model.";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("stdfaust.lib");

process = pm.russianBell_ui <: _,_;
