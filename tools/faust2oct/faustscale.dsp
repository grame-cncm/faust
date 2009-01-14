// simple faust example
// just scale the input

gain = nentry("gain", 1, 0, 1, 0.01);

process		= *(gain);
