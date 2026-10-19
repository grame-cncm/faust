// The input is read twice by compound definitions (frac, x/(x+1), an interpolation) and
// by a recursive filter : under -vec, the loop that stores the input must run before the
// loops that read it.
c = hslider("c", 0.3, 0, 1, 0.01);
process = _ <: (_ <: _ - floor(_)), (+ ~ *(0.5)), (_ <: _/(_+1)), (_ <: _ + c*(_' - _));
