// WARNING: this model is incomplete and is only here for testing purposes

declare name "MarimbaMIDI";
declare description "Simple MIDI-controllable marimba physical model.";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("stdfaust.lib");

process = button("gate") : ba.impulsify : pm.marimbaBarModel(0,0.2,1,2) <: _,_;
