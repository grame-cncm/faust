# Faust Manual

This is code: `process = -;`.

```
process = +;
```

And here's a working Faust example:

<!-- faust-run -->
```
import("stdfaust.lib");
freq = hslider("freq",440,50,2000,0.01);
process = os.osc(freq);
```
<!-- /faust-run -->

and another one:

<!-- faust-run -->
```
import("stdfaust.lib");
freq = hslider("freq",440,50,2000,0.01);
process = os.sawtooth(freq);
```
<!-- /faust-run -->

More precisely :

* A *signal* $s$ is a discrete function of time $s:\mathbb{Z}\rightarrow\mathbb{R}$.

# Faust Syntax

## Expressions

Despite its textual syntax, Faust is conceptually a block-diagram language. 
Faust expressions represent DSP block-diagrams and are assembled from primitive 
ones using various *composition* operations. More traditional *numerical* 
expressions in infix notation are also possible. Additionally Faust provides 
time based expressions, like delays, expressions related to lexical 
environments, expressions to interface with foreign function and lambda 
expressions.

<img src="img/expression.svg" class="mx-auto d-block">

### Diagram Expressions

Diagram expressions are assembled from primitive ones using either binary composition operations or high level iterative constructions.

<img src="img/diagramexp.svg" class="mx-auto d-block">

#### Diagram Composition Operations 

Five binary *composition operations* are available to combine block-diagrams: 

* *recursion* (`~`),
* *parallel* (`,`),
* *sequential* (`:`),
* *split* (`<:`),
* *merge* (`:>`).

One can think of each of these composition operations as a particular way to 
connect two block diagrams. 

<img src="img/diagcomposition.svg" class="mx-auto d-block">

To describe precisely how these connections are done, we have to introduce some 
notation. The number of inputs and outputs of a block-diagram $A$ are expressed 
as $\mathrm{inputs}(A)$ and $\mathrm{outputs}(A)$. The inputs and outputs 
themselves are respectively expressed as: $[0]A$, $[1]A$, $[2]A$, $\ldots$ and 
$A[0]$, $A[1]$, $A[2]$, etc. 

For each composition operation between two block-diagrams $A$ and $B$ we will 
describe the connections $A[i]\rightarrow [j]B$ that are created and the 
constraints on their relative numbers of inputs and outputs.

The priority and associativity of this five operations are.

#### Parallel Composition

#### Sequential Composition

#### Split Composition

#### Merge Composition

#### Recursive Composition

#### Inputs and Outputs of an Expression

#### Iterations 

### Infix Notation and Other Syntax Extensions

#### Math Operators

#### Bitwise Operators

#### Comparison

#### Delay

#### Prefix Notation

#### Partial Application

### Time Expressions

#### `@` Operator

#### `'` Operator 

### Environment Expressions

#### `with`

#### `letrec`

#### `environment`

#### Access

#### `library`

<!-- TODO: import? -->

#### `component`

#### Explicit Substitution

### Foreign Expressions

#### `ffunction`

#### Signature

#### Types

#### Variables and Constants

#### File Include

#### Library File

### Applications and Abstractions

#### Abstractions 

#### Applications

#### Pattern Matching

## Primitives
