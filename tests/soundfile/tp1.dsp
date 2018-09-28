import("stdfaust.lib");

so_play(s, part) = (part, reader(s)) : outs(s)
	with {
		length(s) = part,0 : s : _,si.block(outputs(s)-1);
		srate(s) = part,0 : s : !,_,si.block(outputs(s)-2);
		outs(s) = s : si.block(2), si.bus(outputs(s)-2);
		reader(s) = 1 : (+,length(s):fmod)~_ : int;
	};
	
so_loop(s, part) = (part, reader(s)) : outs(s)
	with {
		length(s) = part,0 : s : _,si.block(outputs(s)-1);
		srate(s) = part,0 : s : !,_,si.block(outputs(s)-2);
		outs(s) = s : si.block(2), si.bus(outputs(s)-2);
		reader(s) = float(srate(s))/ma.SR : (+,length(s):fmod)~_ : int;
	};
	
so_loop_speed(s, part, speed) = (part, reader(s)) : outs(s)
	with {
		length(s) = part,0 : s : _,si.block(outputs(s)-1);
		srate(s) = part,0 : s : !,_,si.block(outputs(s)-2);
		outs(s) = s : si.block(2), si.bus(outputs(s)-2);
		reader(s) = float(speed*srate(s))/ma.SR : (+,length(s):fmod)~_ : int;
	};
	
so_loop_speed_level(s, part, speed, level) = (part, reader(s)) : outs(s)
	with {
		length(s) = part,0 : s : _,si.block(outputs(s)-1);
		srate(s) = part,0 : s : !,_,si.block(outputs(s)-2);
		outs(s) = s : si.block(2), bus_level(outputs(s)-2);
		bus_level(n) = par(i,n,*(level));
		reader(s) = float(speed*srate(s))/ma.SR : (+,length(s):fmod)~_ : int;
	};

part = nentry("file", 0, 0, 10, 1);
speed = hslider("speed", 1, 0, 4, 0.01);
level = hslider("level", 0.5, 0, 1, 0.01);

//process = (part, +(1)~_) : soundfile("files [url: {'RnB.wav';'tango.wav';'levot.wav'}]",2) :(!,!,_,_);

//process = (part, 1) : soundfile("files [url: {'/Documents/faust-github-faust2/tests/soundfile/RnB.wav';'/Documents/faust-github-faust2/tests/soundfile/tango.wav';'/Documents/faust-github-faust2/tests/soundfile/levot.wav'}]",2):(_,!,!,!);

//process = so_play(soundfile("files [url: {'/Documents/faust-github-faust2/tests/soundfile/RnB.wav';'/Documents/faust-github-faust2/tests/soundfile/tango.wav';'/Documents/faust-github-faust2/tests/soundfile/levot.wav'}]",2), part);


//process = so_loop(soundfile("files [url: {'/Documents/faust-github-faust2/tests/soundfile/RnB.wav';'/Documents/faust-github-faust2/tests/soundfile/tango.wav';'/Documents/faust-github-faust2/tests/soundfile/levot.wav'}]",2), part);

//process = so_loop_speed(soundfile("files [url: {'/Documents/faust-github-faust2/tests/soundfile/RnB.wav';'/Documents/faust-github-faust2/tests/soundfile/tango.wav';'/Documents/faust-github-faust2/tests/soundfile/levot.wav'}]",2), part, speed);

process = so_loop_speed_level(soundfile("files [url: {'RnB.wav' ;'tango.wav';  'levot.wav'}]",2), part, speed, level);
