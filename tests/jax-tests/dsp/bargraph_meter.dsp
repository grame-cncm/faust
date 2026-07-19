import("stdfaust.lib");
level = hbargraph("level", -1, 1);
process = _ <: attach(_, abs : level);
