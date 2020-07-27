import("stdfaust.lib");

process = button("play")*no.noise : structure(4,4,200);

//--------------------------------------------------------------------------------------------------
// usage (osx):
//   faust2caqt structure4chris.dsp
//   open ./structure4chris.app
//--------------------------------------------------------------------------------------------------

//---------------------------------------IMPLEMENTATION---------------------------------------------


//--------------------------------------------------------------------------------------------------
// structure(X,Y,D): a 2D structure of X*Y interconnected nodes 
// with a propagation time of D samples between them. 
// The structure has a mono input and a stereo output
structure(X,Y,D) = (connections(X,Y, 1,1) : nodes(X, Y)) ~ delaylines(X,Y,D-1) : listen(X,Y, 1,Y/2, X-1, Y/2);


//--------------------------------------------------------------------------------------------------
// creates the connections for a mesh of X*Y nodes with 4 inputs and 4 outputs 
// with an injection point at coord x0,y0.
connections(X, Y, x0, y0) = route(X*Y*4+1, X*Y*4, 
                                par(x, X, par(y, Y, connections(x,y))), 
                                in, N(x0,y0),
                                in, E(x0,y0),
                                in, S(x0,y0),
                                in, W(x0,y0)
                            )   
    with {
        in = X*Y*4 + 1; // additional input for signal injection

        // for each node we establish connections with its 4 neighbours
        connections(x,y) = N(x,y), S(x,y-1),
                        S(x,y), N(x,y+1),
                        W(x,y), E(x-1,y),
                        E(x,y), W(x+1,y);

        N(x,y) = (1 + 0 + (x+y*X)*4) * (x>=0) * (x<X) * (y>=0) * (y<Y);
        E(x,y) = (1 + 1 + (x+y*X)*4) * (x>=0) * (x<X) * (y>=0) * (y<Y);
        S(x,y) = (1 + 2 + (x+y*X)*4) * (x>=0) * (x<X) * (y>=0) * (y<Y);
        W(x,y) = (1 + 3 + (x+y*X)*4) * (x>=0) * (x<X) * (y>=0) * (y<Y);
    };


//--------------------------------------------------------------------------------------------------
// Among the X*Y nodes, listen to the node of coordinates (x,y) 
listen(X, Y, x0, y0, x1, y1) = route( X*Y*4,  2,  
                                N(x0,y0), 1,
                                E(x0,y0), 1,
                                S(x0,y0), 1,
                                W(x0,y0), 1,

                                N(x1,y1), 2,
                                E(x1,y1), 2,
                                S(x1,y1), 2,
                                W(x1,y1), 2
                           )   
    with {
        N(x,y) = (1 + 0 + (x+y*X)*4) * (x>=0) * (x<X) * (y>=0) * (y<Y);
        E(x,y) = (1 + 1 + (x+y*X)*4) * (x>=0) * (x<X) * (y>=0) * (y<Y);
        S(x,y) = (1 + 2 + (x+y*X)*4) * (x>=0) * (x<X) * (y>=0) * (y<Y);
        W(x,y) = (1 + 3 + (x+y*X)*4) * (x>=0) * (x<X) * (y>=0) * (y<Y);
    };


//--------------------------------------------------------------------------------------------------
// the X*Y nodes with specific borders
nodes(X,Y) = 
        // the X*Y nodes
        par (x, X, north),
        par (y, Y-2, (west, par (x, X-2, node), east)),
        par (x, X, south)

    with {
        // regular nodes
        node(n,e,s,w) = (e+s+w)/3, (n+s+w)/3, (n+e+w)/3, (n+e+s)/3;

        // border nodes
        north(n,e,s,w) = 0, 0, filter(s), 0;
        east(n,e,s,w) = 0, 0, 0, filter(w);
        south(n,e,s,w) = filter(n), 0, 0, 0;
        west(n,e,s,w) = 0, filter(e), 0, 0;

        // common filter inside each border node
        filter = fi.lowpass(3,4000); 
    };


//--------------------------------------------------------------------------------------------------
// X*Y*4 parallel delay lines
delaylines(X,Y,D) = par(i, X*Y*4, @(D));

