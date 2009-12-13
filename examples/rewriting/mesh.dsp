
/* Layout of a systolic array:

        x1        xm
        ↓         ↓
   y1 → □ → ... → □ → y1'
        ↓         ↓
       ...       ...
        ↓         ↓
   yn → □ → ... → □ → yn'
        ↓         ↓
        x1'       xm'

  g(m,f)   : y,x1,...,xm -> x1',...,xm',y'
  constructs a single row of size m.

  h(n,m,f) : y1,...,yn,x1,...,xm -> x1',...,xm',yn',...,y1'
  constructs an array of size nxm.

  f is the function computed by each cell, which must take
  exactly two inputs and yield exactly two outputs. */

g(1,f)		= f;
g(m,f)		= (f, r(m-1)) : (_, g(m-1,f));

h(1,m,f)	= g(m,f);
h(n,m,f)	= (r(n+m) <:
		   (!,r(n-1),s(m), (_,s(n-1),r(m) : g(m,f)))) :
                  (h(n-1,m,f), _);

// route n inputs
r(1)		= _;
r(n)		= _,r(n-1);

// skip n inputs
s(1)		= !;
s(n)		= !,s(n-1);

// sample cell function
f		= + <: _,_;

//process		= g(3,f);
process		= h(2,3,f);
