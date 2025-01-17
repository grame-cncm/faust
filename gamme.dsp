//  faust2caqt djembe.dsp 
import("stdfaust.lib");
gpitch = ba.pulsen(1, 20000) : ondemand(waveform{60, 62, 64, 65, 67, 69, 71, 72}:!,_) : ba.midikey2hz;
process = ba.pulsen(5000, 20000) : en.adsr(0.05,0.05,0.99, 0.15) * os.osc(gpitch) <: dm.freeverb_demo;