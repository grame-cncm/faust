declare name 		"pitchShifter";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

 //--------------------------------------
 // Very simple real time pitch shifter
 //--------------------------------------
 
import("pkg:faust/faust/stdfaust.lib@1.0.0");

pitchshifter = vgroup("Pitch Shifter", ef.transpose(
									hslider("window (samples)", 1000, 50, 10000, 1),
									hslider("xfade (samples)", 10, 1, 10000, 1),
									hslider("shift (semitones) ", 0, -12, +12, 0.1)
								  )
				);

process = pitchshifter;
