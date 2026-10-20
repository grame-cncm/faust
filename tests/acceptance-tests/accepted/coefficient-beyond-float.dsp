// a coefficient beyond FLT_MAX is an infinity in single precision : the sharing of the dense
// sums must still end (it looped on it) ; the program is accepted, its output unbounded
process = _ <: 1e39*_ + 2*_' + 3*_'';
