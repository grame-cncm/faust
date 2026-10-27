// -2147483648 % -1 gives its exact value, 0 (the divisor is taken in absolute value)
process = int(hslider("x", 0, -2147483648, 0, 1)) % int(hslider("k", -1, -2, -1, 1));
