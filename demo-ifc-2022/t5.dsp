// double sampleAndHold implemented using ondemand

foo = 1:+~_;
process = ondemand(foo)(button("play1")), ondemand(foo)(button("play2"));
