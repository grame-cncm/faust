//------------------------------------------------------------------
//	DAFX, Digital Audio Effects (Wiley ed.)
//	chapter 2 	: filters
//	section 2.3 : Equalizers
//	page 53 	: second order shelving filter design
//------------------------------------------------------------------

import("music.lib");

//--------------- Second Order Generic Transfert Function -------------------------

CONVOL3(k0,k1,k2,x) = k0*x + k1*x' + k2*x''; 
CONVOL2(k0,k1,x) 	= k0*x + k1*x';			
FUN3(k0,k1,k2,x) 	= x*k0 + mem(x)*k1 + mem(mem(x))*k2;
FUN2(k0,k1,x) 		= x*k0 + mem(x)*k1;
SUB(x,y)			= y-x;

TF2(b0,b1,b2,a1,a2) = CONVOL3(b0,b1,b2) : SUB ~ CONVOL2(a1,a2); 



//------------------- low-frequency shelving cut (table 2.3) --------------------

V0(g)			= pow(10,g/-20.0);
K(fc) 			= tan(PI*fc/SR);
square(x)		= x*x;
denom(fc,g)		= 1 + sqrt(2*V0(g))*K(fc) + V0(g)*square(K(fc));

lfcut(fc, g)	= TF2(  (1 + sqrt(2)*K(fc) + square(K(fc))) / denom(fc,g),
						 2 * (square(K(fc)) - 1) / denom(fc,g),
						(1 - sqrt(2)*K(fc) + square(K(fc))) / denom(fc,g),
						 2 * (V0(g)*square(K(fc)) - 1) / denom(fc,g),
						(1 - sqrt(2*V0(g))*K(fc) + V0(g)*square(K(fc))) / denom(fc,g)
					 );


//------------------------------ User Interface -----------------------------------
						
freq 			= hslider("freq", 1000, 20, 20000, 0.1);
att				= hslider("attenuation (db)", 0, -96, 10, 0.1);


//----------------------------------- Process -------------------------------------
						
process 		= vgroup("low-freq shelving cut", lfcut(freq,att));

