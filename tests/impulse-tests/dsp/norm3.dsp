// =================================================================
// Faust Test Suite for Non-Arithmetic Primitives (norm3.dsp)
// =================================================================
//
// This file provides a comprehensive test suite for simplification rules
// that apply to non-arithmetic primitives like delays, casts, and conditionals.
// It specifically includes refined tests for nested delays to check how
// simplification behaves based on the signal rate of the delay time.
//

// =================================================================
// Test Group 1: Delay Simplification (`normalizeDelayTerm` rules)
// =================================================================

// --- Test 1.1 ---
c_delay_1 = hslider("1.1_c", 2, 1, 10, 1);
// Input: (s * c_delay_1)'
// Expected: c_delay_1 * s'
// Rule: (k*s)' -> k*s'. A control-rate constant `c_delay_1` should be
//       pulled out of the single-sample delay operation.
test_delay_1(s) = (s * c_delay_1)';

// --- Test 1.2 ---
c_delay_2 = hslider("1.2_c", 2, 1, 10, 1);
// Input: (s / c_delay_2)'
// Expected: s' / c_delay_2
// Rule: (s/k)' -> s'/k. A control-rate divisor is pulled out.
test_delay_2(s) = (s / c_delay_2)';

// --- Test 1.3 ---
// Input: (s@10)@20
// Expected: s@30
// Rule: (s@n)@m -> s@(n+m) where n is constant.
//       This tests the `getSigOrder(n) == 0` case.
test_delay_3(s) = (s@10)@20;

// --- Test 1.4 ---
c_delay_4a = hslider("1.4_c1", 10, 1, 100, 1);
c_delay_4b = hslider("1.4_c2", 20, 1, 100, 1);
// Input: (s@c_delay_4a)@c_delay_4b
// Expected: s@(c_delay_4a + c_delay_4b)
// Rule: (s@n)@m -> s@(n+m) where n is control-rate.
//       This tests the `getSigOrder(n) == 1` case.
test_delay_4(s) = (s@int(c_delay_4a))@int(c_delay_4b);

// --- Test 1.5 ---
c_delay_5 = hslider("1.5_c", 20, 1, 100, 1);
// Input: (s@(abs(s2)*10))@c_delay_5
// Expected: (s@(abs(s2)*10))@c_delay_5  (NOT simplified)
// Rule: (s@n)@m is NOT simplified when n is audio-rate.
//       This tests the `getSigOrder(n) == 2` case, which should fail the check.
//       Using abs() to ensure the delay time is always non-negative.
test_delay_5(s, s2) = (s@(int(abs(s2)*10)))@int(c_delay_5);

// --- Test 1.6 ---
// Input: s@0
// Expected: s
// Rule: s@0 -> s. A delay of zero is an identity operation.
test_delay_6(s) = s@0;


// =================================================================
// Test Group 2: Casting Simplification (`simplify` rules)
// =================================================================

// --- Test 2.1 ---
// Input: int(3.7)
// Expected: 3
// Rule: int(const) -> const. Constant folding on the `int` cast.
test_cast_1 = int(3.7);

// --- Test 2.2 ---
// Input: float(5)
// Expected: 5.0
// Rule: float(const) -> const. Constant folding on the `float` cast.
test_cast_2 = float(5);


// =================================================================
// Test Group 3: Conditional and Selector Simplification (`simplify` rules)
// =================================================================

// --- Test 3.1 ---
x_sel_1 = hslider("3.1_x", 0, -1, 1, 1);
y_sel_1 = hslider("3.1_y", 0, -1, 1, 1);
// Input: select2(0, x_sel_1, y_sel_1)
// Expected: x_sel_1
// Rule: select2(0, a, b) -> a.
test_select_1 = select2(0, x_sel_1, y_sel_1);

// --- Test 3.2 ---
x_sel_2 = hslider("3.2_x", 0, -1, 1, 1);
y_sel_2 = hslider("3.2_y", 0, -1, 1, 1);
// Input: select2(1, x_sel_2, y_sel_2)
// Expected: y_sel_2
// Rule: select2(1, a, b) -> b.
test_select_2 = select2(1, x_sel_2, y_sel_2);

// --- Test 3.3 ---
// Input: select2(c, s, s)
// Expected: s
// Rule: select2(c, x, x) -> x.
test_select_3(s) = select2(hslider("3.3_c",0,0,1,1), s, s);


// =================================================================
// Main Process Line
// =================================================================
process(a,b,c,d,e,f,g,h,i,j,k) = test_delay_1(a),
                                 test_delay_2(b),
                                 test_delay_3(c),
                                 test_delay_4(d),
                                 test_delay_5(e,f),
                                 test_delay_6(g),
                                 test_cast_1,
                                 test_cast_2,
                                 test_select_1,
                                 test_select_2,
                                 test_select_3(h);
