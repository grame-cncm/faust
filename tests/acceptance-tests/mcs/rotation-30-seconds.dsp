// a sine computed by a rotation (os.oscrs) drives a delay : the rounding drift of the
// rotation bounds the delay for 30 seconds at 48000 Hz in single precision, accepted with
// the default -mcs 10, refused under -mcs 60
SR = min(192000, max(50, fconstant(int fSamplingFreq, <math.h>)));
th = 2*3.141592653589793*440/SR;
c = cos(th);
s = sin(th);
cross = _,_ <: !,_,_,!;
nlf2(x) = ((_<:_,_),(_<:_,_) : (*(s),*(c),*(c),*(0-s)) :> (_,+(x))) ~ cross;
process = _ @ int(10*(nlf2(1-1') : _,!) + 20);
