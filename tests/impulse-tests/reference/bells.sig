E0     = min(1.92e+05f, max(5e+01f, float(fSamplingFreq)));                 // real konst [50, 192000] lsb -27
E1     = 100.53097f/E0;                                                     // real konst [0.00052359875, 2.0106194] lsb -27
E2     = -1.0f+E1;                                                          // real konst [-0.9994764, 1.0106194] lsb -32
E3     = 2753.8428f/E0;                                                     // real konst [0.014342931, 55.07686] lsb -27
// real block [0.59460336, 191.78343] lsb -75
E4     = pow(2.0f, 0.083333336f*(-69.0f+max(6e+01f, min(1.6e+02f, nentry("pitch0",6e+01f,6e+01f,1.6e+02f,0.01f)))));
E5     = -pow(1.0f-E1, 2.0f);                                               // real konst [-1.0213518, 0] lsb -32
E6     = 0.5f*E0;                                                           // real konst [25, 96000] lsb -60
E7     = float(button("play0")>0.0f);                                       // real block [0, 1] lsb -1
E8     = float(E7>E7');                                                     // real samp [0, 1] lsb -1
E9     = 2.1900356f*E8;                                                     // real samp [0, 2.1900356] lsb -32
E10    = max(0.0f, min(1.0f, nentry("feedback",0.989f,0.0f,1.0f,0.001f)));  // real block [0, 1] lsb -42
E11    = 0.0022816064f*E0;                                                  // real konst [0.11408032, 438.06845] lsb -68
E12    = 0.5f*(1.0f+E5);                                                    // real konst [-0.010675907, 0.5] lsb -65
E13    = -E12;                                                              // real konst [-0.5, 0.010675907] lsb -65
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R0.0   = FIR(R0.0; 0.0f, -(2.0f*E2*cos(E3*E4)), E5)+0.999926f*float(438.2877f*E4<E6)*(E9+E10*R0.1')@int(min(4096.0f, max(0.0f, E11/E4)));
R0.1   = FIR(R0.0; E12, 0.0f, E13);                                         // real samp [-inf, inf] invalid
E14    = 24876.438f/E0;                                                     // real konst [0.12956478, 497.52878] lsb -27
E15    = 5.0063033f*E8;                                                     // real samp [0, 5.0063033] lsb -31
E16    = 0.00025257576f*E0;                                                 // real konst [0.012628787, 48.49455] lsb -71
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R1.0   = FIR(R1.0; 0.0f, -(2.0f*E2*cos(E14*E4)), E5)+float(3959.208f*E4<E6)*(E15+E10*R1.1')@int(min(4096.0f, max(0.0f, E16/E4)));
R1.1   = FIR(R1.0; E12, 0.0f, E13);                                         // real samp [-inf, inf] invalid
E17    = 47774.59f/E0;                                                      // real konst [0.24882598, 955.4918] lsb -27
E18    = 6.7063036f*E8;                                                     // real samp [0, 6.7063036] lsb -31
E19    = 0.0001315173f*E0;                                                  // real konst [0.0065758647, 25.251322] lsb -72
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R2.0   = FIR(R2.0; 0.0f, -(2.0f*E2*cos(E17*E4)), E5)+float(7603.562f*E4<E6)*(E18+E10*R2.1')@int(min(4096.0f, max(0.0f, E19/E4)));
R2.1   = FIR(R2.0; E12, 0.0f, E13);                                         // real samp [-inf, inf] invalid
E20    = 8236.24f/E0;                                                       // real konst [0.042897083, 164.72481] lsb -27
// real block [0.59460336, 191.78343] lsb -75
E21    = pow(2.0f, 0.083333336f*(-69.0f+max(6e+01f, min(1.6e+02f, nentry("pitch1",61.0f,6e+01f,1.6e+02f,0.01f)))));
E22    = float(button("play1")>0.0f);                                       // real block [0, 1] lsb -1
E23    = float(E22>E22');                                                   // real samp [0, 1] lsb -1
E24    = 2.0914886f*E23;                                                    // real samp [0, 2.0914886] lsb -32
E25    = 0.0007628706f*E0;                                                  // real konst [0.038143527, 146.47116] lsb -70
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R3.0   = FIR(R3.0; 0.0f, -(2.0f*E2*cos(E20*E21)), E5)+0.9999828f*float(1310.8384f*E21<E6)*(E24+E10*R3.1')@int(min(4096.0f, max(0.0f, E25/E21)));
R3.1   = FIR(R3.0; E12, 0.0f, E13);                                         // real samp [-inf, inf] invalid
E26    = 35478.215f/E0;                                                     // real konst [0.18478236, 709.56433] lsb -27
E27    = 1.7063034f*E23;                                                    // real samp [0, 1.7063034] lsb -33
E28    = 0.00017709982f*E0;                                                 // real konst [0.008854991, 34.003166] lsb -72
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R4.0   = FIR(R4.0; 0.0f, -(2.0f*E2*cos(E26*E21)), E5)+0.9999655f*float(5646.533f*E21<E6)*(E27+E10*R4.1')@int(min(4096.0f, max(0.0f, E28/E21)));
R4.1   = FIR(R4.0; E12, 0.0f, E13);                                         // real samp [-inf, inf] invalid
// real block [0.59460336, 191.78343] lsb -75
E29    = pow(2.0f, 0.083333336f*(-69.0f+max(6e+01f, min(1.6e+02f, nentry("pitch2",62.0f,6e+01f,1.6e+02f,0.01f)))));
E30    = float(button("play2")>0.0f);                                       // real block [0, 1] lsb -1
E31    = float(E30>E30');                                                   // real samp [0, 1] lsb -1
E32    = 2.1900356f*E31;                                                    // real samp [0, 2.1900356] lsb -32
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R5.0   = FIR(R5.0; 0.0f, -(2.0f*E2*cos(E3*E29)), E5)+0.999926f*float(438.2877f*E29<E6)*(E32+E10*R5.1')@int(min(4096.0f, max(0.0f, E11/E29)));
R5.1   = FIR(R5.0; E12, 0.0f, E13);                                         // real samp [-inf, inf] invalid
E33    = 5.0063033f*E31;                                                    // real samp [0, 5.0063033] lsb -31
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R6.0   = FIR(R6.0; 0.0f, -(2.0f*E2*cos(E14*E29)), E5)+float(3959.208f*E29<E6)*(E33+E10*R6.1')@int(min(4096.0f, max(0.0f, E16/E29)));
R6.1   = FIR(R6.0; E12, 0.0f, E13);                                         // real samp [-inf, inf] invalid
E34    = 6.7063036f*E31;                                                    // real samp [0, 6.7063036] lsb -31
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R7.0   = FIR(R7.0; 0.0f, -(2.0f*E2*cos(E17*E29)), E5)+float(7603.562f*E29<E6)*(E34+E10*R7.1')@int(min(4096.0f, max(0.0f, E19/E29)));
R7.1   = FIR(R7.0; E12, 0.0f, E13);                                         // real samp [-inf, inf] invalid
// real block [0.59460336, 191.78343] lsb -75
E35    = pow(2.0f, 0.083333336f*(-69.0f+max(6e+01f, min(1.6e+02f, nentry("pitch3",63.0f,6e+01f,1.6e+02f,0.01f)))));
E36    = float(button("play3")>0.0f);                                       // real block [0, 1] lsb -1
E37    = float(E36>E36');                                                   // real samp [0, 1] lsb -1
E38    = 2.0914886f*E37;                                                    // real samp [0, 2.0914886] lsb -32
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R8.0   = FIR(R8.0; 0.0f, -(2.0f*E2*cos(E20*E35)), E5)+0.9999828f*float(1310.8384f*E35<E6)*(E38+E10*R8.1')@int(min(4096.0f, max(0.0f, E25/E35)));
R8.1   = FIR(R8.0; E12, 0.0f, E13);                                         // real samp [-inf, inf] invalid
E39    = 1.7063034f*E37;                                                    // real samp [0, 1.7063034] lsb -33
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R9.0   = FIR(R9.0; 0.0f, -(2.0f*E2*cos(E26*E35)), E5)+0.9999655f*float(5646.533f*E35<E6)*(E39+E10*R9.1')@int(min(4096.0f, max(0.0f, E28/E35)));
R9.1   = FIR(R9.0; E12, 0.0f, E13);                                         // real samp [-inf, inf] invalid
// real block [0.59460336, 191.78343] lsb -75
E40    = pow(2.0f, 0.083333336f*(-69.0f+max(6e+01f, min(1.6e+02f, nentry("pitch4",64.0f,6e+01f,1.6e+02f,0.01f)))));
E41    = float(button("play4")>0.0f);                                       // real block [0, 1] lsb -1
E42    = float(E41>E41');                                                   // real samp [0, 1] lsb -1
E43    = 2.1900356f*E42;                                                    // real samp [0, 2.1900356] lsb -32
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R10.0  = FIR(R10.0; 0.0f, -(2.0f*E2*cos(E3*E40)), E5)+0.999926f*float(438.2877f*E40<E6)*(E43+E10*R10.1')@int(min(4096.0f, max(0.0f, E11/E40)));
R10.1  = FIR(R10.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E44    = 5.0063033f*E42;                                                    // real samp [0, 5.0063033] lsb -31
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R11.0  = FIR(R11.0; 0.0f, -(2.0f*E2*cos(E14*E40)), E5)+float(3959.208f*E40<E6)*(E44+E10*R11.1')@int(min(4096.0f, max(0.0f, E16/E40)));
R11.1  = FIR(R11.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E45    = 6.7063036f*E42;                                                    // real samp [0, 6.7063036] lsb -31
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R12.0  = FIR(R12.0; 0.0f, -(2.0f*E2*cos(E17*E40)), E5)+float(7603.562f*E40<E6)*(E45+E10*R12.1')@int(min(4096.0f, max(0.0f, E19/E40)));
R12.1  = FIR(R12.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real block [0.59460336, 191.78343] lsb -75
E46    = pow(2.0f, 0.083333336f*(-69.0f+max(6e+01f, min(1.6e+02f, nentry("pitch5",65.0f,6e+01f,1.6e+02f,0.01f)))));
E47    = float(button("play5")>0.0f);                                       // real block [0, 1] lsb -1
E48    = float(E47>E47');                                                   // real samp [0, 1] lsb -1
E49    = 2.0914886f*E48;                                                    // real samp [0, 2.0914886] lsb -32
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R13.0  = FIR(R13.0; 0.0f, -(2.0f*E2*cos(E20*E46)), E5)+0.9999828f*float(1310.8384f*E46<E6)*(E49+E10*R13.1')@int(min(4096.0f, max(0.0f, E25/E46)));
R13.1  = FIR(R13.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E50    = 1.7063034f*E48;                                                    // real samp [0, 1.7063034] lsb -33
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R14.0  = FIR(R14.0; 0.0f, -(2.0f*E2*cos(E26*E46)), E5)+0.9999655f*float(5646.533f*E46<E6)*(E50+E10*R14.1')@int(min(4096.0f, max(0.0f, E28/E46)));
R14.1  = FIR(R14.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real block [0.59460336, 191.78343] lsb -75
E51    = pow(2.0f, 0.083333336f*(-69.0f+max(6e+01f, min(1.6e+02f, nentry("pitch6",66.0f,6e+01f,1.6e+02f,0.01f)))));
E52    = float(button("play6")>0.0f);                                       // real block [0, 1] lsb -1
E53    = float(E52>E52');                                                   // real samp [0, 1] lsb -1
E54    = 2.1900356f*E53;                                                    // real samp [0, 2.1900356] lsb -32
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R15.0  = FIR(R15.0; 0.0f, -(2.0f*E2*cos(E3*E51)), E5)+0.999926f*float(438.2877f*E51<E6)*(E54+E10*R15.1')@int(min(4096.0f, max(0.0f, E11/E51)));
R15.1  = FIR(R15.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E55    = 5.0063033f*E53;                                                    // real samp [0, 5.0063033] lsb -31
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R16.0  = FIR(R16.0; 0.0f, -(2.0f*E2*cos(E14*E51)), E5)+float(3959.208f*E51<E6)*(E55+E10*R16.1')@int(min(4096.0f, max(0.0f, E16/E51)));
R16.1  = FIR(R16.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E56    = 6.7063036f*E53;                                                    // real samp [0, 6.7063036] lsb -31
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R17.0  = FIR(R17.0; 0.0f, -(2.0f*E2*cos(E17*E51)), E5)+float(7603.562f*E51<E6)*(E56+E10*R17.1')@int(min(4096.0f, max(0.0f, E19/E51)));
R17.1  = FIR(R17.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real block [0.59460336, 191.78343] lsb -75
E57    = pow(2.0f, 0.083333336f*(-69.0f+max(6e+01f, min(1.6e+02f, nentry("pitch7",67.0f,6e+01f,1.6e+02f,0.01f)))));
E58    = float(button("play7")>0.0f);                                       // real block [0, 1] lsb -1
E59    = float(E58>E58');                                                   // real samp [0, 1] lsb -1
E60    = 2.0914886f*E59;                                                    // real samp [0, 2.0914886] lsb -32
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R18.0  = FIR(R18.0; 0.0f, -(2.0f*E2*cos(E20*E57)), E5)+0.9999828f*float(1310.8384f*E57<E6)*(E60+E10*R18.1')@int(min(4096.0f, max(0.0f, E25/E57)));
R18.1  = FIR(R18.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E61    = 1.7063034f*E59;                                                    // real samp [0, 1.7063034] lsb -33
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R19.0  = FIR(R19.0; 0.0f, -(2.0f*E2*cos(E26*E57)), E5)+0.9999655f*float(5646.533f*E57<E6)*(E61+E10*R19.1')@int(min(4096.0f, max(0.0f, E28/E57)));
R19.1  = FIR(R19.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real block [0.59460336, 191.78343] lsb -75
E62    = pow(2.0f, 0.083333336f*(-69.0f+max(6e+01f, min(1.6e+02f, nentry("pitch8",68.0f,6e+01f,1.6e+02f,0.01f)))));
E63    = float(button("play8")>0.0f);                                       // real block [0, 1] lsb -1
E64    = float(E63>E63');                                                   // real samp [0, 1] lsb -1
E65    = 2.1900356f*E64;                                                    // real samp [0, 2.1900356] lsb -32
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R20.0  = FIR(R20.0; 0.0f, -(2.0f*E2*cos(E3*E62)), E5)+0.999926f*float(438.2877f*E62<E6)*(E65+E10*R20.1')@int(min(4096.0f, max(0.0f, E11/E62)));
R20.1  = FIR(R20.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E66    = 5.0063033f*E64;                                                    // real samp [0, 5.0063033] lsb -31
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R21.0  = FIR(R21.0; 0.0f, -(2.0f*E2*cos(E14*E62)), E5)+float(3959.208f*E62<E6)*(E66+E10*R21.1')@int(min(4096.0f, max(0.0f, E16/E62)));
R21.1  = FIR(R21.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E67    = 6.7063036f*E64;                                                    // real samp [0, 6.7063036] lsb -31
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R22.0  = FIR(R22.0; 0.0f, -(2.0f*E2*cos(E17*E62)), E5)+float(7603.562f*E62<E6)*(E67+E10*R22.1')@int(min(4096.0f, max(0.0f, E19/E62)));
R22.1  = FIR(R22.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real block [0.59460336, 191.78343] lsb -75
E68    = pow(2.0f, 0.083333336f*(-69.0f+max(6e+01f, min(1.6e+02f, nentry("pitch9",69.0f,6e+01f,1.6e+02f,0.01f)))));
E69    = float(button("play9")>0.0f);                                       // real block [0, 1] lsb -1
E70    = float(E69>E69');                                                   // real samp [0, 1] lsb -1
E71    = 2.0914886f*E70;                                                    // real samp [0, 2.0914886] lsb -32
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R23.0  = FIR(R23.0; 0.0f, -(2.0f*E2*cos(E20*E68)), E5)+0.9999828f*float(1310.8384f*E68<E6)*(E71+E10*R23.1')@int(min(4096.0f, max(0.0f, E25/E68)));
R23.1  = FIR(R23.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E72    = 1.7063034f*E70;                                                    // real samp [0, 1.7063034] lsb -33
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R24.0  = FIR(R24.0; 0.0f, -(2.0f*E2*cos(E26*E68)), E5)+0.9999655f*float(5646.533f*E68<E6)*(E72+E10*R24.1')@int(min(4096.0f, max(0.0f, E28/E68)));
R24.1  = FIR(R24.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E73    = 15770.537f/E0;                                                     // real konst [0.08213821, 315.41077] lsb -27
E74    = 0.0003984129f*E0;                                                  // real konst [0.019920643, 76.49528] lsb -71
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R25.0  = FIR(R25.0; 0.0f, -(2.0f*E2*cos(E73*E4)), E5)+float(2509.959f*E4<E6)*(5.2995043f*E8+E10*R25.1')@int(min(4096.0f, max(0.0f, E74/E4)));
R25.1  = FIR(R25.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R26.0  = FIR(R26.0; 0.0f, -(2.0f*E2*cos(E73*E40)), E5)+float(2509.959f*E40<E6)*(5.2995043f*E42+E10*R26.1')@int(min(4096.0f, max(0.0f, E74/E40)));
R26.1  = FIR(R26.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R27.0  = FIR(R27.0; 0.0f, -(2.0f*E2*cos(E73*E62)), E5)+float(2509.959f*E62<E6)*(5.2995043f*E64+E10*R27.1')@int(min(4096.0f, max(0.0f, E74/E62)));
R27.1  = FIR(R27.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R28.0  = FIR(R28.0; 0.0f, -(2.0f*E2*cos(E73*E21)), E5)+float(2509.959f*E21<E6)*(5.2995043f*E23+E10*R28.1')@int(min(4096.0f, max(0.0f, E74/E21)));
R28.1  = FIR(R28.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R29.0  = FIR(R29.0; 0.0f, -(2.0f*E2*cos(E73*E46)), E5)+float(2509.959f*E46<E6)*(5.2995043f*E48+E10*R29.1')@int(min(4096.0f, max(0.0f, E74/E46)));
R29.1  = FIR(R29.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R30.0  = FIR(R30.0; 0.0f, -(2.0f*E2*cos(E73*E68)), E5)+float(2509.959f*E68<E6)*(5.2995043f*E70+E10*R30.1')@int(min(4096.0f, max(0.0f, E74/E68)));
R30.1  = FIR(R30.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R31.0  = FIR(R31.0; 0.0f, -(2.0f*E2*cos(E73*E29)), E5)+float(2509.959f*E29<E6)*(5.2995043f*E31+E10*R31.1')@int(min(4096.0f, max(0.0f, E74/E29)));
R31.1  = FIR(R31.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R32.0  = FIR(R32.0; 0.0f, -(2.0f*E2*cos(E73*E51)), E5)+float(2509.959f*E51<E6)*(5.2995043f*E53+E10*R32.1')@int(min(4096.0f, max(0.0f, E74/E51)));
R32.1  = FIR(R32.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R33.0  = FIR(R33.0; 0.0f, -(2.0f*E2*cos(E73*E35)), E5)+float(2509.959f*E35<E6)*(5.2995043f*E37+E10*R33.1')@int(min(4096.0f, max(0.0f, E74/E35)));
R33.1  = FIR(R33.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R34.0  = FIR(R34.0; 0.0f, -(2.0f*E2*cos(E73*E57)), E5)+float(2509.959f*E57<E6)*(5.2995043f*E59+E10*R34.1')@int(min(4096.0f, max(0.0f, E74/E57)));
R34.1  = FIR(R34.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E75    = 2775.3606f/E0;                                                     // real konst [0.014455003, 55.507214] lsb -27
E76    = 0.002263917f*E0;                                                   // real konst [0.113195844, 434.67206] lsb -68
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R35.0  = FIR(R35.0; 0.0f, -(2.0f*E2*cos(E75*E4)), E5)+0.999926f*float(441.71234f*E4<E6)*(E9+E10*R35.1')@int(min(4096.0f, max(0.0f, E76/E4)));
R35.1  = FIR(R35.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E77    = 24924.258f/E0;                                                     // real konst [0.12981384, 498.48517] lsb -27
E78    = 0.00025209118f*E0;                                                 // real konst [0.012604559, 48.40151] lsb -71
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R36.0  = FIR(R36.0; 0.0f, -(2.0f*E2*cos(E77*E4)), E5)+float(3966.8186f*E4<E6)*(E15+E10*R36.1')@int(min(4096.0f, max(0.0f, E78/E4)));
R36.1  = FIR(R36.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E79    = 60754.96f/E0;                                                      // real konst [0.31643206, 1215.0992] lsb -27
E80    = 0.000103418475f*E0;                                                // real konst [0.0051709237, 19.856348] lsb -73
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R37.0  = FIR(R37.0; 0.0f, -(2.0f*E2*cos(E79*E4)), E5)+float(9669.452f*E4<E6)*(E18+E10*R37.1')@int(min(4096.0f, max(0.0f, E80/E4)));
R37.1  = FIR(R37.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E81    = 8275.275f/E0;                                                      // real konst [0.04310039, 165.50551] lsb -27
E82    = 0.0007592721f*E0;                                                  // real konst [0.037963603, 145.78024] lsb -70
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R38.0  = FIR(R38.0; 0.0f, -(2.0f*E2*cos(E81*E21)), E5)+0.9999828f*float(1317.0509f*E21<E6)*(E24+E10*R38.1')@int(min(4096.0f, max(0.0f, E82/E21)));
R38.1  = FIR(R38.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E83    = 35407.31f/E0;                                                      // real konst [0.18441306, 708.1462] lsb -27
E84    = 0.00017745448f*E0;                                                 // real konst [0.008872723, 34.071262] lsb -72
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R39.0  = FIR(R39.0; 0.0f, -(2.0f*E2*cos(E83*E21)), E5)+0.9999655f*float(5635.248f*E21<E6)*(E27+E10*R39.1')@int(min(4096.0f, max(0.0f, E84/E21)));
R39.1  = FIR(R39.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R40.0  = FIR(R40.0; 0.0f, -(2.0f*E2*cos(E75*E29)), E5)+0.999926f*float(441.71234f*E29<E6)*(E32+E10*R40.1')@int(min(4096.0f, max(0.0f, E76/E29)));
R40.1  = FIR(R40.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R41.0  = FIR(R41.0; 0.0f, -(2.0f*E2*cos(E77*E29)), E5)+float(3966.8186f*E29<E6)*(E33+E10*R41.1')@int(min(4096.0f, max(0.0f, E78/E29)));
R41.1  = FIR(R41.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R42.0  = FIR(R42.0; 0.0f, -(2.0f*E2*cos(E79*E29)), E5)+float(9669.452f*E29<E6)*(E34+E10*R42.1')@int(min(4096.0f, max(0.0f, E80/E29)));
R42.1  = FIR(R42.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R43.0  = FIR(R43.0; 0.0f, -(2.0f*E2*cos(E81*E35)), E5)+0.9999828f*float(1317.0509f*E35<E6)*(E38+E10*R43.1')@int(min(4096.0f, max(0.0f, E82/E35)));
R43.1  = FIR(R43.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R44.0  = FIR(R44.0; 0.0f, -(2.0f*E2*cos(E83*E35)), E5)+0.9999655f*float(5635.248f*E35<E6)*(E39+E10*R44.1')@int(min(4096.0f, max(0.0f, E84/E35)));
R44.1  = FIR(R44.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R45.0  = FIR(R45.0; 0.0f, -(2.0f*E2*cos(E75*E40)), E5)+0.999926f*float(441.71234f*E40<E6)*(E43+E10*R45.1')@int(min(4096.0f, max(0.0f, E76/E40)));
R45.1  = FIR(R45.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R46.0  = FIR(R46.0; 0.0f, -(2.0f*E2*cos(E77*E40)), E5)+float(3966.8186f*E40<E6)*(E44+E10*R46.1')@int(min(4096.0f, max(0.0f, E78/E40)));
R46.1  = FIR(R46.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R47.0  = FIR(R47.0; 0.0f, -(2.0f*E2*cos(E79*E40)), E5)+float(9669.452f*E40<E6)*(E45+E10*R47.1')@int(min(4096.0f, max(0.0f, E80/E40)));
R47.1  = FIR(R47.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R48.0  = FIR(R48.0; 0.0f, -(2.0f*E2*cos(E81*E46)), E5)+0.9999828f*float(1317.0509f*E46<E6)*(E49+E10*R48.1')@int(min(4096.0f, max(0.0f, E82/E46)));
R48.1  = FIR(R48.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R49.0  = FIR(R49.0; 0.0f, -(2.0f*E2*cos(E83*E46)), E5)+0.9999655f*float(5635.248f*E46<E6)*(E50+E10*R49.1')@int(min(4096.0f, max(0.0f, E84/E46)));
R49.1  = FIR(R49.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R50.0  = FIR(R50.0; 0.0f, -(2.0f*E2*cos(E75*E51)), E5)+0.999926f*float(441.71234f*E51<E6)*(E54+E10*R50.1')@int(min(4096.0f, max(0.0f, E76/E51)));
R50.1  = FIR(R50.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R51.0  = FIR(R51.0; 0.0f, -(2.0f*E2*cos(E77*E51)), E5)+float(3966.8186f*E51<E6)*(E55+E10*R51.1')@int(min(4096.0f, max(0.0f, E78/E51)));
R51.1  = FIR(R51.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R52.0  = FIR(R52.0; 0.0f, -(2.0f*E2*cos(E79*E51)), E5)+float(9669.452f*E51<E6)*(E56+E10*R52.1')@int(min(4096.0f, max(0.0f, E80/E51)));
R52.1  = FIR(R52.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R53.0  = FIR(R53.0; 0.0f, -(2.0f*E2*cos(E81*E57)), E5)+0.9999828f*float(1317.0509f*E57<E6)*(E60+E10*R53.1')@int(min(4096.0f, max(0.0f, E82/E57)));
R53.1  = FIR(R53.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R54.0  = FIR(R54.0; 0.0f, -(2.0f*E2*cos(E83*E57)), E5)+0.9999655f*float(5635.248f*E57<E6)*(E61+E10*R54.1')@int(min(4096.0f, max(0.0f, E84/E57)));
R54.1  = FIR(R54.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R55.0  = FIR(R55.0; 0.0f, -(2.0f*E2*cos(E75*E62)), E5)+0.999926f*float(441.71234f*E62<E6)*(E65+E10*R55.1')@int(min(4096.0f, max(0.0f, E76/E62)));
R55.1  = FIR(R55.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R56.0  = FIR(R56.0; 0.0f, -(2.0f*E2*cos(E77*E62)), E5)+float(3966.8186f*E62<E6)*(E66+E10*R56.1')@int(min(4096.0f, max(0.0f, E78/E62)));
R56.1  = FIR(R56.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R57.0  = FIR(R57.0; 0.0f, -(2.0f*E2*cos(E79*E62)), E5)+float(9669.452f*E62<E6)*(E67+E10*R57.1')@int(min(4096.0f, max(0.0f, E80/E62)));
R57.1  = FIR(R57.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R58.0  = FIR(R58.0; 0.0f, -(2.0f*E2*cos(E81*E68)), E5)+0.9999828f*float(1317.0509f*E68<E6)*(E71+E10*R58.1')@int(min(4096.0f, max(0.0f, E82/E68)));
R58.1  = FIR(R58.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R59.0  = FIR(R59.0; 0.0f, -(2.0f*E2*cos(E83*E68)), E5)+0.9999655f*float(5635.248f*E68<E6)*(E72+E10*R59.1')@int(min(4096.0f, max(0.0f, E84/E68)));
R59.1  = FIR(R59.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E85    = 2.0914886f*E8;                                                     // real samp [0, 2.0914886] lsb -32
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R60.0  = FIR(R60.0; 0.0f, -(2.0f*E2*cos(E20*E4)), E5)+0.9999828f*float(1310.8384f*E4<E6)*(E85+E10*R60.1')@int(min(4096.0f, max(0.0f, E25/E4)));
R60.1  = FIR(R60.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E86    = 1.7063034f*E8;                                                     // real samp [0, 1.7063034] lsb -33
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R61.0  = FIR(R61.0; 0.0f, -(2.0f*E2*cos(E26*E4)), E5)+0.9999655f*float(5646.533f*E4<E6)*(E86+E10*R61.1')@int(min(4096.0f, max(0.0f, E28/E4)));
R61.1  = FIR(R61.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E87    = 2.1900356f*E23;                                                    // real samp [0, 2.1900356] lsb -32
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R62.0  = FIR(R62.0; 0.0f, -(2.0f*E2*cos(E3*E21)), E5)+0.999926f*float(438.2877f*E21<E6)*(E87+E10*R62.1')@int(min(4096.0f, max(0.0f, E11/E21)));
R62.1  = FIR(R62.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E88    = 5.0063033f*E23;                                                    // real samp [0, 5.0063033] lsb -31
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R63.0  = FIR(R63.0; 0.0f, -(2.0f*E2*cos(E14*E21)), E5)+float(3959.208f*E21<E6)*(E88+E10*R63.1')@int(min(4096.0f, max(0.0f, E16/E21)));
R63.1  = FIR(R63.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E89    = 6.7063036f*E23;                                                    // real samp [0, 6.7063036] lsb -31
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R64.0  = FIR(R64.0; 0.0f, -(2.0f*E2*cos(E17*E21)), E5)+float(7603.562f*E21<E6)*(E89+E10*R64.1')@int(min(4096.0f, max(0.0f, E19/E21)));
R64.1  = FIR(R64.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E90    = 2.0914886f*E31;                                                    // real samp [0, 2.0914886] lsb -32
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R65.0  = FIR(R65.0; 0.0f, -(2.0f*E2*cos(E20*E29)), E5)+0.9999828f*float(1310.8384f*E29<E6)*(E90+E10*R65.1')@int(min(4096.0f, max(0.0f, E25/E29)));
R65.1  = FIR(R65.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E91    = 1.7063034f*E31;                                                    // real samp [0, 1.7063034] lsb -33
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R66.0  = FIR(R66.0; 0.0f, -(2.0f*E2*cos(E26*E29)), E5)+0.9999655f*float(5646.533f*E29<E6)*(E91+E10*R66.1')@int(min(4096.0f, max(0.0f, E28/E29)));
R66.1  = FIR(R66.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E92    = 2.1900356f*E37;                                                    // real samp [0, 2.1900356] lsb -32
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R67.0  = FIR(R67.0; 0.0f, -(2.0f*E2*cos(E3*E35)), E5)+0.999926f*float(438.2877f*E35<E6)*(E92+E10*R67.1')@int(min(4096.0f, max(0.0f, E11/E35)));
R67.1  = FIR(R67.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E93    = 5.0063033f*E37;                                                    // real samp [0, 5.0063033] lsb -31
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R68.0  = FIR(R68.0; 0.0f, -(2.0f*E2*cos(E14*E35)), E5)+float(3959.208f*E35<E6)*(E93+E10*R68.1')@int(min(4096.0f, max(0.0f, E16/E35)));
R68.1  = FIR(R68.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E94    = 6.7063036f*E37;                                                    // real samp [0, 6.7063036] lsb -31
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R69.0  = FIR(R69.0; 0.0f, -(2.0f*E2*cos(E17*E35)), E5)+float(7603.562f*E35<E6)*(E94+E10*R69.1')@int(min(4096.0f, max(0.0f, E19/E35)));
R69.1  = FIR(R69.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E95    = 2.0914886f*E42;                                                    // real samp [0, 2.0914886] lsb -32
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R70.0  = FIR(R70.0; 0.0f, -(2.0f*E2*cos(E20*E40)), E5)+0.9999828f*float(1310.8384f*E40<E6)*(E95+E10*R70.1')@int(min(4096.0f, max(0.0f, E25/E40)));
R70.1  = FIR(R70.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E96    = 1.7063034f*E42;                                                    // real samp [0, 1.7063034] lsb -33
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R71.0  = FIR(R71.0; 0.0f, -(2.0f*E2*cos(E26*E40)), E5)+0.9999655f*float(5646.533f*E40<E6)*(E96+E10*R71.1')@int(min(4096.0f, max(0.0f, E28/E40)));
R71.1  = FIR(R71.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E97    = 2.1900356f*E48;                                                    // real samp [0, 2.1900356] lsb -32
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R72.0  = FIR(R72.0; 0.0f, -(2.0f*E2*cos(E3*E46)), E5)+0.999926f*float(438.2877f*E46<E6)*(E97+E10*R72.1')@int(min(4096.0f, max(0.0f, E11/E46)));
R72.1  = FIR(R72.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E98    = 5.0063033f*E48;                                                    // real samp [0, 5.0063033] lsb -31
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R73.0  = FIR(R73.0; 0.0f, -(2.0f*E2*cos(E14*E46)), E5)+float(3959.208f*E46<E6)*(E98+E10*R73.1')@int(min(4096.0f, max(0.0f, E16/E46)));
R73.1  = FIR(R73.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E99    = 6.7063036f*E48;                                                    // real samp [0, 6.7063036] lsb -31
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R74.0  = FIR(R74.0; 0.0f, -(2.0f*E2*cos(E17*E46)), E5)+float(7603.562f*E46<E6)*(E99+E10*R74.1')@int(min(4096.0f, max(0.0f, E19/E46)));
R74.1  = FIR(R74.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E100   = 2.0914886f*E53;                                                    // real samp [0, 2.0914886] lsb -32
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R75.0  = FIR(R75.0; 0.0f, -(2.0f*E2*cos(E20*E51)), E5)+0.9999828f*float(1310.8384f*E51<E6)*(E100+E10*R75.1')@int(min(4096.0f, max(0.0f, E25/E51)));
R75.1  = FIR(R75.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E101   = 1.7063034f*E53;                                                    // real samp [0, 1.7063034] lsb -33
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R76.0  = FIR(R76.0; 0.0f, -(2.0f*E2*cos(E26*E51)), E5)+0.9999655f*float(5646.533f*E51<E6)*(E101+E10*R76.1')@int(min(4096.0f, max(0.0f, E28/E51)));
R76.1  = FIR(R76.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E102   = 2.1900356f*E59;                                                    // real samp [0, 2.1900356] lsb -32
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R77.0  = FIR(R77.0; 0.0f, -(2.0f*E2*cos(E3*E57)), E5)+0.999926f*float(438.2877f*E57<E6)*(E102+E10*R77.1')@int(min(4096.0f, max(0.0f, E11/E57)));
R77.1  = FIR(R77.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E103   = 5.0063033f*E59;                                                    // real samp [0, 5.0063033] lsb -31
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R78.0  = FIR(R78.0; 0.0f, -(2.0f*E2*cos(E14*E57)), E5)+float(3959.208f*E57<E6)*(E103+E10*R78.1')@int(min(4096.0f, max(0.0f, E16/E57)));
R78.1  = FIR(R78.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E104   = 6.7063036f*E59;                                                    // real samp [0, 6.7063036] lsb -31
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R79.0  = FIR(R79.0; 0.0f, -(2.0f*E2*cos(E17*E57)), E5)+float(7603.562f*E57<E6)*(E104+E10*R79.1')@int(min(4096.0f, max(0.0f, E19/E57)));
R79.1  = FIR(R79.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E105   = 2.0914886f*E64;                                                    // real samp [0, 2.0914886] lsb -32
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R80.0  = FIR(R80.0; 0.0f, -(2.0f*E2*cos(E20*E62)), E5)+0.9999828f*float(1310.8384f*E62<E6)*(E105+E10*R80.1')@int(min(4096.0f, max(0.0f, E25/E62)));
R80.1  = FIR(R80.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E106   = 1.7063034f*E64;                                                    // real samp [0, 1.7063034] lsb -33
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R81.0  = FIR(R81.0; 0.0f, -(2.0f*E2*cos(E26*E62)), E5)+0.9999655f*float(5646.533f*E62<E6)*(E106+E10*R81.1')@int(min(4096.0f, max(0.0f, E28/E62)));
R81.1  = FIR(R81.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E107   = 2.1900356f*E70;                                                    // real samp [0, 2.1900356] lsb -32
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R82.0  = FIR(R82.0; 0.0f, -(2.0f*E2*cos(E3*E68)), E5)+0.999926f*float(438.2877f*E68<E6)*(E107+E10*R82.1')@int(min(4096.0f, max(0.0f, E11/E68)));
R82.1  = FIR(R82.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E108   = 5.0063033f*E70;                                                    // real samp [0, 5.0063033] lsb -31
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R83.0  = FIR(R83.0; 0.0f, -(2.0f*E2*cos(E14*E68)), E5)+float(3959.208f*E68<E6)*(E108+E10*R83.1')@int(min(4096.0f, max(0.0f, E16/E68)));
R83.1  = FIR(R83.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
E109   = 6.7063036f*E70;                                                    // real samp [0, 6.7063036] lsb -31
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R84.0  = FIR(R84.0; 0.0f, -(2.0f*E2*cos(E17*E68)), E5)+float(7603.562f*E68<E6)*(E109+E10*R84.1')@int(min(4096.0f, max(0.0f, E19/E68)));
R84.1  = FIR(R84.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R85.0  = FIR(R85.0; 0.0f, -(2.0f*E2*cos(E81*E4)), E5)+0.9999828f*float(1317.0509f*E4<E6)*(E85+E10*R85.1')@int(min(4096.0f, max(0.0f, E82/E4)));
R85.1  = FIR(R85.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R86.0  = FIR(R86.0; 0.0f, -(2.0f*E2*cos(E83*E4)), E5)+0.9999655f*float(5635.248f*E4<E6)*(E86+E10*R86.1')@int(min(4096.0f, max(0.0f, E84/E4)));
R86.1  = FIR(R86.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R87.0  = FIR(R87.0; 0.0f, -(2.0f*E2*cos(E75*E21)), E5)+0.999926f*float(441.71234f*E21<E6)*(E87+E10*R87.1')@int(min(4096.0f, max(0.0f, E76/E21)));
R87.1  = FIR(R87.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R88.0  = FIR(R88.0; 0.0f, -(2.0f*E2*cos(E77*E21)), E5)+float(3966.8186f*E21<E6)*(E88+E10*R88.1')@int(min(4096.0f, max(0.0f, E78/E21)));
R88.1  = FIR(R88.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R89.0  = FIR(R89.0; 0.0f, -(2.0f*E2*cos(E79*E21)), E5)+float(9669.452f*E21<E6)*(E89+E10*R89.1')@int(min(4096.0f, max(0.0f, E80/E21)));
R89.1  = FIR(R89.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R90.0  = FIR(R90.0; 0.0f, -(2.0f*E2*cos(E81*E29)), E5)+0.9999828f*float(1317.0509f*E29<E6)*(E90+E10*R90.1')@int(min(4096.0f, max(0.0f, E82/E29)));
R90.1  = FIR(R90.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R91.0  = FIR(R91.0; 0.0f, -(2.0f*E2*cos(E83*E29)), E5)+0.9999655f*float(5635.248f*E29<E6)*(E91+E10*R91.1')@int(min(4096.0f, max(0.0f, E84/E29)));
R91.1  = FIR(R91.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R92.0  = FIR(R92.0; 0.0f, -(2.0f*E2*cos(E75*E35)), E5)+0.999926f*float(441.71234f*E35<E6)*(E92+E10*R92.1')@int(min(4096.0f, max(0.0f, E76/E35)));
R92.1  = FIR(R92.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R93.0  = FIR(R93.0; 0.0f, -(2.0f*E2*cos(E77*E35)), E5)+float(3966.8186f*E35<E6)*(E93+E10*R93.1')@int(min(4096.0f, max(0.0f, E78/E35)));
R93.1  = FIR(R93.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R94.0  = FIR(R94.0; 0.0f, -(2.0f*E2*cos(E79*E35)), E5)+float(9669.452f*E35<E6)*(E94+E10*R94.1')@int(min(4096.0f, max(0.0f, E80/E35)));
R94.1  = FIR(R94.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R95.0  = FIR(R95.0; 0.0f, -(2.0f*E2*cos(E81*E40)), E5)+0.9999828f*float(1317.0509f*E40<E6)*(E95+E10*R95.1')@int(min(4096.0f, max(0.0f, E82/E40)));
R95.1  = FIR(R95.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R96.0  = FIR(R96.0; 0.0f, -(2.0f*E2*cos(E83*E40)), E5)+0.9999655f*float(5635.248f*E40<E6)*(E96+E10*R96.1')@int(min(4096.0f, max(0.0f, E84/E40)));
R96.1  = FIR(R96.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R97.0  = FIR(R97.0; 0.0f, -(2.0f*E2*cos(E75*E46)), E5)+0.999926f*float(441.71234f*E46<E6)*(E97+E10*R97.1')@int(min(4096.0f, max(0.0f, E76/E46)));
R97.1  = FIR(R97.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R98.0  = FIR(R98.0; 0.0f, -(2.0f*E2*cos(E77*E46)), E5)+float(3966.8186f*E46<E6)*(E98+E10*R98.1')@int(min(4096.0f, max(0.0f, E78/E46)));
R98.1  = FIR(R98.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R99.0  = FIR(R99.0; 0.0f, -(2.0f*E2*cos(E79*E46)), E5)+float(9669.452f*E46<E6)*(E99+E10*R99.1')@int(min(4096.0f, max(0.0f, E80/E46)));
R99.1  = FIR(R99.0; E12, 0.0f, E13);                                        // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R100.0 = FIR(R100.0; 0.0f, -(2.0f*E2*cos(E81*E51)), E5)+0.9999828f*float(1317.0509f*E51<E6)*(E100+E10*R100.1')@int(min(4096.0f, max(0.0f, E82/E51)));
R100.1 = FIR(R100.0; E12, 0.0f, E13);                                       // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R101.0 = FIR(R101.0; 0.0f, -(2.0f*E2*cos(E83*E51)), E5)+0.9999655f*float(5635.248f*E51<E6)*(E101+E10*R101.1')@int(min(4096.0f, max(0.0f, E84/E51)));
R101.1 = FIR(R101.0; E12, 0.0f, E13);                                       // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R102.0 = FIR(R102.0; 0.0f, -(2.0f*E2*cos(E75*E57)), E5)+0.999926f*float(441.71234f*E57<E6)*(E102+E10*R102.1')@int(min(4096.0f, max(0.0f, E76/E57)));
R102.1 = FIR(R102.0; E12, 0.0f, E13);                                       // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R103.0 = FIR(R103.0; 0.0f, -(2.0f*E2*cos(E77*E57)), E5)+float(3966.8186f*E57<E6)*(E103+E10*R103.1')@int(min(4096.0f, max(0.0f, E78/E57)));
R103.1 = FIR(R103.0; E12, 0.0f, E13);                                       // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R104.0 = FIR(R104.0; 0.0f, -(2.0f*E2*cos(E79*E57)), E5)+float(9669.452f*E57<E6)*(E104+E10*R104.1')@int(min(4096.0f, max(0.0f, E80/E57)));
R104.1 = FIR(R104.0; E12, 0.0f, E13);                                       // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R105.0 = FIR(R105.0; 0.0f, -(2.0f*E2*cos(E81*E62)), E5)+0.9999828f*float(1317.0509f*E62<E6)*(E105+E10*R105.1')@int(min(4096.0f, max(0.0f, E82/E62)));
R105.1 = FIR(R105.0; E12, 0.0f, E13);                                       // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R106.0 = FIR(R106.0; 0.0f, -(2.0f*E2*cos(E83*E62)), E5)+0.9999655f*float(5635.248f*E62<E6)*(E106+E10*R106.1')@int(min(4096.0f, max(0.0f, E84/E62)));
R106.1 = FIR(R106.0; E12, 0.0f, E13);                                       // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R107.0 = FIR(R107.0; 0.0f, -(2.0f*E2*cos(E75*E68)), E5)+0.999926f*float(441.71234f*E68<E6)*(E107+E10*R107.1')@int(min(4096.0f, max(0.0f, E76/E68)));
R107.1 = FIR(R107.0; E12, 0.0f, E13);                                       // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R108.0 = FIR(R108.0; 0.0f, -(2.0f*E2*cos(E77*E68)), E5)+float(3966.8186f*E68<E6)*(E108+E10*R108.1')@int(min(4096.0f, max(0.0f, E78/E68)));
R108.1 = FIR(R108.0; E12, 0.0f, E13);                                       // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid  <-- invalid from here (the recursion)
R109.0 = FIR(R109.0; 0.0f, -(2.0f*E2*cos(E79*E68)), E5)+float(9669.452f*E68<E6)*(E109+E10*R109.1')@int(min(4096.0f, max(0.0f, E80/E68)));
R109.1 = FIR(R109.0; E12, 0.0f, E13);                                       // real samp [-inf, inf] invalid
// real samp [-inf, inf] invalid
process = (R0.1+R1.1+R2.1+R3.1+R4.1+R5.1+R6.1+R7.1+R8.1+R9.1+R10.1+R11.1+R12.1+R13.1+R14.1+R15.1+R16.1+R17.1+R18.1+R19.1+R20.1+R21.1+R22.1+R23.1+R24.1+2.0f*(R25.1+R26.1+R27.1+(R28.1+R29.1+R30.1)+(R31.1+R32.1+(R33.1+R34.1)))+(R35.1+R36.1+R37.1+R38.1+R39.1+R40.1+R41.1+R42.1+R43.1+R44.1+R45.1+R46.1+R47.1+R48.1+R49.1+R50.1+R51.1+R52.1+R53.1+R54.1+R55.1+R56.1+R57.1+R58.1+R59.1)+(R60.1+R61.1+R62.1+R63.1+R64.1+R65.1+R66.1+R67.1+R68.1+R69.1+R70.1+R71.1+R72.1+R73.1+R74.1+R75.1+R76.1+R77.1+R78.1+R79.1+R80.1+R81.1+R82.1+R83.1+R84.1+(R85.1+R86.1+R87.1+R88.1+R89.1+R90.1+R91.1+R92.1+R93.1+R94.1+R95.1+R96.1+R97.1+R98.1+R99.1+R100.1+R101.1+R102.1+R103.1+R104.1+R105.1+R106.1+R107.1+R108.1+R109.1)));
