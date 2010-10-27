foo(n,x,y) = vgroup( "foo %n", *(x*y));

process = tgroup("toto", par(i, 4, foo(i, hslider("slid1", 0,0,1,0.1), hslider("/t:toto/slid2", 0,0,1,0.1))));


