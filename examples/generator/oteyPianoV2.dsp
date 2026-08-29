declare name "OteyPiano";
declare author "Faust port of C. Otey's piano model (Stanford Ph210, 2007) by Claude Fable AI";
declare reference "http://large.stanford.edu/courses/2007/ph210/otey2/";
declare options "[midi:on] [nvoices:8]";

import("stdfaust.lib");

//============================================================================
// A physical model of the piano, ported from C. Otey's original C code
// (piano.cpp / dwgs.cpp / filter.cpp / reverb.cpp, December 2007).
//
//   hammer pulse -> strike-point comb -> up to 3 detuned waveguide strings
//   -> bridge (impedance-ratio reflection) -> 8-line circulant FDN
//      soundboard -> stereo taps
//
// The physical string parameters (length, radius, tension, impedance Z,
// inharmonicity B) follow piano.cpp's closed-form fits in the note's
// frequency; the loss filter and the dispersion allpass use filter.cpp's
// exact designs.  The hammer is commuted to a velocity-shaped pulse (the
// original integrates the hysteretic felt ODE at 3x oversampling; its
// perceptual effect -- shorter, brighter, disproportionately loud contact
// at high velocity -- is kept).  Strings per note (1 bass / 2 mid / 3
// treble) and their detune {1, 1.0003, 0.9996} are the original's TUNE.
//============================================================================

freq = hslider("freq [unit:Hz]", 220, 27.5, 4186, 0.01);
gain = hslider("gain", 0.7, 0, 1, 0.01);          // hammer velocity
gate = button("gate");

c1     = hslider("v:piano/[0]c1 [tooltip:string loss, low partials]", 0.5, 0.05, 2, 0.01);
c3     = hslider("v:piano/[1]c3 [tooltip:string loss, high partials]", 5.85, 0.5, 30, 0.05);
direct = hslider("v:piano/[2]direct", 0.06, 0, 1, 0.01);
volume = hslider("v:piano/[3]volume", 0.7, 0, 1, 0.01);

//------------------------- physical string parameters -----------------------
// Straight from Piano::Piano() in piano.cpp.
f0c  = 27.5;
lr   = log(freq/f0c) / log(4192.0/f0c);           // 0..1 across the keyboard
Lstr = 0.04 + 1.4 / (1 + exp(-3.4 + 1.4*log(freq/f0c)));
rstr = 0.002 * (1 + 0.6*log(freq/f0c))^(-1.4);    // string radius (m)
rhoL = ma.PI * rstr * rstr * 7850;                // linear mass density
Tstr = (2*Lstr*freq)^2 * rhoL;                    // tension
Zstr = sqrt(Tstr * rhoL);                         // string impedance
Zb   = 4000;                                      // bridge impedance
rcore = min(rstr, 0.0006);                        // wound bass: steel core
Bstiff = ma.PI^3 * 200e9 * rcore^4 / (4 * Lstr*Lstr * Tstr);  // inharmonicity

// 1 string below midi 31, 2 below 41, 3 above -- computed from freq.
midinote = 69 + 12*log(freq/440)/log(2);
nstr  = 1 + (midinote >= 31) + (midinote >= 41);
ZbEff = Zb + (nstr-1)*Zstr;
// Velocity-wave reflection at the bridge junction, and the transmission
// that drives the soundboard (piano.cpp's 2Z/(Z*nstrings+Zb)).
rBridge = (ZbEff - Zstr) / (ZbEff + Zstr);
outCoupling = 2*Zstr / (Zstr*nstr + Zb);

//---------------------------------- hammer ----------------------------------
trig  = gate : ba.impulsify;
timer = (+(1) : *(1 - trig)) ~ _ : /(ma.SR);      // seconds since key-on
tc    = (0.0002 + 0.0009 * (220/freq)^(0.6)) * (1.35 - 0.6*gain)
        : max(0.0002) : min(0.0035);
pulse = 0.5 * (1 - cos(2*ma.PI * timer/tc)) * (timer < tc);
// Strike point at 1/7 of the string (piano.cpp's hp): the wave reflected
// from the near pin returns inverted after hp/f seconds, notching every
// 7th partial -- the comb the ear knows a piano by.
hp = 1.0/7.0;
strikeComb = _ <: _, de.fdelay2(1024, hp * ma.SR/freq) : -;
// Zero-mean, velocity-brightened excitation (commuted hammer).
// The final highpass keeps sub-harmonics out of the string loops (their DC
// gain is enormous); it lives here, on the excitation, NOT inside the loops,
// where its phase lead would detune them.
hammer = pulse * gain^(1.5) * min(2.5, (freq/220)^(0.25))
         : fi.lowpass(1, 1400 + 16000*gain*gain)
         : strikeComb
         : fi.dcblocker : fi.highpass(2, freq*0.25);

//---------------------------------- string ----------------------------------
// One folded waveguide loop per string: delay, Thiran dispersion, loss
// filter, bridge reflection.  Filters use filter.cpp's exact designs, and
// the delay line is shortened by their measured phase delay at f0.

// Thiran allpass section delay from filter.cpp's empirical Db(B,f,M).
thiranD(f, M) = exp(Cd - Ikey*kd)
with {
    C1 = ba.if(M == 4, 0.069618, 0.071089);
    C2 = ba.if(M == 4, 2.0427,   2.1074);
    k1 = ba.if(M == 4, -0.00050469, -0.0026580);
    k2 = ba.if(M == 4, -0.0064264,  -0.014811);
    k3 = ba.if(M == 4, -2.8743,     -2.9018);
    logB = log(Bstiff);
    kd = exp(k1*logB*logB + k2*logB + k3);
    Cd = exp(C1*logB + C2);
    Ikey = log(f * 2^(1.0/12.0) / 27.5) / log(2^(1.0/12.0));
};

// One string's forward path: delay, Thiran dispersion, loss filter.  The
// bridge reflection is NOT folded in here any more -- it happens at the
// shared junction in `bridge` below, so the strings can couple.
stringBody(f0) = de.fdelay4(4096, dl) : dispersion : lossFilter
with {
    w = 2 * ma.PI * f0 / ma.SR;

    // Dispersion: 4 Thiran sections below 400 Hz, 1 above (dwgs.cpp), each
    // of delay D; bypassed when D <= 1, as in thiriandispersion().
    M = ba.if(f0 > 400, 1, 4);
    D = thiranD(f0, M);
    active(i) = (D > 1) & ((i == 0) | (f0 <= 400));
    a1t = -2*(D - 2)/(D + 1);
    a2t = (D - 1)*(D - 2)/((D + 1)*(D + 2));
    sec(i) = fi.tf2(select2(active(i), 1, a2t), select2(active(i), 0, a1t),
                    select2(active(i), 0, 1),
                    select2(active(i), 0, a1t), select2(active(i), 0, a2t));
    dispersion = seq(i, 4, sec(i));
    // Exact phase delay of one active section at f0.
    pdSec = 0 - (atan2(0 - (a1t*sin(w) + sin(2*w)), a2t + a1t*cos(w) + cos(2*w))
                 - atan2(0 - (a1t*sin(w) + a2t*sin(2*w)), 1 + a1t*cos(w) + a2t*cos(2*w))) / w
            : +(2*ma.PI/w * ((a2t + a1t*cos(w) + cos(2*w)) < 0));  // unwrap
    dispDelay = M * pdSec * (D > 1);

    // Loss filter, filter.cpp's loss(): H(z) = g(1+a1)/(1 + a1 z^-1) with
    // g = 1 - c1/f0 and a1 from c3 -- the tau(w) = 1/(c1 + c3 w^2) design.
    lg  = 1 - c1/f0;
    bb  = 4*c3 + f0;
    a1l = (0 - bb + sqrt(bb*bb - 16*c3*c3)) / (4*c3);
    lossFilter = fi.tf1(lg*(1 + a1l), 0, a1l);
    pdLoss = atan2(0 - a1l*sin(w), 1 + a1l*cos(w)) / w;

    dl = max(2, ma.SR/f0 - dispDelay - pdLoss - 1);
};

// The original's TUNE[3] = {1, 1.0003, 0.9996}; extra strings are silent
// where the register uses fewer.  All strings meet the bridge at ONE
// scattering junction (dwgs.cpp shares the load across them): the wave
// reflected into string k is o_k - t*S, with S the sum of the incoming
// string velocities and t = 2Z/(nZ+Zb).  For one string this reduces to
// the (Zb-Z)/(Zb+Z) reflection; for two or three, the in-phase motion
// pours energy into the bridge and dies fast while the detuned strings
// drift out of phase and sustain -- the piano's two-stage decay.
tJ = 2*Zstr / (Zstr*nstr + Zb);
bridge = (couple ~ si.bus(3)) : sumS * 100
with {
    on2 = nstr >= 2;
    on3 = nstr >= 3;
    sumS(o1, o2, o3) = tJ * (o1 + o2*on2 + o3*on3);
    couple(o1, o2, o3) = stringBody(freq,        hammer + o1 - s),
                         stringBody(freq*1.0003, hammer + o2 - s),
                         stringBody(freq*0.9996, hammer + o3 - s)
    with { s = sumS(o1, o2, o3); };
};

//-------------------------------- soundboard --------------------------------
// reverb.cpp verbatim: 8 delay lines, circulant feedback matrix with first
// row {a, 1+a, a, ..., a}, a = -1/4 (all eigenvalues on the unit circle),
// and a loss(Fs/len, 20, 20) filter per line.  The original sums the lines
// with alternating +/-1/8 into mono; a second, differently alternating tap
// gives an equally valid decorrelated channel for stereo.
sbLen(0) = 37;  sbLen(1) = 87;  sbLen(2) = 181; sbLen(3) = 271;
sbLen(4) = 359; sbLen(5) = 592; sbLen(6) = 687; sbLen(7) = 721;

soundboard(x) = (fb ~ si.bus(8)) : taps
with {
    aC = -0.25;
    lossLine(k) = fi.tf1(lg*(1 + a1l), 0, a1l)
    with {
        f0 = ma.SR / sbLen(k);
        lg  = 1 - 20.0/f0;
        bb  = 4*20.0 + f0;
        a1l = (0 - bb + sqrt(bb*bb - 16.0*20.0*20.0)) / (4*20.0);
    };
    line(k) = de.delay(1024, sbLen(k)) : lossLine(k);
    fb(o0, o1, o2, o3, o4, o5, o6, o7) =
        line(0, x + aC*s + o1), line(1, x + aC*s + o2),
        line(2, x + aC*s + o3), line(3, x + aC*s + o4),
        line(4, x + aC*s + o5), line(5, x + aC*s + o6),
        line(6, x + aC*s + o7), line(7, x + aC*s + o0)
    with { s = o0+o1+o2+o3+o4+o5+o6+o7; };
    taps(o0, o1, o2, o3, o4, o5, o6, o7) =
        0.5/8 * (o0 - o1 + o2 - o3 + o4 - o5 + o6 - o7),
        0.5/8 * (o0 + o1 - o2 - o3 + o4 + o5 - o6 - o7);
};

//---------------------------------- output ----------------------------------
process = bridge <: _, soundboard : mix
with {
    mix(d, l, r) = (d*direct + l) * volume, (d*direct + r) * volume;
};
