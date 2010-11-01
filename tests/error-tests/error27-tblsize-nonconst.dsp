import("music.lib");

foo(i) = rdtable(SR, time%6, i);

process = foo(time%128);