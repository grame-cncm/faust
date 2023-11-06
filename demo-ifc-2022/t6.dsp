// double sampleAndHold implemented using ondemand

foo = 1:+~_;
process = ondemand(foo)(button("play")), ondemand(foo)(button("play"));
