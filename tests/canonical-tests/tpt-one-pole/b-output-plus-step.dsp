import("stdfaust.lib");
// the TPT one-pole lowpass : step v = G (x - s), output y = s + v, state s' = s + 2v
G = hslider("g", 0.1, 0.001, 0.4, 0.001);
x = _ : min(1) : max(-1);
process = x : (loop ~ _) : !,_ with { loop(s, x) = y + v, y with { v = G*(x - s); y = s + v; }; };
