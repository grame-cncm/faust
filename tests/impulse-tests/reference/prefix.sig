E0 = prefix(0.35f, 0.9f);  // real samp [0.35, 0.9] lsb -34
process = (prefix(0.5f, 0.8f), prefix(0.31f, IN[0]), prefix(0.7f, prefix(0.32f, IN[1])), E0, E0);  // real samp [0.5, 0.8] lsb -33 ; real samp [-inf, inf] ; real samp [-inf, inf] ; real samp [0.35, 0.9] lsb -34 ; real samp [0.35, 0.9] lsb -34
