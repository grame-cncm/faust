// Modeling a 2D surface with a von neumann 

surface(X,Y) = route(X*Y, X*Y, par(x, X, par(y, Y, neighborhood(X,Y).vonNeumann(x,y) ) ) );
                            
// von Neumann neighborhood (or 4-neighborhood)
neighborhood(X,Y) = environment {

    vonNeumann(x,y) =
        (coord(x,y), coord(x+1,y)),
        (coord(x,y), coord(x-1,y)),
        (coord(x,y), coord(x,y+1)),
        (coord(x,y), coord(x,y-1));
    
    Moore(x,y) =
        (coord(x,y), coord(x+1,y)),
        (coord(x,y), coord(x-1,y)),
        (coord(x,y), coord(x,y+1)),
        (coord(x,y), coord(x,y-1)),
        (coord(x,y), coord(x+1,y+1)),
        (coord(x,y), coord(x-1,y-1)),
        (coord(x,y), coord(x-1,y+1)),
        (coord(x,y), coord(x+1,y-1));
    
    coord(x,y) = (1+x+y*X) * (x>=0) * (x<X) * (y>=0) * (y<Y);
};

process = surface(2,2);

/*

    0   1   2

    3   4   5

    6   7   8


    0   1

    2   3

*/