// WARNING: This a "legacy example based on a deprecated library". Check filters.lib
// for more accurate examples of filter functions

declare name 		"multibandFilter";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

//---------------------------Multi Band Filter-----------------------------
//
//-------------------------------------------------------------------------

process 		= hgroup("Multi Band Filter", seq(i, 10, vgroup("peak %i", component("bandfilter.dsp").bandfilter(1000*(1+i)))));
