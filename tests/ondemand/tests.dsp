import("stdfaust.lib");

clock(n) = 1 : (+,n:%)~_  : ==(1); 

// Various tests illustrating the behaviour of ondemand(P)
// > faust2csvplot -lang ocpp tests.dsp
// > faust -svg -lang ocpp tests.dsp 
// > ./tests -n 20

// T01: 1:ondemand(P) == P
t01 = 1 : ondemand(1:+~_); // 1 2 3 4 5 ...

t02 = clock(2) : ondemand(1:+~_); // 1 1 2 2 3 3 ...

t03 = clock(2) : ondemand(t01); // 1 1 2 2 3 3 ...

t04 = clock(2) : ondemand(no.noise); // 5.74858859e-06 5.74858859e-06 -0.344845951 -0.344845951

t05 = no.noise, (clock(2) : ondemand(no.noise)); //

t06 = no.noise, (clock(2), no.noise : ondemand(_)); // Sample and hold

t07 = clock(2) : ondemand(t06); // Sample and hold

process = t07;

