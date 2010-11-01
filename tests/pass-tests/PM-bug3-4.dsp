toto (n) = fact(n) 
			with {
				fact (0) = 1;
				fact (n) = n*fact(n-1);
			};
	
foo (x:y) = (y:x);
	
process = foo(sin:sqrt);
