// real block [0, 1] lsb -1
E0 = float(button("[1] Left          [tooltip: Send impulse into LEFT channel]/[2] Impulse Selection/Stereo Reverb Tester")>0.0f);
// real block [0, 1] lsb -1
E1 = float(button("[2] Center          [tooltip: Send impulse into LEFT and RIGHT channels]/[2] Impulse Selection/Stereo Reverb Tester")>0.0f);
E2 = E1-E1'>0.0f;  // int samp [0, 1] lsb 0
// real samp [-168.5732, 168.5732] lsb -173
E3 = 0.1f*float(checkbox("[2] Pink Noise          [tooltip: Pink Noise (or 1/f noise) is Constant-Q Noise (useful for adjusting the EQ sections)]/[1] Input Config/Stereo Reverb Tester")>0.0f)*FIR(4.656613e-10f*IIR(float(IIR(12345; 1103515245)); 2.494956f, -2.0172658f, 0.5221894f); 0.049922034f, -0.095993534f, 0.0506127f, -0.004408786f);
// real block [0, 1] lsb -1
E4 = float(button("[3] Right          [tooltip: Send impulse into RIGHT channel]/[2] Impulse Selection/Stereo Reverb Tester")>0.0f);
process = (float((E0-E0'>0.0f)+E2)+E3, float(E2+(E4-E4'>0.0f))+E3);  // real samp [-168.5732, 170.5732] lsb -173 ; real samp [-168.5732, 170.5732] lsb -173
