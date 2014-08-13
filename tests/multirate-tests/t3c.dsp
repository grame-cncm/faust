// Faust Template
process = \(x,y).( (vectorize(10,x) : serialize : +(y)), y );

