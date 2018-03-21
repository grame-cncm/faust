
import("stdfaust.lib");

// play a soundfile in a loop taking into account the sampling rate
so_loop(s) = float(srate(s))/ma.SR : (+,length(s):fmod)~_ : int : outs(s)
	with {
		length(s) = 0 : s : _,cut(outputs(s)-1);
		srate(s) = 0 : s : !,_,cut(outputs(s)-2);
		channels(s) = 0 : s : !,!,_,cut(outputs(s)-3);
		outs(s) = s : cut(3), bus(outputs(s)-3);
		cut(n) = par(i,n,!);
		bus(n) = par(i,n,_);
	};	
		
// play a soundfile in a loop taking into account the sampling rate, with speed control
so_loop_rate(s, speed) = float(speed*srate(s))/ma.SR : (+,length(s):fmod)~_ : int : outs(s)
	with {
		length(s) = 0 : s : _,cut(outputs(s)-1);
		srate(s) = 0 : s : !,_,cut(outputs(s)-2);
		channels(s) = 0 : s : !,!,_,cut(outputs(s)-3);
		outs(s) = s : cut(3), bus(outputs(s)-3);
		cut(n) = par(i,n,!);
		bus(n) = par(i,n,_);
	};

// play a soundfile in a loop taking into account the sampling rate, with speed and level controls
so_loop_rate_speed(s, speed, volume) = float(speed*srate(s))/ma.SR : (+,length(s):fmod)~_ : int : outs(s)
	with {
		length(s) = 0 : s : _,cut(outputs(s)-1);
		srate(s) = 0 : s : !,_,cut(outputs(s)-2);
		channels(s) = 0 : s : !,!,_,cut(outputs(s)-3);
		outs(s) = s : cut(3), bus(outputs(s)-3);
		cut(n) = par(i,n,!);
		bus(n) = par(i,n,*(volume));
	};
	
speed = hslider("speed", 1, 0, 4, 0.01);

//process = so_loop_rate(soundfile("tango.wav",1), speed),so_loop_rate(soundfile("levot.wav",1), speed) : dm.freeverb_demo;

process = so_loop_rate(soundfile("tango.wav",1), speed),so_loop_rate(soundfile("levot.wav",1), speed);

//process = so_loop_rate(soundfile("tango.wav",2), hslider("speed", 1, 0, 4, 0.01));
//process = so_loop_rate_speed(soundfile("tango.wav",2), hslider("speed", 1, 0, 4, 0.01), hslider("level", 0.5, 0, 1, 0.01));
//process = outputs(soundfile("tango.wav",0));

//process = so.loop(soundfile("tango.wav",2));
//process = so.loop_rate(soundfile("tango.wav",2), hslider("speed", 1, 0, 4, 0.01));
//process = so.loop_rate_speed(soundfile("tango.wav",2), hslider("speed", 1, 0, 4, 0.01), hslider("level", 0.5, 0, 1, 0.01));
