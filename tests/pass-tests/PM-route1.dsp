
// Basic route pattern matching tests

test_exact = case {
    (route(2,2,1,2,2,1)) => 100;
    (_) => 0;
};

test_vars = case {
    (route(n,m,1,2,2,1)) => n * 10 + m;
    (_) => 0;
};

test_priority = case {
    (route(2,2,1,2,2,1)) => 300;
    (route(n,m,1,2,2,1)) => 400;
    (_) => 0;
};

process = test_exact(route(2,2,1,2,2,1)), 
          test_vars(route(2,3,1,2,2,1)),
          test_priority(route(2,2,1,2,2,1));
