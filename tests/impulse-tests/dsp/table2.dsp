
rw1 = rwtable(SIZE, integrator, windex, input, rindex)
with {
    SIZE = 10;
    integrator = +(1) ~ _;
    windex = (integrator+1)%SIZE;
    rindex = (integrator+2)%SIZE;
    input = 2*integrator;
};

rw2 = rwtable(SIZE, integrator, windex, input, rindex)
with {
    SIZE = 7;
    integrator = +(0.1) ~ _;
    windex = (integrator+1)%SIZE;
    rindex = (integrator+2)%SIZE;
    input = 1.24*integrator;
};

rw3 = rwtable(SIZE, integrator, windex, input, rindex)
with {
    SIZE = 10;
    integrator = waveform {1,2,3,7,4,8,1} : !,_;
    windex = (integrator+1)%SIZE;
    rindex = (integrator+2)%SIZE;
    input = 1.24*integrator;
};

rw4 = rwtable(SIZE, integrator, windex, input, rindex)
with {
    SIZE = 7;
    integrator = waveform {1.4,2.1,3.8,7.12,4.9,8.9,1.2} : !,_;
    windex = (integrator+1)%SIZE;
    rindex = (integrator+2)%SIZE;
    input = 1.24*integrator;
};

process = rw1,rw2,rw3,rw4;