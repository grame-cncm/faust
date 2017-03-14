// Forward Deep Neural Net (DNN), any number of layers of any size each

declare name    "DNN";
declare author  "JOS";
declare license "STK-4.3";

import("stdfaust.lib");

layerSizes = (8,5,8); // autoencoder with 8 in & out, 5-state hidden layer
w(m,n,k) = m*100+n*10+k; // placeholder weights: m=layer, n=fromNode, k=destNode

M = ba.count(layerSizes);
N(l) = ba.take(l+1,layerSizes); // Nodes per layer

process = seq(m, M-1, layer(m))
// look at weights:
// process = par(m,M,par(n,N(m),par(k,N(m),w(m,n,k))))
with {
  layer(m) = weights(m) :> nonlinearities(m);
  nonlinearities(m) = bus(N(m)*N(m+1)) :> par(n,N(m+1),nl(n));
  weights(m) = bus(N(m)) <: par(n,N(m),(bus(N(m+1))<:wts(m,n)));
  wts(m,n) = bus(N(m+1)) : par(k,N(m+1),*(w(m,n,k)));
  nl(n,x) = x * (x>0); // ReLU
  bus(N) = par(k,N,_);
};
