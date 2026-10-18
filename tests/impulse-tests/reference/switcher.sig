E0 = max(0.0f, min(1.0f, hslider("source 0 <-> source 1",0.0f,0.0f,1.0f,1.0f)));  // real block [0, 1] lsb -32
process = (mix(E0, IN[0], IN[2]), mix(E0, IN[1], IN[3]));                         // real samp [-inf, inf] invalid ; real samp [-inf, inf] invalid
