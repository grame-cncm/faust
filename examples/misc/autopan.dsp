//--------------------------autopan----------------------------
//
// For a stereo input, adjust the left and right gains
// according to rate-synced sine oscillators. This example is
// reverse-engineered from Ableton Live's "Auto Pan" audio
// effect. We don't implement the "spin" feature in which
// the two LFOs could have different frequencies.
// We also don't use other LFOs such as triangle/square/noise.
//
// #### Usage
//
// ```
// si.bus(2) : autopan(amount, rate, phase, shape) : si.bus(2)
// ```
//
// Where:
//
// * `amount`: adjusts the amount of LFO modulation that is
//    applied to incoming signals
// * `rate`: sets the frequency of the LFO in Hertz
// * `phase`: adjusts the amount of the offset between the
//    waveforms for the left and right channel. At 180,
//    the LFOs will be perfectly out of phase. For other
//    values, you will hear more moments where the
//    overall volume is reduced
// * `shape`: turning `shape` up pushes the waveforms to their
//    upper and lower limits, "hardening" their shape
//------------------------------------------------------------
import("stdfaust.lib");

autopan(amount, rate, phase, shape) = _*gainLeft, _*gainRight
with {

    // A saturator
    // Assume `x` is a signal between -1 and 1. This function
    // pushes the output towards -1 and 1. As the shape
    // parameter goes from 0 to 1, an input sine will become
    // closer to a square. If `shape` is zero, then the
    // function doesn't change the input signal.
    saturator(shape, x) = result
    with {
        // It's ok to replace tanh with another saturator
        result = x, ma.tanh(x*10.) : it.interpolate_linear(shape);
    };

    phase2Gain(phase) = os.oscp(rate, phase)
        : saturator(shape) // comment out this line to remove the saturator
        : it.remap(-1., 1., 1.-amount, 1.);

    gainLeft = 0. : phase2Gain;
    gainRight = phase : ma.deg2rad : phase2Gain;
};

amount = hslider("[0]Amount[style:knob]", 0., 0., 1., .001);
rate = hslider("[1]Rate[style:knob][unit:Hz][scale:log]", 1., .05, 90., .001);
phase = hslider("[2]Phase[style:knob][unit:°]", 180., 0., 360., 15) : si.smoo;
shape = hslider("[3]Shape[style:knob]", 0., 0., 1., 0.001) : si.smoo;

process = hgroup("Auto Pan", autopan(amount, rate, phase, shape));
