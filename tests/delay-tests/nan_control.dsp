// The slider at its minimum gives sqrt(-1) = NaN, an amount outside any interval
process = _ <: @(10 * min(sqrt(hslider("x", 0, -1, 1, 0.01)), 1));
