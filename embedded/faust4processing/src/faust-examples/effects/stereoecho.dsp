declare name 		"stereoecho";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2007";

//-----------------------------------------------
// 				A 1 second Stereo Echo
//-----------------------------------------------

import("music.lib");

process = vgroup("stereo echo", (echo1s, echo1s));
