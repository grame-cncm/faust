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

wrap(s) = s - int(s);
normsin(s) = sin(2 * ma.PI * s);
phasor(f) = (os.sawtooth(f) + 1) / 2;
stretch(ms) = ba.countdown(ma.SR * ms / 1000) : >(0);
pulsetrain(ms, n, trig) =  (trig: stretch(ms * n)) * ba.pulse(ma.SR * ms / 1000);

cricket(f1, f2, trig) = s1 : *(44) <: ((aa.clip(0, 1.0): wrap), (aa.clip(1.0, 4.0) : wrap)) :> (+):
               normsin : aa.clip(0.0, 1.0) : *(s2) : *(0.3): *(e)
               with {
                   f = 0.8;
                   sig = phasor(f);
                   phase = sig : ba.sAndH(trig);
                   s1 = wrap(sig + (1 - phase));
                   s2 = os.osc(f1) + os.osc(f2);
                   e = trig : stretch(1000 / f);
               };

trig1 = no.sparse_noise(0.1) :  abs : >(0) : pulsetrain(500, 5);
trig2 = no.sparse_noise(0.15) : abs : >(0) : pulsetrain(300, 3);
trig3 = no.sparse_noise(0.05) : abs : >(0) : pulsetrain(250, 6);
waterfall = no.noise <: ((fi.resonlp(1000, 1, 0.3) * (0.5 + (no.lfnoise(0.2) ^ 2) * 0.5)),
                          fi.resonhp(5000, 1, 0.03)) :> _;

process = cricket(5134, 12342, trig1) +
          cricket(3134, 8342,  trig2) +
          cricket(8134, 15342, trig3) +
          waterfall;
