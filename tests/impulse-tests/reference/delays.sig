// real samp [-inf, inf] invalid ; real samp [-inf, inf] invalid ; real samp [-inf, inf] invalid
process = (0.001f*IIR(IN[0]@int(max(0.0f, min(1e+03f, nentry("d1",2e+02f,0.0f,1e+03f,1.0f)))); 0.999f), 0.001f*IIR(IN[1]@int(max(0.0f, min(2e+03f, nentry("d2",2e+02f,0.0f,2e+03f,1.0f)))); 0.999f), 0.001f*IIR(IN[2]@int(max(2e+02f, min(3e+03f, nentry("d3",4e+02f,2e+02f,3e+03f,1.0f)))); 0.999f));
