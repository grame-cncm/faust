// Modeling a 2D surface with a von neumann 

surface(X,Y) = route(X*Y,X*Y, 
                    par(x,X,
                        par(y,Y,
                            (coord(x,y), coord(x+1,y)),
                            (coord(x,y), coord(x-1,y)),
                            (coord(x,y), coord(x,y+1)),
                            (coord(x,y), coord(x,y-1))
                            )))
        with {
            coord(x,y) = (1+x+y*X) * (x>=0) * (x<X) * (y>=0) * (y<Y);
        };


process = surface(40,40);


/*

    0   1   2

    3   4   5

    6   7   8



*/