import("math.lib");
import("oscillator.lib");


process = C, 0.0 : M : M : M : S;


C = square(freq) + square(freq + delta) : *(level)
with {
    freq  = hslider("freq carre", 440, 20, 8000, 1);
    delta = hslider("delta", 2, 0, 6, 0.1);
    level = hslider("level", 0.5, 0, 1, 0.01);
};
// C = square(freq)
// with {
//     freq = hslider("freq carre", 440, 20, 8000, 1);
// };


M(x, y) = z, F(x*x*x - z*z*z + y)
with {
    z = F(x);
};


// S(x, y) = x + T3 * y
// with {
//     T3 = -0.3333333333333333 * checkbox("NL");
// };
S(x, y) = x - 0.3333333333333333 * y;


F = *(v / (1.0 + v)) : + ~ /(1.0 + v)
with {
    v = (2.0 * PI / SR) * hslider("freq[unit:Hz]", 700, 1, 20000, 1);
};
// F = *(0.08) : + ~ *(0.92);
