ml = library("music.lib");

oscs(freq) = rdtable(tablesize, sinwaveform, int(ml.phase(freq)) );
oscc(freq) = rdtable(tablesize, coswaveform, int(ml.phase(freq)) );
oscp(freq,p) = oscs(freq) * cos(p) + oscc(freq) * sin(p);
// osc = oscs; // music.lib
sinwaveform = float(ml.time)*(2.0*pi)/float(tablesize) : sin;
coswaveform = float(ml.time)*(2.0*pi)/float(tablesize) : cos;
tablesize = 1 << 16;
pi = 4.0*atan(1.0);
