//----------------------------`door`--------------------------
// door(force) : produces a creaking door sound,
//                          based on examples
//                          from the book "Designing Sound"
//                                by Andy Farnell
//
// #### Usage
//
// ```
// door(force) : _
// ```
//
// Where:
//
// * `force`: a float value between 0 and 1
//              (0.3 to 0.93 for best results)
//
// #### Examples
//
// ```
// door(hslider("force", 0, 0, 0.93, 0.001)) <: _, _;
// ```
//
//------------------------------------------------------------

import("stdfaust.lib");

stickslip(force) = metro : timer : *(1000) : min(100) : /(100) :
                   sqrt <: (+(0.1) : sqrt), (vline) : (*)
    with {
        swap(a, b) = (b, a);
        metro = force : ba.line(ba.sec2samp(0.1)) : (step1 ~ _);
        step1(t, s) = s <: (>(0.3)), (swap(1) : (-) <:
                   ((*(60) : +(3)), (*(6) : *(no.noise : abs : ba.sAndH(t)))) : (+)) : _, (/(1000) : ba.sec2samp : ba.pulse) : (*);
        timer(s) = 1 : ba.pulse_countup(((s : mem) == 0)) : /(ma.SR) : ba.sAndH(s);
        vline(s) = s <: _, mem : (!=) : en.ar(0, s / 1000) <: (*);
    };

wood1 = _ <: ((fs, qs, si.bus(6)) : ro.interleave(6, 3) : par(i, 6, flt)), *(0.2) :> _
    with {
        fs = (62.5, 125, 250, 395, 560, 790);
        qs = (1, 1, 2, 2, 3, 3);
        flt(f, q) = fi.resonbp(f, q, 1);
    };

wood2 = _ <: (ds, si.bus(8)) : ro.interleave(8, 2) : par(i, 8, res) :> fi.highpass(1, 125)
    with {
        res(b) = dfbe(b, 0.05);
        ds = (4.52, 5.06, 6.27, 8, 5.48, 7.14, 10.12, 16);
        dfbe(i, g) = ((+) : de.delay(ba.sec2samp(0.1), ba.sec2samp(i / 1000))) ~ (*(g));
    };

door(force) = stickslip(force) : wood1 : wood2 : *(0.2);

process = door(force) <: (_, _)
    with {
        force = button("door") : ba.impulsify : en.ar(2, 1.5) : *(0.61) : +(0.28);
    };
