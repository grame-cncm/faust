declare name 		"echo";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";
//-----------------------------------------------
// 				A Simple Echo
//-----------------------------------------------

import("music.lib");

process = vgroup("echosimple", echo1s);
