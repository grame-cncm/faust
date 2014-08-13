smooth (c) 	= *(1-c) : +~*(c);
process 	= vectorize(10,_) : smooth(0.9) : serialize;

