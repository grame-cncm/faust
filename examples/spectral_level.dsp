// Spectrum analyzer

import("filter.lib");
BandsPerOctave = 3; // third-octave filter bank
process = mth_octave_spectral_level_demo(BandsPerOctave) <: _,_;
