E0 = max(5e+01f, min(1e+04f, hslider("window (samples)/Pitch Shifter",1e+03f,5e+01f,1e+04f,1.0f)));  // real block [50, 10000] lsb -32
// real samp [0, 9999.999] lsb -72
R0 = fmod(1.0f+E0-pow(2.0f, 0.083333336f*max(-12.0f, min(12.0f, hslider("shift (semitones) /Pitch Shifter",0.0f,-12.0f,12.0f,0.1f))))+R0', E0);
E1 = int(E0+R0);                                                                                     // int samp [50, 20000] lsb 0
E2 = 1.0f-R0;                                                                                        // real samp [-9998.999, 1] lsb -72
E3 = E0-float(E1);                                                                                   // real samp [-19950, 9950] lsb -32
// real samp [-inf, inf] invalid
process = (mix(min(1.0f/max(1.0f, min(1e+04f, hslider("xfade (samples)/Pitch Shifter",1e+01f,1.0f,1e+04f,1.0f)))*R0, 1.0f), IN[0]@(E1&65535)*(E2-E3)+(R0+E3)*IN[0]@(1+E1&65535), IN[0]@(int(R0)&65535)*(float(int(R0))+E2)+(-float(int(R0))+R0)*IN[0]@(1+int(R0)&65535)));
