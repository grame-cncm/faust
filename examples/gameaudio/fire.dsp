import("stdfaust.lib");

//----------------------------`fire`---------------------------
// fire(is_wet) : produces burning fire sound
//
// #### Usage
//
// ```
// fire(is_wet) : _
// ```
//
// Where:
//
// * `is_wet`: a binary flag/signal adding wet wood
//             popping sound
//
// #### Example
//
// ```
// checkbox("wet") : fire : _
// ```
//
//------------------------------------------------------------

sq(x) = x * x;
stretch(ms) = ba.countdown(ma.SR * ms / 1000): >(0);

crackle(dens, rel) = ((no.noise : fi.lowpass(3, 10000)) * 0.77 * os.osc(50 / dens) * 
                      en.arfe(0.001, release, 0, trigger: >(0)
                      : stretch(sus)))
                      : fi.highpass(3, 1000)
    with {
        trigger = no.sparse_noise(dens): abs;
        sus = 2 + (trigger: ba.latch(trigger) * 8);
        release = rel + (0.3 * (no.noise : abs : ba.latch(trigger)));
    };

fire(is_wet) = (is_wet * wet) + (base <: (_, fi.lowpass(3, 1000), fi.highpass(3, 10000)) :> _)
    with {
        hiss = (no.noise : fi.lowpass(3, 500)) / 5;
        hiss2 = 0.8 * (no.noise : fi.highpass(3, 3000) / 8) * sq(no.lfnoise(1000));
        wet = (3 * crackle(0.1, 0.05)) + (2 * crackle(0.2, 0.3));
        base = hiss + hiss2 + (0.2 * crackle(5, 0.1));
    };

process = checkbox("wet"): fire;
