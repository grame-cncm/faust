// -single: 10 * 0.29 + 0.1 is below 3 rounded apart, exactly 3 when fused into an FMA
process = _ <: @(hslider("x", 0, 0, 0.29, 0.001) * 10 + 0.1);
