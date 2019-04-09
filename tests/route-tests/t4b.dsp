import("stdfaust.lib");

R = 4;
N = R*R;
src = par(i, N, i);
bus = par(i, N, _);
//xr = route(N,N,par(i, N, (i+1,N-i)));
r = ro.interleave(R,R);

// NxM -> MxN
// i: NxM -> 
/*
 k:0..NxM-1
 i:0..N-1; j:0..M-1 

 0 -> 0*M
 1 -> 1*M
 2 -> 2*M
 i -> (i%N)*M + i/N

*/
xr(N,M) = route(16, 16, par(i, N, (i+1, (i%N)*M + int(i/N) + 1)));
wxw(N,M) = route(N*M, N*M, par(i, N*M, (i+1, (i%N)*M + int(i/N) + 1)));
zxw(N,M) = route(N*M, N*M, par(i, N*M, (i+1, (i%N)*M+1)));
zzxw(N,M) = route(N*M, N*M, par(i, N*M, (i+1, i/N)));
xw(N,M) = route(N*M, N*M, par(i, N*M, (i+1, (i%N)*M + i/N + 1)));

test = route(4, 4, par(i, 4, (i*5)/4));
process = xw(R,R);