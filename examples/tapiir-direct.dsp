//======================================================
//
// 						TAPIIR 
//	  		(from Maarten de Boer's Tapiir)
//	version with direct outputs instead of a stereo mix
//
//======================================================

dsize 		= 524288;



// user interface
//---------------


tap(n)  	= vslider("tap %n", 0,0,1,0.1);
in(n)  		= vslider("input %n", 1,0,1,0.1);
gain  		= vslider("gain", 1,0,1,0.1);
del 		= vslider("delay (sec)", 0, 0, 5, 0.01) * SR;


// bus, mixer and matrix
//-----------------------------------------------------------

bus(n) 				= 	par(i,n,_);

mixer(taps,lines) 	= 	par(i,taps,*(tap(i))), 
						par(i,lines,*(in(i))) 
						:>  *(gain);
						
						
matrix(taps,lines) 	= ( bus(lines+taps) 
						<: tgroup("",  
								par(i, taps, 
									hgroup("Tap %i", 
										mixer(taps,lines) : delay(dsize,del)))) 
					  ) ~ bus(taps);


direct (taps)		= hgroup ("direct outputs", par (i, taps, *(vslider("direct %i", 0, 0, 1, 0.1))));


// tapiir
//--------
				  				  
tapiir(taps,lines) 	= 	vgroup("Tapiir",
							bus(lines) 
							<: (matrix(taps,lines), bus(lines)) 
							<: vgroup( "outputs", par(i, lines, hgroup("output %i", mixer(taps,lines)) ))
						);


				  				  
dtapiir(taps,lines) 	= 	vgroup("Direct Tapiir",
							bus(lines) 
							<: matrix(taps,lines) 
							<: vgroup( "outputs", direct(taps))
							);


process 			=  dtapiir(8,2);


