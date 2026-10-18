E0 = int(float(button("Capture/Audio Capture")>0.0f));  // int block [0, 1] lsb 0
R0 = (E0+R0')*(E0-E0'<=0);                              // int samp [-2147483648, 2147483647] lsb 0
R1 = select2(E0, R1', IN[0])@(-1+R0&524287);            // real samp [-inf, inf]
// real samp [-inf, inf]
process = (R1*(0.001f*IIR(pow(1e+01f, 0.05f*max(-96.0f, min(4.0f, hslider("level (db)/Audio Capture",0.0f,-96.0f,4.0f,0.1f)))); 0.999f)));
