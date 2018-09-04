import("stdfaust.lib");

so_play(s, entry) = (entry, reader(s)) : outs(s)
	with {
		length(s) = entry,0 : s : _,si.block(outputs(s)-1);
		srate(s) = entry,0 : s : !,_,si.block(outputs(s)-2);
		outs(s) = s : si.block(2), si.bus(outputs(s)-2);
		cut(n) = par(i,n,!);
		reader(s) = 1 : (+,length(s):fmod)~_ : int;
		entry = nentry("file", 0, 0, 10, 1);
	};
	
so_loop(s, entry) = (entry, reader(s)) : outs(s)
	with {
		length(s) = entry,0 : s : _,si.block(outputs(s)-1);
		srate(s) = entry,0 : s : !,_,si.block(outputs(s)-2);
		outs(s) = s : si.block(2), si.bus(outputs(s)-2);
		reader(s) = float(srate(s))/ma.SR : (+,length(s):fmod)~_ : int;
	};
	
so_loop_speed(s, entry, speed) = (entry, reader(s)) : outs(s)
	with {
		length(s) = entry,0 : s : _,si.block(outputs(s)-1);
		srate(s) = entry,0 : s : !,_,si.block(outputs(s)-2);
		outs(s) = s : si.block(2), si.bus(outputs(s)-2);
		reader(s) = float(speed*srate(s))/ma.SR : (+,length(s):fmod)~_ : int;
	};
	
so_loop_speed_level(s, entry, speed, level) = (entry, reader(s)) : outs(s)
	with {
		length(s) = entry,0 : s : _,si.block(outputs(s)-1);
		srate(s) = entry,0 : s : !,_,si.block(outputs(s)-2);
		outs(s) = s : si.block(2), bus_level(outputs(s)-2);
		bus_level(n) = par(i,n,*(level));
		reader(s) = float(speed*srate(s))/ma.SR : (+,length(s):fmod)~_ : int;
	};

entry = nentry("file", 0, 0, 10, 1);
speed = hslider("speed", 1, 0, 4, 0.01);
level = hslider("level", 0.5, 0, 1, 0.01);

//process = (entry, +(1)~_) : soundfile("files [url: {'RnB.wav';'tango.wav';'levot.wav'}]",2) :(!,!,_,_);

//process = (entry, 1) : soundfile("files [url: {'/Documents/faust-github-faust2/tests/soundfile/RnB.wav';'/Documents/faust-github-faust2/tests/soundfile/tango.wav';'/Documents/faust-github-faust2/tests/soundfile/levot.wav'}]",2):(_,!,!,!);

//process = so_play(soundfile("files [url: {'/Documents/faust-github-faust2/tests/soundfile/RnB.wav';'/Documents/faust-github-faust2/tests/soundfile/tango.wav';'/Documents/faust-github-faust2/tests/soundfile/levot.wav'}]",2), entry);


//process = so_loop(soundfile("files [url: {'/Documents/faust-github-faust2/tests/soundfile/RnB.wav';'/Documents/faust-github-faust2/tests/soundfile/tango.wav';'/Documents/faust-github-faust2/tests/soundfile/levot.wav'}]",2), entry);

//process = so_loop_speed(soundfile("files [url: {'/Documents/faust-github-faust2/tests/soundfile/RnB.wav';'/Documents/faust-github-faust2/tests/soundfile/tango.wav';'/Documents/faust-github-faust2/tests/soundfile/levot.wav'}]",2), entry, speed);

process = so_loop_speed_level(soundfile("files [url: {'/Documents/faust-github-faust2/tests/soundfile/RnB.wav';'/Documents/faust-github-faust2/tests/soundfile/tango.wav';'/Documents/faust-github-faust2/tests/soundfile/levot.wav'}]",2), entry, speed, level);
