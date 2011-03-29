declare name 		"multibandfilter";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

//---------------------------Multi Band Filter-----------------------------
//
//-------------------------------------------------------------------------

process 		= hgroup("Multi Band Filter",
							seq( i, 10, vgroup("peak %i", component("bandfilter.dsp").bandfilter(1000*(1+i))) )
						);
