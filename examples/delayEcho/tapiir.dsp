declare name 		"tapiir";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

//======================================================
//
// 					TAPIIR
//	  (from Maarten de Boer's Tapiir)
//
//======================================================

import("stdfaust.lib");

dsize = 524288;

// user interface
//---------------
tap(n) = vslider("tap %n", 0,0,1,0.1);
in(n) = vslider("input %n", 1,0,1,0.1);
gain = vslider("gain", 1,0,1,0.1);
del = vslider("delay (sec)", 0, 0, 5, 0.01) * ma.SR;

// mixer and matrix
//-----------------------------------------------------------
mixer(taps,lines) = par(i,taps,*(tap(i))), par(i,lines,*(in(i))) :> *(gain);

matrix(taps,lines) = (si.bus(lines+taps)
                        <: tgroup("",
                        par(i, taps, hgroup("Tap %i", mixer(taps,lines) : de.delay(dsize,del))))
                    ) ~ si.bus(taps);

// tapiir
//--------
tapiir(taps,lines) = vgroup("Tapiir",
                            si.bus(lines)
                            <: (matrix(taps,lines), si.bus(lines))
                            <: vgroup("outputs", par(i, lines, hgroup("output %i", mixer(taps,lines))))
                            );

process = tapiir(6,2);


