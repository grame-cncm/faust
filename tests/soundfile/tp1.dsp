import("stdfaust.lib");

part = nentry("file", 0, 0, 2, 1);
speed = hslider("speed", 1, 0, 4, 0.01);
level = hslider("level", 0.5, 0, 1, 0.01);

//process = (part, +(1)~_) : soundfile("files [url: {'RnB.wav';'tango.wav';'levot.wav'}]",2) :(!,!,_,_);

//process = so.loop(soundfile("files [url: {'/Documents/faust-github-faust2/tests/soundfile/RnB.wav';'/Documents/faust-github-faust2/tests/soundfile/tango.wav';'/Documents/faust-github-faust2/tests/soundfile/levot.wav'}]",2), part);

//process = so.loop_speed(soundfile("files [url: {'RnB.wav';'tango.wav';'levot.wav'}]",2), part, speed);

//process = so.loop_speed_level(soundfile("files [url: {'RnB.wav';'tango.wav';'levot.wav'}]",2), part, speed, level);

process = so.loop_speed_level(soundfile("files [url: {'RnB.wav';'tango.wav';'levot-all.wav'}]",2), part, speed, level);
