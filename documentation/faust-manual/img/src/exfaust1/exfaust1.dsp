
import("stdfaust.lib");
freq = hslider("freq",440,50,2000,0.01);
process = os.sawtooth(freq);

