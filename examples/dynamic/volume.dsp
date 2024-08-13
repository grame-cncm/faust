declare name 		"volume";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

//-----------------------------------------------
// 			Volume control in dB
//-----------------------------------------------

import("pkg:faust/faust/stdfaust.lib@1.0.0");

gain = vslider("[1]", 0, -70, +4, 0.1) : ba.db2linear : si.smoo;

process = *(gain);
