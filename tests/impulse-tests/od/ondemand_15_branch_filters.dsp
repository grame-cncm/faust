import("stdfaust.lib");

outerGate = checkbox("outer") == 0;
mode = hslider("mode[style:menu{'LP':0;'HP':1;'SQ':2;'NOISE':3}]", 0, 0, 3, 1);
freq = hslider("freq", 300, 80, 1200, 1);

process = outerGate : ondemand(sum(i, 4, branch(i, freq)))
with {
  modeI = int(mode);
  gate(i) = (modeI == i);
  branch(i, f) = gate(i) : ondemand(src(i, f));
  src(0, f) = os.osc(f) : fi.lowpass(2, f);
  src(1, f) = os.osc(f) : fi.highpass(2, f);
  src(2, f) = os.square(f) : fi.lowpass(2, f / 2);
  src(3, f) = no.noise : fi.highpass(2, f / 2);
};
