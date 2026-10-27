// a divisor folded to 0 : the comparison is always false
process = select2(checkbox("c"), 5, 7) % (hslider("h", 1, 1, 2, 0.5) > 3);
