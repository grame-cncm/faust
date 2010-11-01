// exemple de schema illisible
toto(0,f) = _;
toto(1,f) = f(1);
toto(n,f) = f(n) : toto(n-1,f);
	
process = toto(10,\(i).(*(i)));
