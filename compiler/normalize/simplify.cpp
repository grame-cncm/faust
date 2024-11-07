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

// declarations

static Tree simplification(Tree sig);
static Tree sigMap(Tree key, tfun f, Tree t);

static Tree traced_simplification(Tree sig)
{
    faustassert(sig);
#ifdef TRACE
    cerr << ++gGlobal->TABBER << "Start simplification of : " << ppsig(sig, MAX_ERROR_SIZE) << endl;
    /*
    fprintf(stderr, "\nStart simplification of : ");
    printSignal(sig, stderr);
    fprintf(stderr, "\n");
    */
#endif
    Tree r = simplification(sig);
    faustassert(r != nullptr);
#ifdef TRACE
    cerr << --gGlobal->TABBER << "Simplification of : " << ppsig(sig, MAX_ERROR_SIZE)
         << " Returns : " << ppsig(r, MAX_ERROR_SIZE) << endl;
    /*
    fprintf(stderr, "Simplification of : ");
    printSignal(sig, stderr);
    fprintf(stderr, " -> ");
    printSignal(r, stderr);
    fprintf(stderr, "\n");
    */
#endif
    return r;
}

Tree simplify(Tree sig)
{
    // TO IMPROVE: the simplication has to be done twice here because the second can still discover
    // possible simplications
    Tree r1 = sigMap(gGlobal->SIMPLIFIED, traced_simplification, sig);
    Tree r2 = sigMap(gGlobal->SIMPLIFIED, traced_simplification, r1);
    return r2;
}

// Implementation

static bool isSigBool(Tree sig)
{
    int  opnum;
    Tree t1, t2;

    if (!isSigBinOp(sig, &opnum, t1, t2)) {
        return false;
    }
    if (isBoolOpcode(opnum)) {
        return true;
    }

    return isLogicalOpcode(opnum) && isSigBool(t1) && isSigBool(t2);
}

static Tree simplification(Tree sig)
{
    faustassert(sig);
    int  opnum, opnum2;
    Tree t1, t2, t3, v1, v2;

    xtended* xt = (xtended*)getUserData(sig);
    // primitive elements
    if (xt) {
        vector<Tree> args;
        for (int i = 0; i < sig->arity(); i++) {
            args.push_back(sig->branch(i));
        }

        faustassert(args.size() == xt->arity());

        // to avoid negative power to further normalization
        if (xt != gGlobal->gPowPrim) {
            return xt->computeSigOutput(args);
        } else {
            return normalizeAddTerm(xt->computeSigOutput(args));
        }

    } else if (isSigBinOp(sig, &opnum, t1, t2)) {
        BinOp* op = gBinOpTable[opnum];
        Node   n1 = t1->node();
        Node   n2 = t2->node();

        if (isNum(n1) && isNum(n2)) {
            return tree(op->compute(n1, n2));
        }

        // New rules for -E

        // -n*(x-y) -> n*(y-x)
        // -1*(x-y) -> y-x
        else if ((opnum == kMul) && isNegative(n1) && isSigBinOp(t2, &opnum2, v1, v2) &&
                 (opnum2 == kSub)) {
            if (isMinusOne(n1)) {
                return sigBinOp(kSub, v2, v1);
            } else {
                return sigBinOp(kMul, tree(minusNode(n1)), sigBinOp(kSub, v2, v1));
            }

            // (x-y)*-n -> n*(y-x)
            // (x-y)*-1 -> y-x
        } else if ((opnum == kMul) && isNegative(n2) && isSigBinOp(t1, &opnum2, v1, v2) &&
                   (opnum2 == kSub)) {
            if (isMinusOne(n2)) {
                return sigBinOp(kSub, v2, v1);
            } else {
                return sigBinOp(kMul, tree(minusNode(n2)), sigBinOp(kSub, v2, v1));
            }
        }

        // n*(m*x) -> (n*m)*x or x (if n*m == 1)
        else if ((opnum == kMul) && isNum(n1) && isSigBinOp(t2, &opnum2, v1, v2) &&
                 (opnum2 == kMul) && isNum(v1)) {
            Tree m = tree(mulNode(n1, v1->node()));
            if (isOne(m)) {
                return v2;
            } else {
                return sigBinOp(kMul, m, v2);
            }
        }

        // n*(x*m) -> (n*m)*x or x (if n*m == 1)
        else if ((opnum == kMul) && isNum(n1) && isSigBinOp(t2, &opnum2, v1, v2) &&
                 (opnum2 == kMul) && isNum(v2)) {
            Tree m = tree(mulNode(n1, v2->node()));
            if (isOne(m)) {
                return v1;
            } else {
                return sigBinOp(kMul, m, v1);
            }
        }

        // End new rules
        else if (opnum == kSub && isZero(n1)) {
            return sigBinOp(kMul, sigInt(-1), t2);
        }

        else if (op->isLeftNeutral(n1)) {
            return t2;
        }

        else if (op->isLeftAbsorbing(n1)) {
            return t1;
        }

        else if (op->isRightNeutral(n2)) {
            return t1;
        }

        else if (op->isRightAbsorbing(n2)) {
            return t2;
        }

        else if (t1 == t2) {
            if ((opnum == kAND) || (opnum == kOR)) {
                return t1;
            }
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
