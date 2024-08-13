// WARNING: This a "legacy example based on a deprecated library". Check misceffects.lib
// for more accurate examples of echo functions

declare name 		"quadEcho";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2007";

//-----------------------------------------------
// 				A 1 second quadriphonic Echo
//-----------------------------------------------

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = vgroup("stereo echo", multi(ef.echo1s, 4))
	with { 
		multi(f,1) = f;
		multi(f,n) = f,multi(f,n-1);
	};							
	
