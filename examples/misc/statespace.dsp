declare name 		"statespace";
declare version 	"1.0";
declare author 		"JOS";
declare license 	"MIT";
declare copyright 	"(c) Julius O. Smith III, 2020";

//-----------------------------------------------
// General Linear State-Space Model: p inputs, q outputs, N states
//-----------------------------------------------

import("stdfaust.lib");

p = 2; // number of inputs
q = 3; // number of outputs
N = 5; // number of states

A = matrix(N,N);
B = matrix(N,p);
Bd = par(i,p,mem) : B; // to follow conventional definition
C = matrix(q,N);
D = matrix(q,p);

// ./matrix.dsp with M and N transposed to follow convention:
matrix(M,N) = tgroup("Matrix: %M x %N", par(in, N, _)
              <: par(out, M, mixer(N, out))) with {
  fader(in) = ba.db2linear(vslider("Input %in", -10, -96, 4, 0.1));
  mixer(N,out) = hgroup("Output %out", par(in, N, *(fader(in)) ) :> _ );
};

bsum(N) = si.bus(2*N) :> si.bus(N);

system = si.bus(p) <: D, (Bd : (bsum(N)~(A)) : C) :> si.bus(q);

process = system;
