# Signal Normalization Module

## Overview

The `compiler/normalize` module implements algebraic normalization and simplification of signal expressions in the Faust compiler. This module transforms signal expressions into canonical forms through factorization, constant folding, and algebraic optimization, enabling more efficient code generation.

## Module Architecture

```text
normalize/
├── aterm.{hh,cpp}         # Additive term representation and algebra
├── mterm.{hh,cpp}         # Multiplicative term representation  
├── normalize.{hh,cpp}     # Core normalization algorithms
├── simplify.{hh,cpp}      # Signal simplification and optimization
├── normalform.{hh,cpp}    # Complete normalization pipeline
└── README.md              # This documentation
```

## Core Data Structures

### Multiplicative Terms (mterm)

Represents expressions of the form `k * x^n * y^m * ...` where:
- `k` is a numeric coefficient (`Tree fCoef`)
- `x, y, ...` are signal factors stored in `std::map<Tree, int> fFactors`
- `n, m, ...` are integer powers (map values)

**Key Operations:**
```cpp
mterm m1(5);           // Coefficient: 5
mterm m2(tree);        // From expression tree
m1 *= m2;              // Multiply terms
m1 /= divisor;         // Divide by another term
```

### Additive Terms (aterm)

Represents sums of multiplicative terms `m1 + m2 + m3 + ...` using:
- `std::map<Tree, mterm> fSig2MTerms` - maps signatures to multiplicative terms
- Automatic grouping of terms with identical factor signatures

**Example transformation:**
```cpp
aterm a(tree);                  // Convert expression to additive term
mterm d = a.greatestDivisor();  // Find greatest common divisor
aterm result = a.factorize(d);  // Factor out common terms
Tree normalized = a.normalizedTree(); // Convert back to tree
```

## Signal Order System

The module uses a 4-level ordering system (`getSigOrder()`) for optimization decisions:

| Order | Description | Examples |
|-------|-------------|----------|
| 0 | Numerical constants | `42`, `3.14` (compile-time constants) |
| 1 | Foreign constants | External C/C++ constants (`fconst`) |
| 2 | User interface values | Sliders, buttons, checkboxes, external variables |
| 3 | Audio signals | `input(0)`, delays, tables, time-varying signals |

This ordering enables:

- Constant factorization (order < 2 can be moved outside operations)
- Delay optimization (constant delays can be composed)
- Proper evaluation sequence (lower order evaluated first)

## Core Algorithms

### Add-Normal Form Normalization

**Function:** `normalizeAddTerm(Tree t)`

**Algorithm:**
```cpp
aterm A(t);                          // Convert to additive term
mterm D = A.greatestDivisor();       // Find common factors
while (D.isNotZero() && D.complexity() > 0) {
    A = A.factorize(D);              // Factor out common terms
    D = A.greatestDivisor();         // Look for more opportunities  
}
return A.normalizedTree();           // Convert back to tree
```

**Example:** Expressions like `a + b*a` become `a*(1 + b)` through factorization

### Delay Normalization

**Function:** `normalizeDelayTerm(Tree s, Tree d)`

**Applied Rules:**
- `s@0 → s` (zero delay elimination)
- `0@d → 0` (zero signal elimination)  
- `(k*s)@d → k*(s@d)` when k is constant
- `(s/k)@d → (s@d)/k` when k is constant
- `(s@n)@m → s@(n+m)` when n is constant

**Implementation checks signal order < 2 to determine if expressions are constant.**

### Signal Simplification

**Function:** `simplify(Tree sig)`

**Optimization Categories:**

1. **Constant Folding:**
```cpp
if (isNum(n1) && isNum(n2)) {
    return tree(op->compute(n1, n2));  // Direct computation
}
```

2. **Algebraic Identities:**
- Left/right neutral: `0 + x = x`, `1 * x = x`
- Left/right absorbing: `0 * x = 0`
- Identical operands: `x && x = x`, `x == x = 1`

3. **Negative Number Patterns:**
- `-n*(x-y) → n*(y-x)`
- `-1*(x-y) → y-x`

4. **Multiplication Optimization:**
- `n*(m*x) → (n*m)*x`
- Eliminates intermediate multiplications

## Public API

### Core Normalization Functions

```cpp
// Main entry points
Tree normalizeAddTerm(Tree t);              // Additive normalization
Tree normalizeDelay1Term(Tree s);           // Single-sample delay normalization
Tree normalizeDelayTerm(Tree s, Tree d);    // Delay normalization  
Tree simplify(Tree sig);                    // General simplification

// Complete normalization pipeline
Tree simplifyToNormalForm(Tree sig);        // Full optimization
tvec simplifyToNormalForm2(tvec siglist);   // Batch processing
```

### Additive Term Operations

```cpp
aterm a;                           // Empty term (zero)
aterm a(tree);                     // From expression tree
a += tree;                         // Add expression
a -= tree;                         // Subtract expression
Tree result = a.normalizedTree();  // Back to tree form
mterm gcd = a.greatestDivisor();   // Find common factors
```

### Multiplicative Term Operations

```cpp
mterm m(5);                        // Coefficient constructor
mterm m(tree);                     // From expression tree
m *= other;                        // Multiply
m /= other;                        // Divide
bool canDivide = m.hasDivisor(n);  // Check divisibility
int cost = m.complexity();         // Complexity metric
```

## Memoization and Performance

### Caching Strategy

The module uses property-based memoization:
```cpp
Tree simplify(Tree sig) {
    return sigMap(gGlobal->SIMPLIFIED, traced_simplification, sig);
}
```

**Cache Keys:**
- `SIMPLIFIED` - Algebraic simplification results
- `NORMALFORM` - Complete normal form cache
- `DOCTABLES` - Documentation table conversions

### Performance Optimizations

1. **Early Exit Conditions:**
   - Zero operand detection
   - Identity operation shortcuts
   - Complexity threshold checking

2. **Memory Management:**
   - Inherits from `Garbageable` for automatic cleanup
   - Factor cleanup removes zero-power terms
   - Shared expression reuse

3. **Order-Based Processing:**
   - Constants processed first for maximum folding
   - Complex expressions processed last
   - Enables optimal term grouping

## Integration with Compiler Pipeline

### Input Sources
- Expression trees from evaluation phase
- Recursive signal definitions
- User interface primitive expressions

### Processing Pipeline
1. **deBruijn2Sym** - Convert recursive indices to symbols
2. **typeAnnotation** - Add type information
3. **Range UI generation** - Add UI constraints (optional)
4. **Math function typing** - Type mathematical primitives
5. **Simplification** - Apply algebraic rules
6. **Type promotion** - Handle type casting
7. **Final validation** - Ensure correctness

### Output Products
- Normalized expression trees
- Optimized signal graphs
- Type-correct expressions ready for code generation

## Error Handling

### Exception Types
```cpp
// Division by zero detection
if (isZero(y)) {
    stringstream error;
    error << "ERROR : % by 0 in " << ppsig(x) << " % " << ppsig(y);
    throw faustexception(error.str());
}
```

### Validation Patterns
- `faustassert()` for internal consistency checks
- Null pointer validation before operations
- Type compatibility verification

## Debugging Support

### Trace Output
Enable with `#define TRACE`:
```cpp
cerr << "Start simplification of : " << ppsig(sig) << endl;
cerr << "Simplification returns : " << ppsig(result) << endl;
```

### Pretty Printing
```cpp
std::string printSignal(Tree sig, bool shared, int max_size);
std::ostream& aterm::print(std::ostream& dst) const;
std::ostream& mterm::print(std::ostream& dst) const;
```

## Dependencies

### Core Dependencies
- `tree.hh` - Expression tree data structure
- `signals.hh` - Signal construction and analysis  
- `garbageable.hh` - Memory management base class

### Compiler Integration
- `global.hh` - Global compiler state and configuration
- `sigtype.hh`, `sigtyperules.hh` - Type system integration
- `sigorderrules.hh` - Signal complexity analysis
- `xtended.hh` - Extended primitive functions

### Utility Libraries  
- `ppsig.hh` - Pretty printing for debugging
- `exception.hh` - Error handling infrastructure
- `tlib.hh` - Tree manipulation utilities

## Implementation Notes

### Coefficient Handling
- Special cases for -1, 0, 1 coefficients
- Magnitude-based comparisons for GCD computation
- Proper sign tracking during reconstruction

### Tree Reconstruction
- Order-based assembly (constants → complexity)
- Signed arithmetic with explicit sign tracking
- Division term handling for proper semantics

### Memory Efficiency
- Automatic cleanup of zero-power factors
- Reuse of common subexpressions through memoization
- Lazy evaluation for expensive operations

This module forms the mathematical foundation for Faust's optimization pipeline, transforming user expressions into efficient, canonical forms suitable for high-performance audio code generation.