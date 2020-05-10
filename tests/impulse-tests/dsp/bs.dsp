// Test the BS variable access

process = ramp(BS, 10)
with {
	ramp = case {
		(0) => _;
		(n) => \(y,x).(if(y+x/n < x, y+x/n, if(y-x/n > x, y-x/n, x))) ~ _;
	};
	if(cond,then,else) = select2(cond,else,then);
	BS = fvariable(int count, <math.h>);
};
