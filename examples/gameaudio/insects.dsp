import("stdfaust.lib");

//---------------------------`cricket`-------------------------
// cricket(f1, f2, trig) : produces a cricket chirp,
//                         the cricket sound based on examples
//                         from the book "Designing Sound"
//                               by Andy Farnell
//
// #### Usage
//
// ```
// cricket(f1, f2, trig) : _
// ```
//
// Where:
//
// * ` f1 `: frequency of the first harmonic of the chirp
// * ` f2 `: frequency of the second harmonic of the chirp
// * `trig`: the trigger impulse
//
// #### Examples
//
// ```
// ba.pulse(20000) : cricket(5134, 12342) : _
// ```
// or
// ```
// button("chirp") : ba.impulsify : cricket(5134, 12342, trig1) : _
// ```
//
//------------------------------------------------------------

//--------------------------`critters`------------------------
// critters(freqs) : produces background 'critters' sound,
//                            based on examples
//                            from the book "Designing Sound"
//                                  by Andy Farnell
//
// #### Usage
//
// ```
// critters(freqs) : _
// ```
//
// Where:
//
// * `freqs`: a list with 4 frequencies
//
// #### Examples
//
// ```
// critters((2012, 4, 20, 2)) : _
// ```
//
//------------------------------------------------------------

//----------------------------`frog`--------------------------
// frog(l, f, trig) : produces a frog croaking sound,
//                             based on examples
//                             from the book "Designing Sound"
//                                   by Andy Farnell
//
// #### Usage
//
// ```
// frog(l, f, trig) : _
// ```
//
// Where:
//
// * ` l  `: length of the croak in [ms]
// * ` f  `: the frequency of resonance (don't go below ~300Hz)
// * `trig`: the trigger impulse
//
// #### Examples
//
// ```
// button("croak") : ba.impulsify : frog(250, 900) : _
// ```
//
//------------------------------------------------------------


wrap(s) = s - int(s);
normsin(s) = sin(2 * ma.PI * s);
normcos(s) = cos(2 * ma.PI * s);
phasor(f) = os.phasor(1, f);
stretch(ms) = ba.countdown(ma.SR * ms / 1000) : >(0);
pulsetrain(ms, n, trig) =  (trig: stretch(ms * n)) * ba.pulse(ma.SR * ms / 1000);

cricket(f1, f2, trig) = s1 : *(44) <: ((aa.clip(0, 1.0): wrap), (aa.clip(1.0, 4.0) : wrap)) :> (+):
               normsin : aa.clip(0.0, 1.0) : *(s2) : *(0.3): *(e)
               with {
                   f = 0.8;
                   sig = phasor(f);
                   phase = sig : ba.sAndH(trig);
                   s1 = wrap(sig + (1 - phase));
                   s2 = os.osc(f1) + os.osc(f2) : *(no.lfnoise(500));
                   e = trig : stretch(1000 / f);
               };

water = no.noise : abs : ba.sAndH(no.sparse_noise(250) : abs : >(0)) :
        *(1200) : +(400) : os.osc : fi.resonhp(850, 15, 1) : *(0.008);

hum = no.noise : fi.resonlp(800, 1, 0.08);

critters(freqs) = freqs : prod(i, ba.count(freqs), phasor: normcos):>
           fi.resonhp(20, 1, 1) : *(os.osc(0.01)): *(0.025);

frog(l, f, trig) = out
    with {
        sq(x) = x * x;
        src = en.asr(0.0, 1.0, l / 1000, trig);
        ch1 = 1.0 / (src : max(0.5): *(-1.0): +(ch2): *(3): sq: *(2): -(1) : wrap *(122): sq: +(1));
        ch2 = src : min(0.5);
        ch3 = (1 - src) <: ((max(0.9) : *(-1)), min(0.5)) :> *(3) <: ((*(40): +(f)), (*(90): +(2 * f)), (*(240): +(3 * f)));
        out = ch3 : vcf(ch1, 5), vcf(ch1, 4), vcf(ch1, 3) : (*(0.45), _, *(0.45)) :> fi.resonhp(10, 1, 1): *(0.5);
        vcf(s, res, f) = s : fi.resonbp(f, res, 1): fi.resonlp(1400, 1, 1);
    };

process = insects, background : ro.interleave(2, 2) : par(i, 2, sum(j, 2, _))
    with {
        N = ba.count(channels);
        trig_data = ((0.1, 500, 5),  (0.15, 300, 3),
                     (0.05, 250, 6), (0.0921, 320, 4),
                     (0.093, 250, 3), (0.09, 300, 2), (0.087, 150, 5));
        channels = (cricket(5134, 12342),
                    cricket(3134, 8342),
                    cricket(8134, 15342),
                    cricket(6134, 1842),
                    frog(250, 900),
                    frog(400, 600),
                    frog(200, 800));
        spat(rng1, rng2, trig) = sp.spat(2, r, d)
            with {
                r = rng1 : abs : ba.sAndH(trig);
                d = rng2 : abs : ba.sAndH(trig);
            };
        trig(f, ms, n) = no.sparse_noise(f) : abs : >(0) <:  (_, pulsetrain(ms, n));
        trigsm = trig_data : par(i, N, trig): ro.interleave(2, N);
        btrigs = trigsm : (si.bus(N), si.block(N));
        trigs =  trigsm : (si.block(N), si.bus(N));
        spats = (no.multinoise(2 * N), btrigs, (trigs : channels)) : ro.interleave(N, 4): par(i, N, spat);
        insects = spats : ro.interleave(2, N) : par(i, 2, sum(j, N, _));
        background = water + hum +
                     critters((2012, 4, 20, 2)) +
                     critters((2134, 4.279, 20.4, 15.5)) : *(0.4) <: (_, _);
    };
