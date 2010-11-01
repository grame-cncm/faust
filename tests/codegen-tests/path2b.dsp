foo(n,x,y) = vgroup( "foo %n", *(x*y));

process = tgroup("toto", vgroup("foo", hslider("../slid2", 0,0,1,0.1)));
 
