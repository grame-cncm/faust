// compare interleave with equivalent route expression

import("stdfaust.lib");

R = 20;

r1(N,M) = ro.interleave(N,M); // time 2mn
r2(N,M) = route(N*M, N*M, par(i, N*M, (i+1, (i%N)*M + int(i/N) + 1))); // time 0.1s

//process = r1(R,R);      // time 2mn
process = r2(R,R);    // time 0.3s