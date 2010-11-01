import("music.lib");

//foo (d) = (+:delay1s(d)) ~ _;
foo (d) = (+:@(d)) ~ _;
process = _ <: foo(30), foo(20);