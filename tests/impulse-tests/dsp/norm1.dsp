// =================================================================
// Faust Normalization and Optimization Test Suite
// =================================================================
//
// This file serves as a comprehensive test suite for the Faust compiler's
// symbolic simplification and optimization engine, specifically the logic
// handled by the `aterm` and `mterm` classes.
//
// Purpose:
// Each expression in this file is designed to test a specific algebraic
// rule or simplification case. By compiling this code and examining the
// output, one can verify that the compiler correctly normalizes and optimizes
// the expressions as expected.
//
// Structure:
// - The file is divided into thematic groups (Simplification, Commutativity, etc.).
// - Each test case is a single output channel in the final `process` line.
// - To prevent cross-channel optimizations from interfering with the tests,
//   every expression uses a unique set of `hslider` variables (e.g., x1_1, x2_1).
// - Comments above each line specify the input expression, the expected
//   normalized result, and the primary algebraic rule being tested.
//

// =================================================================
// Test Group 1: Basic Simplification
// =================================================================
x1_1 = hslider("1.1_x", 0, -10, 10, 0.1);

x1_2 = hslider("1.2_x", 0, -10, 10, 0.1);
y1_2 = hslider("1.2_y", 0, -10, 10, 0.1);

x1_3 = hslider("1.3_x", 0, -10, 10, 0.1);

x1_4 = hslider("1.4_x", 0, -10, 10, 0.1);

x1_5 = hslider("1.5_x", 0, -10, 10, 0.1);
y1_5 = hslider("1.5_y", 0, -10, 10, 0.1);

x1_6 = hslider("1.6_x", 0, -10, 10, 0.1);

simplification_tests =
    // Input: (x1_1 + x1_1)
    // Expected: (2 * x1_1)
    // Rule: Combining Like Terms. The `aterm` receives two `mterm`s, both with the
    //       same signature for `x1_1`. It adds their coefficients (1 + 1 = 2).
    (x1_1 + x1_1),

    // Input: (x1_2 + y1_2 + x1_2)
    // Expected: ((2 * x1_2) + y1_2)
    // Rule: Combining Like Terms (with Associativity). The `aterm` flattens the
    //       sum and identifies two `mterm`s with the signature for `x1_2`, combining them.
    (x1_2 + y1_2 + x1_2),

    // Input: ((5 * x1_3) - (2 * x1_3))
    // Expected: (3 * x1_3)
    // Rule: Combining Like Terms (with Subtraction). Two `mterm`s with the same
    //       signature are created. The `aterm` sums their coefficients (5 - 2 = 3).
    ((5 * x1_3) - (2 * x1_3)),

    // Input: ((2 * x1_4) - (5 * x1_4))
    // Expected: (-3 * x1_4)
    // Rule: Combining Like Terms (to Negative). The coefficients are summed (2 - 5 = -3).
    ((2 * x1_4) - (5 * x1_4)),

    // Input: (x1_5 + y1_5 - x1_5)
    // Expected: y1_5
    // Rule: Additive Cancellation. The `aterm` combines the `mterm` for `x1_5` (coef: 1)
    //       and `-x1_5` (coef: -1). The resulting coefficient is 0, so the term is
    //       removed from the `aterm`'s map.
    (x1_5 + y1_5 - x1_5),

    // Input: ((2.5 * x1_6) + (1.2 * x1_6))
    // Expected: (3.7 * x1_6)
    // Rule: Combining Like Terms (Floating-Point). The logic is identical for floats.
    ((2.5 * x1_6) + (1.2 * x1_6));


// =================================================================
// Test Group 2: Commutativity and Associativity
// =================================================================
x2_1 = hslider("2.1_x", 0, -10, 10, 0.1);
y2_1 = hslider("2.1_y", 0, -10, 10, 0.1);

x2_2 = hslider("2.2_x", 0, -10, 10, 0.1);
y2_2 = hslider("2.2_y", 0, -10, 10, 0.1);

x2_3 = hslider("2.3_x", 0, -10, 10, 0.1);
y2_3 = hslider("2.3_y", 0, -10, 10, 0.1);
z2_3 = hslider("2.3_z", 0, -10, 10, 0.1);

x2_4 = hslider("2.4_x", 0, -10, 10, 0.1);
y2_4 = hslider("2.4_y", 0, -10, 10, 0.1);
z2_4 = hslider("2.4_z", 0, -10, 10, 0.1);

x2_5 = hslider("2.5_x", 0, -10, 10, 0.1);
y2_5 = hslider("2.5_y", 0, -10, 10, 0.1);

commutativity_tests =
    // Input: (x2_1 + y2_1)
    // Expected: (x2_1 + y2_1)
    // Rule: Commutativity of Addition. `aterm::normalizedTree` sorts terms into a
    //       canonical order, making the output identical regardless of input order.
    (x2_1 + y2_1),
    // Input: (y2_1 + x2_1)
    // Expected: (x2_1 + y2_1)
    (y2_1 + x2_1),

    // Input: (x2_2 * y2_2)
    // Expected: (x2_2 * y2_2)
    // Rule: Commutativity of Multiplication. `mterm::signatureTree` sorts the factors
    //       `x2_2` and `y2_2` internally, so both `x*y` and `y*x` produce the same signature key.
    (x2_2 * y2_2),
    // Input: (y2_2 * x2_2)
    // Expected: (x2_2 * y2_2)
    (y2_2 * x2_2),

    // Input: ((x2_3 + y2_3) + z2_3)
    // Expected: ((x2_3 + y2_3) + z2_3)
    // Rule: Associativity of Addition. The `aterm` constructor flattens the expression
    //       into a single list of terms, so the initial grouping is irrelevant.
    ((x2_3 + y2_3) + z2_3),
    // Input: (x2_4 + (y2_4 + z2_4))
    // Expected: ((x2_4 + y2_4) + z2_4)
    (x2_4 + (y2_4 + z2_4)),

    // Input: ((3*y2_5) + (2*x2_5) - y2_5)
    // Expected: (2 * (x2_5 + y2_5))
    // Rule: Combining Like Terms & Factorization. The `aterm` first combines `3*y2_5`
    //       and `-y2_5` into `2*y2_5`. The factorization stage then finds the common
    //       coefficient `2` and factors it out.
    ((3*y2_5) + (2*x2_5) - y2_5);


// =================================================================
// Test Group 3: Zero, Identity, and Cancellation
// =================================================================
x3_1 = hslider("3.1_x", 0, -10, 10, 0.1);
x3_2 = hslider("3.2_x", 0, -10, 10, 0.1);
x3_3 = hslider("3.3_x", 0, -10, 10, 0.1);
x3_4 = hslider("3.4_x", 0, -10, 10, 0.1);
x3_5 = hslider("3.5_x", 0, -10, 10, 0.1);
x3_6 = hslider("3.6_x", 0, -10, 10, 0.1);
y3_6 = hslider("3.6_y", 0, -10, 10, 0.1);
z3_6 = hslider("3.6_z", 0, -10, 10, 0.1);
x3_7 = hslider("3.7_x", 0, -10, 10, 0.1);
y3_7 = hslider("3.7_y", 0, -10, 10, 0.1);

identity_tests =
    // Input: (x3_1 + 0)
    // Expected: x3_1
    // Rule: Additive Identity. An `mterm` for `0` has a zero coefficient and is
    //       not added to the `aterm`'s map.
    (x3_1 + 0),

    // Input: (x3_2 - 0)
    // Expected: x3_2
    // Rule: Additive Identity (Subtraction). Same as addition.
    (x3_2 - 0),

    // Input: (x3_3 * 1)
    // Expected: x3_3
    // Rule: Multiplicative Identity. The `mterm` for `x3_3 * 1` simplifies to
    //       a term with factor `x3_3` and coefficient 1.
    (x3_3 * 1),

    // Input: (x3_4 * 0)
    // Expected: 0
    // Rule: Multiplication by Zero. The `mterm`'s coefficient becomes 0, and
    //       `mterm::cleanup` removes all factors, resulting in the number 0.
    (x3_4 * 0),

    // Input: (x3_5 - x3_5)
    // Expected: 0
    // Rule: Additive Inverse. The coefficients (1 and -1) sum to 0, and the term is removed.
    (x3_5 - x3_5),

    // Input: ((x3_6*y3_6) + z3_6 - (y3_6*x3_6))
    // Expected: z3_6
    // Rule: Cancellation with Commutativity. The system recognizes `x3_6*y3_6` and
    //       `y3_6*x3_6` have the same signature and cancels their coefficients (1 and -1).
    ((x3_6*y3_6) + z3_6 - (y3_6*x3_6)),

    // Input: ((3*x3_7) - (3*x3_7) + y3_7)
    // Expected: y3_7
    // Rule: Coefficient Cancellation. Same as above, with coefficients 3 and -3.
    ((3*x3_7) - (3*x3_7) + y3_7);


// =================================================================
// Test Group 4: Nested and Compound Expressions
// =================================================================
x4_1 = hslider("4.1_x", 0, -10, 10, 0.1);
y4_1 = hslider("4.1_y", 0, -10, 10, 0.1);
x4_2 = hslider("4.2_x", 0, -10, 10, 0.1);
y4_2 = hslider("4.2_y", 0, -10, 10, 0.1);
z4_2 = hslider("4.2_z", 0, -10, 10, 0.1);
x4_3 = hslider("4.3_x", 0, -10, 10, 0.1);
y4_3 = hslider("4.3_y", 0, -10, 10, 0.1);
z4_3 = hslider("4.3_z", 0, -10, 10, 0.1);

// CORRECTED: Initial value changed from 0 to 1 to prevent division by zero.
x4_4 = hslider("4.4_x", 1, -10, 10, 0.1);
y4_4 = hslider("4.4_y", 0, -10, 10, 0.1);

x4_5 = hslider("4.5_x", 0, -10, 10, 0.1);
y4_5 = hslider("4.5_y", 0, -10, 10, 0.1);

compound_expr_tests =
    // Input: (2 * (x4_1 + y4_1))
    // Expected: ((2 * x4_1) + (2 * y4_1))
    // Rule: Distributive Property. The Faust parser expands this to `(2*x4_1) + (2*y4_1)`
    //       before the normalization engine runs.
    (2 * (x4_1 + y4_1)),

    // Input: (x4_2 - (y4_2 - z4_2))
    // Expected: ((x4_2 + z4_2) - y4_2)
    // Rule: Distribution of Negation. The parser expands this to `x4_2 - y4_2 + z4_2`.
    (x4_2 - (y4_2 - z4_2)),

    // Input: ((x4_3*y4_3) * (z4_3*x4_3))
    // Expected: ((x4_3^2 * y4_3) * z4_3)
    // Rule: Associativity and Product of Powers. The `mterm` logic flattens the product
    //       and sums the exponents of `x4_3` (1 + 1 = 2).
    ((x4_3*y4_3) * (z4_3*x4_3)),

    // Input: ((x4_4*y4_4)/x4_4)
    // Expected: y4_4
    // Rule: Multiplicative Cancellation. The `mterm` processes factors `x4_4^1`, `y4_4^1`,
    //       and `x4_4^-1`. The exponents for `x4_4` sum to 0, and `mterm::cleanup` removes it.
    ((x4_4*y4_4)/x4_4),

    // Input: ((x4_5+y4_5)/2)
    // Expected: ((0.5 * x4_5) + (0.5 * y4_5))
    // Rule: Distribution of Division. The parser expands this to `(x4_5/2) + (y4_5/2)`.
    ((x4_5+y4_5)/2);


// =================================================================
// Test Group 5: Power and Exponent Handling
// =================================================================
x5_1 = hslider("5.1_x", 0, -10, 10, 0.1);
x5_2 = hslider("5.2_x", 0, -10, 10, 0.1);
x5_3 = hslider("5.3_x", 0, -10, 10, 0.1);
y5_3 = hslider("5.3_y", 0, -10, 10, 0.1);

// CORRECTED: Initial value changed from 0 to 1 to prevent division by zero.
x5_4 = hslider("5.4_x", 1, -10, 10, 0.1);
// CORRECTED: Initial value changed from 0 to 1 to prevent division by zero.
x5_5 = hslider("5.5_x", 1, -10, 10, 0.1);

power_expr_tests =
    // Input: pow(x5_1, 2)
    // Expected: x5_1^2
    // Rule: Definition of Exponentiation. `isSigPow` identifies the power operation.
    pow(x5_1, 2),

    // Input: (x5_2 * x5_2)
    // Expected: x5_2^2
    // Rule: Definition of Exponentiation. `mterm` logic combines the two `x5_2` factors.
    (x5_2 * x5_2),

    // Input: ((x5_3*x5_3*y5_3) * (y5_3*y5_3))
    // Expected: (x5_3^2 * y5_3^3)
    // Rule: Product of Powers Rule (a^m * a^n = a^(m+n)). `mterm` sums exponents.
    ((x5_3*x5_3*y5_3) * (y5_3*y5_3)),

    // Input: (pow(x5_4, 5) / pow(x5_4, 3))
    // Expected: x5_4^2
    // Rule: Quotient of Powers Rule (a^m / a^n = a^(m-n)). Division is treated as
    //       adding a negative exponent (5 + (-3) = 2).
    (pow(x5_4, 5) / pow(x5_4, 3)),

    // Input: (pow(x5_5, 2) / (x5_5*x5_5))
    // Expected: 1
    // Rule: Cancellation of Powers. Exponents sum to 0: 2 (from pow) - 1 - 1 = 0.
    (pow(x5_5, 2) / (x5_5*x5_5));


// =================================================================
// Test Group 6: Factorization
// =================================================================
x6_1 = hslider("6.1_x", 0, -10, 10, 0.1);
y6_1 = hslider("6.1_y", 0, -10, 10, 0.1);
z6_1 = hslider("6.1_z", 0, -10, 10, 0.1);
x6_2 = hslider("6.2_x", 0, -10, 10, 0.1);
y6_2 = hslider("6.2_y", 0, -10, 10, 0.1);
x6_3 = hslider("6.3_x", 0, -10, 10, 0.1);
y6_3 = hslider("6.3_y", 0, -10, 10, 0.1);
x6_4 = hslider("6.4_x", 0, -10, 10, 0.1);
a6_5 = hslider("6.5_a", 0, -10, 10, 0.1);
b6_5 = hslider("6.5_b", 0, -10, 10, 0.1);
x6_5 = hslider("6.5_x", 0, -10, 10, 0.1);
y6_5 = hslider("6.5_y", 0, -10, 10, 0.1);

factorization_tests =
    // Input: ((x6_1*y6_1) + (x6_1*z6_1))
    // Expected: (x6_1 * (y6_1 + z6_1))
    // Rule: Simple Factorization. `aterm::greatestDivisor` finds `x6_1`.
    //       `aterm::factorize` rewrites the expression.
    ((x6_1*y6_1) + (x6_1*z6_1)),

    // Input: ((4*x6_2) + (2*y6_2))
    // Expected: (2 * ((2 * x6_2) + y6_2))
    // Rule: Coefficient Factorization. The GCD of the coefficients (2) is found and factored out.
    ((4*x6_2) + (2*y6_2)),

    // Input: ((x6_3*x6_3*y6_3) + (x6_3*y6_3*y6_3))
    // Expected: ((x6_3 * y6_3) * (x6_3 + y6_3))
    // Rule: Power Factorization. `greatestDivisor` finds common factors to their
    //       lowest powers (`x6_3^1` and `y6_3^1`), resulting in a GCD of `x6_3*y6_3`.
    ((x6_3*x6_3*y6_3) + (x6_3*y6_3*y6_3)),

    // Input: ((3*x6_4*x6_4) - (6*x6_4))
    // Expected: ((3 * x6_4) * (x6_4 - 2))
    // Rule: Complex Factorization. The GCD combines coefficient and symbolic analysis (`3*x6_4`).
    ((3*x6_4*x6_4) - (6*x6_4)),

    // Input: (a6_5*x6_5 + a6_5*y6_5) + (b6_5*x6_5 + b6_5*y6_5)
    // Expected: ((a6_5 + b6_5) * (x6_5 + y6_5))
    // Rule: Multi-Level Factorization. This tests the iterative loop in `normalizeAddTerm`.
    ((a6_5*x6_5 + a6_5*y6_5) + (b6_5*x6_5 + b6_5*y6_5));

// =================================================================
// Main Process Line
// =================================================================
// Each test group is routed to a separate set of output channels,
// ensuring they are compiled as independent signal chains.
process = simplification_tests,
          commutativity_tests,
          identity_tests,
          compound_expr_tests,
          power_expr_tests,
          factorization_tests;