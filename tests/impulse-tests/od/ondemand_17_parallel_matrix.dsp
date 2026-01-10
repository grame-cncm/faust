import("stdfaust.lib");

outerGate = checkbox("outer") == 0;

gates = (checkbox("g1") == 0, checkbox("g2") == 0, checkbox("g3") == 0);
freqs = (200, 300, 400);

process = outerGate : ondemand(par(i, 3, voice(i)) :> _)
with {
  gate(i) = gates : ba.selector(i, 3);
  freq(i) = freqs : ba.selector(i, 3);
  voice(i) = gate(i) : ondemand(os.osc(freq(i)));
};
