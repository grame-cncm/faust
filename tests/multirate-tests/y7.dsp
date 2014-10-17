// mutual recursion

foo(r,x) = r*x;
fii(r,x) = r/x;

cross = _,_ <: !,_,_,!;

process = (cross,_,_:_,cross,_ : foo,fii) ~ (_,_);
