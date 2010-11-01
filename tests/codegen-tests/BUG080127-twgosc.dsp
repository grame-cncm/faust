//-------------------------------------
// BUG decouvert par jos le 27 janv 2008
// Non partage d'une expression slow
//-------------------------------------



import("music.lib");

amp = vslider("_amp",0.1,0,1,0.01);
fr = vslider("_freq",440,10,20000,1);

//----------------------------- wgr ---------------------------------
// Second order transformer-normalized digital waveguide resonator
// wgr(fr,G)
//   fr : frequency (Hz)
//   r  : per-sample loss factor for exponential decay 
//        (set to 1 to make a numerically stable oscillator)
//
// Reference:
// http://ccrma.stanford.edu/~jos/pasp/Digital_Waveguide_Oscillator.html
//
//wgr(fr,r,x) = (*(G)+x, _ <: _, ((+:*(C)) <: _,_), _ : +,-) ~ cross : *(g),_
//wgr(fr,r,x) = (*(G)+x*g,_<:_,((+:*(C))<:_,_),_:+,-) ~ cross
  wgr(fr,r,x) = (*(G),_<:_,((+:*(C))<:_,_),_:+:+(x),-) ~ cross : _,/(0-g)
with { 
  C = cos(2*PI*fr/SR);
  g = sqrt((1-C)/(1+C)); // compensate amplitude (only needed when 
  G = r*g/(1-1' + g');   //   frequency changes substantially)
  cross = _,_ <: !,_,_,!;
};

//---------------------------- wgosc --------------------------------
// wgosc - a unit-amplitude cosine oscillator made by pulsing wgr
//         and blocking the unnormalized phase-quadrature output.
// NOTE: Amplitude drifts if the frequency is changed too much, 
//       especially when taken near dc for a while.
wgoscq(fr) = 1-1' : wgr(fr,1);       // phase quadrature outputs
wgoscc(fr) = 1-1' : wgr(fr,1) : _,!; // cosine (cheapest at 1 mpy/sample)
wgoscs(fr) = 1-1' : wgr(fr,1) : !,_; // sine (needs a division for unit amp)
wgosc = wgoscc;

//process = wgosc(fr) : *(amp);
//process = wgoscq(fr);
//process = wgoscc(fr);
// Should be 1.0 for all time:
//process = wgoscc(fr) * wgoscc(fr) + wgoscs(fr) * wgoscs(fr);

/////--------------------------------
///// VERSION SIMPLIFIEE DU PROBLEME
/////--------------------------------

//process = wgoscq(fr);
process = test(fr);

test(fr) =*(g), *(g-g')
with { 
  C = cos(2*PI*fr/SR);
  g = sqrt((1-C)/(1+C)); // compensate amplitude (only needed when 
  //G = g/(1-1' + g');   //   frequency changes substantially)
};
