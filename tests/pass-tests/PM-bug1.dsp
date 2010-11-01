 // ------------------------------------------------------------------
 // In this example the two choice0 should give the same operation (/)
 // But this is not the case as "3,6:foo:/" is not correctly 
 // simplified to 2.
 //-------------------------------------------------------------------
 
 foo(x,y) = (y,x);
 
 choice0 = case {
 			(1) => *;
 			(2) => /;
 			(x)	=> +;
 		  };

 process = choice0((6,3:/)), choice0((3,6:foo:/));
 
 