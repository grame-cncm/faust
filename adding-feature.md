# On adding features to languages

## First of all

Adding a feature has a very high development cost, mainly due to the fact that this new feature induces a break in the versions: there will be the next code that will not be compilable by the previous language (which can be even worse if your feature doesn't ensure backward compatibility: the break occurs in both directions). In this respect, it may be useful to write a compatibility script. Also, the first question to ask yourself when adding a feature is:

- is the feature you are about to add really necessary? In other words: Is it useful only in a negligible number of cases? Is it understandable only by the few gurus who wrote the language? Can it simply be emulated directly in the language (or in the compiler)? Will it be difficult to maintain?
- isn't the code base too unstable to afford a new potential source of bugs? If you hesitated to answer no to any of these questions, you should close this file and reconsider adding a feature.

With that said, let's get down to business.

## Practical example

The problem considered here is the addition of a signal interval annotation system in the Faust language, allowing to indicate and test compiler-calculated major/minorities. This language (like all DSLs) is certainly not a very good example for the general case, however, some techniques should be quite similar.

We propose to add two pairs of primitives to Faust:

 * `highest(s)` and `lowest(s)`, single-input signals returning respectively the major and minor of the signal `s` computed by the compiler. From the point of view of the Faust type lattice, they are constants, computable at compile time (of course), floating point (so not boolean), parallelizable (I think), and this, whatever the input signal.

 * `assertbounds(lo, hi, sig)`, with `lo` and `hi` two constants known at compile time, which will have two behaviors: in normal mode, it creates a signal whose value is that of `sig` but whose interval is `[lo, hi]`, in debug mode, it checks during execution that this interval is indeed checked.

N.B. Two other primitives concerning the resolution of signals should probably be added.

## Lexer/Parser

The first step is to extend the set of valid Faust programs so that they contain (preferably exactly) the strings representing these primitives, by modifying the syntax (lexing) and semantics (parsing) of Faust. Indeed, if we ask Faust to compile the following program:

    process = assertbounds(-1, 1);

we get the following error: 

    1 : ERROR : undefined symbol : assertbounds

To do this, we have to modify the files describing the lexer and the parser, here written in Flex/Bison (for more details, see the Dragon Book)

In Faust, these files are located in `compiler/parser`.

### Lexing

In Bison, the declaration of tokens is done in the parser, here `faustparser.y`, so let's declare 4 new tokens:

     %token ASSERTBOUNDS
     %token LOWEST
     %token HIGHEST

Then we need to associate these tokens with Faust strings, so let's modify the lexer. The file containing the lexer is in `faustlexer.l`. Just add (between the two `%%`) :

    "assertbounds" return ASSERTBOUNDS;
    "lowest" return LOWEST;
    "highest" return HIGHEST;

Let's recompile the parser and the compiler (`make parser` and `make` at the root). Compiling the example :

    process = assertbounds(-1, 1);

we now get: 

    1 : ERROR : syntax error
    
### Parsing

Since we are going to add a primitive, it will logically come from the non-terminal `primitive`. Since we are dealing with primitives, our tokens will be terminal.

Warning: we are talking about the implementation of a new primitive, not an `xtended` one.

In most compilers, for a primitive of arity `n`, it is usual to ask the parser to build an object symbolizing the primitive by calling the `C++` constructor of the primitive with the result of parsing the arguments of the primitive. However, since the Faust language describes a block algebra, the arguments are not always explicitly passed to the primitive, they can be routed. Hence a small _wrapper_ around the constructor of the primitive, depending on the airty of the primitive.

As they have an arity of 1 and 3, two new boxes must be defined: 

	| ASSERTBOUNDS { $$ = boxPrim3(sigAssertBounds);}
	| LOWEST { $$ = boxPrim1(sigLowest);}
	| HIGHEST { $$ = boxPrim1(sigHighest);}

the parsing is finished.

## Signal constructors

Faust constructors are extremely classical from a computational point of view: each signal is a tree with in its root a symbol unique to the operation of the signal (e.g. an ADD symbol for an addition) and as children its arguments (boilerplate incoming code).

They are defined in `signals.cpp` with their destructors (in the functional programming sense of the term, not memory management).

But first we have to define the symbols of the signals. For optimization reasons, they are defined once and for all in `global.hh` and `global.cpp` (a single mutable object called `gGlobal` which emulates the global variables to the whole code):

`global.hh`

```c++
Sym SIGASSERTBOUNDS;
Sym SIGHIGHEST;
Sym SIGLOWEST;
```

`global.cpp`

```c++
SIGASSERTBOUNDS = symbol("sigAssertBounds");
SIGHIGHEST = symbol("sigHighest");
SIGLOWEST = symbol("sigLowest");
```

We can now define the constructor of the signal `assertbounds` as well as its destructor :

`signals.hh`

```c++
Tree sigAssertBounds(Tree s1, Tree s2, Tree s3);
Tree sigLowest(Tree s);
Tree sigHighest(Tree s);

bool isSigAssertBounds(Tree t, Tree& s1, Tree& s2, Tree& s3);
bool isSigLowest(Tree t, Tree& s);
bool isSigHighest(Tree t, Tree& s);
```

`signals.cpp`

```c++
Tree sigAssertBounds(Tree s1, Tree s2, Tree s3)
{
    return tree(gGlobal->SIGASSERTBOUNDS, s1, s2, s3);
}

bool isSigAssertBounds(Tree t, Tree& s1, Tree& s2, Tree& s3)
{
    return isTree(t, gGlobal->SIGASSERTBOUNDS, s1, s2, s3);
}
```

And now it compiles, unfortunately. Indeed, if the compiler is now able to create an object for the primitives, it still has no idea how to compile it. And indeed, if we compile the example: 

	`process = assertbounds;`

We get:

    ERROR: getSubSignals unrecognized signal: sigAssertBounds[-1,1,SigInput[0]]
    
## Compilation

Now that the signals are built, we can start compiling. Let's modify the `getSubSignals` function. This function is in the `subsignals.cpp` file (we can for example use the auto-generated documentation with Doxygen `make doc` at the root, or the definition search features in modern editors like Emacs), it just extracts the signals from the subtrees of the signal tree (let's not forget that a signal is stored as a tree). Our boxes all have two signals, so we can use the `sigPrefix` case as an example.

After compiling and executing the code, we get the new and more interesting error: 

	ERROR inferring signal type: unrecognized signal

So we have to modify the type inference system present in the `signals/sigtyperules.cpp` file. The formal definition of Faust types can be found as a comment in the header of the `sigtype.hh` file.

Let's start with `assertbounds`, the principle of this function being to add bounds to a signal, just use the `promoteInterval` method

other files to change for the backend -ocpp

- `signals/sigToGraph.cpp`, for signal graphs

- `signals/sigIdentity.cpp`, for signal graphs

- `boxes/ppbox.cpp`, for diagrams

- `generator/compile_scal.cpp`, this file is the one that contains the actual compilation

- `sigprint.cpp`, if you need a special drawing

Think about tests against the: 

- generated code

- intervals

What happens with non-decimal constants in the F2D version?

What happens if the interval gives an exact version in double but there is an overflow in float (e.g. annoying delays)?
