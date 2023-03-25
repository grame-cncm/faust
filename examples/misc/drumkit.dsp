
//-------------------------------------------------
// 		A simple, fully generative
//		drum machine
//-------------------------------------------------

import("stdfaust.lib");

drumkit(gate, ks, ss, hs) = k_seq, s_seq, h_seq :> /(3)
    with {
        N = outputs(ks);
        env = en.ar(0.001, 0.05);
        kick(g) = g : env : *(os.osc(100));
        snare(g) = g : env : *(no.noise : fi.low_shelf(-60, 3000));
        hihat(g) = g : env : *(no.noise : fi.highpass(3, 10000));
        sequencer(t) = t : ba.selectn(N, gate : ba.pulse_countup_loop(N - 1, 1)) : *(gate : mem);
        k_seq = sequencer(ks) : kick;
        s_seq = sequencer(ss) : snare;
        h_seq = sequencer(hs) : hihat;
    };

drumkit_ui(n) = drumkit(attach(gate, nn), ks, ss, hs)
    with {
        gate = ba.pulse(ba.tempo(bpm));
        ks = par(i, n, checkbox("v:Drum kit/h:[0]kick/%2i"));
        ss = par(i, n, checkbox("v:Drum kit/h:[1]snare/%2i"));
        hs = par(i, n, checkbox("v:Drum kit/h:[2]hihat/%2i"));
        bpm = hslider("v:Drum kit/[4]BPM", 350, 10, 800, 1);
        mon = par(i, n, hbargraph("v:Drum kit/h:[3]seq/%2i[style:led]", 0, 1));
        nn = 1 : ba.selectoutn(n, gate : ba.pulse_countup_loop(n - 1, 1)) : mon :> _;
    };

drumkit_ui_demo = drumkit_ui(15) <: (_, _);

process = drumkit_ui_demo;

