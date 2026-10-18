E0  = min(1.92e+05f, max(5e+01f, float(fSamplingFreq)));                                            // real konst [50, 192000] lsb -27
E1  = exp(-(2e+02f/E0));                                                                            // real konst [0.018315634, 0.998959] lsb -27
// real samp [0.00051572797, 20.004883] lsb -39
E2  = IRM(max(0.5f, min(2e+01f, hslider("Delay [unit:ms] [OWL:PARAMETER_B]",1e+01f,0.5f,2e+01f,0.01f))); E1);
// real samp [0, 0.99999994] lsb -74
R0  = frac(1.0f/E0*max(0.0f, min(1.0f, hslider("Rate [unit:hz] [OWL:PARAMETER_A]",0.1f,0.0f,1.0f,0.001f)))+R0');
E3  = 512.0f*fmod(R0, 1.0f);                                                                        // real samp [0, 511.99997] lsb -97
E4  = float(-1+IIR(1; 1));                                                                          // real samp [-2147483648, 2147483648] lsb -1
E5  = 0.001953125f*E4;                                                                              // real samp [-4194304, 4194304] lsb -42
E6  = 0.00390625f*E4;                                                                               // real samp [-8388608, 8388608] lsb -41
// real konst [-1, 1.0000019] lsb -73
E7  = WRTbl2p(513, sigGen(2.0f*(float(0.0f<=E5&E5<=0.5f)*(-0.5f+E6)+float(0.5f<E5&E5<=1.0f)*(1.5f-E6))));
E8  = int(E3);                                                                                      // int samp [0, 511] lsb 0
E9  = 1.0f-E1;                                                                                      // real konst [0.0010409951, 0.9816844] lsb -32
// real samp [3.122985e-05, 943.67456] lsb -400
E10 = 0.01f*E9*IIR(max(3.0f, min(1e+02f, hslider("Depth [unit:%] [OWL:PARAMETER_D]",2e+01f,3.0f,1e+02f,1.0f))); E1);
E11 = mix(frac(E3), sigRDTbl(E7, max(0, min(E8, 512))), sigRDTbl(E7, max(0, min(1+E8, 512))))*E10;  // real samp [-943.6749, 943.67676] lsb -497
E12 = 0.001f*E0*(E2*(1.0f+E11));                                                                    // real samp [-3620756, 3628445] lsb -605
E13 = int(E12);                                                                                     // int samp [-3620756, 3628445] lsb 0
E14 = float(E13);                                                                                   // real samp [-3620756, 3628445] lsb -1
E15 = 0.001f*E0*E2;                                                                                 // real samp [2.5786398e-05, 3840.938] lsb -108
E16 = int(E15);                                                                                     // int samp [0, 3840] lsb 0
E17 = E16&4095;                                                                                     // int samp [0, 3840] lsb 0
E18 = float(E16);                                                                                   // real samp [0, 3840] lsb -1
E19 = 1.0f-E15+E18;                                                                                 // real samp [-3839.938, 3841] lsb -108
E20 = -E18+E15;                                                                                     // real samp [-3840, 3840.938] lsb -108
E21 = 1+E16&4095;                                                                                   // int samp [1, 3841] lsb 0
// real samp [0, 511.99997] lsb -427
E22 = 512.0f*fmod(R0+0.5f*E9*IIR(max(0.0f, min(1.0f, hslider("L-R Offset [OWL:PARAMETER_C]",0.0f,0.0f,1.0f,0.001f))); E1), 1.0f);
E23 = int(E22);                                                                                     // int samp [0, 511] lsb 0
// real samp [-943.6749, 943.67676] lsb -827
E24 = E10*mix(frac(E22), sigRDTbl(E7, max(0, min(E23, 512))), sigRDTbl(E7, max(0, min(1+E23, 512))));
E25 = 0.001f*E0*(E2*(1.0f+E24));                                                                    // real samp [-3620756, 3628445] lsb -935
E26 = int(E25);                                                                                     // int samp [-3620756, 3628445] lsb 0
E27 = float(E26);                                                                                   // real samp [-3620756, 3628445] lsb -1
// real samp [-inf, inf] invalid ; real samp [-inf, inf] invalid
process = (-(IN[0]@(E13&4095)*(E14+mix(E15, 1.0f, -E11)))-(-E14+E12)*IN[0]@(1+E13&4095)+IN[0]@E17*E19+E20*IN[0]@E21, -(IN[1]@(E26&4095)*(E27+mix(E15, 1.0f, -E24)))-(-E27+E25)*IN[1]@(1+E26&4095)+E19*IN[1]@E17+E20*IN[1]@E21);
