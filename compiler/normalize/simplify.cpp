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
#include "sigpattern.hh"
#include "sigtransform.hh"
#include "sigprint.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"
#include "simplify.hh"
#include "xtended.hh"

using namespace std;

#undef TRACE

// declarations

static Tree simplification(Tree sig);

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

namespace {

// Simplify as a transformation: the driver walks the DAG (fresh variable per
// recursive group, memo local to the call), the algebra applies the rule cascade
// to every rebuilt signal node. Extended primitives fold through the primitive
// itself, on the already-simplified children.
class SimplifyAlgebra final : public TransformAlgebra {
   public:
    XSig combine(Tree orig, const std::vector<XSig>& c,
                 FixPointEvaluator<XSig>& ev) const override
    {
        XSig r = TransformAlgebra::combine(orig, c, ev);
        return o(traced_simplification(r.out));
    }

    XSig xtdApp(Tree, xtended* p, const std::vector<XSig>& c) const override
    {
        std::vector<Tree> args;
        args.reserve(c.size());
        for (const XSig& v : c) {
            args.push_back(v.out);
        }
        // to avoid negative power to further normalization
        Tree r = p->computeSigOutput(args);
        return o(p != gGlobal->gPowPrim ? r : normalizeAddTerm(r));
    }
};

}  // namespace

Tree simplify(Tree sig)
{
    SimplifyAlgebra A;
    return signalTransform(sig, A, gGlobal->gSimplifiedMemo);
}

Tree simplifyExpression(Tree sig)
{
    return traced_simplification(sig);
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

// The rules, written in the pattern algebra (sigpattern.hh): each left-hand
// side is a term of the free algebra over the signal signature extended with
// variables; the right-hand side is ordinary construction on the bindings.
// Rule ORDER is semantics: it reproduces the historical cascade exactly.
static Tree simplification(Tree sig)
{
    faustassert(sig);
    using namespace pat;

    Tree n, m, x, y, sel;

    // extended primitives never reach this cascade: the driver routes them to
    // SimplifyAlgebra::xtdApp, which folds through the primitive itself

    int  opnum;
    Tree t1, t2;
    if (isSigBinOp(sig, &opnum, t1, t2)) {
        // the generic frame: rules valid FOR ALL operators, driven by the op tables
        ::BinOp* op = gBinOpTable[opnum];
        Node   n1 = t1->node();
        Node   n2 = t2->node();

        if (isNum(n1) && isNum(n2)) {
            return tree(op->compute(n1, n2));
        }

        // -n*(x-y) -> n*(y-x) ; -1*(x-y) -> y-x
        if (Mul(negNum(n), Sub(var(x), var(y))).match(sig)) {
            return isMinusOne(n->node())
                       ? sigBinOp(kSub, y, x)
                       : sigBinOp(kMul, tree(minusNode(n->node())), sigBinOp(kSub, y, x));
        }

        // (x-y)*-n -> n*(y-x) ; (x-y)*-1 -> y-x
        if (Mul(Sub(var(x), var(y)), negNum(n)).match(sig)) {
            return isMinusOne(n->node())
                       ? sigBinOp(kSub, y, x)
                       : sigBinOp(kMul, tree(minusNode(n->node())), sigBinOp(kSub, y, x));
        }

        // n*(m*x) -> (n*m)*x or x (if n*m == 1)
        if (Mul(pat::num(n), Mul(pat::num(m), var(x))).match(sig)) {
            Tree p = tree(mulNode(n->node(), m->node()));
            return isOne(p->node()) ? x : sigBinOp(kMul, p, x);
        }

        // n*(x*m) -> (n*m)*x or x (if n*m == 1)
        if (Mul(pat::num(n), Mul(var(x), pat::num(m))).match(sig)) {
            Tree p = tree(mulNode(n->node(), m->node()));
            return isOne(p->node()) ? x : sigBinOp(kMul, p, x);
        }

        // 0-x -> -1*x
        if (Sub(zero(), var(x)).match(sig)) {
            return sigBinOp(kMul, sigInt(-1), x);
        }

        if (op->isLeftNeutral(n1)) {
            return t2;
        }
        if (op->isLeftAbsorbing(n1)) {
            return t1;
        }
        if (op->isRightNeutral(n2)) {
            return t1;
        }
        if (op->isRightAbsorbing(n2)) {
            return t2;
        }

        if (t1 == t2) {
            // x op x : hash-consing decides the equality
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
    }

    // delays go to their normal-form engine
    if (Mem(var(x)).match(sig)) {
        return normalizeDelay1Term(x);
    }
    if (Delay(var(x), var(y)).match(sig)) {
        return normalizeDelayTerm(x, y);
    }

    // casts fold on literals
    if (IntCast(var(x)).match(sig)) {
        int    i;
        double d;
        if (isInt(x->node(), &i)) {
            return x;
        }
        if (isDouble(x->node(), &d)) {
            return tree(int(d));
        }
        return sig;
    }
    if (BitCast(var(x)).match(sig)) {
        return sig;
    }
    if (FloatCast(var(x)).match(sig)) {
        int    i;
        double d;
        if (isInt(x->node(), &i)) {
            return tree(double(i));
        }
        if (isDouble(x->node(), &d)) {
            return x;
        }
        return sig;
    }

    // select2(0, x, y) -> x ; select2(n, x, y) -> y ; select2(c, x, x) -> x
    if (Select2(var(sel), var(x), var(y)).match(sig)) {
        if (isZero(sel->node())) {
            return x;
        }
        if (isNum(sel->node())) {
            return y;
        }
        if (x == y) {
            return x;
        }
        return sig;
    }

    // enable/control against a constant guard
    if (Enable(var(x), var(y)).match(sig) || Control(var(x), var(y)).match(sig)) {
        if (isZero(y->node())) {
            return sigInt(0);  // a 'zero' with the correct type
        }
        if (isOne(y->node())) {
            return x;
        }
        return sig;
    }

    // lowest/highest collapse to their certified interval bound
    if (Lowest(var(x)).match(sig)) {
        typeAnnotation(x, gGlobal->gLocalCausalityCheck);
        return sigReal(getCertifiedSigType(x)->getInterval().lo());
    }
    if (Highest(var(x)).match(sig)) {
        typeAnnotation(x, gGlobal->gLocalCausalityCheck);
        return sigReal(getCertifiedSigType(x)->getInterval().hi());
    }

    return sig;
}

/**
 * Recursively transform a graph by applying a function f, renaming the
 * recursive trees along the way.
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
