// the sine of an audio input, whose values are not bounded, may be NaN : the conversion
// gives NaN the value 0, and the delay lies within [0, 8]
process = @(_, int(4*sin(_)+4));
