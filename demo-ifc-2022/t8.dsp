// double sampleAndHold implemented using ondemand

process = _ <: ondemand(@(10))(button("play")), ondemand(@(20))(button("play"));
