/*
Beamforming - Prototyp
*/

import("music.lib");

nquads = 6; // amount of quadrants on 1 axis
roomsize = 2.0; // x*x meters
nmics = 6; // amount of microfones

// delay with offset, to avoid negative delays
//delayl(n) = fdelay(512, n+256);
delayl(n) = delay(512, n+256); // without interpolation

// x-axis of mic(n) (depends on arrangement of mics)
mic(n) = 0.1*n-0.1;

// vectornorm
vabs(x,y) = sqrt(x*x+y*y);

// subtraction of vectors
vsub(x1,y1,x2,y2) = (x1-x2) , (y1-y2);

// index to meters (x/y-axis):
// index = 0...nquads
i2x(x) = (x/nquads)*roomsize-(roomsize*0.5);
i2y(y) = (y/nquads)*roomsize;

// Laufzeit L(x1,y1,x2,y2): time from point (x1,y1) to (x2,y2)
// Betrag(Vektorsubtraktion(M-P)) / 343 m/s * 44100 /s -> also in Samples
stime(mx,my,px,py) = vsub(mx,my,i2x(px),i2y(py)):vabs / 343 * 44100;

// Laufzeitdifferenz Ld(mic):
// m is the mic-number; Ld(mic) = L(mic(0)) - L(mic(m)); mic(m) computes only x-axis
dtime(x, y, m) = stime(mic(0),-0.5,x,y)-stime(mic(m),-0.5,x,y);

// create delays (x,y): index of coordinates of the focused point, m:microfonnumber
delayer(x, y, m) = delayl(dtime(x, y, m));

// add delays
add(x) = seq(i, x-2, +,par(j,x-2-i,_)) : +;
//beamer(x, y) = par(i, nmics, delayer(x, y, i)):seq(j,nmics-1,+);
beamer(x, y) = par(i, nmics, delayer(x, y, i)) : add(nmics);

audioin = par(i,nmics,_);

// spread audioins to beamformers
beamform = audioin<:par(x, nquads, par(y, nquads, beamer(x, y)));

// sehr ineffizient wegen dem log10 -> mal mit icc probieren
// env = abs : max(db2linear(-96)) : linear2db : min(10)  : max ~ -(96.0/SR);
env = abs : max ~ -(96.0/SR);

envs = par(i,nquads*nquads,env);

gui = par(x, nquads, hgroup("ctrl %3d",
  par(y, nquads, vbargraph("ctrl %2c", 0, 1) with { c=x*10+y; })) with { d=x;});

process = beamform : envs : gui;


