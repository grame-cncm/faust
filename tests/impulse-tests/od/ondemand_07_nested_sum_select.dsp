import("stdfaust.lib");

outerGate = checkbox("outer") == 0;
mode = hslider("mode[style:menu{'A':0;'B':1;'C':2}]", 0, 0, 2, 1);

process = outerGate : ondemand(sum(i, 3, gate(i) * voice(i)))
with {
  modeI = int(mode);
  gate(i) = (modeI == i);
  freq(i) = (220, 330, 440) : ba.selector(i, 3);
  voice(i) = gate(i) : ondemand(os.osc(freq(i)));
};
