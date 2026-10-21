// a soundfile part number whose range goes beyond the 256 parts : refused, and under
// -nocert accepted and held within [0, 255] at run time
process = (int(hslider("p", 0, 0, 300, 1)), 0) : soundfile("s[url:{'x.wav'}]", 1) : !, !, _;
