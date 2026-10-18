// real block [-2147483648, 2147483648] lsb -1 ; real block [0, 1.0000002] lsb -39
process = (float(pow(int(max(0.0f, min(5e+04f, hslider("n",5e+04f,0.0f,5e+04f,1.0f)))), 2)), pow(max(0.0f, min(1.0f, hslider("x",0.6f,0.0f,1.0f,0.01f))), 2.0f));
