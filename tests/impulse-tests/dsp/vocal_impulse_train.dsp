declare name "vocal_impulse_train";
// The vocal family witness : lf_imptrain builds its pulse from the
// x - x@1 pattern on a shared phasor -- the family whose mono-scalar
// election once read the same value twice and silenced the train
// (kernel taps are old-value readers too). Two formant resonators
// share the source, exercising shared delayed reads downstream.
// Hermetic on purpose : only the suite-local legacy libraries, so every
// backend leg resolves identically whatever its working directory.

fl = library("filter.lib");
ol = library("oscillator.lib");

source = ol.lf_imptrain(110.0);
process = source <: fl.resonbp(650.0, 40.0, 1.0), fl.resonbp(1080.0, 50.0, 0.8) :> _;
