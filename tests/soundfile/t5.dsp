
import("stdfaust.lib");

// play a soundfile in a loop taking into account the sampling rate
loop(s) = float(rate(s))/ma.SR : (+,length(s):fmod)~_ : int : outs(s)
	with {
		length(s) 	= 0 : s : _,cut(outputs(s)-1);
		rate(s) 	= 0 : s : !,_,cut(outputs(s)-2);
		outs(s) 	= s : cut(2), bus(outputs(s)-2);
		cut(n) 		= par(i,n,!);
		bus(n)		= par(i,n,_);
	};

// play a soundfile in a loop taking into account the sampling rate, with speed and level controls
player(s, speed, volume) = float(speed*rate(s))/ma.SR : (+,length(s):fmod)~_ : int : outs(s)
	with {
		length(s) 	= 0 : s : _,cut(outputs(s)-1);
		rate(s) 	= 0 : s : !,_,cut(outputs(s)-2);
		outs(s) 	= s : cut(2), bus(outputs(s)-2);
		cut(n) 		= par(i,n,!);
		bus(n)		= par(i,n,*(volume));
	};

//process = loop(soundfile("tango.wav",2));

process = player(soundfile("tango.wav",2), hslider("speed", 1, 0, 4, 0.01), hslider("level", 0.5, 0, 1, 0.01));

