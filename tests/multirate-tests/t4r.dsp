// Faust Template
process = +~_, (vectorize(10,_) : serialize : +~_);

