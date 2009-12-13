
// sequences from tuples (parallel -> serial)

serial((x,y))	= serial(x) : serial(y);
serial(x)	= x;

process		= serial((sin,cos,tan));
