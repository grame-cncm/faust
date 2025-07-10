// =================================================================
// Enriched Faust Signal Ordering Test Suite
// =================================================================
//
// This file provides a comprehensive test suite for the Faust compiler's
// normalization engine, focusing on how it handles expressions that mix
// signal-rate and control-rate components.
//
// Purpose:
// This enriched version adds more complex test cases to verify that the
// canonical ordering rules hold up during advanced simplification and
// factorization, providing a more complete validation of the `aterm`/`mterm` machinery.
//
// Structure:
// - Each test is a standalone function with named signal-rate parameters.
// - Control-rate variables (`hslider`) are defined uniquely for each test.
// - The main `process` line calls each test function with a unique audio input.
//

// =================================================================
// Test Group 1: Additive Ordering
// =================================================================

// --- Test 1.1 ---
c_add_1 = hslider("c_add_1", 0, -10, 10, 0.1);
// Input: ((c_add_1 + s) - c_add_1)
// Expected: s
// Rule: Additive Cancellation. Forces the engine to deconstruct the mixed-rate
//       sum. The control-rate terms cancel, leaving only the signal.
test_1_1(s) = ((c_add_1 + s) - c_add_1);

// --- Test 1.2 ---
c_add_2 = hslider("c_add_2", 0, -10, 10, 0.1);
// Input: (s + c_add_2 + s)
// Expected: (c_add_2 + (2 * s))
// Rule: Canonical Sum Reconstruction. The `s` terms are combined. The `aterm`
//       rebuilds the sum with the lowest-rate term (control) first.
test_1_2(s) = (s + c_add_2 + s);

// --- Test 1.3 ---
c_add_3 = hslider("c_add_3", 0, -10, 10, 0.1);
// Input: (c_add_3 + s + c_add_3)
// Expected: ((2 * c_add_3) + s)
// Rule: Canonical Sum Reconstruction. The control-rate terms are combined.
test_1_3(s) = (c_add_3 + s + c_add_3);


// =================================================================
// Test Group 2: Multiplicative Ordering
// =================================================================

// --- Test 2.1 ---
c_mul_1 = hslider("c_mul_1", 1, -10, 10, 0.1);
// Input: ((c_mul_1 * s) / c_mul_1)
// Expected: s
// Rule: Multiplicative Cancellation. The `mterm` factors for `c_mul_1` cancel out.
test_2_1(s) = ((c_mul_1 * s) / c_mul_1);

// --- Test 2.2 ---
c_mul_2 = hslider("c_mul_2", 1, -10, 10, 0.1);
// Input: (c_mul_2 * s * c_mul_2)
// Expected: (s * (c_mul_2^2))
// Rule: Internal Factor Ordering. The `mterm` combines `c_mul_2` factors into `c_mul_2^2`,
//       then sorts the factors by rate, placing the signal `s` first.
test_2_2(s) = (c_mul_2 * s * c_mul_2);


// =================================================================
// Test Group 3: Compound Expression Ordering
// =================================================================

// --- Test 3.1 ---
c_cmpd_1 = hslider("c_cmpd_1", 1, -10, 10, 0.1);
// Input: (((c_cmpd_1*c_cmpd_1) + s) - (c_cmpd_1*c_cmpd_1))
// Expected: s
// Rule: Term-Level Cancellation. The control-rate term `c_cmpd_1^2` is cancelled.
test_3_1(s) = (((c_cmpd_1*c_cmpd_1) + s) - (c_cmpd_1*c_cmpd_1));

// --- Test 3.2 ---
c_cmpd_2 = hslider("c_cmpd_2", 1, -10, 10, 0.1);
// Input: ((c_cmpd_2 * s) + (s * c_cmpd_2))
// Expected: (2 * (s * c_cmpd_2))
// Rule: Internal and External Ordering. The two terms are combined, and the
//       factors within the resulting term are ordered by rate.
test_3_2(s) = ((c_cmpd_2 * s) + (s * c_cmpd_2));


// =================================================================
// Test Group 4: Advanced Factorization and Compound Rules
// =================================================================

// --- Test 4.1 ---
c_adv_1 = hslider("c_adv_1", 1, -10, 10, 0.1);
c_adv_2 = hslider("c_adv_2", 1, -10, 10, 0.1);
// Input: (s * c_adv_1) + (s * c_adv_2)
// Expected: s * (c_adv_1 + c_adv_2)
// Rule: Factorization with Signal-Rate Term. This tests if the engine can
//       identify a signal-rate term `s` as the greatest common divisor and
//       factor it out correctly.
test_4_1(s) = (s * c_adv_1) + (s * c_adv_2);

// --- Test 4.2 ---
c_adv_3 = hslider("c_adv_3", 1, -10, 10, 0.1);
c_adv_4 = hslider("c_adv_4", 1, -10, 10, 0.1);
c_adv_5 = hslider("c_adv_5", 1, -10, 10, 0.1);
// Input: (s*c_adv_3 + c_adv_4) - (c_adv_3*s - c_adv_5)
// Expected: c_adv_4 + c_adv_5
// Rule: Complex Cancellation. This tests commutativity (`s*c` vs `c*s`),
//       cancellation of the mixed-rate term, and distribution of negation.
test_4_2(s) = (s*c_adv_3 + c_adv_4) - (c_adv_3*s - c_adv_5);

// --- Test 4.3 ---
c_adv_6 = hslider("c_adv_6", 1, -10, 10, 0.1);
// Input: s * c_adv_6 * s
// Expected: c_adv_6 * s^2
// Rule: Grouping and Ordering of Mixed-Rate Powers. This tests if the `mterm`
//       correctly groups the `s` factors into `s^2` and then correctly orders
//       the final factors with the lowest rate (`c_adv_6`) first.
test_4_3(s) = s * c_adv_6 * s;


// =================================================================
// Main Process Line
// =================================================================
// Each test function is called with a unique audio input,
// ensuring they are compiled as independent signal chains.
process(a,b,c,d,e,f,g,h,i,j) = test_1_1(a),
                               test_1_2(b),
                               test_1_3(c),
                               test_2_1(d),
                               test_2_2(e),
                               test_3_1(f),
                               test_3_2(g),
                               test_4_1(h),
                               test_4_2(i),
                               test_4_3(j);
