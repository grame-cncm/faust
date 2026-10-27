// a divisor folded to 0 (the comparison is always false) : the remainder gives 0
process = select2(checkbox("c"), 5, 7) % (hslider("h", 1, 1, 2, 0.5) > 3);
