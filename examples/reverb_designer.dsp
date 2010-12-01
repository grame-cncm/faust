  N = 16; // Feedback Delay Network (FDN) order (power of 2, 2 to 16)
 NB =  5; // Number of T60-controlled frequency-bands (3 or more)
BSO =  3; // Order of each lowpass/highpass bandsplit (odd positive integer)

process = component("effect.lib").fdnrev0_demo(N,NB,BSO);

// For a much less computationally expensive but still useable FDN reverb, try 
// N=8; NB=3; BSO=1; // Warning: instability has been observed at high T60s!
                  // This is not yet understood.

