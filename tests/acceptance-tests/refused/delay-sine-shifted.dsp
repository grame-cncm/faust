// the sine of an audio input, whose values are not bounded, may be NaN : a delay of
// unknown bounds, even shifted into [0, 8]
process = @(_, int(4*sin(_)+4));
