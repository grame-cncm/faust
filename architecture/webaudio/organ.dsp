// Simple Organ
import("stdfaust.lib");

// MIDI keyon-keyoff
midigate = button ("gate");    
// MIDI keyon key                        	
midifreq = hslider("freq[unit:Hz]", 440, 20, 20000, 1);	
// MIDI keyon velocity
midigain = hslider("gain", 0.5, 0, 10, 0.01);	       	

// Implementation
phasor(f) = f/ma.SR : (+,1.0:fmod) ~ _ ;
osc(f) = phasor(f) * 6.28318530718 : sin;
timbre(freq) = osc(freq) + 0.5 * osc(2.0*freq) + 0.25 * osc(3.0*freq);
envelop(gate, gain) = gate * gain : smooth(0.9995)
with { 
	smooth(c) = * (1-c) : + ~ * (c); 
};
voice(gate, gain, freq) = envelop(gate, gain) * timbre(freq);

// Main
process = voice(midigate, midigain, midifreq) * hslider("volume", 0.5, 0, 1, 0.01);
