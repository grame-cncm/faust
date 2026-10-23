// -single: 15 * 0.32 + 0.2 is below 5 rounded apart, exactly 5 when fused into an FMA;
// reaches the copy-delay underflow in -vec, where the buffer is padded to a multiple of 4
process = _ <: @(hslider("x", 0, 0, 0.32, 0.001) * 15 + 0.2);
