// mutual recursion

foo = up(4), _ : *;
fii = down(4),_ : *;

cross = _,_ <: !,_,_,!;

process = (cross,_,_:_,cross,_ : foo,fii) ~ (_,_);


