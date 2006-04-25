declare name 		"echo";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"¢ GRAME 2006";
//-----------------------------------------------
// 				A Simple Echo
//-----------------------------------------------

import("music.lib");

process = vgroup("echo-simple", echo1s);
