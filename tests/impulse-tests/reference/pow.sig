E0 = sqrt(3.0f*waveform{...});       // real samp [0.5477225, 5.1672044] lsb -67
E1 = 4.0f*waveform{...};             // real samp [0.4, 35.6] lsb -66
E2 = pow(5.0f*waveform{...}, 2.0f);  // real samp [0.24999997, 1980.2502] lsb -66
E3 = int(6.0f*waveform{...});        // int samp [0, 53] lsb 0
E4 = 7.0f*waveform{...};             // real samp [0.7, 62.3] lsb -66
// real samp [0.5477225, 5.1672044] lsb -67 ; real samp [0.74008274, 2.2731488] lsb -67 ; real samp [0.89177936, 1.5629005] lsb -66 ; real samp [0.94434065, 1.2501603] lsb -66 ; real samp [0.24999997, 1980.2502] lsb -66 ; real samp [0.24999997, 1980.2502] lsb -66 ; int samp [0, 2809] lsb 0 ; real samp [0, 2809.0005] lsb -31 ; real samp [0.48998246, 3882.8928] lsb -66 ; real samp [0.48999992, 3881.2905] lsb -66 ; real konst [1, 1] lsb -32 ; real samp [0.8, 71.2] lsb -65 ; real konst [1, 1] lsb -32 ; real samp [0.9, 80.1] lsb -65
process = (E0, sqrt(E0), pow(E1, 0.125f), pow(E1, 0.0625f), E2, E2, pow(E3, 2), pow(float(E3), 2.0f), pow(E4, 2.0001f), pow(E4, 2.0f), 1.0f, 8.0f*waveform{...}, 1.0f, 9.0f*waveform{...});
