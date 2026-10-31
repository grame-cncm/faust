// round(x) moves halfway values away from zero, rint(x) moves them to even,
// and remainder(x, y) uses the rint of x/y. t runs over halfway values of both
// signs, where the two roundings disagree, v over ordinary values, and w gives
// large quotients with values that are exact in single precision too.
t = float((+(1) ~ _) % 16) * 0.5 - 4.0;
v = float((+(1) ~ _) % 11) * 1.37 - 7.1;
w = float((+(1) ~ _) % 11) * 1001.0 + 0.25;

process = round(t), rint(t), remainder(t, 1.0), round(v), rint(v), remainder(v, 0.9),
          remainder(w, 0.6875);
