 
 foo(x,y) = (y,x);
 
 choice0 = case {
 			(1) => *;
 			(2) => /;
 			(x)	=> +;
 		  };
 
 choice1 = case {
 			((3,2:-)) => *;
 			((4,2:-)) => /;
 			(x)	=> +;
 		  };
 
 choice2 = case {
 			((2,3:foo:-)) => *;
 			((2,4:foo:-)) => /;
 			(x)	=> +;
 		  };

 //process = choice0((6,3:/));
 process = choice0((3,6:foo:/));
 
 