declare name 		"statespace";
declare version 	"1.0";
declare author 		"JOS";
declare license 	"MIT";
declare copyright 	"(c) Julius O. Smith III, 2020";

//-----------------------------------------------
// General Linear State-Space Model Example
//-----------------------------------------------

import("stdfaust.lib");

p = 2; // number of inputs
q = 3; // number of outputs
N = 5; // number of states

A = matrix(N,N); // state transition matrix
B = matrix(N,p); // input-to-states matrix
C = matrix(q,N); // states-to-output matrix
D = matrix(q,p); // direct-term matrix, bypassing state

// ./matrix.dsp with M and N transposed to follow convention:
matrix(M,N) = tgroup("Matrix: %M x %N", par(in, N, _)
              <: par(out, M, mixer(N, out))) with {
  fader(in) = ba.db2linear(vslider("Input %in", -10, -96, 4, 0.1));
  mixer(N,out) = hgroup("Output %out", par(in, N, *(fader(in)) ) :> _ );
};

Bd = par(i,p,mem) : B; // input delay needed for conventional definition
vsum(N) = si.bus(2*N) :> si.bus(N); // vector sum of two N-vectors

// Illustrate nonzero initial state, following conventional definition:
impulse = 1-1'; // For zero initial state, set impulse = 0 or simplify code
x0 = par(i,N,i*impulse); // initial state = (0,1,2,3,...,N-1)

system = si.bus(p) <: D, (Bd : vsum(N)~(A), x0 : vsum(N) : C) :> si.bus(q);

process = system;

