declare name "KarplusStrong";
declare description "Simple call of the Karplus-Strong model for the Faust physical modeling library";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("stdfaust.lib");

process = pm.ks_ui_MIDI <: _,_;
