// mutual recursion

import("multirate.lib");

foo = upsample(4), _ : *;
fii = downsample(4),_ : *;

cross = _,_ <: !,_,_,!;

process = (cross,_,_:_,cross,_ : foo,fii) ~ (_,_);


