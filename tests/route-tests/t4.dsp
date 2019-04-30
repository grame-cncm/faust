// cross 1000 signals: 
// input 0 -> output 999, 
// input 1 -> output 998, 
// ..., 
// input 999 -> output 0

N = 1000;
r = route(N, N, par(i, N, (i+1,N-i)));

process = r;