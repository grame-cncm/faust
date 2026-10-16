//ERROR : endless recursive pattern matching
rec(s, 0) = _;
rec(s, 1) = s;
rec(s, n) = rec(s, n-2) : *(s);
process = rec(0.5, hslider("n", 2, 1, 8, 1));
