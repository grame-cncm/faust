/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
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

#undef TRACE

// declarations

static Tree simplification(Tree sig);
static Tree sigMap(Tree key, tfun f, Tree t);

static Tree traced_simplification(Tree sig)
{
    faustassert(sig);
#ifdef TRACE
    cerr << ++gGlobal->TABBER << "Start simplification of : " << ppsig(sig) << endl;
    /*
    fprintf(stderr, "\nStart simplification of : ");
    printSignal(sig, stderr);
    fprintf(stderr, "\n");
    */
#endif
    Tree r = simplification(sig);
    faustassert(r != 0);
#ifdef TRACE
    cerr << --gGlobal->TABBER << "Simplification of : " << ppsig(sig) << " Returns : " << ppsig(r) << endl;
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
    return sigMap(gGlobal->SIMPLIFIED, traced_simplification, sig);
}

// Implementation

static Tree simplification(Tree sig)
{
    faustassert(sig);
    int  opnum;
    Tree t1, t2, t3, t4;

    xtended* xt = (xtended*)getUserData(sig);
    // primitive elements
    if (xt) {
        // return 3;
        vector<Tree> args;
        for (int i = 0; i < sig->arity(); i++) {
            args.push_back(sig->branch(i));
        }

        // to avoid negative power to further normalization
        if (xt != gGlobal->gPowPrim) {
            return xt->computeSigOutput(args);
        } else {
            return normalizeAddTerm(xt->computeSigOutput(args));
        }

    } else if (isSigBinOp(sig, &opnum, t1, t2)) {
        BinOp* op = gBinOpTable[opnum];

        Node n1 = t1->node();
        Node n2 = t2->node();

        if (isNum(n1) && isNum(n2))
            return tree(op->compute(n1, n2));

        else if (opnum == kSub && isZero(n1))
            return sigBinOp(kMul, sigInt(-1), t2);

        else if (op->isLeftNeutral(n1))
            return t2;

        else if (op->isRightNeutral(n2))
            return t1;

        else
            return normalizeAddTerm(sig);

    } else if (isSigDelay1(sig, t1)) {
        return normalizeDelay1Term(t1);

    } else if (isSigFixDelay(sig, t1, t2)) {
        return normalizeFixedDelayTerm(t1, t2);

    } else if (isSigIntCast(sig, t1)) {
        Tree   tx;
        int    i;
        double x;
        Node   n1 = t1->node();

        if (isInt(n1, &i)) return t1;
        if (isDouble(n1, &x)) return tree(int(x));
        if (isSigIntCast(t1, tx)) return t1;

        return sig;

    } else if (isSigFloatCast(sig, t1)) {
        Tree   tx;
        int    i;
        double x;
        Node   n1 = t1->node();

        if (isInt(n1, &i)) return tree(double(i));
        if (isDouble(n1, &x)) return t1;
        if (isSigFloatCast(t1, tx)) return t1;

        return sig;

    } else if (isSigSelect2(sig, t1, t2, t3)) {
        Node n1 = t1->node();

        if (isZero(n1)) return t2;
        if (isNum(n1)) return t3;

        if (t2 == t3) return t2;

        return sig;

    } else if (isSigSelect3(sig, t1, t2, t3, t4)) {
        Node n1 = t1->node();

        if (isZero(n1)) return t2;
        if (isOne(n1)) return t3;
        if (isNum(n1)) return t4;

        if (t3 == t4) return simplification(sigSelect2(t1, t2, t3));

        return sig;
    
        
    // Enable(t1, 0) => 0
    // Enable(t1, 1) => t1
    // otherwise sig
    } else if (isSigEnable(sig, t1, t2)) {
        Node n2 = t2->node();
        
        if (isZero(n2))
            return sigMul(t1, sigInt(0)); // a 'zero' with the correct type
        
        else if (isOne(n2))
            return t1;
        
        else
            return sig;
  
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
    // printf("start sigMap\n");
    Tree p, id, body;

    if (getProperty(t, key, p)) {
        return (isNil(p)) ? t : p;  // truc pour eviter les boucles

    } else if (isRec(t, id, body)) {
        setProperty(t, key, gGlobal->nil);  // avoid infinite loop
        return rec(id, sigMap(key, f, body));

    } else {
        tvec br;
        int  n = t->arity();
        for (int i = 0; i < n; i++) {
            br.push_back(sigMap(key, f, t->branch(i)));
        }

        Tree r1 = tree(t->node(), br);

        Tree r2 = f(r1);
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
    // printf("start sigMap\n");
    Tree p, id, body;

    if (getProperty(t, key, p)) {
        return (isNil(p)) ? t : p;  // truc pour eviter les boucles

    } else if (isRec(t, id, body)) {
        faustassert(isRef(t, id));  // controle temporaire

        Tree id2;
        if (searchEnv(id, id2, env)) {
            // déjà en cours de visite de cette recursion
            return ref(id2);
        } else {
            // premiere visite de cette recursion
            id2        = tree(Node(unique("renamed")));
            Tree body2 = sigMapRename(key, pushEnv(id, id2, env), f, body);
            return rec(id2, body2);
        }

    } else {
        tvec br;
        int  n = t->arity();
        for (int i = 0; i < n; i++) {
            br.push_back(sigMapRename(key, env, f, t->branch(i)));
        }

        Tree r1 = tree(t->node(), br);

        Tree r2 = f(r1);
        if (r2 == t) {
            setProperty(t, key, gGlobal->nil);
        } else {
            setProperty(t, key, r2);
        }
        return r2;
    }
}

#if 0
static void eraseProperties (Tree key, Tree t)
{
	//printf("start sigMap\n");
	Tree p,id,body;

	if (getProperty(t, key, p)) {
		// already erased, nothing to do

	} else if (isRec(t, id, body)) {
		t->clearProperties();
        Tree r=rec(id, body);
        faustassert(r==t);
		setProperty(t, key, gGlobal->nil);	// avoid infinite loop
		eraseProperties(key, body);

	} else {

		for (int i=0; i<t->arity(); i++) {
			eraseProperties(key,t->branch(i));
		}
	}
}

void eraseAllProperties(Tree t)
{
    cerr << "begin eraseAllProperties" << endl;
	eraseProperties(tree(Node(unique("erase_"))), t);
    cerr << "end eraseAllProperties" << endl;
}
#endif

/**
 * Converts regular tables into doc tables in order to
 * facilitate the mathematical documentation generation
 */

static Tree docTableConverter(Tree sig);

Tree docTableConvertion(Tree sig)
{
    Tree r = sigMapRename(gGlobal->DOCTABLES, gGlobal->NULLENV, docTableConverter, sig);
    return r;
}

// Implementation

static Tree docTableConverter(Tree sig)
{
    Tree tbl, tbl2, id, id2, size, igen, isig, ridx, widx, wsig;

    if (isSigRDTbl(sig, tbl, ridx)) {
        // we are in a table to convert
        if (isSigTable(tbl, id, size, igen)) {
            // it's a read only table
            faustassert(isSigGen(igen, isig));
            return sigDocAccessTbl(sigDocConstantTbl(size, isig), ridx);
        } else {
            // it's a read write table
            faustassert(isSigWRTbl(tbl, id, tbl2, widx, wsig));
            faustassert(isSigTable(tbl2, id2, size, igen));
            faustassert(isSigGen(igen, isig));

            return sigDocAccessTbl(sigDocWriteTbl(size, isig, widx, wsig), ridx);
        }

    } else {
        // nothing to convert
        return sig;
    }
}
