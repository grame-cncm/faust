fact = case {
	(0) => 1;
	(n) => n*fact(n-1);
	};
	
toto = case {
		(fact(5)) 	=> *;
		//(120) 	=> *;
		(x)		=> x;
		};
	
process = toto(fact(6)),  toto(fact(5));
