//-----------------------------------------------------------------
// bug discovered by jos and resolved by removing recursive call 
// to simplify() in normalizeFixedDelayTerm()
//-----------------------------------------------------------------

import("music.lib");

tf1(b0,b1,a1) = _ <: *(b0), (mem : *(b1)) :> + ~ *(0-a1);

tf1s(b1,b0,a0,w1) = tf1(b0d,b1d,a1d)
with {
  c   = 1/tan((w1)*0.5/srate); // bilinear-transform scale-factor
  d   = a0 + c;
  b1d = (b0 - b1*c) / d;
  b0d = (b0 + b1*c) / d;
  a1d = (a0 - c) / d;
};

tf2(b0,b1,b2,a1,a2) = sub ~ conv2(a1,a2) : conv3(b0,b1,b2)
with {
  conv3(k0,k1,k2,x)     = k0*x + k1*x' + k2*x'';
  conv2(k0,k1,x)        = k0*x + k1*x';
  sub(x,y)              = y-x;
};

tf2s(b2,b1,b0,a1,a0,w1) = tf2(b0d,b1d,b2d,a1d,a2d)
with {
  c   = 1/tan((w1)*0.5/srate); // bilinear-transform scale-factor
  csq = c*c;
  d   = a0 + a1 * c + csq;
  b0d = (b0 + b1 * c + b2 * csq)/d;
  b1d = 2 * (b0 - b2 * csq)/d;
  b2d = (b0 - b1 * c + b2 * csq)/d;
  a1d = 2 * (a0 - csq)/d;
  a2d = (a0 - a1*c + csq)/d;
};

// new:

lowpass5(fc) =
	      tf1s(0,1,1,w1) :
	      tf2s(0,0,1,a11,1,w1) :
	      tf2s(0,0,1,a12,1,w1)
with {
  a11 = 1.618033988749895;
  a12 = 0.618033988749895;
  w1 = 2.0*pie*fc;
};

// new:

highpass5(fc) =
	      tf1s(1,0,1,w1) :
	      tf2s(1,0,0,a11,1,w1) :
	      tf2s(1,0,0,a12,1,w1)
with {
  a12 = 0.618033988749895;
  a11 = 1+a12;
  w1 = 2.0*pie*fc;
};

// new:

highpass5_plus_lowpass5(fc) = _<: highpass5(fc), lowpass5(fc) :>_;

pie = PI;
//pie = 4*atan(1.0); // cured the seg fault at one time (no longer)

srate = float(SR); // seg fault
//srate = 44100.0; // cures the seg fault!

Noct=3;
ftop=16000;
fbank = delayeq(Noct) with {
  fc(n) = ftop * 2^(float(n-Noct-1)); // -3dB crossover frequencies
  ap(n) = highpass5_plus_lowpass5(fc(n)); // delay-equalizing allpass
  delayeq(Noct) = par(i,Noct-1,apchain(i+1)), _, _;
  apchain(i) = seq(j,Noct-i,ap(j+1));
};

process = fbank;


