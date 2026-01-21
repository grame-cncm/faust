// PM-route1.dsp - Basic route pattern matching tests
// Tests exact matching and pattern variables with route primitive

import("stdfaust.lib");

// Test 1: Exact match on complete route expression
test_exact = case {
    (route(2,2,1,2,2,1)) => 100;
    (_) => 0;
};

// Test 2: Pattern variables bind input/output counts only
test_vars_io = case {
    (route(n,m,1,2,2,1)) => n * 10 + m;
    (_) => -1;
};

// Test 3: Different exact routes
test_exact2 = case {
    (route(3,3,1,2,3,1,2,3)) => 200;
    (_) => 0;
};

// Test 4: Sequential matching - first match wins
test_priority = case {
    (route(2,2,1,2,2,1)) => 300;   // Specific pattern
    (route(n,m,1,2,2,1)) => 400;   // More general pattern
    (_) => 0;
};

process = 
    test_exact(route(2,2,1,2,2,1)),       // Expected: 100 (exact match)
    test_vars_io(route(2,3,1,2,2,1)),     // Expected: 23 (2*10 + 3)
    test_exact2(route(3,3,1,2,3,1,2,3)),  // Expected: 200 (exact match) 
    test_priority(route(2,2,1,2,2,1));    // Expected: 300 (first match)
