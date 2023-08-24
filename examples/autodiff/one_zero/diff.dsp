b1 = hslider("b1 [diff:1]", .5, 0, 1, .001);
process = _ <: _,_',b1 : _,* : +;
