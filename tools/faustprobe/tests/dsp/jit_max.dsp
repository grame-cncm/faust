// d is 128 for the first 9 frames, then 16: max(-1, d) is d.
c = 1 : + ~ _;
b = c < 10;
d = 16 + 112*b;
process = d, max(-1, d);
