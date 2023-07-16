import("stdfaust.lib");

gain = .75;
dc = -.15;

process = _*(gain),dc : +;
