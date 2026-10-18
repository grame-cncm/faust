E0 = float(button("play/excitator")>0.0f);  // real block [0, 1] lsb -1
// real samp [-0.5, 16777216] lsb -33
R0 = float(E0-E0'>0.0f)-1.0f/max(2.0f, min(512.0f, hslider("excitation [unit:f]/excitator",327.023f,2.0f,512.0f,1.0f)))*float(R0'>0.0f)+R0';
// real samp [-16777216, 16777216] lsb -1248
R1 = (0.5f*(1.0f-max(0.0f, min(1.0f, hslider("attenuation/resonator",0.0f,0.0f,1.0f,0.01f))))*FIR(R1; 0.0f, 1.0f, 1.0f)+4.656613e-10f*max(0.0f, min(1.0f, hslider("level",0.5f,0.0f,1.0f,0.01f)))*(float(IIR(12345; 1103515245))*float(R0>0.0f)))@(int(-1.5f+max(2.0f, min(512.0f, hslider("duration [unit:f]/resonator",271.994f,2.0f,512.0f,1.0f))))&4095);
process = (R1);                             // real samp [-16777216, 16777216] lsb -1248
