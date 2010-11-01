// exemple de schema non encore simplifié


fold(1,f,x)	= x(0);
fold(n,f,x)	= f(fold(n-1,f,x),x(n-1));
fpar(n)	= fold(n,\(x,y).(x,y));
partial(i)	= 2*i;

process	= fpar(5, \(i,x).(partial(i)));

