// WARNING: This a "legacy example based on a deprecated library". Check misceffects.lib
// for more accurate examples of echo functions

declare name 		"echo";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";
//-----------------------------------------------
// 				A Simple Echo
//-----------------------------------------------

import("pkg:faust/faust/stdfaust.lib@1.0.0");

process = vgroup("echo-simple", ef.echo1s);
