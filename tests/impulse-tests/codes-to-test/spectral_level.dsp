// Spectrum analyzer


declare name 		"spectrum_level";

fl = library("filter.lib");

BandsPerOctave = 3; // third-octave filter bank
process = fl.mth_octave_spectral_level_demo(BandsPerOctave) <: _,_;
