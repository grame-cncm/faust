import("oscillator.lib");

process = C, 0.0 : M : S;

C = square(440.0);

M(x, y) = z, F(z + y)
with {
    z = F(x);
};

S(x, y) = x - 0.3333333333333333 * y;

F = *(0.08) : + ~ *(0.92);
