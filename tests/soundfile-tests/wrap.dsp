// A 3 channels soundfile read with 70 outputs: output k is channel k % 3 (see soundfile-wrap.cpp)
process = 0,_~+(1) : soundfile("son[url:{'wrap3.wav'}]", 70) : !,!,par(i, 70, _);
