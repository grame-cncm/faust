declare name 		"matrix";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

//-----------------------------------------------
// Audio Matrix : N inputs x M outputs
//-----------------------------------------------

import("stdfaust.lib");

Fader(in)		= ba.db2linear(vslider("Input %in", -10, -96, 4, 0.1));
Mixer(N,out) 	= hgroup("Output %out", par(in, N, *(Fader(in)) ) :> _ );
Matrix(N,M) 	= tgroup("Matrix %N x %M", par(in, N, _) <: par(out, M, Mixer(N, out)));

process = Matrix(8, 8);
