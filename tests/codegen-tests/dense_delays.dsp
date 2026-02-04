// Dense delay line: max delay 64, density ~100%
// Should trigger dense delay representation (not copy delay).

process = _ <: sum(i,64, @(i+1));
