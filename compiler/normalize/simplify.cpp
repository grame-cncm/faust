/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include <stdio.h>
#include <map>

#include "compatibility.hh"
#include "exception.hh"
#include "global.hh"
#include "list.hh"
#include "normalize.hh"
#include "num.hh"
#include "ppsig.hh"
#include "recursivness.hh"
#include "signals.hh"
#include "sigorderrules.hh"
#include "sigprint.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"
#include "simplify.hh"
#include "xtended.hh"

using namespace std;

#undef TRACE

/*****************************************************************************
 * DECLARATIONS
 *****************************************************************************/

/**
 * @brief Internal simplification function (recursive implementation).
 * 
 * This is the core simplification function that applies various algebraic
 * and logical rules to reduce signal complexity. It handles all signal types
 * including primitives, binary operations, and extended functions.
 * 
 * @param sig The signal to simplify
 * @return The simplified signal
 */
static Tree simplification(Tree sig);

/**
 * @brief Apply a function to a signal tree with memoization.
 * 
 * This utility function applies a transformation function to a signal tree
 * while using memoization (caching) to avoid recomputing results for
 * previously processed signals.
 * 
 * @param key Memoization key (typically a property like SIMPLIFIED)
 * @param f The transformation function to apply
 * @param t The signal tree to process
 * @return The transformed signal tree
 */
static Tree sigMap(Tree key, tfun f, Tree t);

/**
 * @brief Wrapper for simplification with optional tracing.
 * 
 * This function provides debug tracing capabilities around the core
 * simplification function. When TRACE is defined, it outputs detailed
 * information about what signal is being simplified and the result.
 * 
 * @param sig The signal to simplify
 * @return The simplified signal
 */
static Tree traced_simplification(Tree sig)
{
    faustassert(sig);
#ifdef TRACE
    cerr << ++gGlobal->TABBER << "Start simplification of : " << ppsig(sig, MAX_ERROR_SIZE) << endl;
#endif
    // Apply the core simplification algorithm
    Tree r = simplification(sig);
    faustassert(r != nullptr);
#ifdef TRACE
    cerr << --gGlobal->TABBER << "Simplification of : " << ppsig(sig, MAX_ERROR_SIZE)
         << " Returns : " << ppsig(r, MAX_ERROR_SIZE) << endl;
#endif
    return r;
}

/**
 * @brief Main public interface for signal simplification.
 * 
 * This function provides the public API for signal simplification with
 * automatic memoization. It ensures that each signal is simplified only
 * once by caching results using the SIMPLIFIED property.
 * 
 * The simplification process includes:
 * - Constant folding (compile-time evaluation)
 * - Algebraic identities (x*1->x, x+0->x, etc.)
 * - Logical simplifications for boolean operations
 * - Special rules for power operations and negative numbers
 * - Normalization of additive terms
 * 
 * @param sig The signal expression to simplify
 * @return The simplified signal expression
 */
Tree simplify(Tree sig)
{
    return sigMap(gGlobal->SIMPLIFIED, traced_simplification, sig);
}

/*****************************************************************************
 * IMPLEMENTATION
 *****************************************************************************/

/**
 * @brief Check if a signal represents a boolean value.
 * 
 * This function determines whether a signal produces boolean values
 * by analyzing its operation type. Boolean signals include:
 * - Comparison operations (==, !=, <, <=, >, >=)
 * - Logical operations on boolean operands (&&, ||)
 * 
 * @param sig The signal to test
 * @return true if the signal produces boolean values
 */
static bool isSigBool(Tree sig)
{
    int  opnum;
    Tree t1, t2;

    // Check if it's a binary operation
    if (!isSigBinOp(sig, &opnum, t1, t2)) {
        return false;
    }
    
    // Direct boolean operations (comparisons)
    if (isBoolOpcode(opnum)) {
        return true;
    }

    // Logical operations on boolean operands
    return isLogicalOpcode(opnum) && isSigBool(t1) && isSigBool(t2);
}

/**
 * @brief Core simplification algorithm implementing algebraic rules.
 * 
 * This function implements the main simplification logic by applying various
 * algebraic and logical transformation rules. It handles different signal types:
 * 
 * 1. Extended primitives (mathematical functions)
 * 2. Binary operations (arithmetic, logical, comparison)
 * 3. Special patterns (negative multiplication, etc.)
 * 4. Other signal types (recursively simplified)
 * 
 * Key optimizations implemented:
 * - Constant folding for compile-time evaluation
 * - Algebraic identities (x*1, x+0, etc.)
 * - Special patterns for negative numbers and subtraction
 * - Power operation normalization
 * 
 * @param sig The signal to simplify
 * @return The simplified signal
 */
static Tree simplification(Tree sig)
{
    faustassert(sig);
    int  opnum, opnum2;
    Tree t1, t2, t3, v1, v2;

    // Handle extended primitives (mathematical functions)
    xtended* xt = (xtended*)getUserData(sig);
    if (xt) {
        // Collect arguments for the extended primitive
        vector<Tree> args;
        for (int i = 0; i < sig->arity(); i++) {
            args.push_back(sig->branch(i));
        }

        faustassert(args.size() == xt->arity());

        // Special handling for power operations to avoid negative power issues
        if (xt != gGlobal->gPowPrim) {
            return xt->computeSigOutput(args);
        } else {
            // Apply additive normalization to power results
            return normalizeAddTerm(xt->computeSigOutput(args));
        }

    // Handle binary operations (arithmetic, logical, comparison)
    } else if (isSigBinOp(sig, &opnum, t1, t2)) {
        BinOp* op = gBinOpTable[opnum];
        Node   n1 = t1->node();
        Node   n2 = t2->node();

        // Constant folding: evaluate operations on numeric constants
        if (isNum(n1) && isNum(n2)) {
            return tree(op->compute(n1, n2));
        }

        /***********************************************************************
         * SPECIAL ALGEBRAIC RULES FOR NEGATIVE NUMBERS
         ***********************************************************************/

        // Rule: -n*(x-y) -> n*(y-x)
        // Rule: -1*(x-y) -> y-x
        else if ((opnum == kMul) && isNegative(n1) && isSigBinOp(t2, &opnum2, v1, v2) &&
                 (opnum2 == kSub)) {
            if (isMinusOne(n1)) {
                // -1 * (x-y) = y-x
                return sigBinOp(kSub, v2, v1);
            } else {
                // -n * (x-y) = n * (y-x)
                return sigBinOp(kMul, tree(minusNode(n1)), sigBinOp(kSub, v2, v1));
            }

        // Rule: (x-y)*-n -> n*(y-x)  
        // Rule: (x-y)*-1 -> y-x
        } else if ((opnum == kMul) && isNegative(n2) && isSigBinOp(t1, &opnum2, v1, v2) &&
                   (opnum2 == kSub)) {
            if (isMinusOne(n2)) {
                // (x-y) * -1 = y-x
                return sigBinOp(kSub, v2, v1);
            } else {
                // (x-y) * -n = n * (y-x)
                return sigBinOp(kMul, tree(minusNode(n2)), sigBinOp(kSub, v2, v1));
            }
        }

        /***********************************************************************
         * MULTIPLICATION OPTIMIZATION RULES
         ***********************************************************************/

        // Rule: n*(m*x) -> (n*m)*x or x (if n*m == 1)
        else if ((opnum == kMul) && isNum(n1) && isSigBinOp(t2, &opnum2, v1, v2) &&
                 (opnum2 == kMul) && isNum(v1)) {
            Tree m = tree(mulNode(n1, v1->node()));
            if (isOne(m)) {
                // n*(1*x) = x
                return v2;
            } else {
                // n*(m*x) = (n*m)*x
                return sigBinOp(kMul, m, v2);
            }
        }

        // Rule: n*(x*m) -> (n*m)*x or x (if n*m == 1)
        else if ((opnum == kMul) && isNum(n1) && isSigBinOp(t2, &opnum2, v1, v2) &&
                 (opnum2 == kMul) && isNum(v2)) {
            Tree m = tree(mulNode(n1, v2->node()));
            if (isOne(m)) {
                // n*(x*1) = x
                return v1;
            } else {
                // n*(x*m) = (n*m)*x
                return sigBinOp(kMul, m, v1);
            }
        }

        /***********************************************************************
         * GENERAL ALGEBRAIC IDENTITY RULES
         ***********************************************************************/

        // Rule: 0 - x -> -1 * x
        else if (opnum == kSub && isZero(n1)) {
            return sigBinOp(kMul, sigInt(-1), t2);
        }

        // Left neutral element rules (e.g., 0 + x = x, 1 * x = x)
        else if (op->isLeftNeutral(n1)) {
            return t2;
        }

        // Left absorbing element rules (e.g., 0 * x = 0)
        else if (op->isLeftAbsorbing(n1)) {
            return t1;
        }

        // Right neutral element rules (e.g., x + 0 = x, x * 1 = x)
        else if (op->isRightNeutral(n2)) {
            return t1;
        }

        // Right absorbing element rules (e.g., x * 0 = 0)
        else if (op->isRightAbsorbing(n2)) {
            return t2;
        }

        /***********************************************************************
         * IDENTICAL OPERAND RULES
         ***********************************************************************/

        // Handle operations where both operands are identical
        else if (t1 == t2) {
            // Logical operations: x && x = x, x || x = x
            if ((opnum == kAND) || (opnum == kOR)) {
                return t1;
            }
            // Comparison operations: x >= x = 1, x <= x = 1, x == x = 1
            if ((opnum == kGE) || (opnum == kLE) || (opnum == kEQ)) {
                return sigInt(1);
            }
            if ((opnum == kGT) || (opnum == kLT) || (opnum == kNE) || (opnum == kRem) ||
                (opnum == kXOR)) {
                return sigInt(0);
            }

        } else if ((opnum == kAND) || (opnum == kOR)) {
            if (isOne(n1) && isSigBool(t2)) {
                return opnum == kAND ? t2 : sigInt(1);
            }
            if (isOne(n2) && isSigBool(t1)) {
                return opnum == kAND ? t1 : sigInt(1);
            }
        }

        return (global::isOpt("FAUST_SIG_NO_NORM") ? sig : normalizeAddTerm(sig));

    } else if (isSigDelay1(sig, t1)) {
        return normalizeDelay1Term(t1);

    } else if (isSigDelay(sig, t1, t2)) {
        return normalizeDelayTerm(t1, t2);

    } else if (isSigIntCast(sig, t1)) {
        int    i;
        double x;
        Node   n1 = t1->node();

        if (isInt(n1, &i)) {
            return t1;
        }
        if (isDouble(n1, &x)) {
            return tree(int(x));
        }

        return sig;

    } else if (isSigBitCast(sig, t1)) {
        return sig;

    } else if (isSigFloatCast(sig, t1)) {
        int    i;
        double x;
        Node   n1 = t1->node();

        if (isInt(n1, &i)) {
            return tree(double(i));
        }
        if (isDouble(n1, &x)) {
            return t1;
        }

        return sig;

    } else if (isSigSelect2(sig, t1, t2, t3)) {
        Node n1 = t1->node();

        if (isZero(n1)) {
            return t2;
        }
        if (isNum(n1)) {
            return t3;
        }

        if (t2 == t3) {
            return t2;
        }

        return sig;

    } else if (isSigEnable(sig, t1, t2)) {
        Node n2 = t2->node();

        if (isZero(n2)) {
            return sigInt(0);  // a 'zero' with the correct type
        }

        else if (isOne(n2)) {
            return t1;
        }

        else {
            return sig;
        }

        // Control(t1, 0) => 0
        // Control(t1, 1) => t1
        // otherwise sig
    } else if (isSigControl(sig, t1, t2)) {
        Node n2 = t2->node();

        if (isZero(n2)) {
            return sigInt(0);  // a 'zero' with the correct type
        }

        else if (isOne(n2)) {
            return t1;
        }

        else {
            return sig;
        }

    } else if (isSigLowest(sig, t1)) {
        typeAnnotation(t1, gGlobal->gLocalCausalityCheck);
        Type ty = getCertifiedSigType(t1);
        return sigReal(ty->getInterval().lo());

    } else if (isSigHighest(sig, t1)) {
        typeAnnotation(t1, gGlobal->gLocalCausalityCheck);
        Type ty = getCertifiedSigType(t1);
        return sigReal(ty->getInterval().hi());

    } else {
        return sig;
    }
}

/**
 * Recursively transform a graph by applying a function f.
 * map(f, foo[t1..tn]) = f(foo[map(f,t1)..map(f,tn)])
 */
static Tree sigMap(Tree key, tfun f, Tree t)
{
    Tree p, id, body;

    if (getProperty(t, key, p)) {
        return (isNil(p)) ? t : p;  // trick to avoid loops

    } else if (isRec(t, id, body)) {
        setProperty(t, key, gGlobal->nil);  // avoid infinite loop
        return rec(id, sigMap(key, f, body));

    } else {
        tvec br;
        int  n   = t->arity();
        int  arg = 0;
        if (isUIInputItem(t) || isUIOutputItem(t)) {
            // Do not handle labels to avoid simplifying them when using reserved keyword
            br.push_back(t->branch(arg));
            arg++;
        }
        for (int i = arg; i < n; i++) {
            br.push_back(sigMap(key, f, t->branch(i)));
        }

        Tree r2 = f(tree(t->node(), br));
        if (r2 == t) {
            setProperty(t, key, gGlobal->nil);
        } else {
            setProperty(t, key, r2);
        }
        return r2;
    }
}

/**
 * Like SigMap, recursively transform a graph by applying a
 * function f. But here recursive trees are also renamed.
 * map(f, foo[t1..tn]) = f(foo[map(f,t1)..map(f,tn)])
 */
static Tree sigMapRename(Tree key, Tree env, tfun f, Tree t)
{
    Tree p, id, body;

    if (getProperty(t, key, p)) {
        return (isNil(p)) ? t : p;  // trick to avoid loops

    } else if (isRec(t, id, body)) {
        faustassert(isRef(t, id));  // temporary control

        Tree id2;
        if (searchEnv(id, id2, env)) {
            // already in the process of visiting this recursion
            return ref(id2);
        } else {
            // first visit of this recursion
            id2        = tree(Node(unique("renamed")));
            Tree body2 = sigMapRename(key, pushEnv(id, id2, env), f, body);
            return rec(id2, body2);
        }

    } else {
        tvec br;
        int  n   = t->arity();
        int  arg = 0;
        if (isUIInputItem(t) || isUIOutputItem(t)) {
            // Do not handle labels to avoid simplifying them when using reserved keyword
            br.push_back(t->branch(arg));
            arg++;
        }
        for (int i = arg; i < n; i++) {
            br.push_back(sigMapRename(key, env, f, t->branch(i)));
        }

        Tree r2 = f(tree(t->node(), br));
        if (r2 == t) {
            setProperty(t, key, gGlobal->nil);
        } else {
            setProperty(t, key, r2);
        }
        return r2;
    }
}

#if 0
static void eraseProperties(Tree key, Tree t)
{
	//printf("start sigMap\n");
	Tree p,id,body;

	if (getProperty(t, key, p)) {
		// already erased, nothing to do

	} else if (isRec(t, id, body)) {
		t->clearProperties();
        Tree r = rec(id, body);
        faustassert(r==t);
		setProperty(t, key, gGlobal->nil);	// avoid infinite loop
		eraseProperties(key, body);

	} else {

		for (int i = 0; i < t->arity(); i++) {
			eraseProperties(key,t->branch(i));
		}
	}
}

static void eraseAllProperties(Tree t)
{
    cerr << "begin eraseAllProperties" << endl;
	eraseProperties(tree(Node(unique("erase_"))), t);
    cerr << "end eraseAllProperties" << endl;
}
#endif

static Tree docTableConverter(Tree sig);

/**
 * Converts regular tables into doc tables in order to
 * facilitate the mathematical documentation generation
 */
Tree docTableConvertion(Tree sig)
{
    Tree r = sigMapRename(gGlobal->DOCTABLES, gGlobal->NULLENV, docTableConverter, sig);
    return r;
}

// Implementation

static Tree docTableConverter(Tree sig)
{
    Tree gen, wi, ws, tbl, ri, size, isig;

    if (isSigRDTbl(sig, tbl, ri)) {
        // we are in a table to convert
        if (isSigWRTbl(tbl, size, gen)) {
            // rdtable
            faustassert(isSigGen(gen, isig));
            return sigDocAccessTbl(sigDocConstantTbl(size, isig), ri);
        } else {
            // rwtable
            faustassert(isSigWRTbl(tbl, size, gen, wi, ws));
            faustassert(isSigGen(gen, isig));
            return sigDocAccessTbl(sigDocWriteTbl(size, isig, wi, ws), ri);
        }

    } else {
        // nothing to convert
        return sig;
    }
}
