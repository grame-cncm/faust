//mise en cache des expressions recursives
x = 1:+~_;
y = 2:*~_;

foo(x,y,u,v) = x+y+u, y-x+v;

process = foo~(_,_);
