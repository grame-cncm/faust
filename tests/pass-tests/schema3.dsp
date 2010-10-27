// exemple de schema illisible

 import("music.lib");
 fold		= case {
		    (1,f,x) => x(0);
		    (n,f,x) => f(fold(n-1,f,x),x(n-1));
		  };
 fpar(n)	= fold(n,\(x,y).(x,y));
 freq		= hslider("freq", 440, 20, 20000, 0.1);
 partial(i)	= osc(i*freq);
 process	= fpar(5, partial);

