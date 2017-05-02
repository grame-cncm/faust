declare name "EnglishChurchBell";
declare description "English church bell physical model.";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("stdfaust.lib");

process = pm.englishBell_ui <: _,_;
