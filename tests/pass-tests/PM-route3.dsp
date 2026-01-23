
// Route pattern edge cases

// Mixed variables and constants with grouping
test_mixed = case {
    (route(n,m, a, (b,c), d)) => a + b + c + d;
    (_) => 0;
};

// Tail variable capture
test_tail = case {
    (route(n,m, 10, x)) => 1;
    (_) => 0;
};

// Single pair
test_single = case {
    (route(n,m, x, y)) => x + y;
    (_) => 0;
};

// Long list
test_long = case {
    (route(n,m, 1,2,3,4,5,6)) => 999;
    (_) => 0;
};

process = test_mixed(route(1,1,10,20,30,40)), 
          test_tail(route(1,1,10,20,30,40)), 
          test_single(route(1,1,5,6)),
          test_long(route(1,1,1,2,3,4,5,6));
