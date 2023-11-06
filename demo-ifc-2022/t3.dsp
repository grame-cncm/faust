// same button, double sampleAndHold implemented using ondemand

process = _ <: ondemand(_)(button("play")), ondemand(_)(button("play"));
