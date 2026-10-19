// real samp [0, 1] lsb -1 invalid ; real samp [-inf, inf] invalid ; real samp [-inf, inf] invalid ; real samp [-inf, inf] invalid
process = (frac(IN[0]), IIR(IN[0]; 0.5f), tpt(IN[0]), IN[0]+max(0.0f, min(1.0f, hslider("c",0.3f,0.0f,1.0f,0.01f)))*FIR(IN[0]; -1.0f, 1.0f));
