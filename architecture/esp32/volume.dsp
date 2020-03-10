vol = nentry("Volume[knob:1]", 0.5, 0, 1, 0.01);
program = component("mono.dsp").process;

process = program : par(i, outputs(program), *(vol));