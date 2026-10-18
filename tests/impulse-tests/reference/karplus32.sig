E0  = max(0.0f, min(1.0f, hslider("output volume/karplus32",0.4866f,0.0f,1.0f,0.1f)));              // real block [0, 1] lsb -36
E1  = max(0.0f, min(32.0f, hslider("polyphony/resonator x32/karplus32",14.0f,0.0f,32.0f,1.0f)));    // real block [0, 32] lsb -32
// real block [0, 1] lsb -39
E2  = 1.0f-max(0.0f, min(1.0f, hslider("attenuation/resonator x32/karplus32",0.0f,0.0f,1.0f,0.01f)));
E3  = float(button("play/excitator/karplus32")>0.0f);                                               // real block [0, 1] lsb -1
// real samp [-0.5, 16777216] lsb -33
R0  = float(E3-E3'>0.0f)-1.0f/max(2.0f, min(512.0f, hslider("excitation (samples)/excitator/karplus32",128.0f,2.0f,512.0f,1.0f)))*float(R0'>0.0f)+R0';
// real samp [-1.0000153, 1.0000153] lsb -148
E4  = 4.656613e-10f*max(0.0f, min(1.0f, hslider("level/noise generator/karplus32",0.5f,0.0f,1.0f,0.1f)))*(float(IIR(12345; 1103515245))*(1.5258789e-05f+float(R0>0.0f)));
// real block [0.5, 510.5] lsb -32
E5  = -1.5f+max(2.0f, min(512.0f, hslider("duration (samples)/resonator x32/karplus32",128.0f,2.0f,512.0f,1.0f)));
R1  = (0.5f*E2*FIR(R1; 0.0f, 1.0f, 1.0f)+E4)@(int(E5)&4095);                                        // real samp [-268435456, 268435456] lsb -1292
E6  = max(0.0f, min(512.0f, hslider("detune/resonator x32/karplus32",37.9904f,0.0f,512.0f,1.0f)));  // real block [0, 512] lsb -32
R2  = (E4+0.5f*E2*FIR(R2; 0.0f, 1.0f, 1.0f))@(int(8.0f*E6+E5)&4095);                                // real samp [-268435456, 268435456] lsb -1292
R3  = (E4+0.5f*E2*FIR(R3; 0.0f, 1.0f, 1.0f))@(int(16.0f*E6+E5)&4095);                               // real samp [-268435456, 268435456] lsb -1292
R4  = (E4+0.5f*E2*FIR(R4; 0.0f, 1.0f, 1.0f))@(int(24.0f*E6+E5)&4095);                               // real samp [-268435456, 268435456] lsb -1292
R5  = (E4+0.5f*E2*FIR(R5; 0.0f, 1.0f, 1.0f))@(int(2.0f*E6+E5)&4095);                                // real samp [-268435456, 268435456] lsb -1292
R6  = (E4+0.5f*E2*FIR(R6; 0.0f, 1.0f, 1.0f))@(int(1e+01f*E6+E5)&4095);                              // real samp [-268435456, 268435456] lsb -1292
R7  = (E4+0.5f*E2*FIR(R7; 0.0f, 1.0f, 1.0f))@(int(18.0f*E6+E5)&4095);                               // real samp [-268435456, 268435456] lsb -1292
R8  = (E4+0.5f*E2*FIR(R8; 0.0f, 1.0f, 1.0f))@(int(26.0f*E6+E5)&4095);                               // real samp [-268435456, 268435456] lsb -1292
R9  = (E4+0.5f*E2*FIR(R9; 0.0f, 1.0f, 1.0f))@(int(4.0f*E6+E5)&4095);                                // real samp [-268435456, 268435456] lsb -1292
R10 = (E4+0.5f*E2*FIR(R10; 0.0f, 1.0f, 1.0f))@(int(12.0f*E6+E5)&4095);                              // real samp [-268435456, 268435456] lsb -1292
R11 = (E4+0.5f*E2*FIR(R11; 0.0f, 1.0f, 1.0f))@(int(2e+01f*E6+E5)&4095);                             // real samp [-268435456, 268435456] lsb -1292
R12 = (E4+0.5f*E2*FIR(R12; 0.0f, 1.0f, 1.0f))@(int(28.0f*E6+E5)&4095);                              // real samp [-268435456, 268435456] lsb -1292
R13 = (E4+0.5f*E2*FIR(R13; 0.0f, 1.0f, 1.0f))@(int(6.0f*E6+E5)&4095);                               // real samp [-268435456, 268435456] lsb -1292
R14 = (E4+0.5f*E2*FIR(R14; 0.0f, 1.0f, 1.0f))@(int(14.0f*E6+E5)&4095);                              // real samp [-268435456, 268435456] lsb -1292
R15 = (E4+0.5f*E2*FIR(R15; 0.0f, 1.0f, 1.0f))@(int(22.0f*E6+E5)&4095);                              // real samp [-268435456, 268435456] lsb -1292
R16 = (E4+0.5f*E2*FIR(R16; 0.0f, 1.0f, 1.0f))@(int(3e+01f*E6+E5)&4095);                             // real samp [-268435456, 268435456] lsb -1292
R17 = (E4+0.5f*E2*FIR(R17; 0.0f, 1.0f, 1.0f))@(int(E6+E5)&4095);                                    // real samp [-268435456, 268435456] lsb -1292
R18 = (E4+0.5f*E2*FIR(R18; 0.0f, 1.0f, 1.0f))@(int(9.0f*E6+E5)&4095);                               // real samp [-268435456, 268435456] lsb -1292
R19 = (E4+0.5f*E2*FIR(R19; 0.0f, 1.0f, 1.0f))@(int(17.0f*E6+E5)&4095);                              // real samp [-268435456, 268435456] lsb -1292
R20 = (E4+0.5f*E2*FIR(R20; 0.0f, 1.0f, 1.0f))@(int(25.0f*E6+E5)&4095);                              // real samp [-268435456, 268435456] lsb -1292
R21 = (E4+0.5f*E2*FIR(R21; 0.0f, 1.0f, 1.0f))@(int(3.0f*E6+E5)&4095);                               // real samp [-268435456, 268435456] lsb -1292
R22 = (E4+0.5f*E2*FIR(R22; 0.0f, 1.0f, 1.0f))@(int(11.0f*E6+E5)&4095);                              // real samp [-268435456, 268435456] lsb -1292
R23 = (E4+0.5f*E2*FIR(R23; 0.0f, 1.0f, 1.0f))@(int(19.0f*E6+E5)&4095);                              // real samp [-268435456, 268435456] lsb -1292
R24 = (E4+0.5f*E2*FIR(R24; 0.0f, 1.0f, 1.0f))@(int(27.0f*E6+E5)&4095);                              // real samp [-268435456, 268435456] lsb -1292
R25 = (E4+0.5f*E2*FIR(R25; 0.0f, 1.0f, 1.0f))@(int(5.0f*E6+E5)&4095);                               // real samp [-268435456, 268435456] lsb -1292
R26 = (E4+0.5f*E2*FIR(R26; 0.0f, 1.0f, 1.0f))@(int(13.0f*E6+E5)&4095);                              // real samp [-268435456, 268435456] lsb -1292
R27 = (E4+0.5f*E2*FIR(R27; 0.0f, 1.0f, 1.0f))@(int(21.0f*E6+E5)&4095);                              // real samp [-268435456, 268435456] lsb -1292
R28 = (E4+0.5f*E2*FIR(R28; 0.0f, 1.0f, 1.0f))@(int(29.0f*E6+E5)&4095);                              // real samp [-268435456, 268435456] lsb -1292
R29 = (E4+0.5f*E2*FIR(R29; 0.0f, 1.0f, 1.0f))@(int(7.0f*E6+E5)&4095);                               // real samp [-268435456, 268435456] lsb -1292
R30 = (E4+0.5f*E2*FIR(R30; 0.0f, 1.0f, 1.0f))@(int(15.0f*E6+E5)&4095);                              // real samp [-268435456, 268435456] lsb -1292
R31 = (E4+0.5f*E2*FIR(R31; 0.0f, 1.0f, 1.0f))@(int(23.0f*E6+E5)&4095);                              // real samp [-268435456, 268435456] lsb -1292
R32 = (E4+0.5f*E2*FIR(R32; 0.0f, 1.0f, 1.0f))@(int(31.0f*E6+E5)&4095);                              // real samp [-268435456, 268435456] lsb -1292
// real samp [-4294967296, 4294967296] lsb -1329 ; real samp [-4294967296, 4294967296] lsb -1329
process = (E0*(float(E1>0.0f)*R1+float(E1>8.0f)*R2+float(E1>16.0f)*R3+float(E1>24.0f)*R4+(float(E1>2.0f)*R5+float(E1>1e+01f)*R6+float(E1>18.0f)*R7+float(E1>26.0f)*R8)+(float(E1>4.0f)*R9+float(E1>12.0f)*R10+float(E1>2e+01f)*R11+float(E1>28.0f)*R12+(float(E1>6.0f)*R13+float(E1>14.0f)*R14+float(E1>22.0f)*R15+float(E1>3e+01f)*R16))), E0*(float(E1>1.0f)*R17+float(E1>9.0f)*R18+float(E1>17.0f)*R19+float(E1>25.0f)*R20+(float(E1>3.0f)*R21+float(E1>11.0f)*R22+float(E1>19.0f)*R23+float(E1>27.0f)*R24)+(float(E1>5.0f)*R25+float(E1>13.0f)*R26+float(E1>21.0f)*R27+float(E1>29.0f)*R28+(float(E1>7.0f)*R29+float(E1>15.0f)*R30+float(E1>23.0f)*R31+float(E1>31.0f)*R32))));
