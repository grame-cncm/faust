// real samp [-1, 1] lsb -100
process = (4.656613e-10f*max(0.0f, min(1.0f, vslider("Volume[style:knob][acc: 0 0 -10 0 10]",0.5f,0.0f,1.0f,0.1f)))*float(IIR(12345; 1103515245)));
