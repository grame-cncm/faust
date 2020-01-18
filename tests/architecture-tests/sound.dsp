
import("stdfaust.lib");

so_loop_speed(s, part, speed) = (part, reader(s)) : outs(s)
	with {
		length(s) = part,0 : s : _,si.block(outputs(s)-1);
		srate(s) = part,0 : s : !,_,si.block(outputs(s)-2);
		outs(s) = s : si.block(2), si.bus(outputs(s)-2);
		reader(s) = float(speed*srate(s))/ma.SR : (+,length(s):fmod)~_ : int;
	};

part = nentry("file", 0, 0, 10, 1);
speed = hslider("speed", 1, 0, 4, 0.01);

process = so_loop_speed(soundfile("s1.wav",1), part, speed),
			so_loop_speed(soundfile("s2.wav",1), part, speed) : dm.freeverb_demo;
