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

import("music.lib");


dsize 		= 524288;



// user interface
//---------------


tap(n)  	= vslider("tap %n", 0,0,1,0.1);
in(n)  		= vslider("input %n", 1,0,1,0.1);
gain  		= vslider("gain", 1,0,1,0.1);
del 		= vslider("delay (sec)", 0, 0, 5, 0.01) * SR;


// mixer and matrix
//-----------------------------------------------------------

mixer(taps,lines) 	= 	par(i,taps,*(tap(i))),
						par(i,lines,*(in(i)))
						:>  *(gain);


matrix(taps,lines) 	= ( bus(lines+taps)
						<: tgroup("",
								par(i, taps,
									hgroup("Tap %i",
										mixer(taps,lines) : delay(dsize,del))))
					  ) ~ bus(taps);


// tapiir
//--------

tapiir(taps,lines) 	= 	vgroup("Tapiir",
							bus(lines)
							<: (matrix(taps,lines), bus(lines))
							<: vgroup( "outputs", par( i, lines, hgroup("output %i", mixer(taps,lines)) ) )
						);



process 			=  tapiir(6,2);


