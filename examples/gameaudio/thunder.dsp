import("stdfaust.lib");

//---------------------------`thunder`------------------------
// thunder(trig) : produces a rumbling thunder,
//                         based on examples
//                         from the book "Designing Sound"
//                               by Andy Farnell
//
// #### Usage
//
// ```
// thunder(trig) : _
// ```
//
// Where:
//
// * `trig`: the trigger impulse
//
// #### Examples
//
// ```
// button("rumble") : ba.impulsify : thunder;
// ```
//
//------------------------------------------------------------

N = 6;
TM = 100;

strike(t, v) =  t : e : *(no.noise) <: (fi.resonbp(f1, 3, 1),
                                        fi.resonbp(f2, 3, 1)) :> (_)
    with {
        vh = ba.sAndH(t, v);
        f1 = vh * 1200 + 100;
        f2 = f1 * 0.5;
        a = 1 - vh + 0.4 : pow(5) : *(200);
        e = en.ar(0, a / 1000);
    };

delay(t, d) = a : edge
    with
    {
        dd = d : ba.sAndH(t);
        a = en.ar(dd / 1000, 0, t);
        edge(s) = (s' != 0) & (s == 0); 
    };

integ_with_reset(s) = +(s) ~ (b)
    with {
        b(s) = ba.if(s < TM, s, 0);
    };

trig_and_delay(t, r) = s, d
    with {
        d = t * (r / 25) : integ_with_reset;
        s = ba.if(d < TM, t, 0);
    };

strikepattern(t) = out : (_, scale)
    with {
        rnd = round(abs(no.noise) * (TM-1));
        rnd_out(t) = rnd : ba.sAndH(t);
        out = t : ((+) <: (_, rnd_out) : trig_and_delay) ~ (delay);
        scale(x) = (TM - x) / TM;
    };

multistrike(t) = out : *(0.5)
    with {
        pat = t : strikepattern;
        fst(a, b) = a;
        snd(a, b) = b;
        strksv = pat : snd <: si.bus(N);
        sel = pat : fst : ba.selectoutn(N, pat : fst : ba.pulse_countup_loop(N-1, 1));
        out = sel, strksv : ro.interleave(N, 2) : par(i, N, strike) :> (_);
    };

black_noise(t) = e : *(a) : *(0.2)
    with {
        lpf = fi.resonlp(80, 1, 1);
        a = no.noise : lpf : lpf : fi.resonhp(10, 1, 1) : *(12) : aa.clip(-1, 1) : lpf : lpf;
        e = en.ar(3, 10, delay(t, 1000));
    };

echos(t) = out
    with {
        trig = delay(t, 200);
        e1 = en.ar(0, 0.6, trig);
        e2 = en.ar(0, 1.5, trig);
        s1 = e1 * 30 + 3;
        out = no.noise : fi.resonlp(s1, 1, 1) : *(80)
          : *(no.noise) : aa.clip(-1, 1) : fi.resonbp(333, 4, 1) : *(e2) : *(0.9);
    };

thunder(trig) = multistrike(trig), black_noise(trig), echos(trig) :> (_);

process = button("rumble") : ba.impulsify : thunder <: (_, _);

