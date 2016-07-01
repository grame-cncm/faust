
# route.lib 
A library of basic elements to handle signal routing in Faust.

It should be used using the `si` environment:

```
ro = library("route.lib");
process = ro.functionCall;
```

Another option is to import `stdfaust.lib` which already contains the `si`
environment:

```
import("stdfaust.lib");
process = ro.functionCall;
```

## Functions Reference

### `cross(n)`
Cross n signals: `(x1,x2,..,xn) -> (xn,..,x2,x1)`.

#### Usage

```
_,_,_ : cross(3) : _,_,_
```

Where:

* `n`: number of signals (int, must be known at compile time)

#### Note

Special case: `cross2`:

```
cross2 = _,cross(2),_;
```

---


### `crossnn(n)`
Cross two `bus(n)`s.

#### Usage

```
_,_,... : crossmm(n) : _,_,...
```

Where:

* `n`: the number of signals in the `bus`

---


### `crossn1(n)`
Cross bus(n) and bus(1).

#### Usage

```
_,_,... : crossn1(n) : _,_,...
```

Where:

* `n`: the number of signals in the first `bus`

---


### `interleave(row,col)`
Interleave row*col cables from column order to row order.
input : x(0), x(1), x(2) ..., x(row*col-1)
output: x(0+0*row), x(0+1*row), x(0+2*row), ..., x(1+0*row), x(1+1*row), x(1+2*row), ...

#### Usage

```
_,_,_,_,_,_ : interleave(3,2) : _,_,_,_,_,_
```

Where:

* `row`: the number of row (int, known at compile time)
* `column`: the number of column (int, known at compile time)

---


### `butterfly(n)`
Addition (first half) then substraction (second half) of interleaved signals.

#### Usage

```
_,_,_,_ : butterfly(4) : _,_,_,_
```

Where:

* `n`: size of the butterfly (n is int, even and known at compile time)

---


### `hadamard(n)`
Hadamard matrix function of size `n = 2^k`.

#### Usage

```
_,_,_,_ : hadamard(4) : _,_,_,_
```

Where:

* `n`: `2^k`, size of the matrix (int, must be known at compile time)

#### Note:

Implementation contributed by Remy Muller.

---


### `recursivize(p,q)`
Create a recursion from two arbitrary processors p and q.

#### Usage

```
_,_ : stereoize(p,q) : _,_

```

Where:

* `p`: the forward arbitrary processor
* `q`: the feedback arbitrary processor

---

