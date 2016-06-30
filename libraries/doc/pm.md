
# pm.lib 
Faust physical modeling library.

It should be used using the `fi` environment:

```
pm = library("pm.lib");
process = pm.functionCall;
```

Another option is to import `stdfaust.lib` which already contains the `pm`
environment:

```
import("stdfaust.lib");
process = pm.functionCall;
```

### chain(A:B:...)
Creates a chain of bidirectional blocks. 
Blocks must have 3 inputs and outputs. The first input/output correspond to the left 
going signal, the second input/output correspond to the right going signal and the 
third input/output is the mix of the main signal output. The implied one sample delay
created by the `~` operator is generalized to the left and right going waves. Thus, n
blocks in `chain()` will add an n samples delay to both the left and right going waves.
### Usage
```
rightGoingWaves,leftGoingWaves,mixedOutput : chain(A:B) : rightGoingWaves,leftGoingWaves,mixedOutput
with{
     A = _,_,_;
     B = _,_,_;
};
```
### Requires
`filter.lib` (`crossnn`)

---


### input(x)
Adds a waveguide input anywhere between 2 blocks in a chain of blocks (see `chain()`).
### Usage
```
string(x) = chain(A:input(x):B)
```
Where `x` is the input signal to be added to the chain. 

---


### output()
Adds a waveguide output anywhere between 2 blocks in a chain of blocks and sends it 
to the mix output channel (see `chain()`).
### Usage
```
chain(A:output:B)
```

---


### terminations(a,b,c)
Creates terminations on both sides of a `chain()` without closing the inputs and 
outputs of the bidirectional signals chain. As for `chain()`, this function adds a 1
sample delay to the bidirectional signal both ways.
### Usage
```
rightGoingWaves,leftGoingWaves,mixedOutput : terminations(a,b,c) : rightGoingWaves,leftGoingWaves,mixedOutput
with{
     a = *(-1); // left termination
     b = chain(D:E:F); // bidirectional chain of blocks (D, E, F, etc.)
     c = *(-1); // right termination
};
```  
### Requires
`filter.lib` (`crossnn`)

---


### fullTerminations(a,b,c)
Same as `terminations()` but closes the inputs and outputs of the bidirectional chain
(only the mixed output remains).
### Usage
```
terminations(a,b,c) : _
with{
     a = *(-1); // left termination
     b = chain(D:E:F); // bidirectional chain of blocks (D, E, F, etc.)
     c = *(-1); // right termination
};
```  
### Requires
`filter.lib` (`crossnn`)

---


### leftTermination(a,b)
Creates a termination on the left side of a `chain()` without closing the inputs and 
outputs of the bidirectional signals chain. This function adds a 1 sample delay near
the termination.
### Usage
```
rightGoingWaves,leftGoingWaves,mixedOutput : terminations(a,b) : rightGoingWaves,leftGoingWaves,mixedOutput
with{
     a = *(-1); // left termination
     b = chain(D:E:F); // bidirectional chain of blocks (D, E, F, etc.)
};
```  
### Requires
`filter.lib` (`crossnn`)

---


### rightTermination(b,c)
Creates a termination on the right side of a `chain()` without closing the inputs and 
outputs of the bidirectional signals chain. This function adds a 1 sample delay near
the termination.
### Usage
```
rightGoingWaves,leftGoingWaves,mixedOutput : terminations(b,c) : rightGoingWaves,leftGoingWaves,mixedOutput
with{
     b = chain(D:E:F); // bidirectional chain of blocks (D, E, F, etc.)
     c = *(-1); // right termination
};
```  
### Requires
`filter.lib` (`crossnn`)

---


### waveguide(nMax,n)
A simple waveguide block based on a 4th order fractional delay.
### Usage
```
rightGoingWaves,leftGoingWaves,mixedOutput : waveguide(nMax,n) : rightGoingWaves,leftGoingWaves,mixedOutput
```
With: 
* `nMax`: the maximum length of the waveguide in samples
* `n` the length of the waveguide in samples. 
### Requires
`filter.lib` (`fdelay4`)

---


### idealString(length,reflexion,xPosition,x)
An ideal string with rigid terminations and where the plucking position and the 
pick-up position are the same. 
### Usage
```
1-1' : idealString(length,reflexion,xPosition,x)
```
With:
* `length`: the length of the string in meters
* `reflexion`: the coefficient of reflexion (0-0.99999999)
* `pluckPosition`: the plucking position (0.001-0.999)
* `x`: the input signal for the excitation
### Requires
`filter.lib` (`fdelay4`,`crossnn`)

---

