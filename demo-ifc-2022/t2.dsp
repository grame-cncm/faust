// double sampleAndHold implemented using ondemand

process = _ <: ondemand(_)(button("play1")), ondemand(_)(button("play2"));
