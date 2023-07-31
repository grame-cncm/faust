alpha = hslider("alpha [diff:1]", 0, 0, 1, .001);
process = _ <: _,_',alpha : _,* : +;
