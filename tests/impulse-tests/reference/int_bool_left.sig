// int block [-2147483648, 2147483520] lsb 0
E0 = int(min(2.1474835e+09f, max(max(-3e+09f, min(3e+09f, hslider("x",-3e+09f,-3e+09f,3e+09f,1.0f))), -2.1474836e+09f)));
process = ((E0>0)-E0, -1+E0+(E0<0));  // int block [-2147483648, 2147483647] lsb 0 ; int block [-2147483648, 2147483647] lsb 0
