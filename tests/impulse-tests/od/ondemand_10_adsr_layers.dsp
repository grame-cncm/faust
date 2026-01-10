import("stdfaust.lib");

outerGate = checkbox("outer") == 0;
gateA = checkbox("gateA") == 0;
gateB = checkbox("gateB") == 0;
rel = hslider("release", 0.4, 0.01, 2, 0.01);

play(freq, gate) = (env > 0) : ondemand(os.osc(freq) * env)
with {
  env = en.adsr(0.01, 0.1, 0.8, rel, gate);
};

mix = play(220, gateA) + play(330, gateB);

process = outerGate : ondemand(mix);
