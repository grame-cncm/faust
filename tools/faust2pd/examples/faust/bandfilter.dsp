declare name 		"bandfilter";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

import("math.lib");
import("music.lib");

//---------------------second order filter--------------------------
// filter(Q,F,G)
//  			Q : quality factor [1..100]
//				F :	frequency (Hz)
//				G : gain [0..1]
//------------------------------------------------------------------

filter(Q,F,G)	= TF2(  (1 +  K/Q + K*K) 	/ D,
						 2 * (K*K - 1) 		/ D,
						(1 - K/Q + K*K) 	/ D,
						 2 * (K*K - 1) 		/ D,
						(1 - V*K/Q + K*K) 	/ D
					 )
		with {
				V = db2linear(G);
				K = tan(PI*F/SR);
				D = 1 + V*K/Q + K*K;
		};



//--------------- Band Filter with user interface ------------------
// bandfilter(F)
//  			F :	default frequency (Hz)
//
//------------------------------------------------------------------

bandfilter(F)	= filter(	nentry("Q factor",50,0.1,100,0.1),
							nentry("freq (Hz)", F, 20, 20000, 1),
							0 - vslider("gain (dB)", 0, -50, 50, 0.1)
						);



//------------------------- Process --------------------------------

process 		= vgroup("Bandfilter", bandfilter(1000));

