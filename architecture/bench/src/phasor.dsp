import("music.lib");

phasor_imp(freq, reset, phase) = (select2(prefix(1, clk), +(inc), phase) : decimal) ~ _
with {
    clk = reset>0;
    inc = freq/SR;
};

process = phasor_imp(700, reset, phase), reset, phase
with {  
    reset = waveform {0., 0., 0., 0., 1., 1., 0., 0., 0., 0., 0} : !,_;
    phase = waveform {0.1, 0.8, 0.9, 0.2} : !,_;
};