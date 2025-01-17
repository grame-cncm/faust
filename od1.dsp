
t1 = button("play") : ondemand(1);
t2 = button("play"),_ : ondemand(@(1));
t3 = _ <: (button("play1"),_:ondemand(_)), (button("play2"),_:ondemand(_));
t4 = _ <: (button("play1"),_:ondemand(@(1))), (button("play2"),_:ondemand(@(1)));
t5 = _ <: (button("play1"),_:ondemand(@(1))), (button("play1"),_:ondemand(@(1)));