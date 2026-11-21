// Test voice for mcu-poly-test.cpp: a filtered saw with an envelope, a
// [poly:mode] assign mode, a [poly:voice] stereo spread and an effect.
declare name "mcu-poly-voice";
declare options "[nvoices:6]";
import("stdfaust.lib");

freq    = hslider("freq", 220, 20, 10000, 0.01);
gain    = hslider("gain", 0.8, 0, 1, 0.01);
gate    = button("gate");
attack  = hslider("Attack [midi:ctrl 73]", 0.01, 0, 1, 0.001);
release = hslider("Release", 0.2, 0.001, 2, 0.001);
cutoff  = hslider("Cutoff", 2000, 50, 10000, 1);
keys    = hslider("keys [poly:mode] [style:menu{'rotate':0;'reuse':1;'unison':2}]", 0, 0, 2, 1);
voice   = hslider("voice [poly:voice]", 0, 0, 15, 1);
spread  = hslider("Spread", 0.5, 0, 1, 0.01);

env   = en.asr(attack, 1, release, gate);
pan   = 0.5 + spread * (voice / 15 - 0.5);
osc   = os.sawtooth(freq) : fi.lowpass(2, cutoff) : *(env * gain) : attach(_, keys);
process = osc <: *(1 - pan), *(pan);

mix   = hslider("Mix", 0.3, 0, 1, 0.01);
echo  = de.delay(4096, 2400);
effect = par(i, 2, _ <: _ * (1 - mix) + echo * mix);
