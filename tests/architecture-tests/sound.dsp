
import("stdfaust.lib");

speed =  hslider("speed", 1, 0, 4, 0.01);

process = so.loop_rate(soundfile("s1.wav",1), speed),
			so.loop_rate(soundfile("s2.wav",1), speed) : dm.freeverb_demo;
