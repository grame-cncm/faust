declare name "vocal_impulse_train";
// The vocal family witness : os.lf_imptrain builds its pulse from
// x - x@1 on a shared phasor -- the exact pattern whose mono-scalar
// election once read the same value twice and silenced the train
// (kernel taps are old-value readers too). Two formant resonators
// share the source, exercising shared delayed reads downstream.

import("stdfaust.lib");

source = os.lf_imptrain(110.0);
process = source <: fi.resonbp(650.0, 40.0, 1.0), fi.resonbp(1080.0, 50.0, 0.8) :> _;
