E0 = -(8e+01f/min(1.92e+05f, max(5e+01f, float(fSamplingFreq))));              // real konst [-1.6, -0.00041666665] lsb -27
R0 = max(E0+R0', min(1e+01f, 2e+01f*log10(max(0.00031622776f, abs(IN[0])))));  // real samp [-70.000015, 10] lsb -72
R1 = max(E0+R1', min(1e+01f, 2e+01f*log10(max(0.00031622776f, abs(IN[1])))));  // real samp [-70.000015, 10] lsb -72
R2 = max(E0+R2', min(1e+01f, 2e+01f*log10(max(0.00031622776f, abs(IN[2])))));  // real samp [-70.000015, 10] lsb -72
R3 = max(E0+R3', min(1e+01f, 2e+01f*log10(max(0.00031622776f, abs(IN[3])))));  // real samp [-70.000015, 10] lsb -72
R4 = max(E0+R4', min(1e+01f, 2e+01f*log10(max(0.00031622776f, abs(IN[4])))));  // real samp [-70.000015, 10] lsb -72
R5 = max(E0+R5', min(1e+01f, 2e+01f*log10(max(0.00031622776f, abs(IN[5])))));  // real samp [-70.000015, 10] lsb -72
R6 = max(E0+R6', min(1e+01f, 2e+01f*log10(max(0.00031622776f, abs(IN[6])))));  // real samp [-70.000015, 10] lsb -72
R7 = max(E0+R7', min(1e+01f, 2e+01f*log10(max(0.00031622776f, abs(IN[7])))));  // real samp [-70.000015, 10] lsb -72
// int konst [0, 0] lsb 0 ; int konst [0, 0] lsb 0 ; int konst [0, 0] lsb 0 ; int konst [0, 0] lsb 0 ; int konst [0, 0] lsb 0 ; int konst [0, 0] lsb 0 ; int konst [0, 0] lsb 0 ; int konst [0, 0] lsb 0
process = (attach(0, attach(IN[0], vbargraph("[unit:dB]/0/8 channels dB meter",-7e+01f,1e+01f,R0))), attach(0, attach(IN[1], vbargraph("[unit:dB]/1/8 channels dB meter",-7e+01f,1e+01f,R1))), attach(0, attach(IN[2], vbargraph("[unit:dB]/2/8 channels dB meter",-7e+01f,1e+01f,R2))), attach(0, attach(IN[3], vbargraph("[unit:dB]/3/8 channels dB meter",-7e+01f,1e+01f,R3))), attach(0, attach(IN[4], vbargraph("[unit:dB]/4/8 channels dB meter",-7e+01f,1e+01f,R4))), attach(0, attach(IN[5], vbargraph("[unit:dB]/5/8 channels dB meter",-7e+01f,1e+01f,R5))), attach(0, attach(IN[6], vbargraph("[unit:dB]/6/8 channels dB meter",-7e+01f,1e+01f,R6))), attach(0, attach(IN[7], vbargraph("[unit:dB]/7/8 channels dB meter",-7e+01f,1e+01f,R7))));
