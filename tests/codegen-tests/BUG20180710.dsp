import("stdfaust.lib");
// This program should compile but the interval of the table is not 
// correctly computed by faust 2.8.0

phase(f) = f/48000.0 : (+, 1.0 : fmod) ~ _;
sinwave(f) = phase(f) * 2 * ma.PI : sin : +(1) : /(2);
tosc(f) = 48000, sinwave(1), int(max(0, min(phase(f)*48000, 47999))) : rdtable;

process = os.osc(440) : @(tosc(10)*100);


