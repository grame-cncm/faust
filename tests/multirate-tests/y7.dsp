// mutual recursion

import("multirate.lib");

foo(r,x) = r*x;
fii(r,x) = r/x;

//cross (r1,r2,x1,x2) = r2,x1,r1,x2;

cross = _,_ <: !,_,_,!;

process = (cross,_,_:_,cross,_ : foo,fii) ~ (_,_);
