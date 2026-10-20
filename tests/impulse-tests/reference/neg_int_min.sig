// int block [-2147483648, 2147483647] lsb 0 ; int samp [-2147483648, 2147483647] lsb 0
process = (-int(min(2.1474835e+09f, max(max(-3e+09f, min(0.0f, hslider("x",-3e+09f,-3e+09f,0.0f,1.0f))), -2.1474836e+09f))), -int(min(2.1474835e+09f, max(IN[0], -2.1474836e+09f))));
