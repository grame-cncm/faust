// Tests pour ondemand
t1 = button("play") : ondemand(1); // OK
t2 = button("play"),_ : ondemand(@(1)); // OK
t3 = _ <: (button("play1"),_:ondemand(_)), (button("play2"),_:ondemand(_)); // OK
t4 = _ <: (button("play1"),_:ondemand(@(1))), (button("play2"),_:ondemand(@(1))); // OK
t5 = _ <: (button("play1"),_:ondemand(@(1))), (button("play1"),_:ondemand(@(1))); // OK

// gen = +(1)~_;
gen = 1 : +~_;
t6 = gen;
t7 = button("play"):ondemand(gen); // OK avec l'option -fir mais pas sans
t8 = gen,t7;

t9 = button("play"), 1 : ondemand(+~_); // OK en mode fir
t10 = gen, t9;

// bugs
b1 = ondemand(+~_);