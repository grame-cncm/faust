declare name 		"spat";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

//==========================================================
//
// 					    GMEM SPAT
//	implementation of L. Pottier Spatializer
//
//==========================================================

import("pkg:faust/faust/stdfaust.lib@1.0.0");

//------------------------------------------------------
// EXEMPLE : une entree mono spatialisee sur 8 sorties
//------------------------------------------------------

angle = hslider("angle", 0.0, 0, 1, 0.01);
distance = hslider("distance", 0.5, 0, 1, 0.01);

process = vgroup("Spatializer 1x8", sp.spat(8, angle, distance));


