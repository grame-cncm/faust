foo(x) = vgroup( "foo", x);

process = tgroup("toto", foo(hslider("../slid2", 0,0,1,0.1)));
 
