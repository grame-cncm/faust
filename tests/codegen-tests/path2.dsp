foo(n,x,y) = vgroup( "foo %n", *(x*y));

process = tgroup("toto", par(i, 4, foo(i, hslider("slid", 0,0,1,0.1), hslider("../common", 0,0,1,0.1))));
 
