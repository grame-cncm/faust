
foo(r,x) = r*x;
fii(r,x) = abs(r-x);

cross = _,_ <: !,_,_,!;

process = (cross,_,_:_,cross,_ : foo,fii) ~ (_,_);
