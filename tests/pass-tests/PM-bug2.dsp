 
 // here in both case we should be equivalent to  "process = *,*;"
 foo(x,y) = (y,x);
 
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

 process = choice1(1), choice2(1);
 
 