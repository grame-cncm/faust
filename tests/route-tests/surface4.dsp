import("stdfaust.lib");

// surface4(X,Y): creates the connections for a surface of X*Y nodes with 4 inputs and 4 outputs
surface4(X,Y) = route(X*Y*4, X*Y*4, par(x, X, par(y, Y, connections(x,y) )))
    with {
        connections(x,y) =  N(x,y), S(x,y-1),
                            S(x,y), N(x,y+1),
                            W(x,y), E(x-1,y),
                            E(x,y), W(x+1,y);

        N(x,y) = (1 + 0 + (x+y*X)*4) * (x>=0) * (x<X) * (y>=0) * (y<Y);
        E(x,y) = (1 + 1 + (x+y*X)*4) * (x>=0) * (x<X) * (y>=0) * (y<Y);
        S(x,y) = (1 + 2 + (x+y*X)*4) * (x>=0) * (x<X) * (y>=0) * (y<Y);
        W(x,y) = (1 + 3 + (x+y*X)*4) * (x>=0) * (x<X) * (y>=0) * (y<Y);
    };

xstraight4(X,Y) = route( X*Y*4, X*Y*4, 
                    par(x, X, 
                        par(y, Y, 
                            par(p, 4, 
                                (1 + p + (x+y*X)*4, 1 + p + (x+y*X)*4)))));

straight4(X,Y) = par(i, X*Y*4, @(100));

// surface4i(X,Y,x,y): creates the connections for a surface of X*Y nodes with 4 inputs and 4 outputs 
// with an injection point of coord x,y.
surface4i(X, Y, x0, y0) =   route(X*Y*4+1, X*Y*4, 
                                par(x, X, par(y, Y, connections(x,y))), 
                                in, N(x0,y0),
                                in, E(x0,y0),
                                in, S(x0,y0),
                                in, W(x0,y0)
                            )   
    with {
        in = X*Y*4 + 1; // additional input for signal injection
        connections(x,y) =  N(x,y), S(x,y-1),
                            S(x,y), N(x,y+1),
                            W(x,y), E(x-1,y),
                            E(x,y), W(x+1,y);

        N(x,y) = (1 + 0 + (x+y*X)*4) * (x>=0) * (x<X) * (y>=0) * (y<Y);
        E(x,y) = (1 + 1 + (x+y*X)*4) * (x>=0) * (x<X) * (y>=0) * (y<Y);
        S(x,y) = (1 + 2 + (x+y*X)*4) * (x>=0) * (x<X) * (y>=0) * (y<Y);
        W(x,y) = (1 + 3 + (x+y*X)*4) * (x>=0) * (x<X) * (y>=0) * (y<Y);
    };

listen4(X, Y, x, y) =   route(  X*Y*4,  1,  
                                N(x,y), 1,
                                E(x,y), 1,
                                S(x,y), 1,
                                W(x,y), 1
                            )   
    with {
        N(x,y) = (1 + 0 + (x+y*X)*4) * (x>=0) * (x<X) * (y>=0) * (y<Y);
        E(x,y) = (1 + 1 + (x+y*X)*4) * (x>=0) * (x<X) * (y>=0) * (y<Y);
        S(x,y) = (1 + 2 + (x+y*X)*4) * (x>=0) * (x<X) * (y>=0) * (y<Y);
        W(x,y) = (1 + 3 + (x+y*X)*4) * (x>=0) * (x<X) * (y>=0) * (y<Y);
    };



model(X,Y,filter, node) = 
        par (x, X, north),
        par (y, Y-2, (west, par (x, X-2, node), east)),
        par (x, X, south)
    with {
        north(n,e,s,w) = 0, 0, filter(s), 0 ;
        east(n,e,s,w) = 0, 0, 0, filter(w) ;
        south(n,e,s,w) = filter(n), 0, 0, 0 ;
        west(n,e,s,w) = 0, filter(e), 0, 0 ;
    };

node(n,e,s,w) = (e+s+w)/3, (n+s+w)/3, (n+e+w)/3, (n+e+s)/3;



example(X,Y) = (surface4i(X,Y, 1,1) : model(X, Y, \(x).((x+x')*0.25), node)) ~ straight4(X,Y) : listen4(X,Y, X-2,Y-3);

process = button("play") : example(6,10);

//model(4,4, _, node); //listen4(3,3, 1,1); //surface4(2,2); //surface4i(4,4,1,1);


/*

    0   1   2
q
    3   4   5

    6   7   8


    0   1

    2   3

*/