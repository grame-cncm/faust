// Spectrum analyzer

dm = library("demo.lib");

BandsPerOctave = 3; // third-octave filter bank
process = dm.mth_octave_spectral_level_demo(BandsPerOctave) <: _,_;
