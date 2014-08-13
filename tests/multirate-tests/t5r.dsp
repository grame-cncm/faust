// Faust Template
//process = vectorize(10,_) : serialize : +~_;
process = vectorize(10,_) : +~_ : serialize;

