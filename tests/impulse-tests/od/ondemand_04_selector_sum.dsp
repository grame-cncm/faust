import("stdfaust.lib");

freq = hslider("freq[unit:Hz]", 440, 50, 2000, 1);
mode = hslider("mode[style:menu{'Sine':0;'Saw':1;'Noise':2}]", 0, 0, 2, 1);

process = sum(i, 3, gate(i) * (gate(i) : ondemand(branch(i, freq))))
with {
  modeI = int(mode);
  gate(i) = (modeI == i);
  branch(i, f) = (os.osc(f), os.sawtooth(f), no.noise) : ba.selector(i, 3);
};
