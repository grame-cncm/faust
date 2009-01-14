## Test file for faust2octave
## See the README for instructions on how to create the octfiles with
## the loadable functions.


## scale the input with a constant
plot(faustscale(sin(linspace(0,8*pi,44100)), 0.5));

## time-variable scaling of the input
plot(faustscale(sin(linspace(0,8*pi,44100)), [3, 1, 2.1, 0]));

## Multiply two signals (just as example of a plugin that takes two audio inputs)
plot(ringmod(sin(linspace(0,8*pi,44100)), sin(linspace(0,3*pi,44100))));

## waveguide oscillator - requires no input, so first parameter is the number
## of output samples to be produced.
[o1, o2] = wgo(8000, [20,400]);
plot(o2);

## call the functions without arguments to get a (minimal) usage description
wgo();
ringmod();
faustscale();


