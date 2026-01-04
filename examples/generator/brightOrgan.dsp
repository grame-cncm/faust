import("stdfaust.lib");

declare name "brightOrgan";
declare author "Claude AI";

// Safe frequency limit (well below Nyquist)
MAX_FREQ = ma.SR / 2 - 1000;

// Safe filter function - clamps frequency to safe range
safe_resonlp(f, q, gain) = fi.resonlp(min(f, MAX_FREQ * 0.4), q, gain);
safe_lowpass(order, f) = fi.lowpass(order, max(20, min(f, MAX_FREQ * 0.9)));

// Organ parameters
freq = hslider("h:Main/freq [style:knob][midi:ctrl 1]", 220, 55, 880, 0.1);
gate = button("h:Main/gate [midi:ctrl 64]");
volume = hslider("h:Main/volume [style:knob][midi:ctrl 7]", 0.5, 0, 1, 0.01);

// Organ stops
foundation8 = hslider("h:Stops/Foundation 8' [style:knob][midi:ctrl 14]", 0.8, 0, 1, 0.01);
principal4 = hslider("h:Stops/Principal 4' [style:knob][midi:ctrl 15]", 0.5, 0, 1, 0.01);
fifteenth2 = hslider("h:Stops/Fifteenth 2' [style:knob][midi:ctrl 16]", 0.3, 0, 1, 0.01);
flute8 = hslider("h:Stops/Flute 8' [style:knob][midi:ctrl 17]", 0.4, 0, 1, 0.01);
nasard = hslider("h:Stops/Nasard 2 2/3' [style:knob][midi:ctrl 18]", 0.2, 0, 1, 0.01);
tierce = hslider("h:Stops/Tierce 1 3/5' [style:knob][midi:ctrl 19]", 0.15, 0, 1, 0.01);

// Reverb parameters
reverbAmount = hslider("h:Reverb/Amount [style:knob][midi:ctrl 91]", 0.3, 0, 1, 0.01);
reverbDamp = hslider("h:Reverb/Damp [style:knob][midi:ctrl 92]", 0.5, 0, 1, 0.01);
reverbSize = hslider("h:Reverb/Size [style:knob][midi:ctrl 93]", 0.6, 0, 1, 0.01);

// Organ pipe generator (filtered square wave + breath noise)
organ_pipe(f, brightness) = pipe
with {
    // Clamp frequency to safe range
    safe_f = min(f, MAX_FREQ);
    
    // Square wave with odd harmonics
    square = os.square(safe_f);
    
    // Low-pass filter to soften the sound
    cutoff = safe_f * (2 + brightness * 8);
    filtered = square : safe_lowpass(2, cutoff);
    
    // Characteristic organ breath noise (with safe filter)
    breath = no.noise * 0.015 : safe_resonlp(safe_f, 1, 1);
    
    pipe = filtered + breath;
};

// Flute pipe (more sinusoidal)
flute_pipe(f) = pipe
with {
    // Clamp frequency to safe range
    safe_f = min(f, MAX_FREQ);
    
    // Dominant sinusoidal fundamental
    fundamental = os.osc(safe_f);
    // Some harmonics (only if frequency allows)
    h2 = os.osc(min(safe_f * 2, MAX_FREQ)) * 0.25 * (safe_f * 2 < MAX_FREQ);
    h3 = os.osc(min(safe_f * 3, MAX_FREQ)) * 0.08 * (safe_f * 3 < MAX_FREQ);
    // Flute breath noise (with safe filter)
    breath = no.noise * 0.02 : safe_resonlp(safe_f * 1.5, 2, 1);
    
    pipe = fundamental + h2 + h3 + breath;
};

// Combined stops
organ = (
    // Foundation 8' (fundamental)
    organ_pipe(freq, 0.3) * foundation8 +
    
    // Principal 4' (upper octave)
    organ_pipe(freq * 2, 0.4) * principal4 +
    
    // Fifteenth 2' (two octaves)
    organ_pipe(freq * 4, 0.5) * fifteenth2 +
    
    // Flute 8'
    flute_pipe(freq) * flute8 +
    
    // Nasard 2 2/3' (perfect fifth)
    flute_pipe(freq * 3) * nasard * 0.7 +
    
    // Tierce 1 3/5' (major third)
    flute_pipe(freq * 5) * tierce * 0.5
) / 4;

// Organ envelope (characteristic slow attack)
env = en.asr(0.1, 1, 0.2, gate);

// Dry signal
dry = organ * env * volume;

// Smaller reverb with adjustable parameters
reverb(x) = x : re.mono_freeverb(reverbSize, reverbDamp, 0.3, 6000);

// Dry/wet mix
output = dry * (1 - reverbAmount * 0.5) + reverb(dry) * reverbAmount;

// Stereo output
process = output <: _,_;
