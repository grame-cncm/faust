# A NOTE ON HOW TO EXTEND THE COMPILER WITH NEW SIGNAL EXPRESSIONS

The concerned files are:
-   `global.hh` and `global.cpp` where the new symbols are defined
-   `signals.hh` and `signals.cpp` where the new constructors/testers are defined
-   `ppsig.cpp` where pretty printing for the expression is defined
-   `sigtyperules.cpp` where the type of the expression is defined 
-   `subsignals.cpp` where the subsignals of the new expression are computed
-   `signalVisitor.cpp` and `sigIdentity.cpp` where the new expression visit is defined

Additionnaly: `signalSplitter.cpp`, `signalDependencies.cpp`, `delaySimplifier.cpp`  and `compile_scal.cpp` are concerned.

As an example we detail the addition of `sigInstructionTableWrite` and `sigInstructionTableRead` expressions.

## Symbol definitions

In `global.hh` we add

    Sym SIGINSTRUCTIONTABLEWRITE;
    Sym SIGINSTRUCTIONTABLEREAD;

to the declaration of struct global, 

In `global.cpp` in the global() constructor, we initialize:

    SIGINSTRUCTIONTABLEREAD       = symbol("SigTableRead");
    SIGINSTRUCTIONTABLEWRITE      = symbol("SigTableWrite");

## Expression definitions

    Tree sigInstructionTableWrite(Tree id, Tree origin, int tblsize, Tree init, Tree idx, Tree sig);
    bool isSigInstructionTableWrite(Tree s, Tree& id, Tree& origin, int* tblsize, Tree& init, Tree& idx, Tree& sig);

    Tree sigInstructionTableRead(Tree id, Tree origin, Tree idx);
    bool isSigInstructionTableRead(Tree s, Tree& id, Tree& origin, Tree& idx);

## Expression implementations

    Tree sigInstructionTableWrite(Tree id, Tree origin, int tblsize, Tree init, Tree idx, Tree sig)
    {
        return tree(gGlobal->SIGINSTRUCTIONTABLEWRITE, id, origin, tree(tblsize), init, idx, sig);
    }

    bool isSigInstructionTableWrite(Tree s, Tree& id, Tree& origin, int* tblsize, Tree& init, Tree& idx, Tree& sig)
    {
        Tree tsize;
        if (isTree(s, gGlobal->SIGINSTRUCTIONTABLEWRITE, id, origin, tsize, init, idx, sig)) {
            *tblsize = tree2int(tsize);
            return true;
        } else {
            return false;
        }
    }

    Tree sigInstructionTableRead(Tree id, Tree origin, int dmin, Tree idx)
    {
        return tree(gGlobal->SIGINSTRUCTIONTABLEREAD, id, origin, tree(dmin), idx);
    }

    bool isSigInstructionTableRead(Tree s, Tree& id, Tree& origin, int* dmin, Tree& idx)
    {
        Tree tmin;
        if (tree(gGlobal->SIGINSTRUCTIONTABLEREAD, id, origin, tmin, idx)) {
            *dmin = tree2int(tmin);
            return true;
        } else {
            return false;
        }
    }

