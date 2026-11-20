// remainder(x, y) rounds x/y to the nearest integer, ties to even, with or
// without -mapp: x runs over negative and positive values, exact ties included.
ramp = (+(1) ~ _) % 64 - 32;
x = float(ramp) * 0.25;

process = remainder(x, 1.0), remainder(x, 2.0), remainder(x, 4.0), remainder(_ * -9.2, 2.0);
