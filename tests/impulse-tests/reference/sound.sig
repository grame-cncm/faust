E0 = length(soundfile("son[url:{'sound1';'sound2'}]"), 0);  // int block [0, 2147483647] lsb 0 invalid  <-- invalid from here
E1 = max(0, min(IIR(1; 1), -1+E0));                         // int samp [0, 2147483646] lsb 0 invalid
// real samp [-1, 1] lsb -24 invalid ; real samp [-1, 1] lsb -24 invalid ; real samp [-1, 1] lsb -24 invalid ; real samp [-1, 1] lsb -24 invalid
process = (buffer(soundfile("son[url:{'sound1';'sound2'}]"), 0, 0, E1), buffer(soundfile("son[url:{'sound1';'sound2'}]"), 1, 0, E1), buffer(soundfile("son[url:{'sound1';'sound2'}]"), 2, 0, E1), buffer(soundfile("son[url:{'sound1';'sound2'}]"), 3, 0, E1));
