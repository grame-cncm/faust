// real samp [-inf, inf]
process = (IN[0]*(0.001f*IIR(pow(1e+01f, 0.05f*max(-7e+01f, min(4.0f, vslider("[1]",0.0f,-7e+01f,4.0f,0.1f)))); 0.999f)));
