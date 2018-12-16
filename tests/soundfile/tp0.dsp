import("stdfaust.lib");

process = 0,_~+(1):soundfile("son[url:{'tango.wav'}]",2):!,!,_,_;

