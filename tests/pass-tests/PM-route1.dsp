// PM-route1.dsp - Basic route pattern matching tests
// Tests exact matching and pattern variables with route primitive

import("stdfaust.lib");

// Test 1: Exact match on complete route expression
test_exact = case {
    (route(2,2,1,2,2,1)) => 100;
    (x) => 0;
};

// Test 2: Pattern variables bind input/output counts only
test_vars_io = case {
    (route(n,m,1,2,2,1)) => n * 10 + m;
    (x) => -1;
};

// Test 3: Different exact routes
test_exact2 = case {
    (route(3,3,1,2,3,1,2,3)) => 200;
    (x) => 0;
};

// Test 4: Sequential matching - first match wins
test_priority = case {
    (route(2,2,1,2,2,1)) => 300;   // Specific pattern
    (route(n,m,1,2,2,1)) => 400;   // More general pattern
    (x) => 0;
};

// Test 5: Parenthesized route list in pattern (nested pairs)
test_paren_pairs = case {
    (route(n,m,(1,2),(2,1))) => 500;
    (x) => 0;
};

// Test 6: Mixed parentheses in pattern
test_paren_mixed = case {
    (route(n,m,(1,2),2,1)) => 600;
    (x) => 0;
};

// Test 7: Right-nested parentheses in pattern
test_paren_right = case {
    (route(n,m,1,2,(2,1))) => 700;
    (x) => 0;
};

// Test 8: Default case used when no route pattern matches
test_default = case {
    (route(1,1,1,1)) => 800;
    (x) => 0;
};

process = 
    test_exact(route(2,2,1,2,2,1)),        // Expected: 100 (exact match)
    test_vars_io(route(2,3,1,2,2,1)),      // Expected: 23 (2*10 + 3)
    test_exact2(route(3,3,1,2,3,1,2,3)),   // Expected: 200 (exact match) 
    test_priority(route(2,2,1,2,2,1)),     // Expected: 300 (first match)
    test_paren_pairs(route(2,2,1,2,2,1)),  // Expected: 500 (nested pairs)
    test_paren_mixed(route(2,2,1,2,2,1)),  // Expected: 600 (mixed parens)
    test_paren_right(route(2,2,1,2,2,1)),  // Expected: 700 (right-nested)
    test_default(route(2,2,1,2,2,1));      // Expected: 0 (default case)
