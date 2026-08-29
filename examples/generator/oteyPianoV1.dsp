declare name "OteyPiano";
declare author "Faust port of C. Otey's piano model (Stanford Ph210, 2007) by Claude Fable AI";
declare reference "http://large.stanford.edu/courses/2007/ph210/otey2/";
declare options "[midi:on] [nvoices:8]";

import("stdfaust.lib");

//============================================================================
// A physical model of the piano after C. Otey (2007).
//
// Structure (article, Fig. 1):
//   hammer -> two detuned digital-waveguide strings -> bridge -> soundboard
//
// Each string is a velocity-wave delay loop of one round trip (SR/f0),
// closed by the product of its terminations:
//   -1    perfect reflection at the frame pin,
//   Hd    dispersion allpass cascade (stiffness -> inharmonic, stretched
//         partials; the article's Thiran allpass is approximated by a
//         cascade of first-order allpasses with negative coefficient, so
//         high frequencies travel faster, as kappa*d4y/dx4 implies),
//   Hl    loss filter implementing tau(w) = 1/(c1 + c3 w^2): a gain g0
//         (c1, the T60 of the low partials) times a one-pole lowpass (c3),
//   r<1   bridge reflection (bridge impedance ~1000x string impedance);
//         its loss is folded into g0.
// The delay line is shortened to compensate the phase delay of Hd and Hl
// at the fundamental, as the article prescribes.
//
// The hammer's hysteretic felt F(u) = F0 u^p (1 + alpha du/dt) is commuted
// into its perceptual effect: a raised-cosine force pulse whose duration
// shrinks and whose spectrum brightens with hammer velocity (p in 2..4
// makes loud notes disproportionately bright).
//
// The soundboard is the article's feedback delay network: 4 delay lines,
// Hadamard feedback matrix, per-line frequency-dependent losses, a sharp
// ~100 Hz highpass (bending waves slower than sound in air below it), and
// two decorrelated output taps for stereo.
//============================================================================

//---------------------------------- controls --------------------------------
freq = hslider("freq [unit:Hz]", 220, 27.5, 4186, 0.01);
gain = hslider("gain", 0.7, 0, 1, 0.01);          // hammer velocity
gate = button("gate");

stiffness = hslider("v:piano/[0]stiffness", 0.25, 0, 0.9, 0.01);
t60       = hslider("v:piano/[1]t60 [unit:s]", 14, 1, 30, 0.1);
damping   = hslider("v:piano/[2]damping", 0.25, 0, 0.9, 0.01);
detune    = hslider("v:piano/[3]detune [unit:cents]", 1.2, 0, 10, 0.1);
direct    = hslider("v:piano/[4]direct", 0.1, 0, 1, 0.01);
sbT60     = hslider("v:soundboard/[0]sb_t60 [unit:s]", 0.4, 0.1, 2, 0.01);
sbDamp    = hslider("v:soundboard/[1]sb_damp [unit:Hz]", 4500, 500, 12000, 1);
volume    = hslider("v:piano/[5]volume", 0.5, 0, 1, 0.01);

//---------------------------------- hammer ----------------------------------
// Raised-cosine force pulse: contact time ~1-3 ms, shorter for high notes
// and hard hits; brightness follows velocity (the felt stiffens, p > 1).
trig  = gate : ba.impulsify;
timer = (+(1) : *(1 - trig)) ~ _ : /(ma.SR);      // seconds since key-on
// Contact shortens with pitch (~2.5 ms in the bass, ~0.3 ms at C8): the
// pulse's first spectral null sits at 2/tc, and a treble string is only
// excited at all if that null lies above its fundamental.
tc    = (0.00025 + 0.0018 * (220/freq)^(0.6)) * (1.35 - 0.6*gain)
        : max(0.0002) : min(0.0035);
pulse = 0.5 * (1 - cos(2*ma.PI * timer/tc)) * (timer < tc);
// The dcblocker keeps the excitation zero-mean: the folded string loop has
// a DC gain of 1/(1-g0), and a unipolar force pulse would pile up there.
// The (f/220)^0.25 term leans against the shorter pulse's lower energy so
// the keyboard stays roughly level.
hammer = pulse * gain^(1.5) * min(2.5, (freq/220)^(0.25))
         : fi.lowpass(1, 700 + 11000*gain*gain)
         : fi.dcblocker;

//---------------------------------- string ----------------------------------
nAP = 4;   // dispersion allpass sections per string

// The excitation is highpassed at f0/4 before entering the loop: the loop's
// DC gain is 1/(1-g0) -- in the thousands for short treble strings -- so any
// sub-harmonic content in the pulse would pile up over the round trips.
// Filtering outside the loop leaves the loop's tuning and losses untouched.
string(f0) = fi.highpass(2, f0*0.25)
             : (+ : de.fdelay4(4096, dl) : dispersion : lossFilter) ~ *(g0)
with {
    // Dispersion: allpass coefficient grows with pitch, as inharmonicity
    // B does on a real piano (short stiff treble strings). The magnitude is
    // capped by the delay budget: the highest notes have loops of only a
    // dozen samples, and the cascade's own phase delay must fit inside.
    w = 2 * ma.PI * f0 / ma.SR;
    budget = max(0.5, (ma.SR/f0 - 4) / nAP);      // per-section delay budget
    alim = max(0, (budget - 1) / (budget + 1));
    a  = 0 - min(min(0.75, stiffness * sqrt(f0/1000)), alim);
    ap = fi.tf1(a, 1, a);
    dispersion = seq(i, nAP, ap);
    // Exact phase delay of the cascade at the fundamental (not at DC: the
    // whole point of the filter is that those differ).
    apDelay = nAP * (atan2(sin(w), a + cos(w))
                     - atan2(a*sin(w), 1 + a*cos(w))) / w;

    // Loss: g0 sets tau at low frequency (c1 term, bridge loss included),
    // the one-pole lowpass adds the w^2 term (c3).
    g0 = exp(-6.91 / (t60 * f0));
    // The one-pole coefficient shrinks with pitch: a fixed coefficient
    // takes a fixed bite per round trip, and short treble strings make
    // thousands of round trips per second -- a mid-range setting would
    // kill a C8 in milliseconds. Scaling by 300/f0 keeps the *rate* of
    // high-frequency loss (the c3 w^2 term) in a realistic range across
    // the keyboard.
    s  = damping * min(1, 300/f0);
    lossFilter = *(1 - s) : + ~ *(s);
    lossDelay = atan2(s*sin(w), 1 - s*cos(w)) / w;   // exact, at f0

    // One round trip, minus what the filters and the feedback already delay.
    dl = max(2, ma.SR/f0 - apDelay - lossDelay - 1);
};

cents(c) = 2^(c/1200);

// Two strings per note, detuned around f0: their beating gives the piano's
// two-stage decay; both terminate on the same bridge.
bridge = hammer <: string(freq*cents(0-detune*0.5)), string(freq*cents(detune*0.5)) :> *(0.5);

//-------------------------------- soundboard --------------------------------
// 4x4 FDN, Hadamard feedback, per-line losses g_i = 10^(-3 d_i / (SR*T60))
// and a lowpass so decay shortens with frequency, as measured soundboards do.
sbDelays(0) = 1123; sbDelays(1) = 1471; sbDelays(2) = 1811; sbDelays(3) = 2287;

soundboard(x) = loop ~ si.bus(4) : mixdown
with {
    // ro.hadamard is the library's butterfly Hadamard; it is unnormalized
    // (entries +/-1, so a gain of sqrt(4) = 2), hence the 0.5 per line to
    // keep the matrix orthonormal and the loop lossless-at-most.
    line(i) = *(10^(-3.0 * sbDelays(i) / (ma.SR * sbT60)))
              : fi.lowpass(1, sbDamp)
              : de.delay(4096, sbDelays(i));
    // Inject after the matrix: adding x before it would cancel on three of
    // the four Hadamard rows and feed only one line.
    loop = ro.hadamard(4) : par(i, 4, *(0.5) : +(x*0.5) : line(i));
    // Two decorrelated taps -> stereo; sharp highpass at the ~100 Hz
    // bending-wave cutoff, gentle lift of the dense low-mid resonances.
    shape = fi.highpass(4, 95) : fi.peak_eq(3, 150, 180);
    mixdown(y1, y2, y3, y4) = (y1 - y3 : shape), (y2 - y4 : shape);
};

//---------------------------------- output ----------------------------------
process = bridge <: _, soundboard : mix
with {
    mix(d, l, r) = (d*direct + l) * volume, (d*direct + r) * volume;
};
