// x = a*b + c is 0.5 when each operation is rounded apart, 0.49999997 when the C++
// compiler fuses it into an FMA (clang on arm64, by default) : the index of the table
// may be 64, it must keep its guard.
a = hslider("a", 1.30550981, 1.30550981, 2, 0.01);
b = hslider("b", 1.10202765, 1.10202765, 2, 0.01);
c = hslider("c", -0.938707948, -0.938707948, 1, 0.01);
x = a*b + c : hbargraph("x", -2, 6);
process = rdtable(64, (+(1)~_), 63 + (x < 0.5));
