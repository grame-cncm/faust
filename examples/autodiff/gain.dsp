import("stdfaust.lib");

gain = hslider("gain [diff:1]", .5, 0, 1, .001);

process = _*gain;
