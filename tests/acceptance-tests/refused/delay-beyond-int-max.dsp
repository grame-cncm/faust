// a real slider used directly as a delay, whose values go beyond INT_MAX
process = @(_, hslider("d", 3e9, 3e9, 4e9, 1));
