
// Route pattern nesting and canonicalization verification

// Flat pattern
test_nest1 = case {
    (route(n,m,(1,2,3,4))) => 10;
    (_) => 0;
};

// Right-associative pattern (Standard internal form)
test_nest2 = case {
    (route(n,m,(1,(2,(3,4))))) => 20;
    (_) => 0;
};

// Left-associative pattern
test_nest3 = case {
    (route(n,m,((1,2),(3,4)))) => 30;
    (_) => 0;
};

// Mixed grouping
test_nest4 = case {
    (route(n,m,(1,(2,(3,(4)))))) => 40;
    (_) => 0;
};

process = test_nest1(route(1,1,1,2,3,4)), 
          test_nest2(route(1,1,1,2,3,4)), 
          test_nest3(route(1,1,1,2,3,4)), 
          test_nest4(route(1,1,1,2,3,4));
