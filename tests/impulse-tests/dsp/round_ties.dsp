// round(x) and rint(x) move these halfway values to the integer of greater
// magnitude: -1.5 gives -2, not -1. y runs over 1.5, 3.5, ... 15.5, where
// rounding away from zero and rounding to even agree, for both signs.
k = (+(1) ~ _) % 8;
y = float(k) * 2.0 + 1.5;

process = round(y), round(0.0 - y), round(_ * -1.5), rint(y), rint(0.0 - y), rint(_ * -1.5);
