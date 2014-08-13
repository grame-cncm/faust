smooth (c) = *(1-c) : +~*(c);
integrate = +~_;
//process = vectorize(10,_) : smooth(0.9) : serialize;
process = vectorize(10,_) : integrate;
//process = _ : smooth(0.9) ;

