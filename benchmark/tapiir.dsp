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

sig = library("signals.lib");
dl = library("delays.lib");
mat = library("math.lib");


dsize 		= 524288;



// user interface
//---------------


tap(n)  	= vslider("tap %n", 0,0,1,0.1);
in(n)  		= vslider("input %n", 1,0,1,0.1);
gain  		= vslider("gain", 1,0,1,0.1);
del 		= vslider("delay (sec)", 0, 0, 5, 0.01) * mat.SR;


// bus, mixer and matrix
//-----------------------------------------------------------

//bus(n) 				= 	par(i,n,_);

mixer(taps,lines) 	= 	par(i,taps,*(tap(i))),
						par(i,lines,*(in(i)))
						:>  *(gain);


matrix(taps,lines) 	= ( sig.bus(lines+taps)
						<: tgroup("",
								par(i, taps,
									hgroup("Tap %i",
										mixer(taps,lines) : dl.delay(dsize,del))))
					  ) ~ sig.bus(taps);


// tapiir
//--------

tapiir(taps,lines) 	= 	vgroup("Tapiir",
							sig.bus(lines)
							<: (matrix(taps,lines), sig.bus(lines))
							<: vgroup( "outputs", par( i, lines, hgroup("output %i", mixer(taps,lines)) ) )
						);



process 			=  tapiir(6,2);


