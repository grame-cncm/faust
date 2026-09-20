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

/*****************************************************************************
    HISTORY
    22/01/05 : corrected bug on bool signals cached in float variables
*****************************************************************************/

#include <math.h>
#include <stdio.h>
#include <climits>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <vector>

#include "Schedule.hh"
#include "compatibility.hh"
#include "compile.hh"
#include "compile_scal.hh"
#include "dlcodegen.hh"
#include "floats.hh"
#include "normalform.hh"
#include "ppsig.hh"
#include "prim2.hh"
#include "recursivness.hh"
#include "sharing.hh"
#include "sigDependenciesGraph.hh"
#include "sigNewConstantPropagation.hh"
#include "sigPromotion.hh"
#include "sigRecursiveDependencies.hh"
#include "sigRetiming.hh"
#include "sigToGraph.hh"
#include "sigprint.hh"
#include "rewrite.hh"
#include <optional>
#include <unordered_map>
#include "superNodes.hh"
#include "revealFIR.hh"
#include "revealIIR.hh"
#include "HierarchyDot.hh"
#include "placeTemps.hh"
#include "reassociate.hh"
#include "nestSums.hh"
#include "revealSum.hh"
#include "descend.hh"
#include "factorizeFIRs.hh"
#include "kernelCandidacy.hh"
#include "revealMatrix.hh"
#include "lowerSums.hh"
#include "sigtype.hh"
#include "timing.hh"
#include "xtendedCodegen.hh"
#include "global.hh"

#undef TRACE

// Old delays are supposed to work while new delays are in progress
#define OLDDELAY 0

using namespace std;

/**
 * A real constant as C++ source. T() spells the finite values ; the
 * non-finite ones have no literal (T() would print "inf.0") and take the
 * <cmath> macros, sign kept.
 */
/**
 * Int32 add, sub and mul must wrap in two's complement (the integer noise
 * LCG relies on it) but signed overflow is undefined in C++, and clang -O2
 * exploits it ; they render as the faust_wrap_* helpers the class header
 * defines, the same three the cpp backend emits. Other operations, and
 * every real operation, keep the infix rendering.
 */
static const char* wrapHelper(int opcode)
{
    switch (opcode) {
        case kAdd:
            return "faust_wrap_add";
        case kSub:
            return "faust_wrap_sub";
        case kMul:
            return "faust_wrap_mul";
        default:
            return nullptr;
    }
}

static string realLiteral(double r)
{
    if (std::isnan(r)) {
        return "NAN";
    }
    if (std::isinf(r)) {
        return (r < 0) ? "-INFINITY" : "INFINITY";
    }
    return T(r);
}


static void callWithLargeStack(std::function<void()>& function)
{
    auto trampoline = [](void* opaque) -> void* {
        (*static_cast<std::function<void()>*>(opaque))();
        return nullptr;
    };
    callFunWithStackSize(trampoline, &function, size_t(2048) << 20);
}


/**
 * The compilation-order strategy (-ss <n>, --scheduling-strategy; formerly the
 * FAUST_OCPP_SCHEDULE environment variable): 0 = df (the default, deep-first),
 * 1 = bf (breadth-first levels), 2 = sp (special), 3 = rb (reverse
 * breadth-first, and the fallback for any other value, as in the FIR branch),
 * 4 = dfcycles / 5 = bfcycles (DAG of cycles, then deep-first inside),
 * 6 = mc (the model-constrained list scheduler of the -ls engine, ported to
 * the DirectedGraph library: width and register budget from -ls-U / -ls-R).
 * All are dependencies-first, so the generated code is a reordering of the
 * same statements -- semantics unchanged, performance to be measured.
 * Numbering 0-3 matches master-dev-ocpp-od-fir-2-FIR20 for cross-branch
 * comparability.
 */
static long ocppTreeShape(const Tree& t)
{
    Sym s;
    if (isSym(t->node(), &s)) {
        return (long)(size_t)s;
    }
    return 1;  // numeric leaves share one shape
}

// ---- the SHAPE of an expression: the computation with the data forgotten.
// shape(op(a, b)) = op(shape(a), shape(b)) ; data leaves (numbers, inputs)
// become typed holes ; children that are themselves SCHEDULED nodes (the
// truncation boundary: they will be emitted as their own statements) become
// reference holes. Two statements are isomorphic -- SLP-packable -- iff
// their shapes are the SAME TREE, and shapes being hash-consed trees, that
// comparison is pointer identity. Constant delay amounts become holes too:
// offsets are forgotten by the same generic rule. Cycles (rec bodies not on
// the boundary) are cut by an on-stack guard.
static Tree ocppShape(Tree t, const std::set<Tree, treeorder>& inG,
                      std::map<Tree, Tree, treeorder>& memo, std::set<Tree, treeorder>& onstack)
{
    auto it = memo.find(t);
    if (it != memo.end()) {
        return it->second;
    }
    Tree r;
    if (!isSym(t->node())) {
        // a number: a typed hole
        r = tree(symbol(t->node().type() == kIntNode ? "SHAPE_HOLE_I" : "SHAPE_HOLE_F"));
    } else if (onstack.count(t)) {
        r = tree(symbol("SHAPE_HOLE_CYCLE"));
    } else {
        int i;
        if (isSigInput(t, &i)) {
            r = tree(symbol("SHAPE_HOLE_IN"));  // which input: forgotten
        } else {
            onstack.insert(t);
            // operation SELECTORS are part of the computation, not data:
            // the binop opcode (branch 0) stays literal in the shape --
            // mul and add must not share a shape (SLP packs same opcodes)
            int  selKeep = -1;
            {
                int  op;
                Tree x, y;
                if (isSigBinOp(t, &op, x, y)) {
                    selKeep = 0;
                }
            }
            std::vector<Tree> br;
            for (int k = 0; k < t->arity(); k++) {
                Tree c = t->branch(k);
                if (k == selKeep) {
                    br.push_back(c);  // literal selector
                } else if (inG.count(c) && !(c == t)) {
                    br.push_back(tree(symbol("SHAPE_HOLE_REF")));
                } else {
                    br.push_back(ocppShape(c, inG, memo, onstack));
                }
            }
            r = tree(t->node(), br);
            onstack.erase(t);
        }
    }
    memo[t] = r;
    return r;
}



// the shape functor for a given graph: boundary = the graph's node set
static std::function<long(const Tree&)> ocppShapeFunctor(const digraph<Tree>& G)
{
    auto inG  = std::make_shared<std::set<Tree, treeorder>>(G.nodes().begin(), G.nodes().end());
    auto memo = std::make_shared<std::map<Tree, Tree, treeorder>>();
    return [inG, memo](const Tree& t) -> long {
        std::set<Tree, treeorder> onstack;
        // the colour is the shape tree's SERIAL, never its address : the
        // schedulers key their shape classes by this value and break
        // frequency ties in key order -- an address made -ss 8 differ from
        // one run of the same binary to the next (ASLR)
        return long(ocppShape(t, *inG, *memo, onstack)->serial());
    };
}

static schedule<Tree> ocppScheduleRaw(const digraph<Tree>& G)
{
    switch (gGlobal->gSchedulingStrategy) {
        case 0:
            return dfschedule(G);
        case 1:
            return bfschedule(G);
        case 2:
            return spschedule(G);
        case 4:
            return dfcyclesschedule(G);
        case 5:
            return bfcyclesschedule(G);
        case 6:
            return mcschedule(G, gGlobal->gLSRegisters, gGlobal->gLSWidth);
        case 8:
            // shape-ALIGNED order (Yann's alignment step) : shapes as
            // colors, grouped in monochromatic ranks -- the banks
            return alignschedule(G, ocppShapeFunctor(G));
        case 7:
            // compositional v5: csschedule DIRECTLY at Tree grain -- its
            // dominator association, batched round-robin of independent
            // siblings (the tiling that reaches the certified optimum on
            // large(16,6,R4)) and shape-armed DP merges all operate at the
            // statement level the SLP vectorizer sees. Cycle back-edges are
            // ignored by its structures exactly as dfschedule ignores them.
            return csschedule(G, gGlobal->gLSRegisters, gGlobal->gLSWidth,
                              ocppShapeFunctor(G));
        case 9:
            // bank-compositional hybrid : composition under constraint on
            // a previously shape-ALIGNED dag -- banks (capped monochromatic
            // antichains) become the atoms csschedule places. Singleton
            // shapes degenerate into plain cs (deep recurrences keep their
            // locality) ; repeated shapes can no longer be dispersed.
            {
                unsigned int bc = 0;
                int sc = 0;
                return bankschedule(G, gGlobal->gLSRegisters, gGlobal->gLSWidth,
                                    ocppShapeFunctor(G), bc, sc,
                                    false);
            }
        case 11:
        case 12:
            // CSSCHEDULE v3 (spec faust-migration/CSSCHEDULE.md) :
            // dominator blocks, K-wide frontiers, Pareto-beam grid
            // combination under (R,U), ASAP closure as the only R
            // certificate. The best trace is emitted even when no
            // candidate closes under R -- hard R is a certificate, not a
            // validity condition. K = 4 (the frontier width).
            // 11 = depth-first spine, 12 = breadth-first spine (wide,
            // parallel -- fdnRev and paradigma clientele).
            {
                unsigned int k2 = 4;
                long b2 = 1000000;  // global cell budget
                bool bfsp = (gGlobal->gSchedulingStrategy == 12);
                bool           feas = true;
                cs2stats       st;
                schedule<Tree> S2   = csschedule2(G, gGlobal->gLSRegisters, gGlobal->gLSWidth,
                                                  k2, &feas, b2, &st, bfsp);
                return S2;
            }
        default:
            return rbschedule(G);
    }
}

// memory classification at Tree grain : a delayed read (dmin >= 1) is a
// buffer load, an input is a stream load ; writes folded into their
// producer (v1). Shared by the quality print and the emitted comment.
static bool ocppIsMemNode(const Tree& t)
{
    Tree x, y;
    int  i;
    if (isSigInput(t, &i)) {
        return true;
    }
    if (isSigDelay(t, x, y)) {
        interval I = getCertifiedSigType(y)->getInterval();
        return int(I.lo()) >= 1;
    }
    return false;
}

// the scheduled order of the immediate graph, under the chosen strategy
static schedule<Tree> ocppSchedule(const digraph<Tree>& G)
{
    schedule<Tree> S = ocppScheduleRaw(G);
    return S;
}

static Klass* signal2klass(Klass* parent, const string& name, Tree sig)
{
    Type t = getCertifiedSigType(sig);  //, NULLENV);
    if (t->nature() == kInt) {
        ScalarCompiler C(new SigIntGenKlass(parent, name));
        C.compileSingleSignal(sig);
        return C.getClass();

    } else {
        ScalarCompiler C(new SigFloatGenKlass(parent, name));
        C.compileSingleSignal(sig);
        return C.getClass();
    }
}

/*****************************************************************************
 getFreshID
 *****************************************************************************/

map<string, int> ScalarCompiler::fIDCounters;

string ScalarCompiler::getFreshID(const string& prefix)
{
    if (fIDCounters.find(prefix) == fIDCounters.end()) {
        fIDCounters[prefix] = 0;
    }
    int n               = fIDCounters[prefix];
    fIDCounters[prefix] = n + 1;
    return subst("$0$1", prefix, T(n));
}

/*****************************************************************************
 delay floor (-mindelay, experimental)
 *****************************************************************************/

/**
 * Semantic delay floor: rewrite sigDelay(x, y) into sigDelay(x, max(y, K))
 * for LARGE VARIABLE delays -- certified dmin < K and dmax >= 32*K (the
 * excursion threshold: a multi-second echo is floored, a flanger or a
 * variable-pitch string is not). The max is REAL, emitted code included:
 * the interval system then certifies dmin >= K by itself, and when
 * K >= gVecSize the d < N freedom cuts the feedback cycles that go through
 * these delays -- no special case anywhere downstream, the proof travels
 * through the types. Opt-in: settings below K no longer reach them.
 * Trees are rebuilt, so every annotation must be redone by the caller.
 */
static Tree applyDelayFloor(Tree L, int K)
{
    const int excursion = 32 * K;
    return treeRewrite(L, [K, excursion](Tree t) -> Tree {
        Tree x, y;
        int  d;
        if (isSigDelay(t, x, y) && !isSigInt(y, &d)) {
            ::Type ty = getSigType(y);  // null-safe: renamed-rec subtrees are untyped
            if (ty) {
                interval I = ty->getInterval();
                if ((int)I.lo() < K && (int)I.hi() >= excursion) {
                    return sigDelay(x, sigMax(y, sigInt(K)));
                }
            }
        }
        return t;
    });
}

/*****************************************************************************
 prepare
 *****************************************************************************/

static bool isConditionBoundary(Tree t);  // defined with the lazy-select machinery below

/**
 * -gatequiv (spec LA-PAIRE-CANONIQUE) : c*y (c boolean) and
 * select2(c,0,y) are two SPELLINGS of the gated signal -- worth y when
 * c, 0 otherwise. What is compiled is the meaning, not the spelling :
 * the weight of the EXCLUSIVE STATELESS CROWN of y picks the form. Fat
 * crown (> tau) : the select2 spelling, whose sides the lazy emission
 * may guard. Thin crown : the multiplicative spelling -- branch-free,
 * it melts into the arithmetic stream and vectorizes. One shared tau :
 * confluence, no ping-pong, one pass.
 */
static bool gatequivBool(Tree c)
{
    int  op, i;
    Tree x, y;
    if (isSigBinOp(c, &op, x, y)) {
        if (isBoolOpcode(op)) {
            return true;  // comparisons are 0/1 by construction
        }
        if (op == kAND || op == kOR) {
            return gatequivBool(x) && gatequivBool(y);
        }
        return false;
    }
    if (isSigIntCast(c, x) || isSigFloatCast(c, x)) {
        // casts preserve 0/1 -- the multiplicative spelling wraps its
        // boolean in a float cast (float(check == 0))
        return gatequivBool(x);
    }
    if (isSigInt(c, &i)) {
        return i == 0 || i == 1;
    }
    return false;
}

static Tree gatequivNormalize(Tree L)
{
    // ---- shared helpers ------------------------------------------------
    // consumer lists over a tree (rec bodies descended explicitly --
    // letrec does not expose its definitions through arity)
    auto buildConsumers = [](Tree root) {
        std::map<Tree, std::vector<Tree>> consumers;
        std::set<Tree>                    seen;
        std::function<void(Tree)>         walk = [&](Tree t) {
            if (!seen.insert(t).second) {
                return;
            }
            Tree var, body;
            if (isRec(t, var, body)) {
                if (body != nullptr) {
                    consumers[body].push_back(t);
                    walk(body);
                }
                return;
            }
            for (int k = 0; k < t->arity(); k++) {
                consumers[t->branch(k)].push_back(t);
                walk(t->branch(k));
            }
        };
        walk(root);
        return consumers;
    };

    // the INTERNAL gate node -- introduced in phase 1, eliminated in
    // phase 3, never escapes the pass (asserted)
    static Sym GQGATE = symbol("GateQuivInternal");
    auto       gate   = [](Tree c, Tree y) { return tree(GQGATE, c, y); };
    auto       isGate = [](Tree t, Tree& c, Tree& y) { return isTree(t, GQGATE, c, y); };

    auto stripCasts = [](Tree c) {
        Tree x;
        while (isSigIntCast(c, x) || isSigFloatCast(c, x)) {
            c = x;
        }
        return c;
    };
    auto isZeroNum = [](Tree t) {
        int    i;
        double r;
        return (isSigInt(t, &i) && i == 0) || (isSigReal(t, &r) && r == 0.0);
    };
    auto isOneNum = [](Tree t) {
        int    i;
        double r;
        return (isSigInt(t, &i) && i == 1) || (isSigReal(t, &r) && r == 1.0);
    };

    // exclusive stateless crown weight of y under the gating site (the
    // consumers map must match the tree being weighed)
    auto crownWeight = [&](Tree y, Tree site,
                           std::map<Tree, std::vector<Tree>>& consumers) -> int {
        std::set<Tree>            cone;
        std::function<void(Tree)> collect = [&](Tree t) {
            if (cone.count(t)) {
                return;
            }
            Tree tb, ix;
            if (isSigRDTbl(t, tb, ix)) {
                cone.insert(t);
                collect(ix);
                return;
            }
            if (isConditionBoundary(t)) {
                return;
            }
            cone.insert(t);
            for (int k = 0; k < t->arity(); k++) {
                collect(t->branch(k));
            }
        };
        collect(y);
        bool moved = true;
        while (moved) {
            moved = false;
            std::vector<Tree> out;
            for (Tree t : cone) {
                if (t == y) {
                    continue;
                }
                for (Tree pc : consumers[t]) {
                    if (pc != site && cone.count(pc) == 0) {
                        out.push_back(t);
                        break;
                    }
                }
            }
            for (Tree t : out) {
                cone.erase(t);
                moved = true;
            }
        }
        int w = 0;
        for (Tree t : cone) {
            int  op2;
            Tree a2, b2, s2, tb2, ix2;
            if (isSigBinOp(t, &op2, a2, b2) || isSigIntCast(t, a2) || isSigFloatCast(t, a2) ||
                isSigBitCast(t, a2) || isSigSelect2(t, s2, a2, b2) || isSigRDTbl(t, tb2, ix2) ||
                (getUserData(t) != nullptr && t->arity() > 0)) {
                w++;
            }
        }
        return w;
    };

    // ---- phase 1 : TRANSLATION into the object -------------------------
    // both spellings (and the mirror) become gate(c, y) ; c stripped of
    // its wrapping casts (the multiplicative spelling wraps its boolean
    // in float())
    {
        std::unordered_map<Tree, Tree>  memo;
        std::function<Tree(Tree, Tree)> t1 = [&](Tree orig, Tree rebuilt) -> Tree {
            int  op;
            Tree a, b, sel, x, y;
            if (isSigBinOp(orig, &op, a, b) && op == kMul) {
                int  op2;
                Tree ra, rb;
                isSigBinOp(rebuilt, &op2, ra, rb);
                if (gatequivBool(a)) {
                    return gate(stripCasts(ra), rb);
                }
                if (gatequivBool(b)) {
                    return gate(stripCasts(rb), ra);
                }
            }
            if (isSigSelect2(orig, sel, x, y) && gatequivBool(sel)) {
                Tree rs, rx, ry;
                isSigSelect2(rebuilt, rs, rx, ry);
                if (isZeroNum(x)) {
                    return gate(stripCasts(rs), ry);  // select2(c, 0, y) : y when c
                }
                if (isZeroNum(y)) {
                    // mirror : select2(c, x, 0) = x when NOT c
                    return gate(sigBinOp(kEQ, stripCasts(rs), sigInt(0)), rx);
                }
            }
            return rebuilt;
        };
        L = treeRewritePaired(L, t1, memo);
    }

    // ---- phase 2 : NORMALIZATION, growth-oriented ----------------------
    // the algebra never shrinks a gate : conjunction of nested gates,
    // fusion of same-condition sisters under sums, absorption of
    // NUMERIC factors (general pure-exclusive absorption : v2)
    {
        std::unordered_map<Tree, Tree>  memo;
        std::function<Tree(Tree, Tree)> t2 = [&](Tree orig, Tree rebuilt) -> Tree {
            Tree c, y, d, z, a, b;
            if (isGate(rebuilt, c, y)) {
                if (isOneNum(c)) {
                    return y;
                }
                if (isZeroNum(c)) {
                    return sigInt(0);
                }
                if (isGate(y, d, z)) {
                    return gate(sigBinOp(kAND, c, d), z);
                }
            }
            int op;
            if (isSigBinOp(rebuilt, &op, a, b)) {
                Tree c1, y1, c2, y2;
                if (op == kAdd && isGate(a, c1, y1) && isGate(b, c2, y2) && c1 == c2) {
                    return gate(c1, sigBinOp(kAdd, y1, y2));  // sister fusion
                }
                if (op == kMul) {
                    if (isNum(a) && isGate(b, c1, y1)) {
                        return gate(c1, sigBinOp(kMul, a, y1));  // absorption
                    }
                    if (isNum(b) && isGate(a, c1, y1)) {
                        return gate(c1, sigBinOp(kMul, y1, b));
                    }
                }
            }
            return rebuilt;
        };
        L = treeRewritePaired(L, t2, memo);
    }

    // ---- phase 3 : SPELLING by crown weight, AFTER fusion --------------
    const int tau = 12;
    {
        auto consumers = buildConsumers(L);
        std::unordered_map<Tree, Tree>  memo;
        std::function<Tree(Tree, Tree)> t3 = [&](Tree orig, Tree rebuilt) -> Tree {
            Tree c, y;
            if (isGate(rebuilt, c, y)) {
                Tree co, yo;
                // weigh on the ORIGINAL tree (the consumers map's world) ;
                // fall back to the rebuilt one for gates born in phase 2
                Tree wy = isGate(orig, co, yo) ? yo : y;
                Tree ws = isGate(orig, co, yo) ? orig : rebuilt;
                if (crownWeight(wy, ws, consumers) > tau) {
                    return sigSelect2(c, sigInt(0), y);
                }
                return sigBinOp(kMul, c, y);
            }
            return rebuilt;
        };
        L = treeRewritePaired(L, t3, memo);
    }

    // ---- the object never escapes --------------------------------------
    {
        std::set<Tree>            seen;
        std::function<void(Tree)> check = [&](Tree t) {
            if (!seen.insert(t).second) {
                return;
            }
            Tree c, y, var, body;
            if (isTree(t, GQGATE, c, y)) {
                faustexception("gatequiv : internal gate node escaped the pass\n");
            }
            if (isRec(t, var, body)) {
                if (body != nullptr) {
                    check(body);
                }
                return;
            }
            for (int k = 0; k < t->arity(); k++) {
                check(t->branch(k));
            }
        };
        check(L);
    }
    return L;
}

static bool displayTailCarries(Tree t);

/**
 * -xtemp : the explicit temporaries pass (LES-TEMPORAIRES 7, step 1). Every node
 * the cache would store becomes temp(node) ; the roots are rewritten, the
 * annotations redone, the analyses replayed by the caller's `reanalyse`.
 */
Tree ScalarCompiler::placeExplicitTemps(Tree L2, Tree Lx, std::function<void(Tree)> reanalyse)
{
    // -xtemp, the explicit temporaries pass (LES-TEMPORAIRES 7, step 1 :
    // reproduction). Every node the emitter's cache would STORE -- of a
    // kind whose generator consults the cache, read without delay and
    // shared (sharing count > 1, or occurrences in more than one place
    // or in a faster context), or read with delay and shared -- becomes
    // temp(node) ; the emitter obeys the temp (forceCacheCode) and its
    // cache stores nothing else. The decision is thus a transformation
    // of the signals, inspectable and testable ; the policy can then
    // leave the cache's rule (register pressure, recomputation).
    startTiming("explicit temps");
    // the display crown : the stateless nodes between a bargraph and its
    // capture points are computed in the block-rate tail (computeDisplayFrontier,
    // displayExpr). A node that lives ONLY there is never a loop temporary --
    // the cache never stored it either, and a temp would move it from once
    // per block to once per sample (windchimes : a sigmoid). A crown node
    // also reached from the audio side is stored in the loop as before.
    std::set<Tree> crown, audio;
    if (fDisplayList != nullptr && isList(fDisplayList)) {
        std::vector<Tree> work;
        for (Tree l = fDisplayList; isList(l); l = tl(l)) {
            Tree path, mn, mx, x;
            if (isSigVBargraph(hd(l), path, mn, mx, x) || isSigHBargraph(hd(l), path, mn, mx, x)) {
                work.push_back(x);
            }
        }
        std::set<Tree> walked;
        while (!work.empty()) {
            Tree t = work.back();
            work.pop_back();
            if (!walked.insert(t).second || getCertifiedSigType(t)->variability() < kSamp) {
                continue;
            }
            int  i;
            Tree x, y, g;
            tvec V;
            if (isProj(t, &i, g) || isSigDelay(t, x, y) || isSigPrefix(t, x, y) || isSigFIR(t, V) || isSigIIR(t, V) ||
                !displayTailCarries(t)) {
                continue;  // a capture point : loop-computed below it
            }
            crown.insert(t);
            for (int k = 0; k < t->arity(); k++) {
                work.push_back(t->branch(k));
            }
        }
        if (!crown.empty()) {
            // the audio reach : from the outputs and the display state roots,
            // the same descent as the walk below
            std::vector<Tree> work2{L2};
            for (Tree sd : fDisplayStateful) {
                work2.push_back(sd);
            }
            std::unordered_map<Tree, Tree> parent;  // trace only : how the audio side reaches a node
            while (!work2.empty()) {
                Tree t = work2.back();
                work2.pop_back();
                if (!audio.insert(t).second) {
                    continue;
                }
                if (isList(t) || isNil(t)) {
                    for (int k = 0; k < t->arity(); k++) {
                        work2.push_back(t->branch(k));
                    }
                    continue;
                }
                tvec subs;
                Tree size, gen, wi, ws, ax, ay;
                if (isSigWRTbl(t, size, gen, wi, ws)) {
                    subs.push_back(size);
                    if (wi != gGlobal->nil) {
                        subs.push_back(wi);
                        subs.push_back(ws);
                    }
                } else if (isSigAttach(t, ax, ay)) {
                    // the attached signal is display-side only : the audio
                    // path carries the first argument alone
                    subs.push_back(ax);
                } else if (Tree lbl, mn, mx; isSigHBargraph(t, lbl, mn, mx, ax) || isSigVBargraph(t, lbl, mn, mx, ax)) {
                    // the audio path reads the bargraph's VARIABLE (block
                    // rate, the legacy design) : its value is the display
                    // list's, computed in the tail from the captures
                } else if (!isSigGen(t)) {
                    getSubSignals(t, subs);
                }
                for (Tree b : subs) {
                    if (parent.find(b) == parent.end()) {
                        parent[b] = t;
                    }
                    work2.push_back(b);
                }
            }
            if (global::isOpt("FAUST_XTEMP_TRACE")) {
                // the first crown node the audio side reaches, and its path
                for (Tree c : crown) {
                    if (audio.count(c)) {
                        fprintf(stderr, "xtemp : crown node reached from the audio side ; the path from the root :\n");
                        std::vector<Tree> path;
                        for (Tree u = c; u != nullptr; u = (parent.count(u) ? parent[u] : nullptr)) {
                            path.push_back(u);
                        }
                        for (auto it = path.rbegin(); it != path.rend(); ++it) {
                            std::stringstream ss;
                            ss << ppsig(*it, 24);
                            fprintf(stderr, "xtemp :     %s\n", ss.str().c_str());
                        }
                        break;
                    }
                }
            }
        }
    }
    std::set<Tree, treeorder> wrap;
    {
        std::set<Tree>    seen;
        std::vector<Tree> work{Lx};
        while (!work.empty()) {
            Tree t = work.back();
            work.pop_back();
            if (!seen.insert(t).second) {
                continue;
            }
            if (isList(t) || isNil(t)) {
                for (int k = 0; k < t->arity(); k++) {
                    work.push_back(t->branch(k));
                }
                continue;
            }
            if (cacheWouldStore(t) && !(crown.count(t) > 0 && audio.count(t) == 0)) {
                wrap.insert(t);
            } else if (global::isOpt("FAUST_XTEMP_TRACE")) {
                // the shared nodes the pass leaves alone, with the reason
                Occurrences* o = fOccMarkup->retrieve(t);
                int sh = getSharingCount(t, fSharingKey);
                if (sh > 1 || (o && o->hasMultiOccurrences())) {
                    std::stringstream ss;
                    ss << ppsig(t, 40);
                    fprintf(stderr, "xtemp :   skipped (kind %d, occ %d, sharing %d, multi %d, maxd %d) : %s\n", (int)passCoversKind(t), o ? 1 : 0, sh,
                            o ? (int)o->hasMultiOccurrences() : -1, o ? o->getMaxDelay() : -1, ss.str().c_str());
                }
            }
            // the same descent as the analyses : sub-signals, not
            // structural branches -- and never INTO a table generator :
            // its content is compiled by its own sub-container, whose
            // own analysis (prepare2) runs this pass again on it. The
            // main-level sharing of a generator (the same waveform under
            // two tables) is not a sharing the sub-container sees.
            tvec subs;
            Tree size, gen, wi, ws;
            if (isSigWRTbl(t, size, gen, wi, ws)) {
                subs.push_back(size);
                if (wi != gGlobal->nil) {
                    subs.push_back(wi);
                    subs.push_back(ws);
                }
            } else if (!isSigGen(t)) {
                getSubSignals(t, subs);
            }
            for (Tree b : subs) {
                work.push_back(b);
            }
        }
    }
    if (!wrap.empty()) {
        std::unordered_map<Tree, Tree> memo;
        auto defRule = [](Tree, Tree rebuilt) -> Tree { return rebuilt; };
        auto rule    = [&](Tree orig, Tree rebuilt) -> Tree {
            return wrap.count(orig) ? sigTemp(rebuilt) : rebuilt;
        };
        // the rewrite stops at the same boundary as the walk : a table's
        // generator is rebuilt untouched (its own sub-container decides
        // its temporaries), the other branches go through the rewrite --
        // a waveform shared between a table's content and the main graph
        // (table2) is wrapped in the main graph only
        std::function<std::optional<Tree>(Tree)> pre;
        pre = [&](Tree t) -> std::optional<Tree> {
            Tree size, gen, wi, ws;
            if (isSigWRTbl(t, size, gen, wi, ws)) {
                Tree nsize = treeRewritePairedMemo(size, pre, rule, memo, defRule);
                Tree nwi   = (wi == gGlobal->nil) ? wi : treeRewritePairedMemo(wi, pre, rule, memo, defRule);
                Tree nws   = (ws == gGlobal->nil) ? ws : treeRewritePairedMemo(ws, pre, rule, memo, defRule);
                return sigWRTbl(nsize, gen, nwi, nws);
            }
            return std::nullopt;
        };
        L2 = treeRewritePairedMemo(L2, pre, rule, memo, defRule);
        for (Tree& sd : fDisplayStateful) {
            sd = treeRewritePairedMemo(sd, pre, rule, memo, defRule);
        }
        if (fDisplayList != nullptr) {
            fDisplayList = treeRewritePairedMemo(fDisplayList, pre, rule, memo, defRule);
        }
        // the rewrite made new trees : every annotation the emitters read
        // is recomputed, in the order of the first preparation above ;
        // the display sets that named the old trees are remapped or
        // recomputed (stale capture points pointed into cones the
        // analyses no longer reach : vumeter crashed on them)
        fConditionProperty.clear();
        conditionAnnotation(L2);
        recursivnessAnnotation(L2);
        typeAnnotation(L2, true);
        {
            std::set<Tree> preserved;
            for (Tree t : fDisplayPreserved) {
                auto it = memo.find(t);
                preserved.insert(it != memo.end() ? it->second : t);
            }
            fDisplayPreserved = preserved;
            fDisplayCapturePoints.clear();
            fDisplayCaptures.clear();
        }
        if (fDisplayList != nullptr && isList(fDisplayList)) {
            recursivnessAnnotation(fDisplayList);
            typeAnnotation(fDisplayList, false);
            computeDisplayFrontier();
        }
        for (Tree sd : fDisplayStateful) {
            recursivnessAnnotation(sd);
            typeAnnotation(sd, false);
        }
        reanalyse(L2);
    }
    if (global::isOpt("FAUST_XTEMP_TRACE")) {
        fprintf(stderr, "xtemp : %zu temporaries placed (crown %zu nodes, audio reach %zu)\n", wrap.size(), crown.size(), audio.size());
        for (Tree t : wrap) {
            Occurrences* o = fOccMarkup->retrieve(t);
            std::stringstream ss;
            ss << ppsig(t, 40);
            fprintf(stderr, "xtemp :   sharing %d multi %d maxd %d crown %d audio %d : %s\n", getSharingCount(t, fSharingKey),
                    o ? (int)o->hasMultiOccurrences() : -1, o ? o->getMaxDelay() : -1, (int)crown.count(t), (int)audio.count(t),
                    ss.str().c_str());
        }
        // the display cones must be marked like the audio path : name
        // the first node of a capture cone the analyses did not reach
        int unmarked = 0;
        for (Tree p : fDisplayCapturePoints) {
            std::set<Tree>    seen;
            std::vector<Tree> work{p};
            while (!work.empty()) {
                Tree t = work.back();
                work.pop_back();
                if (!seen.insert(t).second || isList(t) || isNil(t) || t->arity() == 0) {
                    continue;
                }
                if (!fOccMarkup->retrieve(t)) {
                    if (unmarked++ == 0) {
                        std::stringstream ss;
                        ss << t->node();
                        fprintf(stderr, "xtemp : unmarked display node %s (temp: %d, in wrap: %d)\n", ss.str().c_str(), (int)isSigTemp(t), (int)wrap.count(t));
                    }
                }
                tvec subs;
                int  n = getSubSignals(t, subs);
                for (int k = 0; k < n; k++) {
                    work.push_back(subs[k]);
                }
            }
        }
        fprintf(stderr, "xtemp : %zu capture points, %d unmarked nodes in their cones\n", fDisplayCapturePoints.size(), unmarked);
    }
    endTiming("explicit temps");
    return L2;
}

static bool famAccessesGroup(Tree n, Tree group);
static bool famReadsGroupNow(Tree n, Tree group);

Tree ScalarCompiler::prepare(Tree LS)
{
    startTiming("prepare");
    Tree L1 = simplifyToNormalForm(LS);

    // dump normal form
    if (gGlobal->gDumpNorm == 0) {
        cout << ppsig(L1) << endl;
        throw faustexception("Dump normal form finished...\n");
    } else if (gGlobal->gDumpNorm == 1) {
        ppsigShared(L1, cout);
        throw faustexception("Dump shared normal form finished...\n");
    } else if (gGlobal->gDumpNorm == 2) {
        // Print signal tree type
        SignalTypePrinter printer(L1);
        throw faustexception("Dump signal type finished...\n");
    }
    // No more table privatisation
    Tree L2 = newConstantPropagation(L1);


    // enable/control escape hatch for the standalone -lsum path : the sum
    // restructuring interacts with the enable cut (osc_enable : a disabled
    // branch leaked its last value instead of 0). enable/control are slated
    // for removal -- no investment ; the option simply steps aside.
    auto hasEnableControl = [](Tree sigs) -> bool {
        std::set<Tree>            seen;
        bool                      found = false;
        std::function<void(Tree)> walk = [&](Tree t) {
            if (found || !seen.insert(t).second) {
                return;
            }
            Tree x, y, var, body;
            if (isSigEnable(t, x, y) || isSigControl(t, x, y)) {
                found = true;
                return;
            }
            if (isRec(t, var, body)) {
                if (body != nullptr) {
                    walk(body);
                }
                return;
            }
            for (int k = 0; k < t->arity(); k++) {
                walk(t->branch(k));
            }
        };
        walk(sigs);
        return found;
    };
    if (gGlobal->gLowerSums && !gGlobal->gReconstructFIRIIRs && !gGlobal->gFamilyForm &&
        !hasEnableControl(L2)) {
        // -lsum STANDALONE (the old_freeverb bisection, 2026-08-18) :
        // lowerSums was trapped inside the -fir reveal lambda -- alone it
        // was a silent no-op. It needs revealSum's n-ary rows but NOT the
        // kernel injection (-fir costs +46 muls on old_freeverb : kernels
        // revealed where they do not pay). Own big-stack thread, the
        // reveal precedent.
        std::function<void()> lsOnly = [&]() {
            startTiming("Sum revealer (lsum standalone)");
            L2 = revealSum(L2, true);  // the dispatch follows : gather through the sharing
            endTiming("Sum revealer (lsum standalone)");
            startTiming("Sum lowering");
            std::set<Tree> keepRows;
            if (gGlobal->gMatrixRows) {
                // matrix rows stay n-ary through the lowering : the -ls
                // row-op regime consumes them whole (spec LA-FORME-MATRICE)
                for (auto& [row, id] : revealMatrix(L2).rowOf) {
                    keepRows.insert(row);
                }
            }
            L2 = lowerSums(L2, keepRows.empty() ? nullptr : &keepRows);
            endTiming("Sum lowering");
        };
        callWithLargeStack(lsOnly);
    }
    if (gGlobal->gGateEquiv) {
        // spec LA-PAIRE-CANONIQUE : the canonical form of the gated
        // signal, by exclusive stateless crown weight. Own big-stack
        // thread : the crown and consumer walks are as deep as the
        // signal graph.
        std::function<void()> gq = [&]() {
            startTiming("gatequiv");
            L2 = gatequivNormalize(L2);
            endTiming("gatequiv");
        };
        callWithLargeStack(gq);
    }
    if (gGlobal->gFamilyForm && gGlobal->gReconstructFIRIIRs) {
        // FAMILIES FIRST, KERNELS AFTER (LES-AUTOMATES §9), at the place of
        // the reveal block so that the rest of the pipeline is -fir's : the
        // plan on the view of the tree as it is (the display roots are not
        // harvested yet : the sum, output and automaton families only --
        // the display families stay with -fam alone), then the kernel
        // passes of -fir around the families, frozen ; the plan is not made
        // again (fFamPlanned), its nodes are the tree's, checked after the
        // harvest (famCheckPlanned)
        startTiming("families first");
        conditionAnnotation(L2);  // the typed plan refuses a conditional template
        fFamRoot = L2;
        planFamilies();
        fFamPlanned = true;
        L2 = famKernelizeOutside(L2);
        fConditionProperty.clear();  // the passes rebuilt trees : the annotation below starts afresh (it merges)
        endTiming("families first");
    }
    if ((gGlobal->gReconstructFIRIIRs && !gGlobal->gFamilyForm) ||
        (gGlobal->gFamilyForm && gGlobal->gLowerSums && !gGlobal->gReconstructFIRIIRs)) {
        // -fir stage 1 : the revealed kernels are INJECTED into the
        // pipeline -- n-ary sums (revealSum) then FIR kernels (revealFIR).
        // revealIIR waits for its typing rule (WCPG, see PILE n.12). The
        // reveal recursions are as deep as the signal graph : dedicated
        // big-stack thread, joined immediately (thunder, drumkit).
        // -fam ALONE does not come here : it plans its families on a view of
        // the tree revealed at plan time and emits the tree itself, so that
        // it changes nothing outside its families (the flattened sums it
        // left behind cost pluckedString x2.4, fdnRev x1.85 under g++ 15
        // with no family at all) ; -fam -lsum reveals here and lowers with
        // the family sums kept n-ary ; -fam -fir neither : families first,
        // kernels after, at the end of the preparation (famKernelizeOutside).
        std::function<void()> reveal = [&]() {
            startTiming("Sum revealer");
            // gather through the shared sub-sums only when lowerSums rebuilds
            // the sharing below ; alone, -fir keeps them as atoms
            L2 = revealSum(L2, gGlobal->gLowerSums);
            endTiming("Sum revealer");
            if (!gGlobal->gReconstructFIRIIRs) {
                // -fam -lsum : the revealed sums and nothing else ; the plan
                // pairs a sum's operands in a structural order, the tree is
                // not rebuilt (a rebuild would reorder the schedule of every
                // program, family or not)
            } else {
            startTiming("FIR revealer");
            L2 = revealFIR(L2);
            endTiming("FIR revealer");
            startTiming("IIR revealer");
            L2 = revealIIR(L2);
            endTiming("IIR revealer");
            if (gGlobal->gFIRHoist) {
                startTiming("Numerator hoisting");
                L2 = hoistCommonNumerators(L2);  // LE-NUMERATEUR-COMMUN
                endTiming("Numerator hoisting");
            }
            startTiming("FIR factorizer");
            L2 = factorizeFIRs(L2);
            // the kernels without coefficient go back to the sums, where the
            // dispatch below shares them ; BEFORE the retiming law, which is a
            // law of kernels. The classic emitter only : the split emitter
            // reads a kernel's history from its informed delay line, and the
            // dissolved sum costs it dearly (vocoder under its fused g++
            // tariff : 27 -> 111 ns). And only with the dispatch : under -fir
            // alone the +-1 multiplications it saves are not worth the
            // spelling it changes (englishBell under clang 22 : 51 -> 142 ns,
            // the SLP packing of the modes lost)
            if (!gGlobal->gLoopSplit && gGlobal->gLowerSums) {
                L2 = dissolveUnitKernels(L2);
            }
            L2 = kernelCandidacy(L2);  // the retiming law, per site
            endTiming("FIR factorizer");
            }
            if (gGlobal->gLowerSums) {
                // experimental co-occurrence lowering : the n-ary sums
                // become binary adds whose shared pairs and canonical
                // prefixes rebuild the structural sharing the flattening
                // destroyed (fdnRev : 823 -> 3056 additions without it)
                startTiming("Sum lowering");
                std::set<Tree> keepRows;
                if (gGlobal->gMatrixRows) {
                    // matrix rows stay n-ary through the lowering : the
                    // -ls row-op regime consumes them whole (spec
                    // LA-FORME-MATRICE)
                    for (auto& [row, id] : revealMatrix(L2).rowOf) {
                        keepRows.insert(row);
                    }
                }
                if (gGlobal->gFamilyForm) {
                    // the family sums and their members' own sums stay
                    // n-ary : a lowered family is not seen (LA-FORME-FAMILLE)
                    for (Tree t : famKeepSums(L2)) {
                        keepRows.insert(t);
                    }
                }
                L2 = lowerSums(L2, keepRows.empty() ? nullptr : &keepRows);
                endTiming("Sum lowering");
            }
        };  // fin du lambda reveal (-fir)
        callWithLargeStack(reveal);
    }

    startTiming("conditionAnnotation");
    conditionAnnotation(L2);
    endTiming("conditionAnnotation");

    startTiming("recursivnessAnnotation");
    recursivnessAnnotation(L2);  // Annotate L2 with recursivness information
    endTiming("recursivnessAnnotation");

    // Both emitters carry the harvested tail : the classic one captures
    // at the end of its loop body, the split one reads the last element
    // of each capture's vector once per chunk (a split emission that
    // dropped the tail was the FFT "miracle" of the August campaigns : a
    // display-only FFT that was no longer computed).
    {
        // spec SIGNAUX-ATTACHES (default since 2026-08-17) : harvest D,
        // dissolve attach and bargraph decorations from the audio path,
        // BEFORE typing (the rebuild creates new trees).
        startTiming("display harvest");
        L2 = harvestDisplay(L2);
        endTiming("display harvest");
        // the harvest rebuilds the trees : every annotation the emitters
        // read must be recomputed on the new world -- INCLUDING the
        // condition property, CLEARED first : conditionAnnotation MERGES
        // (_OR_), so a plain re-run keeps the stale atoms alive. Stale
        // atoms reference the pre-harvest trees : their cones are not in
        // the schedule, and their delayed reads name writers nobody ever
        // compiles (the gate_compressor phantom -- a second, undeclared
        // copy of the whole gate machinery).
        fConditionProperty.clear();
        conditionAnnotation(L2);
        recursivnessAnnotation(L2);
        if (fFamPlanned) {
            famCheckPlanned(L2);  // a family whose nodes the harvest rebuilt is dismantled
        }
    }
    startTiming("L2 typeAnnotation");
    typeAnnotation(L2, true);  // Annotate L2 with type information and check causality
    endTiming("L2 typeAnnotation");
    if (fDisplayList != nullptr && isList(fDisplayList)) {
        // the display cones need every annotation the emitters read
        recursivnessAnnotation(fDisplayList);
        typeAnnotation(fDisplayList, false);
        computeDisplayFrontier();
    }

    if (gGlobal->gMinDelay > 0) {
        // semantic delay floor: needs the intervals just computed, rebuilds
        // trees, so the annotations are redone in the same order as above
        L2 = fFamPlanned ? famAround(L2, [](Tree L) { return applyDelayFloor(L, gGlobal->gMinDelay); })
                         : applyDelayFloor(L2, gGlobal->gMinDelay);
        conditionAnnotation(L2);
        recursivnessAnnotation(L2);
        typeAnnotation(L2, true);
    }

    if (gGlobal->gReassoc) {
        // -reassoc : late state-join (see reassociate.cpp) -- BEFORE the
        // staging pass, so barriers see the final tree shapes
        startTiming("reassociate");
        L2 = fFamPlanned ? famAround(L2, [](Tree L) { return reassociate(L); }) : reassociate(L2);
        endTiming("reassociate");
        conditionAnnotation(L2);
        recursivnessAnnotation(L2);
        typeAnnotation(L2, true);
    }

    if (gGlobal->gTempOps > 0) {
        // -temp <K> : the staging transformation -- deep single-use
        // expressions gain a sigTemp barrier (K=1 : every operation, the
        // SSA form). Placed AFTER the normal form (temp is opaque to the
        // rewrite rules) and BEFORE sharing/occurrences, which count the
        // barriers like any node. Annotations are redone : the placement
        // rebuilds trees.
        startTiming("placeTemps");
        L2 = fFamPlanned ? famAround(L2, [](Tree L) { return placeTemps(L, gGlobal->gTempOps); })
                         : placeTemps(L2, gGlobal->gTempOps);
        endTiming("placeTemps");
        conditionAnnotation(L2);
        recursivnessAnnotation(L2);
        typeAnnotation(L2, true);
    }

    // -lazyselect : the synthesized condition atoms (sel==0, sel!=0) are
    // compiled like any signal by the guarded statements -- they need
    // sharing counts and occurrence marks. Both analyses run ONCE on an
    // extended root list (mark() regenerates its property key, a second
    // call would lose the first).
    // the roots and the two analyses (sharing, occurrences) as one replayable
    // step : the explicit temporaries pass below rewrites the trees and
    // replays it on the wrapped roots
    Tree Lx = nullptr;
    auto analyseRoots = [&](Tree L2) {
        Lx = L2;
        for (Tree sd : fDisplayStateful) {
            // spec SIGNAUX-ATTACHES : S compiles at audio rate -- same
            // extended-root pattern as the lazy-select condition atoms
            Lx = cons(sd, Lx);
        }
        if (fDisplayList != nullptr) {
            // the display list itself joins the sharing/occurrence roots :
            // the marks compile nothing (the schedule does), but the tail
            // emitter's CS() on slow and constant nodes reads them
            // (generateNumber consults getMaxDelay -- null without a mark)
            for (Tree l = fDisplayList; isList(l); l = tl(l)) {
                Tree path, mn, mx, x;
                if (isSigVBargraph(hd(l), path, mn, mx, x) ||
                    isSigHBargraph(hd(l), path, mn, mx, x)) {
                    Lx = cons(hd(l), Lx);  // widget items : declaration-only, no marks needed
                }
            }
        }
        if (!fDisplayStateful.empty() || fDisplayList != nullptr) {
            recursivnessAnnotation(Lx);
            typeAnnotation(Lx, false);
        }
        if (gGlobal->gSelectN) {
            // spec LE-SELECTN : the multiplex atoms must be compilable even
            // when the 4-atom cliff collapsed a branch's condition to nil
            // (the property then no longer carries them, but the emission
            // still guards its assignments with them). They join the
            // sharing/occurrence roots directly from the side table ; the
            // gLazySelect block below runs the annotations on the final Lx.
            for (const auto& e : fSelectNInfo) {
                Lx = cons(e.second.selEff, Lx);
                for (const auto& lf : e.second.leaves) {
                    for (Tree a : lf.atoms) {
                        Lx = cons(a, Lx);
                    }
                }
            }
        }
        if (gGlobal->gLazySelect) {
            std::set<Tree, treeorder> atoms;
            for (const auto& pc : fConditionProperty) {
                for (Tree cc = pc.second; cc && isList(cc); cc = tl(cc)) {
                    for (Tree at = hd(cc); at && isList(at); at = tl(at)) {
                        atoms.insert(hd(at));
                    }
                }
            }
            for (Tree a : atoms) {
                Lx = cons(a, Lx);
            }
            // the atoms are compiled : they need every annotation the emitter
            // reads -- types, recursivness (memoized for the L2 part)
            recursivnessAnnotation(Lx);
            typeAnnotation(Lx, gGlobal->gLocalCausalityCheck);
        }

        startTiming("sharingAnalysis");
        sharingAnalysis(Lx, fSharingKey);  // Annotate L2 (+ condition atoms) with sharing count
        endTiming("sharingAnalysis");

        startTiming("occurrences analysis");
        delete fOccMarkup;
        if (gGlobal->gLazySelect) {
            // REFINED design : conditions must never influence caching. The
            // condition-aware markup (built for enable, whose semantics
            // REQUIRES materialization) forces any node used under two
            // different conditions into a cached statement -- on select
            // cascades this shattered the inline world (vocal : 87 -> 1422
            // statements). Under -lazyselect the markup runs condition-BLIND
            // (df-identical inline/statement partition) ; the conditions,
            // computed separately, only GUARD the statements that exist
            // anyway (getConditionCode at the Statement sites).
            fOccMarkup = new OccMarkup();
        } else {
            fOccMarkup = new OccMarkup(fConditionProperty);
        }
        if (gGlobal->gIIRTransposed && !gGlobal->gLoopSplit) {
            // Under -ls the election stands down : the split emitter only knows
            // the DIRECT form, whose buffers are sized by the occurrence
            // self-marks the election would have skipped.
            // TOPOLOGY election (one judge for occurrences AND emission) : an
            // order>=2 IIR kernel whose history nobody reads from outside --
            // no sigDelay on it, never the source of a multi-tap FIR -- takes
            // the TRANSPOSED all-pole form (scalar state chain, no delay
            // line). The others keep the direct form ; the campaign of
            // 2026-08-10 showed the transposed form LOSES when the delay
            // line must survive for external readers (modal banks +25..58%)
            // and wins ~20% when it disappears (tester/tester2).
            std::set<Tree>    readers;  // IIRs with an external delayed read
            std::set<Tree>    seen;
            std::vector<Tree> work{Lx};
            while (!work.empty()) {
                Tree t = work.back();
                work.pop_back();
                if (!seen.insert(t).second) {
                    continue;
                }
                Tree x, d;
                tvec cs, dd;
                if (isSigDelay(t, x, d) && isSigIIR(x, dd)) {
                    readers.insert(x);
                } else if (kernelWorkVec(t, cs) && cs.size() >= 3 && isSigIIR(cs[0], dd)) {
                    // kernels read their source at delays 0..n-1
                    readers.insert(cs[0]);
                }
                for (int k = 0; k < t->arity(); k++) {
                    work.push_back(t->branch(k));
                }
            }
            for (Tree t : seen) {
                if (tvec cs; isSigIIR(t, cs)) {
                    int order = 0, taps = 0;
                    for (size_t k = 3; k < cs.size(); k++) {
                        if (!isZero(cs[k])) {
                            order = int(k) - 2;
                            taps++;
                        }
                    }
                    // DENSITY guard : the transposed form carries one state per
                    // unit of order, shifted every sample, where the direct form
                    // pays one product per nonzero tap and a delay line. A sparse
                    // recurrence (a feedback loop through long delays : order in
                    // the hundreds, one tap) would become hundreds of scalar
                    // states -- a loop body the C compiler cannot even allocate
                    // in reasonable time. Half the order in taps, at least.
                    if (order >= 2 && 2 * taps >= order && readers.count(t) == 0) {
                        Tree key = tree(symbol("SIGIIRTRANSPOSED"));
                        Tree one = tree(1);
                        t->setProperty(key, one);
                    }
                }
            }
        }
        fOccMarkup->mark(Lx);  // Annotate L2 (+ condition atoms) with occurrences analysis
        endTiming("occurrences analysis");
    };
    analyseRoots(L2);

    if (gGlobal->gExplicitTemps) {
        L2 = placeExplicitTemps(L2, Lx, [&](Tree L) { analyseRoots(L); });
    }

    endTiming("prepare");

    if (gGlobal->gDrawSignals) {
        if (gGlobal->gDrawRetiming) {
            startTiming("retiming");
            Tree L3 = sigRetiming(L2);
            endTiming("retiming");
            startTiming("retimed type annotation");
            typeAnnotation(L3, true);
            endTiming("retimed type annotation");
            ofstream dotfile(subst("$0-rtsig.dot", gGlobal->makeDrawPath()).c_str());
            sigToGraph(L3, dotfile);
        }
        ofstream dotfile(subst("$0-sig.dot", gGlobal->makeDrawPath()).c_str());
        sigToGraph(L2, dotfile);
    }

    fFamRoot = L2;  // -fam : the private nodes of a family are checked against the whole graph
    return L2;
}

Tree ScalarCompiler::prepare2(Tree L0)
{
    startTiming("ScalarCompiler::prepare2");

    recursivnessAnnotation(L0);        // Annotate L0 with recursivness information
    typeAnnotation(L0, true);          // Annotate L0 with type information
    auto analyse2 = [&](Tree L) {
        sharingAnalysis(L, fSharingKey);  // annotate L0 with sharing count
        delete fOccMarkup;
        fOccMarkup = new OccMarkup();
        fOccMarkup->mark(L);  // annotate L0 with occurrences analysis
    };
    analyse2(L0);
    if (gGlobal->gExplicitTemps) {
        // the table generators are compiled here, by the same cache : the
        // pass decides for them too (subcontainer1 : the generator's constant)
        L0 = placeExplicitTemps(L0, L0, analyse2);
    }

    endTiming("ScalarCompiler::prepare2");
    return L0;
}

/*****************************************************************************
 Condition annotation due to enabled expressions
 *****************************************************************************/

#if _DNF_
#define CND2CODE dnf2code
#define _OR_ dnfOr
#define _AND_ dnfAnd
#define _CND_ dnfCond
#else
#define CND2CODE cnf2code
#define _OR_ cnfOr
#define _AND_ cnfAnd
#define _CND_ cnfCond
#endif

string ScalarCompiler::dnf2code(Tree cc)
{
    if (cc == gGlobal->nil) {
        return "";
    }
    Tree c1 = hd(cc);
    cc      = tl(cc);
    if (cc == gGlobal->nil) {
        return and2code(c1);
    } else {
        std::string s1 = and2code(c1);
        std::string s2 = dnf2code(cc);
        return subst("($0 || $1)", s1, s2);
    }
}

string ScalarCompiler::and2code(Tree cs)
{
    if (cs == gGlobal->nil) {
        return "";
    }
    Tree c1 = hd(cs);
    cs      = tl(cs);
    if (cs == gGlobal->nil) {
        return CS(c1);
    } else {
        std::string s1 = CS(c1);
        std::string s2 = and2code(cs);
        return subst("($0 && $1)", s1, s2);
    }
}

string ScalarCompiler::cnf2code(Tree cs)
{
    if (cs == gGlobal->nil) {
        return "";
    }
    Tree c1 = hd(cs);
    cs      = tl(cs);
    if (cs == gGlobal->nil) {
        return or2code(c1);
    } else {
        std::string s1 = or2code(c1);
        std::string s2 = cnf2code(cs);
        return subst("(($0) && $1)", s1, s2);
    }
}

string ScalarCompiler::or2code(Tree cs)
{
    if (cs == gGlobal->nil) {
        return "";
    }
    Tree c1 = hd(cs);
    cs      = tl(cs);
    if (cs == gGlobal->nil) {
        return CS(c1);
    } else {
        std::string s1 = CS(c1);
        std::string s2 = or2code(cs);
        return subst("($0 || $1)", s1, s2);
    }
}

// Temporary implementation for test purposes
string ScalarCompiler::getConditionCode(Tree sig)
{
    Tree cc = fConditionProperty[sig];
    if ((cc != nullptr) && (cc != gGlobal->nil)) {
        return CND2CODE(cc);
    } else {
        return "";
    }
}

#if 0
void ScalarCompiler::conditionStatistics(Tree l)
{
    for (const auto& p : fConditionProperty) {
        fConditionStatistics[p.second]++;
    }
    std::cout << "\nConditions statistics" << std::endl;
    for (const auto& p : fConditionStatistics) {
        std::cout << ppsig(p.first) << ":" << p.second << std::endl;
        
    }
}
#endif

void ScalarCompiler::conditionStatistics(Tree l)
{
    map<Tree, int, treeorder>
        fConditionStatistics;  // used with the new X,Y:enable --> sigEnable(X*Y,Y>0) primitive
    for (const auto& p : fConditionProperty) {
        for (Tree lc = p.second; !isNil(lc); lc = tl(lc)) {
            fConditionStatistics[hd(lc)]++;
        }
    }
    std::cout << "\nConditions statistics" << std::endl;
    for (const auto& p : fConditionStatistics) {
        std::cout << ppsig(p.first) << ":" << p.second << std::endl;
    }
}

/**
 * spec LE-SELECTN : recognize the ba.selectn spelling -- balanced trees
 * of select2 over monotone comparisons of a common selector against
 * constant thresholds -- and certify by interval propagation that the
 * leaves receive the exact anchored saturated partition (-inf,0], {1}
 * (or grouped runs), ..., [N-1,+inf). Two threshold modes : integer
 * (all four monotone ops) and real-integral (kGE/kLT only : every
 * split is then half-open [k,..) and [k,k+1) identifies with the
 * integer pair, so int(x) is an exact selector -- NaN corner excepted,
 * the gatequiv-admitted one). Verify-everything-or-drop ; N >= 3.
 * No tree surgery : certified roots enter fSelectNInfo, the spelling
 * stays in place.
 */
void ScalarCompiler::computeSelectNInfo(Tree L)
{
    fSelectNInfo.clear();
    // family collection : select2 grouped by comparison base (casts stripped)
    std::map<Tree, std::vector<Tree>> families;    // monotone selectors (V1)
    std::map<Tree, std::vector<Tree>> eqFamilies;  // ==/!= selectors (V1.2 chains)
    std::set<Tree>                    seenC;
    std::function<Tree(Tree, bool&)> baseOf = [&](Tree sel, bool& isEq) -> Tree {
        int  op;
        Tree a, b, xx;
        if (isSigBinOp(sel, &op, a, b) &&
            (op == kGT || op == kLT || op == kGE || op == kLE || op == kEQ || op == kNE)) {
            isEq = (op == kEQ || op == kNE);
            Tree base = a;
            if (isSigIntCast(a, xx)) {
                base = xx;
            }
            int    iv;
            double rv;
            if (isSigInt(b, &iv) || isSigReal(b, &rv)) {
                return base;
            }
        }
        return nullptr;
    };
    std::function<void(Tree)> walkC = [&](Tree t) {
        if (!seenC.insert(t).second) {
            return;
        }
        Tree sel, x, y, var, body;
        if (isSigSelect2(t, sel, x, y)) {
            bool isEq = false;
            Tree base = baseOf(sel, isEq);
            if (base != nullptr) {
                (isEq ? eqFamilies : families)[base].push_back(t);
            }
        }
        if (isRec(t, var, body)) {
            if (body != nullptr) {
                walkC(body);
            }
            return;
        }
        for (int k = 0; k < t->arity(); k++) {
            walkC(t->branch(k));
        }
    };
    while (isList(L)) {
        walkC(hd(L));
        L = tl(L);
    }
    const long long INF = 0x3FFFFFFFFFFFLL;
    for (const auto& f : families) {
        if ((int)f.second.size() < 2) {
            continue;
        }
        std::set<Tree> infam(f.second.begin(), f.second.end());
        std::set<Tree> ischild;
        for (Tree t : f.second) {
            Tree sel, x, y;
            isSigSelect2(t, sel, x, y);
            if (infam.count(x)) {
                ischild.insert(x);
            }
            if (infam.count(y)) {
                ischild.insert(y);
            }
        }
        for (Tree root : f.second) {
            if (ischild.count(root)) {
                continue;
            }
            struct IvLeaf {
                long long lo, hi;
                Tree      leaf;
            };
            std::vector<IvLeaf> leaves;
            bool                ok       = true;
            bool                realMode = false;
            Tree                selLhs   = nullptr;  // the comparisons' actual LHS (cast kept)
            std::function<void(Tree, long long, long long)> dive =
                [&](Tree t, long long lo, long long hi) {
                    if (!ok || lo > hi) {
                        ok = false;
                        return;
                    }
                    if (!infam.count(t)) {
                        leaves.push_back({lo, hi, t});
                        return;
                    }
                    Tree sel, x, y, a, b;
                    int  op, k;
                    isSigSelect2(t, sel, x, y);
                    if (!isSigBinOp(sel, &op, a, b)) {
                        ok = false;
                        return;
                    }
                    if (selLhs == nullptr) {
                        selLhs = a;
                    } else if (selLhs != a) {
                        ok = false;  // one selector expression, cast included
                        return;
                    }
                    if (isSigInt(b, &k)) {
                        if (realMode) {
                            ok = false;  // no mixed modes
                            return;
                        }
                    } else {
                        double rr;
                        if (!isSigReal(b, &rr) || rr != (double)(long long)rr ||
                            (op != kGE && op != kLT)) {
                            ok = false;
                            return;
                        }
                        realMode = true;
                        k        = (int)(long long)rr;
                    }
                    long long tlo, thi, flo, fhi;  // convention select2(c,x,y) = c ? y : x
                    switch (op) {
                        case kGE: tlo = k;      thi = hi;    flo = lo;    fhi = k - 1; break;
                        case kGT: tlo = k + 1;  thi = hi;    flo = lo;    fhi = k;     break;
                        case kLT: tlo = lo;     thi = k - 1; flo = k;     fhi = hi;    break;
                        case kLE: tlo = lo;     thi = k;     flo = k + 1; fhi = hi;    break;
                        default:  ok = false; return;
                    }
                    dive(x, std::max(flo, lo), std::min(fhi, hi));
                    dive(y, std::max(tlo, lo), std::min(thi, hi));
                };
            dive(root, -INF, INF);
            if (!ok || leaves.size() < 3) {
                continue;  // N >= 3 (spec, decisions actees)
            }
            std::sort(leaves.begin(), leaves.end(),
                      [](const IvLeaf& u, const IvLeaf& v) { return u.lo < v.lo; });
            bool part = leaves.front().lo == -INF && leaves.front().hi == 0 &&
                        leaves.back().hi == INF && leaves.back().lo < 4096;
            for (size_t i = 1; part && i < leaves.size(); i++) {
                if (leaves[i].lo != leaves[i - 1].hi + 1) {
                    part = false;
                }
            }
            if (!part) {
                continue;
            }
            SelectNInfo info;
            info.selEff = realMode ? sigIntCast(selLhs) : selLhs;
            int N       = (int)leaves.back().lo + 1;
            for (const auto& lf : leaves) {
                long long a = std::max(lf.lo, 0LL);
                long long b = std::min(lf.hi, (long long)(N - 1));
                for (long long k = a; k <= b; k++) {
                    Tree atom;
                    if (k == 0) {
                        atom = sigBinOp(kLE, info.selEff, sigInt(0));
                    } else if (k == N - 1) {
                        atom = sigBinOp(kGE, info.selEff, sigInt(N - 1));
                    } else {
                        atom = sigBinOp(kEQ, info.selEff, sigInt((int)k));
                    }
                    info.leaves.push_back({lf.leaf, {atom}});
                }
            }
            fSelectNInfo[root] = info;
        }
    }
    // ---- V2 : DISPATCH by real domains (spec section 11) -------------
    // Any tree of monotone comparisons of a common base against
    // constants tiles the real line by construction (each split makes
    // complementary halves : no gap, no overlap possible). No index
    // mapping, no anchoring : the object is the partition itself --
    // quantizedChords dispatches on its pitch-quantizer boundaries
    // (1.88775...). Exact open/closed boundary bookkeeping ; empty
    // leaves (contradictory nesting) are dead code, skipped ; the NaN
    // corner is the gatequiv-admitted one (all guards false -> the
    // zero-init survives, where the cascade lands on one leaf).
    // Tried on monotone roots the V1 certificate did not take.
    for (const auto& f : families) {
        if ((int)f.second.size() < 2) {
            continue;
        }
        std::set<Tree> infam(f.second.begin(), f.second.end());
        std::set<Tree> ischild;
        for (Tree t : f.second) {
            Tree sel, x, y;
            isSigSelect2(t, sel, x, y);
            if (infam.count(x)) {
                ischild.insert(x);
            }
            if (infam.count(y)) {
                ischild.insert(y);
            }
        }
        for (Tree root : f.second) {
            if (ischild.count(root) || fSelectNInfo.count(root)) {
                continue;  // internal, or already V1-certified
            }
            struct RLeaf {
                long double lo, hi;
                bool        loIn, hiIn;
                Tree        leaf;
            };
            std::vector<RLeaf>              leaves;
            std::map<long double, Tree>     thr;   // threshold value -> its constant tree
            bool                            ok   = true;
            Tree                            base = nullptr;
            const long double               RINF = 1e300L;
            std::function<void(Tree, long double, bool, long double, bool)> dive =
                [&](Tree t, long double lo, bool loIn, long double hi, bool hiIn) {
                    if (!ok) {
                        return;
                    }
                    bool empty = lo > hi || (lo == hi && !(loIn && hiIn));
                    if (!infam.count(t)) {
                        if (!empty) {
                            leaves.push_back({lo, hi, loIn, hiIn, t});
                        }
                        return;
                    }
                    if (empty) {
                        return;  // dead subtree : its leaves are unreachable
                    }
                    Tree sel, x, y, a, b;
                    int  op, iv;
                    double rv;
                    isSigSelect2(t, sel, x, y);
                    isSigBinOp(sel, &op, a, b);
                    if (base == nullptr) {
                        base = a;
                    } else if (base != a) {
                        ok = false;
                        return;
                    }
                    long double k;
                    if (isSigInt(b, &iv)) {
                        k = (long double)iv;
                    } else if (isSigReal(b, &rv)) {
                        k = (long double)rv;
                    } else {
                        ok = false;
                        return;
                    }
                    thr.emplace(k, b);
                    // convention select2(c,x,y)=c?y:x -- y is the true side
                    switch (op) {
                        case kGE: dive(y, k, true, hi, hiIn);  dive(x, lo, loIn, k, false); break;
                        case kGT: dive(y, k, false, hi, hiIn); dive(x, lo, loIn, k, true);  break;
                        case kLT: dive(y, lo, loIn, k, false); dive(x, k, true, hi, hiIn);  break;
                        case kLE: dive(y, lo, loIn, k, true);  dive(x, k, false, hi, hiIn); break;
                        default:  ok = false; return;
                    }
                };
            dive(root, -RINF, false, RINF, false);
            if (!ok || leaves.size() < 3 || leaves.size() > 65) {
                continue;
            }
            std::sort(leaves.begin(), leaves.end(), [](const RLeaf& u, const RLeaf& v) {
                return u.lo < v.lo || (u.lo == v.lo && u.loIn && !v.loIn);
            });
            SelectNInfo info;
            info.selEff = base;
            for (const auto& lf : leaves) {
                std::vector<Tree> atoms;
                if (lf.lo > -RINF / 2) {
                    atoms.push_back(sigBinOp(lf.loIn ? kGE : kGT, base, thr[lf.lo]));
                }
                if (lf.hi < RINF / 2) {
                    atoms.push_back(sigBinOp(lf.hiIn ? kLE : kLT, base, thr[lf.hi]));
                }
                info.leaves.push_back({lf.leaf, atoms});
            }
            fSelectNInfo[root] = info;
        }
    }
    // ---- V1.2 : equality CHAINS with a default branch ----------------
    // select2(base==k, CONT, TAKEN) nested through the continuation side
    // (kNE : sides swapped). The dispatch atoms ARE the original
    // comparison nodes (hash-consed, already typed) ; the default is
    // guarded by the conjunction of built negations. No clamp, no index
    // math -- the emission reproduces the nested ternaries exactly,
    // NaN corner included (every == false lands on the default, as the
    // cascade does). Chains only : a branch that is itself an eq member
    // rejects the candidate (trees stay in their spelling).
    for (const auto& f : eqFamilies) {
        if ((int)f.second.size() < 2) {
            continue;
        }
        std::set<Tree> infam(f.second.begin(), f.second.end());
        std::set<Tree> ischild;
        for (Tree t : f.second) {
            Tree sel, x, y;
            isSigSelect2(t, sel, x, y);
            if (infam.count(x)) {
                ischild.insert(x);
            }
            if (infam.count(y)) {
                ischild.insert(y);
            }
        }
        for (Tree root : f.second) {
            if (ischild.count(root)) {
                continue;
            }
            SelectNInfo    info;
            std::set<Tree> kseen;
            bool           ok   = true;
            Tree           cur  = root;
            Tree           base = nullptr;
            std::vector<Tree> negs;
            while (ok) {
                Tree sel, x, y, a, b;
                int  op;
                isSigSelect2(cur, sel, x, y);
                isSigBinOp(sel, &op, a, b);
                if (base == nullptr) {
                    base = a;
                } else if (base != a) {
                    ok = false;
                    break;
                }
                if (!kseen.insert(b).second) {
                    ok = false;  // duplicate constant : later test is dead
                    break;
                }
                Tree branch = (op == kEQ) ? y : x;
                Tree cont   = (op == kEQ) ? x : y;
                if (infam.count(branch)) {
                    ok = false;  // a tree, not a chain
                    break;
                }
                info.leaves.push_back({branch, {(op == kEQ) ? sel : sigBinOp(kEQ, a, b)}});
                negs.push_back(sigBinOp(kNE, a, b));
                if (infam.count(cont)) {
                    cur = cont;
                    continue;
                }
                info.leaves.push_back({cont, negs});  // the default entry
                break;
            }
            if (!ok || info.leaves.size() < 3 || info.leaves.size() > 65) {
                continue;  // entries + default >= 3 (spec N >= 3)
            }
            info.selEff = base;
            fSelectNInfo[root] = info;
        }
    }
}

void ScalarCompiler::conditionAnnotation(Tree l)
{
    if (gGlobal->gSelectN) {
        computeSelectNInfo(l);
    }
    while (isList(l)) {
        conditionAnnotation(hd(l), gGlobal->nil);
        l = tl(l);
    }
}

// State boundaries of the lazy-select condition propagation : below these
// nodes the condition is forced to nil (unconditional). Everything feeding a
// state sink (delay lines, recursions, tables, soundfiles) must run every
// sample whatever the selection -- Faust's strict state semantics : an
// unheard echo still ages. Observables (bargraphs, attach) and foreign
// functions (side effects) are boundaries too.
static bool isConditionBoundary(Tree t)
{
    int     i;
    Tree    x, y, z, u, v, w, lbl, mn, mx;
    if (isSigDelay(t, x, y) || isSigDelay1(t, x) || isSigPrefix(t, x, y)) {
        return true;
    }
    if (isProj(t, &i, x) || isRec(t, x, y)) {
        return true;
    }
    if (isSigWRTbl(t, x, y) || isSigWRTbl(t, x, y, u, v) || isSigRDTbl(t, x, y) ||
        isSigGen(t, x)) {
        return true;
    }
    if (isSigSoundfileBuffer(t, x, y, u, v) || isSigWaveform(t)) {
        return true;
    }
    if (isSigHBargraph(t, lbl, mn, mx, x) || isSigVBargraph(t, lbl, mn, mx, x) ||
        isSigAttach(t, x, y) || isSigEnable(t, x, y) || isSigControl(t, x, y)) {
        return true;
    }
    if (Tree ff, largs; isSigFFun(t, ff, largs)) {
        return true;
    }
    return false;
}

// (sel==0) v (sel!=0) = TRUE : a condition holding two complementary
// singleton atoms on the same selector is a tautology -- collapse to nil
// (unconditional) instead of emitting an always-true guard.
static Tree collapseComplements(Tree dnf)
{
    if (dnf == gGlobal->nil) {
        return dnf;
    }
    std::vector<Tree> eqs, nes;
    for (Tree c = dnf; isList(c); c = tl(c)) {
        Tree andl = hd(c);
        if (isList(andl) && isNil(tl(andl))) {
            int  op;
            Tree x, y;
            if (isSigBinOp(hd(andl), &op, x, y)) {
                if (op == kEQ) {
                    eqs.push_back(hd(andl));
                } else if (op == kNE) {
                    nes.push_back(hd(andl));
                }
            }
        }
    }
    for (Tree e : eqs) {
        int  op1, op2;
        Tree x1, y1, x2, y2;
        isSigBinOp(e, &op1, x1, y1);
        for (Tree n : nes) {
            isSigBinOp(n, &op2, x2, y2);
            if (x1 == x2 && y1 == y2) {
                return gGlobal->nil;  // complementary pair : always true
            }
        }
    }
    return dnf;
}

void ScalarCompiler::conditionAnnotation(Tree t, Tree nc)
{
    // fine boundary for STATIC table reads : the read itself is pure --
    // the condition reaches its INDEX cone (the four taps of a cubic
    // tabulate are exactly the expensive guarded work), only the table
    // DEFINITION stays unconditional. The blunt boundary made every
    // tabulate-based select side strict : quantizedChords paid all seven
    // cubic blends per sample where one is taken.
    Tree tb_, ix_;
    bool rdFine = gGlobal->gLazySelect && isSigRDTbl(t, tb_, ix_);
    if (gGlobal->gLazySelect && !rdFine && isConditionBoundary(t)) {
        nc = gGlobal->nil;  // the node and its subtree stay unconditional
    }
    if (gGlobal->gLazySelect && nc != gGlobal->nil) {
        // a condition is an OPTIMIZATION : beyond a few OR-terms the guard
        // costs more than it saves, and on deep select cascades (dx7 : 32
        // algorithms) the DNF growth is combinatorial -- collapse to nil
        // (unconditional, always sound ; nil is the lattice top, so the
        // re-annotation converges immediately)
        int  n  = 0;
        Tree cc = nc;
        while (isList(cc) && n <= 4) {
            for (Tree aa = hd(cc); isList(aa) && n <= 4; aa = tl(aa)) {
                n++;  // count ATOMS (OR-terms x AND-lengths) : a guard of
                      // more than 4 atoms costs more than it saves
            }
            cc = tl(cc);
        }
        // limit 4, and it is a CLIFF, not a dial : at 8 the DNF growth
        // on dx7's 32-algorithm cascade is combinatorial (compiler
        // crash, stack exhausted beyond 2 GB) ; at 4 with the fine
        // table-read boundary below, the quantizer family keeps 95% of
        // its lazy win (63.3 vs 60.0 ns isolated -- the boundary was
        // the big lock, not the depth).
        const int lzlim = 4;
        if (n > lzlim) {
            nc = gGlobal->nil;
        }
    }
    // Check if we need to annotate the tree with new conditions
    auto p = fConditionProperty.find(t);
    if (p != fConditionProperty.end()) {
        Tree cc = p->second;
        Tree xc = _OR_(cc, nc);
        if (gGlobal->gLazySelect) {
            xc = collapseComplements(xc);
        }
        if (cc == xc) {
            // Tree t already correctly annotated, nothing to change
            return;
        } else {
            // we need to re-annotate the tree with a new condition
            nc        = xc;
            p->second = nc;
        }
    } else {
        // first visit
        fConditionProperty[t] = nc;
    }

    // Annotate the subtrees with the new condition nc
    // which is either the nc passed as argument or nc <- (cc v nc)
    Tree x, y;
    if (isSigControl(t, x, y)) {
        // specific annotation case for SigControl
        conditionAnnotation(y, nc);
        conditionAnnotation(x, _AND_(nc, _CND_(y)));
    } else if (gGlobal->gSelectN && fSelectNInfo.count(t)) {
        // spec LE-SELECTN : a certified root dispatches with ONE
        // saturating atom per index (the Codex-blocking correction :
        // k=0 is sel<=0 and k=N-1 is sel>=N-1, never ==, because the
        // clamp keeps the extreme branches alive out of bounds). The
        // spine below is never compiled from here -- not descended.
        const SelectNInfo& info = fSelectNInfo[t];
        conditionAnnotation(info.selEff, nc);
        for (const auto& lf : info.leaves) {
            Tree c = nc;
            for (Tree a : lf.atoms) {
                c = _AND_(c, _CND_(a));
            }
            conditionAnnotation(lf.branch, c);
        }
    } else if (Tree sel; gGlobal->gLazySelect && isSigSelect2(t, sel, x, y)) {
        // lazy select : the selector decides, so it is needed under the
        // SAME condition as the select itself ; each branch's stateless
        // crown inherits the branch condition (the boundary rule above
        // keeps every stateful part unconditional). Emitted statements
        // then guard themselves via getConditionCode -- the machinery
        // built for sigControl serves unchanged. Convention :
        // select2(sel, x, y) = sel ? y : x.
        conditionAnnotation(sel, nc);
        conditionAnnotation(x, _AND_(nc, _CND_(sigBinOp(kEQ, sel, sigInt(0)))));
        conditionAnnotation(y, _AND_(nc, _CND_(sigBinOp(kNE, sel, sigInt(0)))));
    } else if (Tree tb, ix; rdFine && isSigRDTbl(t, tb, ix)) {
        // fine boundary : a STATIC table read is pure -- the condition
        // reaches the index cone, never the table definition
        conditionAnnotation(ix, nc);
        conditionAnnotation(tb, gGlobal->nil);
    } else {
        // general annotation case
        // Annotate the sub signals with nc
        tvec subsig;
        int  n = getSubSignals(t, subsig);
        if (n > 0 && !isSigGen(t)) {
            for (int i = 0; i < n; i++) {
                conditionAnnotation(subsig[i], nc);
            }
        }
    }
}

/*****************************************************************************
 CS : compile a signal
 *****************************************************************************/

/**
 * Test if a signal is already compiled
 * @param sig the signal expression to compile.
 * @param name the string representing the compiled expression.
 * @return true is already compiled
 */
bool ScalarCompiler::getCompiledExpression(Tree sig, string& cexp)
{
    return fCompileProperty.get(sig, cexp);
}

/**
 * Set the string of a compiled expression is already compiled
 * @param sig the signal expression to compile.
 * @param cexp the string representing the compiled expression.
 * @return the cexp (for commodity)
 */
string ScalarCompiler::setCompiledExpression(Tree sig, const string& cexp)
{
    string old;
    if (fCompileProperty.get(sig, old) && (old != cexp)) {
        // stringstream error;
        // error << "ERROR already a compiled expression attached : " << old << " replaced by " <<
        // cexp << endl; throw faustexception(error.str());
    }

    fCompileProperty.set(sig, cexp);
    return cexp;
}

/*****************************************************************************
 vector name property
 *****************************************************************************/

/**
 * Set the vector name property of a signal, the name of the vector used to
 * store the previous values of the signal to implement a delay.
 * @param sig the signal expression.
 * @param vecname the string representing the vector name.
 * @return true is already compiled
 */

void ScalarCompiler::setVectorNameProperty(Tree sig, const string& vecname)
{
    faustassert(vecname.size() > 0);
    fVectorProperty.set(sig, vecname);
}

/**
 * Get the vector name property of a signal, the name of the vector used to
 * store the previous values of the signal to implement a delay.
 * @param sig the signal expression.
 * @param vecname the string where to store the vector name.
 * @return true if the signal has this property, false otherwise
 */

bool ScalarCompiler::getVectorNameProperty(Tree sig, string& vecname)
{
    return fVectorProperty.get(sig, vecname);
}

/**
 * Make sure sig has a vector name property, if not use the one passed in parameter.
 * @param a name in case not already named
 * @param sig the signal expression.
 * @return the vector name associated with sig
 */

std::string ScalarCompiler::ensureVectorNameProperty(const std::string altname, Tree sig)
{
    std::string vecname;
    if (!getVectorNameProperty(sig, vecname)) {
        vecname = altname;
        setVectorNameProperty(sig, vecname);
    }
    return vecname;
}

/**
 * Compile a signal
 * @param sig the signal expression to compile.
 * @return the C code translation of sig as a string
 */

string ScalarCompiler::CS(Tree sig)
{
    // contextor contextRecursivness;
    string code;

    if (!getCompiledExpression(sig, code)) {
// not compiled yet
/*
 if (getRecursivness(sig) != contextRecursivness.get()) {
    contextRecursivness.set(getRecursivness(sig));
 }
 */
#ifdef TRACE
        int step = gGlobal->gSTEP;
        std::cerr << "\n"
                  << step << " [order: " << fScheduleOrder[sig] << "] "
                  << "::" << sig << "\t: generateCode( " << ppsig(sig, 10) << " )" << std::endl;
#endif
        code = generateCode(sig);
        setCompiledExpression(sig, code);

#ifdef TRACE
        std::cerr << "\n"
                  << step << " [order: " << fScheduleOrder[sig] << "] "
                  << "::" << sig << "\t: ============> " << code << std::endl;
#endif
    }
    return code;
}

/*****************************************************************************
 Loop-split emission (experimental, -ls / -ls-sched / -ls-R / -ls-U)
 *****************************************************************************/

/**
 * Thrown during the pre-scan when the program uses a construct the loop-split
 * emitter does not handle yet; the caller falls back to classic emission.
 */
class LoopSplitUnsupported {
   public:
    std::string fWhat;
    bool        fIntentional;  // deliberate route to classic, not a coverage gap
    LoopSplitUnsupported(const std::string& w, bool intentional = false)
        : fWhat(w), fIntentional(intentional)
    {
    }
};

/**
 * Emit the program as a DAG of loops (one per materialized signal: recursive
 * projection, delayed signal, shared sample-rate subexpression, output),
 * instead of one big sample loop. Mutually dependent signals (recursive
 * groups and their satellites) are collapsed into a single loop (Tarjan)
 * whose members are computed in instantaneous-dependency order.
 *
 * Every materialized signal owns a buffer of gVecSize (+ maxDelay) samples;
 * cross-loop reads are indexed accesses, delayed reads look back into the
 * buffer prefix, which is shifted at the end of each sub-block. This is the
 * loop structure of the loop-merging model (../loop-splitting), emitted for
 * real, with a selectable intra-loop op order:
 *   df    depth-first (the control: the natural recursive order)
 *   bf    breadth-first by dependency levels (maximal ILP exposure)
 *   model pressure-aware list scheduler under (R, U), calls preferring
 *         cycles with at most 8 live values (the callee-saved constraint)
 */
class LoopSplitEmitter {
   public:
    LoopSplitEmitter(ScalarCompiler* C, OccMarkup* occ, Tree key)
        : fC(C), fClass(C->fClass), fSN(occ, key)
    {
    }

    void emit(Tree L, const std::vector<Tree>& sched, int nouts);

   private:
    ScalarCompiler* fC;
    Klass*          fClass;
    SuperNodeGraph  fSN;  // the partition (single source of truth)
    // A FAMILY (the tiles spec, LES-TUILES) : P isomorphic chains of S stages, read
    // off the finest partition before any fusion move. rep[c][s] is a member of the
    // block at chain c, stage s -- members are stable identities, block ids are not.
    struct Family {
        int                           P = 0, S = 0;
        std::vector<std::vector<int>> rep;
    };
    std::vector<Family> detectFamilies(bool trace) const;
    std::vector<int>    tileBlocks(const Family& f, int c0, int s0, int k, int d) const;
    void contractTiles(const Family& f, size_t i, int k, int d, bool trace);
    void tileFamilies(const std::vector<Family>& fams, int k, int d, bool trace);
    void electTilings(const std::vector<Family>& fams, bool trace);

    // per-buffer emission decisions (materialized index -> ...)
    std::vector<std::string> fBufName;
    std::vector<int>         fAliasIx;  // tap aliasing: member -> producer index (-1: own buffer)
    std::vector<int>         fAliasD;   //   and the constant delay into the producer's history
    std::vector<int>         fMaxD;
    std::vector<bool>        fIsInt;
    std::vector<bool>        fLocal;  // maxDelay == 0: chunk-local buffer
    std::vector<bool> fRing;      // maxDelay > gMaxCopyDelay: masked ring buffer
    std::vector<int>  fCapD;      // -ls-regstate : deepest display capture of a member (-1: none)
    // -ls-tiles : the cells of every ELECTED tile (k * d > 1). A tile is a
    // loop decision : the greedy that follows the oracle may still pull a
    // foreign single-consumer block into a tile, but never merges two tiles
    // -- otherwise a larger loop cost (-ls-cl) re-fuses the pavage the
    // oracle just chose, and the election is absorbed (measured : at
    // -ls-cl 100 the oracle's code was the greedy's, byte for byte).
    std::vector<char> fTileMember;
    bool              isTileBlock(int b) const
    {
        if (fTileMember.empty()) {
            return false;
        }
        for (int m : fSN.blockMembers(b)) {
            if (fTileMember[m]) {
                return true;
            }
        }
        return false;
    }
    // who reads a materialized member, and what forces it to keep a buffer
    // whatever its block : an output, a display capture, a read at a delay
    // that is not a literal. Built once (storeClasses) for the fusion oracle,
    // reused by the emission so that both answer "is this member written ?"
    // the same way.
    std::vector<std::vector<int>> fReadersOf;
    std::vector<char>             fStoreForced;
    std::vector<bool> fRegState;  // -ls-regstate : read only inside its own block, at
                                  // constant delays -- no chunk buffer, no store per
                                  // sample ; its history crosses the chunks in scalars
    std::vector<int>  fRingMask;  // per ring buffer: size - 1 (power of two)
    bool              fHasRing = false;  // at least one ring: emit the fLSIota index

    // per-loop op DAG under scheduling
    struct LSOp {
        std::string code;              // expression, or full statement for stores
        std::vector<int> deps;
        bool isStore = false;
        bool isCall  = false;
        bool isInt   = false;
        bool resident = false;  // a register-resident value (a constant or a
                                // carried state) : ready from the start, out of
                                // the temporaries' live profile (-ls-regs3)
        int  shape   = 0;  // shadow-side shape tag (emitted ops use their
                           // digit-erased code string instead; see emitLoop)
        int  weight  = 1;  // issue slots consumed (composite ops : a matrix
                           // row op is one INDIVISIBLE op priced at its
                           // vectorized reduction tariff, see the Sum arm)
    };
    std::vector<LSOp>   fOps;
    std::map<Tree, int, treeorder> fOpOf;      // sample-rate op tree -> index in fOps
    std::map<int, int>  fStoreOf;   // materialized index -> its store op
    int                 fLoopNo = 0;  // emission counter, gives each loop a stable id

    // the matrix form (spec LA-FORME-MATRICE) : detected families and the
    // row-op emission regime gate (-mxr)
    MatrixPlans fMatrix;
    bool        fRowOp = false;

    std::map<int, std::string> fMatTable;  // family -> coefficient table field
    std::map<int, bool>        fMatRecBlock;  // block -> carries a recurrence

    // a block carries a recurrence iff its in-block reference graph has a
    // cycle. The row regime claims ONLY those spans : there the sample
    // loop is serial anyway and the row shape wins ; in a feedforward
    // span clang vectorizes ACROSS SAMPLES, and the gather array's
    // per-iteration overwrite is a WAR dependence that kills it
    // (matrix.dsp : x1.73 against the chain, measured).
    bool blockHasRecurrence(int b)
    {
        if (b < 0) {
            return false;  // output-only spans are feedforward
        }
        auto it = fMatRecBlock.find(b);
        if (it != fMatRecBlock.end()) {
            return it->second;
        }
        const std::vector<int>& mem = fSN.blockMembers(b);
        std::set<int>           inb(mem.begin(), mem.end());
        bool                    cyc = false;
        for (int s : mem) {
            std::vector<int> st{s};
            std::set<int>    vis;
            while (!st.empty() && !cyc) {
                int u = st.back();
                st.pop_back();
                for (int v : fSN.refs(u)) {
                    if (v == s) {
                        cyc = true;
                        break;
                    }
                    if (inb.count(v) && vis.insert(v).second) {
                        st.push_back(v);
                    }
                }
            }
            if (cyc) {
                break;
            }
        }
        fMatRecBlock[b] = cyc;
        return cyc;
    }
    // family -> (operand vector name, its gather op ids), valid for the
    // CURRENT loop span only (reset with fOpOf)
    std::map<int, std::pair<std::string, std::vector<int>>> fMatGather;
    std::map<int, std::vector<bool>> fMatResolved;  // which columns are gathered
    // (first gather op id, (vector name, size)) : emitLoop declares the
    // vectors whose gather ops fall in its [lo, hi) span
    std::vector<std::pair<int, std::pair<std::string, int>>> fMatDecls;

    // shorthands into the shared criteria
    static bool isNum(Tree t) { return SuperNodeGraph::isNum(t); }
    static bool isSlow(Tree t) { return SuperNodeGraph::isSlow(t); }
    static Tree defOf(Tree m) { return SuperNodeGraph::defOf(m); }
    static bool isCallPrim(const std::string& n) { return SuperNodeGraph::isCallPrim(n); }
    static void delayBounds(Tree y, int& dmin, int& dmax, bool& dvar)
    {
        SuperNodeGraph::delayBounds(y, dmin, dmax, dvar);
    }

    // ---- pre-scan: refuse constructs the emitter cannot handle yet.
    // Mirrors walk()'s dispatch exactly, and throws BEFORE anything has been
    // written, so the caller can fall back to classic emission cleanly.

    void prescan(Tree t, std::set<Tree, treeorder>& seen)
    {
        int  i;
        Tree x, y, z, sel, w, ff, largs, tb, size, gen, wi, ws, ri, label;
        if (seen.count(t)) {
            return;
        }
        seen.insert(t);
        if (isNum(t) || isSigInput(t, &i)) {
            return;
        }
        if (isSigAttach(t, x, y) && !isSlow(y)) {
            prescan(x, seen);
            prescan(y, seen);
            return;
        }
        if (isSlow(t)) {
            return;  // handled by the scalar machinery, outside the loops
        }
        if (isSigDelay(t, x, y)) {
            prescan(x, seen);
            prescan(y, seen);
            return;
        }
        if (isProj(t, &i, w)) {
            Occurrences* o = fC->fOccMarkup ? fC->fOccMarkup->retrieve(t) : nullptr;
            if (o && o->getMaxDelay() == 0) {
                // zero-delay recursion (a feedback the rewriting reduced to
                // nothing, echo_bug) : the classic emitter has a dedicated
                // idiom (a plain local), the -ls emission would reference
                // its name across worlds -- route the whole program back
                throw LoopSplitUnsupported("zero-delay recursive projection");
            }
            prescan(defOf(t), seen);
            return;
        }
        if (isSigBinOp(t, &i, x, y)) {
            prescan(x, seen);
            prescan(y, seen);
            return;
        }
        if (getUserData(t)) {
            for (int k = 0; k < t->arity(); k++) {
                prescan(t->branch(k), seen);
            }
            return;
        }
        if (isSigFFun(t, ff, largs)) {
            for (int k = 0; k < ffarity(ff); k++) {
                prescan(nth(largs, k), seen);
            }
            return;
        }
        if (isSigSelect2(t, sel, x, y)) {
            prescan(sel, seen);
            prescan(x, seen);
            prescan(y, seen);
            return;
        }
        if (isSigIntCast(t, x) || isSigBitCast(t, x) || isSigFloatCast(t, x)) {
            prescan(x, seen);
            return;
        }
        if (isSigRDTbl(t, tb, ri)) {
            if (isSigWRTbl(tb, size, gen)) {
                prescan(ri, seen);  // read-only table: fine
                return;
            }
            throw LoopSplitUnsupported("rwtable");
        }
        if (isSigVBargraph(t, label, x, y, z) || isSigHBargraph(t, label, x, y, z)) {
            prescan(z, seen);
            return;
        }
        if (isSigAssertBounds(t, x, y, z)) {
            prescan(z, seen);
            return;
        }
        if (isSigTemp(t, x)) {
            // staging barrier : transparent here -- the split emitter
            // stages per instruction anyway, the barrier dissolves into
            // its machine model
            prescan(x, seen);
            return;
        }
        if (tvec V; isSigSum(t, V) || kernelWorkVec(t, V)) {
            // -fir kernels, stage 1 : plain forms (Sum n-ary, FIR weighted
            // taps, IIR direct). V = terms for Sum, [source, c0..cn] for FIR
            for (Tree b : V) {
                prescan(b, seen);
            }
            return;
        }
        if (tvec V; isSigIIR(t, V)) {
            for (size_t k = 1; k < V.size(); k++) {  // branch 0 is nil
                prescan(V[k], seen);
            }
            return;
        }
        std::ostringstream what;
        what << "signal " << t->node();
        throw LoopSplitUnsupported(what.str());
    }

    // ---- body construction: expression walk producing the op DAG ----

    int newOp(const std::string& code, std::vector<int> deps, bool isStore, bool isCall,
              bool isInt)
    {
        LSOp op;
        op.code    = code;
        op.deps    = std::move(deps);
        op.isStore = isStore;
        op.isCall  = isCall;
        op.isInt   = isInt;
        fOps.push_back(op);
        return (int)fOps.size() - 1;
    }

    // an operand is either an inline leaf (kind 0) or an op reference (kind 1)
    struct Operand {
        int         op = -1;   // -1: inline leaf
        std::string code;
    };

    std::string operandCode(const Operand& o) const
    {
        return (o.op < 0) ? o.code : subst("tls$0", T(o.op));
    }

    void addDep(std::vector<int>& deps, const Operand& o)
    {
        if (o.op >= 0) {
            deps.push_back(o.op);
        }
    }

    // read access into a materialized signal's buffer
    std::string accessCode(int idx, const std::string& dcode) const
    {
        if (fAliasIx[idx] >= 0) {
            // aliased tap: every read redirects into the producer's history
            // (only instantaneous reads exist -- maxDelayOf == 0 guard)
            faustassert(dcode == "0");
            return accessCode(fAliasIx[idx], T(fAliasD[idx]));
        }
        if (fMaxD[idx] == 0) {
            return subst("$0[i]", fBufName[idx]);
        }
        if (fRing[idx]) {
            if (dcode == "0") {
                return subst("$0[(fLSIota+i)&$1]", fBufName[idx], T(fRingMask[idx]));
            }
            return subst("$0[(fLSIota+i-($2))&$1]", fBufName[idx], T(fRingMask[idx]), dcode);
        }
        if (dcode == "0") {
            return subst("$0[$1+i]", fBufName[idx], T(fMaxD[idx]));
        }
        return subst("$0[$1+i-($2)]", fBufName[idx], T(fMaxD[idx]), dcode);
    }

    // store destination for a materialized signal's buffer
    std::string storeCode(int idx) const
    {
        if (fMaxD[idx] == 0) {
            return subst("$0[i]", fBufName[idx]);
        }
        if (fRing[idx]) {
            return subst("$0[(fLSIota+i)&$1]", fBufName[idx], T(fRingMask[idx]));
        }
        return subst("$0[$1+i]", fBufName[idx], T(fMaxD[idx]));
    }

    // the value of materialized idx at the LAST sample of the chunk, read
    // d samples back -- valid after the loops and before the Zone3Post
    // shifts (where the display captures are taken)
    std::string lastCode(int idx, int d) const
    {
        if (fAliasIx[idx] >= 0) {
            return lastCode(fAliasIx[idx], fAliasD[idx] + d);
        }
        if (fRegState[idx]) {
            // no buffer : after its loop, the persistent scalar d+1 holds
            // the value d samples before the last one (the rotation runs
            // to maxDelay+1 for these members, see the block emission)
            return subst("fWr$0d$1", T(idx), T(d + 1));
        }
        if (fMaxD[idx] == 0) {
            faustassert(d == 0);
            return subst("$0[count-1]", fBufName[idx]);
        }
        if (fRing[idx]) {
            return subst("$0[(fLSIota+count-1-$2)&$1]", fBufName[idx], T(fRingMask[idx]), T(d));
        }
        return subst("$0[$1+count-1-$2]", fBufName[idx], T(fMaxD[idx]), T(d));
    }

    // a display capture point resolves to the input buffer, to its own
    // vector, or to the writer's history under a constant delay
    bool captureResolvable(Tree p) const
    {
        int  k, dmin, dmax;
        bool dvar;
        Tree x, y;
        if (isSigInput(p, &k) || fSN.indexOf(p) >= 0) {
            return true;
        }
        if (isSigDelay(p, x, y)) {
            delayBounds(y, dmin, dmax, dvar);
            return !dvar && fSN.indexOf(x) >= 0;
        }
        return false;
    }
    std::string captureCode(Tree p) const
    {
        int  k, dmin, dmax;
        bool dvar;
        Tree x, y;
        if (isSigInput(p, &k)) {
            return subst("$1input$0[count-1]", T(k), icast());
        }
        int ix = fSN.indexOf(p);
        if (ix >= 0) {
            return lastCode(ix, 0);
        }
        faustassert(isSigDelay(p, x, y));
        delayBounds(y, dmin, dmax, dvar);
        return lastCode(fSN.indexOf(x), dmin);
    }
    void emitDisplayCaptures();

    // reference to materialized idx read at delay dcode. An instantaneous
    // read of a producer living in the SAME loop is scalarized: it
    // references the producer's root value directly (a register), not the
    // buffer -- this is what makes fusion pay. The store still happens for
    // external readers; d0-topological member order guarantees the root
    // exists. Variable delays that may be 0 keep the buffer access with a
    // dependency on the store (the runtime delay may be positive).
    std::map<int, Operand> fRootOf;  // materialized index -> its body root
    // LES-SOMMES-DISTRIBUEES : a sum whose operands are computed in other blocks,
    // accumulated in place by those blocks into the consumer member's buffer
    struct AccPlan {
        Tree                             sum      = nullptr;
        int                              consumer = -1;  // the consumer's block
        int                              member   = -1;  // the member whose definition is the sum (or factor * sum)
        Tree                             factor   = nullptr;
        bool                             eligible = false;
        std::map<int, std::vector<std::pair<Tree, int>>> contributors;  // block -> its signed operands (+1/-1), in the sum's order
        std::vector<std::pair<Tree, int>>                rest;
        std::set<int>                    removable, internal;
    };
    std::vector<AccPlan> fAccPlans;

    // per-loop streams : read keys (buffer, delay/16 -- delays within one
    // cache line form ONE stream for the prefetcher ; -1 : variable
    // delay) and written buffers. Filled during the current block's walk,
    // read by emitLoop, cleared between blocks.
    std::set<std::pair<int, int>> fCurReadStreams;
    std::set<int>                 fCurWriteStreams;
    // rotation locals for SELF-history reads (grain fin, lfBoost autopsy) :
    // materialized index -> max delay read this loop. A delayed read of the
    // current block's own short history through the slice buffer loads
    // slots ADJACENT to the store -- SLP bait : clang packs them into a
    // 2-lane reduction whose cross-lane add and shuffle ride the serial
    // chain (x1.6 on lfBoost against the same filter one sign away).
    // Rotating locals reproduce the classic idiom -- the state lives in
    // registers -- while the buffer store remains for the tails.
    std::map<int, int> fCurRotDepth;
    std::map<std::pair<int, int>, int> fResidentHistory;  // (host, delay) -> resident op, per loop (-ls-const-live)

    Operand refOperand(int idx, const std::string& dcode, bool maybeInstant, int curScc)
    {
        Operand o;
        if (maybeInstant && fSN.blockOf(idx) == curScc && fAliasIx[idx] < 0) {
            return fRootOf.at(idx);
        }
        {
            // a self-history read may arrive DIRECT (constant dcode) or as
            // an ALIASED TAP (the materialized read redirecting into its
            // producer's history) : resolve to the host and its delay
            int host = (fAliasIx[idx] >= 0) ? fAliasIx[idx] : idx;
            int dR   = -1;
            if (fAliasIx[idx] >= 0) {
                dR = fAliasD[idx];
            } else if (!dcode.empty() &&
                       dcode.find_first_not_of("0123456789") == std::string::npos) {
                dR = atoi(dcode.c_str());
            }
            if (curScc >= 0 && dR >= 1 && fSN.blockOf(host) == curScc && !fRing[host] &&
                fMaxD[host] > 0 && fMaxD[host] <= gGlobal->gMaxCopyDelay) {
                int& dep = fCurRotDepth[host];
                dep      = std::max(dep, dR);
                o.code   = subst("wr$0d$1", T(host), T(dR));
                if (gGlobal->gLSConstLive) {
                    // -ls-const-live : a register-resident history value is a
                    // resident value of the loop like a constant -- a
                    // register from cycle 0 to its last read (one op per
                    // (host, delay) and loop, no issue slot)
                    auto key = fResidentHistory.find({host, dR});
                    if (key != fResidentHistory.end()) {
                        o.op = key->second;
                    } else {
                        bool hostInt = getCertifiedSigType(fSN.materialized()[host])->nature() == kInt;
                        o.op = newOp(o.code, {}, false, false, hostInt);
                        fOps[o.op].weight        = 0;
                        fOps[o.op].shape         = -7;  // a loop-carried state : must stay in a register
                        fResidentHistory[{host, dR}] = o.op;
                    }
                }
                return o;  // register-resident history, no memory stream
            }
        }
        o.code = accessCode(idx, dcode);
        {
            int host = (fAliasIx[idx] >= 0) ? fAliasIx[idx] : idx;
            int d    = atoi(dcode.c_str());  // constant delays only reach here
            fCurReadStreams.insert({host, d / 16});
        }
        // an instantaneous read that goes THROUGH a buffer (aliased tap at
        // zero offset) reads the very slot the host's store writes this
        // iteration : inside the host's own loop the write must precede the
        // read. The direct-root path above gets that ordering for free ; the
        // buffer path must carry the RAW edge explicitly -- without it every
        // intra-loop order beyond creation order is legally allowed to emit
        // the read first (model and df disagreed bit-exactly on zitaRev and
        // reverbTank precisely here).
        if (maybeInstant) {
            int host = (fAliasIx[idx] >= 0) ? fAliasIx[idx] : idx;
            int dEff = (fAliasIx[idx] >= 0) ? fAliasD[idx] : 0;  // dcode == "0"
            if (dEff == 0 && fSN.blockOf(host) == curScc) {
                if (fRegState[host]) {
                    return fRootOf.at(host);  // no buffer slot : the value itself
                }
                auto st = fStoreOf.find(host);
                if (st != fStoreOf.end()) {
                    o.op = newOp(o.code, {st->second}, false, false, fIsInt[idx]);
                    o.code.clear();
                }
            }
        }
        return o;
    }

    Operand walk(Tree t, int curScc, bool root)
    {
        int     i;
        int64_t i64;
        double  r;
        Tree    x, y, z, sel, w, ff, largs, tb, size, gen, ri, label, c;
        Operand o;

        // shared sample-rate op already walked in this loop
        auto shared = fOpOf.find(t);
        if (!root && shared != fOpOf.end()) {
            o.op = shared->second;
            return o;
        }

        // materialized signals referenced from a body become buffer reads
        if (!root && fSN.indexOf(t) >= 0) {
            return refOperand(fSN.indexOf(t), "0", true, curScc);
        }
        // -ls-const-live : a constant or a slow leaf becomes an op of the
        // loop, without dependency, so that the model scheduler tracks its
        // liveness like any value (from its placement to its last use) --
        // the register a hoisted coefficient occupies. Emitted as a local
        // copy the C++ compiler folds away ; one op per distinct tree and
        // loop (fOpOf memo).
        auto constOp = [&](const std::string& code, bool isInt) -> Operand {
            Operand oc;
            if (!gGlobal->gLSConstLive || root) {
                oc.code = code;
                return oc;
            }
            oc.op     = newOp(code, {}, false, false, isInt);
            fOps[oc.op].weight = 0;  // a resident value : a register, no issue slot
            fOpOf[t]  = oc.op;
            return oc;
        };
        if (isSigInt(t, &i)) {
            return constOp(T(i), true);
        }
        if (isSigInt64(t, &i64)) {
            return constOp(T(i64), true);
        }
        if (isSigReal(t, &r)) {
            return constOp(realLiteral(r), false);
        }
        if (isSigInput(t, &i)) {
            o.code = subst("$1input$0[i]", T(i), icast());
            fCurReadStreams.insert({-1000 - i, 0});  // one stream per input channel
            return o;
        }
        if (isSigAttach(t, x, y) && !isSlow(y)) {
            Operand ox = walk(x, curScc, false);
            Operand oy = walk(y, curScc, false);
            std::vector<int> deps;
            addDep(deps, ox);
            addDep(deps, oy);
            o.op = newOp(operandCode(ox), deps, false, false,
                         getCertifiedSigType(t)->nature() == kInt);
            fOpOf[t] = o.op;
            return o;
        }
        if (isSlow(t)) {
            // scalar machinery, code lives outside the loops ; a live value
            // of the loop under -ls-const-live (see constOp)
            return constOp(fC->coefCode(t), getCertifiedSigType(t)->nature() == kInt);
        }
        if (tvec V; kernelWorkVec(t, V)) {
            // stage 1 : plain weighted taps (the scalar regimes -- sliding
            // sum, symmetric pre-add -- need chunk-carried state and wait).
            // V[0] = source read at delays 0..n-1 ; taps at delay >= 1 give
            // the source occurrence marks that MATERIALIZE it (inputs
            // included, as copy members)
            if (V.size() == 2) {  // simple gain, source read at 0 only
                Operand a = walk(V[0], curScc, false);
                Operand c = walk(V[1], curScc, false);
                std::vector<int> deps;
                addDep(deps, a);
                addDep(deps, c);
                o.op = newOp(subst("($0) * ($1)", operandCode(c), operandCode(a)), deps,
                             false, false, getCertifiedSigType(t)->nature() == kInt);
                fOpOf[t] = o.op;
                return o;
            }
            const int ix = fSN.indexOf(V[0]);
            faustassert(ix >= 0);
            // lowering at scheduling time : one product op per tap, then a
            // left chain of adds (ascending taps, the scalar association)
            const bool kInt2 = (getCertifiedSigType(t)->nature() == kInt);
            Operand    acc;
            bool       first = true;
            for (size_t k = 1; k < V.size(); k++) {
                if (isZero(V[k])) {
                    continue;
                }
                Operand tap = refOperand(ix, T(int(k) - 1), k == 1, curScc);
                Operand term;
                if (isOne(V[k])) {
                    term = tap;
                } else {
                    Operand          c = walk(V[k], curScc, false);
                    std::vector<int> pd;
                    addDep(pd, c);
                    addDep(pd, tap);
                    term.op = newOp(subst("(($0) * $1)", operandCode(c), operandCode(tap)),
                                    pd, false, false, kInt2);
                }
                if (first) {
                    acc   = term;
                    first = false;
                } else {
                    std::vector<int> ad;
                    addDep(ad, acc);
                    addDep(ad, term);
                    Operand n2;
                    n2.op = newOp(subst("($0 + $1)", operandCode(acc), operandCode(term)),
                                  ad, false, false, kInt2);
                    acc = n2;
                }
            }
            o = acc;
            if (o.op >= 0) {
                fOpOf[t] = o.op;
            }
            return o;
        }
        if (isSigDelay(t, x, y)) {
            int  dmin, dmax;
            bool dvar;
            delayBounds(y, dmin, dmax, dvar);
            int ix = fSN.indexOf(x);
            if (ix < 0) {
                // delay of a non-materialized signal: slow/constant, transparent
                return walk(x, curScc, false);
            }
            if (!dvar) {
                return refOperand(ix, T(dmin), dmin == 0, curScc);
            }
            Operand oy = walk(y, curScc, false);
            std::string acc = accessCode(ix, operandCode(oy));
            fCurReadStreams.insert({(fAliasIx[ix] >= 0) ? fAliasIx[ix] : ix, -1});
            std::vector<int> deps;
            addDep(deps, oy);
            if (dmin == 0 && fSN.blockOf(ix) == curScc) {
                deps.push_back(fStoreOf.at(ix));
            }
            o.op = newOp(acc, deps, false, false, fIsInt[ix]);
            return o;
        }
        if (tvec V; isSigSum(t, V)) {
            const bool wrapInt = (getCertifiedSigType(t)->nature() == kInt);
            if (fRowOp && !wrapInt && fMatrix.rowOf.count(t) && blockHasRecurrence(curScc)) {
                // MATRIX ROW OP (the -ls regime of the fourth gathering) :
                // the row is ONE indivisible op spelled as an unrolled dot
                // product over TWO CONTIGUOUS ARRAYS -- the family's
                // coefficient table (a field, refilled at control rate
                // like the fSlow it copies) and a per-sample operand
                // vector gathered once per family per loop. Contiguity is
                // the point : the same rows spelled over scattered fSlow
                // scalars stayed scalar (56 live coefficients overflow 32
                // registers -- 66 reloads/sample -- and the interleaved
                // schedule starves clang's SLP seeds), while two dense
                // arrays give vector loads and a uniform reduction
                // (statespace : the 9.46 vs 7.49 residual). Zero cells
                // are gathered and multiplied too : uniformity buys the
                // vector shape, the <=10% budget bounds the waste.
                // Association follows the family's canonical column order
                // (ulp-class vs the source order, legal at onset ; the
                // regime stays out of the impulse-gate option sets). Int
                // rows stay on the chain (wrapInt spelling, excluded v1).
                const auto&         fr  = fMatrix.rowOf.at(t);  // regime "matrix-row"
                const int           fam = fr.first, row = fr.second;
                const MatrixFamily& F = fMatrix.families[fam];
                const int           n = (int)F.tuple.size();
                if (!fMatTable.count(fam)) {
                    // the table field, declared once and refilled at
                    // control rate right after the coefficients' own
                    // slow code (zone2 appends in call order)
                    std::string tab = fC->getFreshID("fMat");
                    fClass->addDeclCode(subst("$0 \t$1[$2];", ifloat(), tab,
                                              T(n * (int)F.rows.size())));
                    for (size_t r2 = 0; r2 < F.rows.size(); r2++) {
                        for (int j = 0; j < n; j++) {
                            // numeric cells (zero padding, literal
                            // weights) are spelled directly : CS's
                            // generateNumber needs an occurrence mark
                            // numbers reached only through the plan
                            // never received (the DNN crash)
                            Tree        cf = F.coef[r2][j];
                            int         ci;
                            int64_t     cl;
                            double      cr;
                            std::string cc = isSigInt(cf, &ci)     ? T(ci)
                                             : isSigInt64(cf, &cl) ? T(cl)
                                             : isSigReal(cf, &cr)  ? T(cr)
                                                                   : fC->CS(cf);
                            fClass->addZone2(subst("$0[$1] = $2;", tab,
                                                   T((int)r2 * n + j), cc));
                        }
                    }
                    fMatTable[fam] = tab;
                }
                auto git = fMatGather.find(fam);
                if (git == fMatGather.end()) {
                    // the operand vector, gathered once per loop span and
                    // shared by every row of the family in it. Cells
                    // start as constant-0 placeholder stores : a family
                    // may straddle loops, and a span must never compute
                    // operands only FOREIGN rows read (the DNN crash --
                    // walking a column no local row uses reached signals
                    // with no occurrence record). Columns are resolved
                    // below, on the first local row that reads them.
                    std::string      arr = "mxv" + T(fam);
                    std::vector<int> gops;
                    for (int j = 0; j < n; j++) {
                        gops.push_back(newOp(subst("$0[$1] = 0;", arr, T(j)), {},
                                             true, false, false));
                    }
                    fMatDecls.push_back({gops[0], {arr, n}});
                    git = fMatGather.insert({fam, {arr, gops}}).first;
                    fMatResolved[fam].assign(n, false);
                }
                {
                    std::vector<bool>& res = fMatResolved[fam];
                    for (int j = 0; j < n; j++) {
                        if (!res[j] && !isZero(F.coef[row][j])) {
                            res[j]              = true;
                            Operand          ox = walk(F.tuple[j], curScc, false);
                            std::vector<int> gd;
                            addDep(gd, ox);
                            const int g  = git->second.second[j];
                            fOps[g].code = subst("$0[$1] = $2;", git->second.first,
                                                 T(j), operandCode(ox));
                            fOps[g].deps = gd;
                        }
                    }
                }
                const std::string& tab = fMatTable[fam];
                const std::string& arr = git->second.first;
                std::string        code;
                for (int j = 0; j < n; j++) {
                    std::string term =
                        subst("$0[$1] * $2[$3]", tab, T(row * n + j), arr, T(j));
                    code = j ? code + " + " + term : term;
                }
                o.op = newOp("(" + code + ")", git->second.second, false, false, false);
                fOps[o.op].shape  = 14;
                // the regime's declared weight : one indivisible op priced at
                // its vectorised reduction tariff, a function of the family's
                // width and of nothing else
                fOps[o.op].weight = std::max(1, (n + 3) / 4 + (n + 2) / 4);
                fOpOf[t]          = o.op;
                return o;
            }
            // LOWERING AT SCHEDULING TIME : the revealed sum becomes a left
            // chain of BINARY add ops -- each one an atom the RUM scheduler
            // places, so isomorphic kernels interleave (the monolithic
            // emission was an opaque brick for isoadj/SLP). Left-chain
            // association == the scalar generateSum, bit-exact ; INT sums
            // wrap through unsigned arithmetic pairwise (mod-2^32 addition
            // is associative, the flat and chained forms agree).
            Operand    acc;
            bool       first = true;
            for (Tree b : V) {
                if (isZero(b)) {
                    continue;
                }
                Operand a = walk(b, curScc, false);
                if (first) {
                    acc   = a;
                    first = false;
                    continue;
                }
                std::vector<int> deps;
                addDep(deps, acc);
                addDep(deps, a);
                Operand n2;
                if (wrapInt) {
                    n2.op = newOp(subst("faust_wrap_add($0, $1)", operandCode(acc), operandCode(a)),
                                  deps, false, false, true);
                } else {
                    n2.op = newOp(subst("($0 + $1)", operandCode(acc), operandCode(a)),
                                  deps, false, false, false);
                }
                acc = n2;
            }
            if (first) {
                o.code = "0";
                return o;
            }
            o = acc;
            if (o.op >= 0) {
                fOpOf[t] = o.op;
            }
            return o;
        }
        if (tvec V; isSigIIR(t, V)) {
            // stage 1 : DIRECT form only (y = X + sum ci*y@i) -- under -ls
            // the transposed election stands down, so the occurrence
            // self-marks size this member's buffer. Descending tap order
            // mirrors generateIIR (bit-exact with the scalar emission).
            const int ixSelf = fSN.indexOf(t);
            faustassert(ixSelf >= 0);
            // lowering at scheduling time : the recurrence stays a chain
            // PER KERNEL (its nature) but fifty kernels' chains interleave
            // BETWEEN them -- which is where plain fusion's win on the
            // modal banks came from. Descending taps from X, the scalar
            // association of generateIIR, bit-exact.
            const bool kInt2 = (getCertifiedSigType(t)->nature() == kInt);
            Operand    acc   = walk(V[1], curScc, false);
            for (size_t k = V.size() - 1; k >= 3; k--) {
                if (isZero(V[k])) {
                    continue;
                }
                Operand tap = refOperand(ixSelf, T(int(k) - 2), false, curScc);
                Operand term;
                if (isOne(V[k])) {
                    term = tap;
                } else {
                    Operand          c = walk(V[k], curScc, false);
                    std::vector<int> pd;
                    addDep(pd, c);
                    addDep(pd, tap);
                    term.op = newOp(subst("(($0) * $1)", operandCode(c), operandCode(tap)),
                                    pd, false, false, kInt2);
                }
                std::vector<int> ad;
                addDep(ad, acc);
                addDep(ad, term);
                Operand n2;
                n2.op = newOp(subst("($0 + $1)", operandCode(acc), operandCode(term)), ad,
                              false, false, kInt2);
                acc = n2;
            }
            o = acc;
            if (o.op >= 0) {
                fOpOf[t] = o.op;
            }
            return o;
        }

        // generic n-ary operation: walk the arguments, then build the op
        std::vector<Tree> args;
        std::string       code;
        bool              call  = false;
        bool              isInt = getCertifiedSigType(t)->nature() == kInt;

        if (isSigBinOp(t, &i, x, y)) {
            Operand a = walk(x, curScc, false), b = walk(y, curScc, false);
            std::vector<int> deps;
            addDep(deps, a);
            addDep(deps, b);
            call = (i == kRem) && !isInt;
            const char* wrap = isInt ? wrapHelper(i) : nullptr;
            o.op = newOp(wrap ? subst("$0($1, $2)", wrap, operandCode(a), operandCode(b))
                              : subst("($0 $1 $2)", operandCode(a), gBinOpTable[i]->fName,
                                      operandCode(b)),
                         deps, false, call, isInt);
            fOpOf[t] = o.op;
            return o;
        }
        if (getUserData(t)) {
            xtendedCodegen* p = static_cast<xtendedCodegen*>((xtended*)getUserData(t));
            std::vector<std::string> acodes;
            std::vector<Type>        types;
            std::vector<int>         deps;
            for (int k = 0; k < t->arity(); k++) {
                Operand a = walk(t->branch(k), curScc, false);
                addDep(deps, a);
                acodes.push_back(operandCode(a));
                types.push_back(getCertifiedSigType(t->branch(k)));
            }
            o.op = newOp(p->generateCode(fClass, acodes, types), deps, false,
                         isCallPrim(p->name()), isInt);
            fOpOf[t] = o.op;
            return o;
        }
        if (isSigFFun(t, ff, largs)) {
            fC->addIncludeFile(ffincfile(ff));
            fC->addLibrary(fflibfile(ff));
            std::string      fcode = ffname(ff);
            std::vector<int> deps;
            fcode += '(';
            std::string sep = "";
            for (int k = 0; k < ffarity(ff); k++) {
                Operand a = walk(nth(largs, k), curScc, false);
                addDep(deps, a);
                fcode += sep + operandCode(a);
                sep = ", ";
            }
            fcode += ')';
            o.op = newOp(fcode, deps, false, true, isInt);
            fOpOf[t] = o.op;
            return o;
        }
        if (isSigSelect2(t, sel, x, y)) {
            Operand s = walk(sel, curScc, false);
            Operand a = walk(x, curScc, false);
            Operand b = walk(y, curScc, false);
            std::vector<int> deps;
            addDep(deps, s);
            addDep(deps, a);
            addDep(deps, b);
            o.op = newOp(subst("(($0) ? $1 : $2)", operandCode(s), operandCode(b),
                               operandCode(a)),
                         deps, false, false, isInt);
            fOpOf[t] = o.op;
            return o;
        }
        if (isSigIntCast(t, x)) {
            Operand a = walk(x, curScc, false);
            std::vector<int> deps;
            addDep(deps, a);
            // unary plus : same type-id-parse guard as the scalar casts
            o.op = newOp(subst("int(+$0)", operandCode(a)), deps, false, false, true);
            fOpOf[t] = o.op;
            return o;
        }
        if (isSigBitCast(t, x)) {
            Operand a = walk(x, curScc, false);
            std::vector<int> deps;
            addDep(deps, a);
            o.op = newOp(subst("(*(int*)&$0)", operandCode(a)), deps, false, false, true);
            fOpOf[t] = o.op;
            return o;
        }
        if (isSigFloatCast(t, x)) {
            Operand a = walk(x, curScc, false);
            std::vector<int> deps;
            addDep(deps, a);
            o.op = newOp(subst("$1(+$0)", operandCode(a), ifloat()), deps, false, false, false);
            fOpOf[t] = o.op;
            return o;
        }
        if (isSigRDTbl(t, tb, ri) && isSigWRTbl(tb, size, gen)) {
            std::string tblname;
            if (!fC->getCompiledExpression(tb, tblname)) {
                tblname = fC->setCompiledExpression(tb, fC->generateStaticTable(tb, size, gen));
            }
            Operand a = walk(ri, curScc, false);
            std::vector<int> deps;
            addDep(deps, a);
            o.op = newOp(subst("$0[$1]", tblname, operandCode(a)), deps, false, false, isInt);
            fOpOf[t] = o.op;
            return o;
        }
        if (isSigVBargraph(t, label, x, y, z) || isSigHBargraph(t, label, x, y, z)) {
            // replicate the declaration side of generateXBargraph; the store
            // happens inside OUR loop, as a store-op
            std::string varname = fC->getFreshID("fbargraph");
            fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
            Tree uipath   = reverse(tl(label));
            Tree uiwidget = uiWidget(hd(label), tree(varname), t);
            fC->fUITree.addUIWidget(uipath, uiwidget);
            Operand a = walk(z, curScc, false);
            std::vector<int> deps;
            addDep(deps, a);
            int st = newOp(subst("$0 = $1;", varname, operandCode(a)), deps, true, false, false);
            o.op   = newOp(varname, {st}, false, false, false);
            fOpOf[t] = o.op;
            return o;
        }
        if (isSigAssertBounds(t, x, y, z)) {
            return walk(z, curScc, false);
        }
        if (isSigTemp(t, x)) {
            return walk(x, curScc, false);  // barrier transparent (see prescan)
        }

        std::ostringstream what;
        what << "signal " << t->node();
        throw LoopSplitUnsupported(what.str());
    }

    // ---- intra-loop scheduling strategies ----

    void emitLoop(std::ostringstream& out, int lo, int hi);
    void dumpSuperNodesDot(std::ostream& out);

    // returns the emission order of ops in [lo, hi)
    std::vector<int> scheduleSpan(int lo, int hi)
    {
        int n = hi - lo;
        std::vector<int> order;
        order.reserve(n);
        if (gGlobal->gLSSched == 0) {
            // df: creation order is the deps-first depth-first order
            for (int k = lo; k < hi; k++) {
                order.push_back(k);
            }
            return order;
        }
        if (gGlobal->gLSSched == 4 || gGlobal->gLSSched == 5) {
            // cs2/cs2b: the compositional scheduler at the op grain
            // (Schedule.hh csschedule2) -- dominator blocks, Pareto beam,
            // (R,U) grid combination. Same contract as model: deps are the
            // only constraints. cs2b = breadth-first spine.
            digraph<int> G;
            for (int k = lo; k < hi; k++) {
                G.add(k);
                for (int d : fOps[k].deps) {
                    if (d >= lo && d < hi) {
                        G.add(k, d, 0);
                    }
                }
            }
            schedule<int> S = csschedule2(G, gGlobal->gLSRegisters, gGlobal->gLSWidth, 4,
                                          nullptr, 1000000, nullptr, gGlobal->gLSSched == 5);
            for (int k : S.elements()) {
                order.push_back(k);
            }
            return order;
        }
        // dependency levels restricted to the span
        std::vector<int> level(n, 0);
        for (int k = lo; k < hi; k++) {
            int lv = 0;
            for (int d : fOps[k].deps) {
                if (d >= lo && d < hi) {
                    lv = std::max(lv, level[d - lo] + 1);
                }
            }
            level[k - lo] = lv;
        }
        if (gGlobal->gLSSched == 1) {
            // bf: stable sort by level (ties keep df order)
            std::vector<int> idx(n);
            for (int k = 0; k < n; k++) {
                idx[k] = k;
            }
            std::stable_sort(idx.begin(), idx.end(),
                             [&](int a, int b) { return level[a] < level[b]; });
            for (int k : idx) {
                order.push_back(lo + k);
            }
            return order;
        }
        if (gGlobal->gLSSched == 3) {
            // layers: natural levels with COLORS grouped inside each level --
            // the intra-loop port of the day's winning recipe at Tree grain
            // (phase-coherent monochromatic runs are what the superword
            // vectorizer packs). The shape of an op is its code with digit
            // runs erased: identifiers lose their indices, numeric literals
            // become holes -- textual isomorphism, exactly SLP's grain.
            auto norm = [](const std::string& c) {
                std::string r;
                r.reserve(c.size());
                for (char ch : c) {
                    if (!isdigit((unsigned char)ch)) {
                        r += ch;
                    }
                }
                return r;
            };
            std::vector<std::string> sh(n);
            for (int k = 0; k < n; k++) {
                sh[k] = norm(fOps[lo + k].code);
            }
            std::vector<int> idx(n);
            for (int k = 0; k < n; k++) {
                idx[k] = k;
            }
            std::stable_sort(idx.begin(), idx.end(), [&](int a, int b) {
                if (level[a] != level[b]) {
                    return level[a] < level[b];
                }
                return sh[a] < sh[b];
            });
            for (int k : idx) {
                order.push_back(lo + k);
            }
            return order;
        }
        // model: the pressure-aware list scheduler
        // -ls-sched-R : the emission scheduler may run under a budget of its
        // own, the fusion oracle keeping -ls-R (to test the order alone at a
        // fixed partition)
        int Rsched = (gGlobal->gLSSchedRegisters > 0) ? gGlobal->gLSSchedRegisters : gGlobal->gLSRegisters;
        if (gGlobal->gLSSched == 6) {
            // profile: sequence or interleave, decided node by node on the
            // live profiles (spec L-ORDONNANCEMENT-PAR-PROFILS)
            order = profileSchedule(fOps, lo, hi, Rsched, gGlobal->gLSWidth, nullptr, nullptr);
            return order;
        }
        order = modelSchedule(fOps, lo, hi, Rsched, gGlobal->gLSWidth, nullptr, nullptr);
        return order;
    }

    /**
     * The profile scheduler (spec L-ORDONNANCEMENT-PAR-PROFILS). A schedule
     * is a set of ops with a cycle each ; its live profile counts, per
     * cycle, the values produced and not yet fully consumed, its issue
     * profile the weights emitted. A node composes the schedules of its
     * operands by sliding each one over the accumulated schedule to the
     * SMALLEST shift admissible under (R, U) and under the dependencies
     * that cross from the slid schedule into the accumulated one (shared
     * values placed earlier). Shift 0 is the total interleaving (BF),
     * shift = length of the accumulated schedule is the sequence (DF) ;
     * the scheduler finds both as particular cases, node by node. Greedy
     * bottom-up : the inner order of a composed schedule is never revisited.
     */
    struct ProfSched {
        std::vector<std::pair<int, int>> ops;  // (op index, cycle)
        std::vector<int> live, issue;          // profiles by cycle
        int length() const { return (int)live.size(); }
    };

    static void profileRecompute(ProfSched& S, const std::vector<LSOp>& ops, int lo, int hi,
                                 const std::vector<int>& cycleOf, const std::vector<std::vector<int>>& users)
    {
        int L = 0;
        for (auto& p : S.ops) {
            L = std::max(L, p.second + 1);
        }
        S.live.assign(L, 0);
        S.issue.assign(L, 0);
        for (auto& p : S.ops) {
            int k = p.first, c = p.second;
            S.issue[c] += ops[k].weight;  // 0 for a resident constant
            if (ops[k].isStore) {
                continue;  // no value produced
            }
            // the value lives from its cycle to the cycle of its last placed
            // user ; a user not yet placed keeps it live to the end
            int last = L;
            bool allPlaced = true;
            for (int u : users[k - lo]) {
                if (cycleOf[u - lo] < 0) {
                    allPlaced = false;
                } else {
                    last = std::max(last == L && allPlaced ? 0 : last, cycleOf[u - lo]);
                }
            }
            if (!allPlaced) {
                last = L;
            } else if (users[k - lo].empty()) {
                last = c + 1;
            } else {
                last = 0;
                for (int u : users[k - lo]) {
                    last = std::max(last, cycleOf[u - lo]);
                }
            }
            // a loop-carried state (a register-resident history read, weight
            // 0, tagged -7) is read at the top of the iteration and rotated at
            // its bottom : it occupies its register for the WHOLE iteration,
            // whatever cycles the composition gave it and its readers. A
            // constant lives from its placement to its last use (the C++
            // compiler reloads it cheaply when registers are short).
            bool state = (ops[k].weight == 0 && ops[k].shape == -7);
            int  from  = state ? 0 : c;
            int  to    = state ? L : std::min(last, L);
            for (int t = from; t < to; t++) {
                S.live[t]++;
            }
        }
    }

    static std::vector<int> profileSchedule(const std::vector<LSOp>& ops, int lo, int hi, int R,
                                            int U, int* cyclesOut, int* peakOut)
    {
        int n = hi - lo;
        std::vector<std::vector<int>> users(n);
        std::vector<int>              consumers(n, 0);
        for (int k = lo; k < hi; k++) {
            for (int d : ops[k].deps) {
                if (d >= lo && d < hi) {
                    users[d - lo].push_back(k);
                    consumers[d - lo]++;
                }
            }
        }
        std::vector<int> cycleOf(n, -1);  // absolute cycle once placed, -1 before
        std::vector<int> subLen(n, 0);    // length of the subtree schedule (for the child order)

        // merge B into A at the smallest admissible shift ; B's ops get
        // their cycles shifted, A is extended. cross deps : an op of B
        // depending on an op already placed in A (memo) must come after it.
        auto merge = [&](ProfSched& A, const ProfSched& B) {
            int LA = A.length(), LB = B.length();
            int smin = 0;
            for (auto& p : B.ops) {
                for (int d : ops[p.first].deps) {
                    if (d >= lo && d < hi && cycleOf[d - lo] >= 0) {
                        bool inB = false;
                        for (auto& q : B.ops) {
                            if (q.first == d) {
                                inB = true;
                                break;
                            }
                        }
                        if (!inB) {
                            smin = std::max(smin, cycleOf[d - lo] + 1 - p.second);
                        }
                    }
                }
            }
            int chosen = LA;
            for (int s = std::max(0, smin); s < LA; s++) {
                bool ok = true;
                for (int t = s; t < std::min(LA, s + LB) && ok; t++) {
                    if (A.live[t] + B.live[t - s] > R || A.issue[t] + B.issue[t - s] > U) {
                        ok = false;
                    }
                }
                if (ok) {
                    chosen = s;
                    break;
                }
            }
            for (auto& p : B.ops) {
                A.ops.push_back({p.first, p.second + chosen});
                cycleOf[p.first - lo] = p.second + chosen;
            }
            profileRecompute(A, ops, lo, hi, cycleOf, users);
        };

        // the recursion : schedule the subtree of op k ; a placed op is a leaf
        std::function<ProfSched(int)> sched = [&](int k) -> ProfSched {
            ProfSched C;
            if (cycleOf[k - lo] >= 0) {
                return C;  // shared value, already placed : a leaf of length 0
            }
            std::vector<int> kids;
            for (int d : ops[k].deps) {
                if (d >= lo && d < hi && cycleOf[d - lo] < 0) {
                    kids.push_back(d);
                }
            }
            std::vector<ProfSched> E;
            for (int d : kids) {
                if (cycleOf[d - lo] < 0) {  // may have been placed by a sibling meanwhile
                    ProfSched S = sched(d);
                    if (!S.ops.empty()) {
                        E.push_back(std::move(S));
                    }
                }
            }
            // residents first (a single weight-0 op each : the background
            // the columns must fit in), then longest first : the short
            // ones slide into the hollows of the long
            auto isResident = [&](const ProfSched& S) {
                return S.ops.size() == 1 && ops[S.ops[0].first].weight == 0;
            };
            std::stable_sort(E.begin(), E.end(), [&](const ProfSched& a, const ProfSched& b) {
                bool ra = isResident(a), rb = isResident(b);
                if (ra != rb) {
                    return ra;
                }
                return a.length() > b.length();
            });
            // the accumulated composition starts from the longest child ; its
            // ops keep their relative cycles as absolute ones
            for (size_t i = 0; i < E.size(); i++) {
                if (i == 0) {
                    C = std::move(E[0]);
                    for (auto& p : C.ops) {
                        cycleOf[p.first - lo] = p.second;
                    }
                    profileRecompute(C, ops, lo, hi, cycleOf, users);
                } else {
                    merge(C, E[i]);
                }
            }
            // place k : after every dep, at the first cycle with room for it
            int t = 0;
            for (int d : ops[k].deps) {
                if (d >= lo && d < hi) {
                    t = std::max(t, cycleOf[d - lo] + 1);
                }
            }
            int w = ops[k].weight;
            while (w > 0 && t < C.length() && C.issue[t] + w > U) {
                t++;
            }
            C.ops.push_back({k, t});
            cycleOf[k - lo] = t;
            profileRecompute(C, ops, lo, hi, cycleOf, users);
            subLen[k - lo] = C.length();
            return C;
        };

        // the sinks of the span are the children of a virtual root
        ProfSched root;
        std::vector<int> sinks;
        for (int k = lo; k < hi; k++) {
            if (consumers[k - lo] == 0) {
                sinks.push_back(k);
            }
        }
        std::vector<ProfSched> E;
        for (int k : sinks) {
            if (cycleOf[k - lo] < 0) {
                ProfSched S = sched(k);
                if (!S.ops.empty()) {
                    E.push_back(std::move(S));
                }
            }
        }
        std::stable_sort(E.begin(), E.end(), [&](const ProfSched& a, const ProfSched& b) {
            bool ra = (a.ops.size() == 1 && ops[a.ops[0].first].weight == 0);
            bool rb = (b.ops.size() == 1 && ops[b.ops[0].first].weight == 0);
            if (ra != rb) {
                return ra;
            }
            return a.length() > b.length();
        });
        for (size_t i = 0; i < E.size(); i++) {
            if (i == 0) {
                root = std::move(E[0]);
                for (auto& p : root.ops) {
                    cycleOf[p.first - lo] = p.second;
                }
                profileRecompute(root, ops, lo, hi, cycleOf, users);
            } else {
                merge(root, E[i]);
            }
        }
        // any op left unplaced (should not happen : every op is a sink or
        // reaches one) is appended in creation order
        for (int k = lo; k < hi; k++) {
            if (cycleOf[k - lo] < 0) {
                cycleOf[k - lo] = root.length();
                root.ops.push_back({k, root.length()});
                profileRecompute(root, ops, lo, hi, cycleOf, users);
            }
        }
        // the order : by cycle, stable by op index -- made dependency-safe by
        // a depth-first emission along that preference (a sibling subtree
        // merged before the one holding a value it reads could otherwise
        // land before it : the greedy composition keeps the profiles, the
        // emission keeps the dependencies)
        std::vector<int> byCycle;
        byCycle.reserve(n);
        for (int k = lo; k < hi; k++) {
            byCycle.push_back(k);
        }
        std::stable_sort(byCycle.begin(), byCycle.end(),
                         [&](int a, int b) { return cycleOf[a - lo] < cycleOf[b - lo]; });
        std::vector<int>  order;
        std::vector<bool> emitted(n, false);
        std::function<void(int)> emit = [&](int k) {
            if (emitted[k - lo]) {
                return;
            }
            emitted[k - lo] = true;
            for (int d : ops[k].deps) {
                if (d >= lo && d < hi) {
                    emit(d);
                }
            }
            order.push_back(k);
        };
        for (int k : byCycle) {
            emit(k);
        }
        if (cyclesOut) {
            *cyclesOut = root.length();
        }
        if (peakOut) {
            int pk = 0;
            for (int v : root.live) {
                pk = std::max(pk, v);
            }
            *peakOut = pk;
        }
        return order;
    }

    /**
     * The pressure-aware list scheduler under (R, U); calls prefer cycles
     * with at most 8 live values (callee-saved constraint). Works on any op
     * vector: the emission path passes fOps, the fusion cost oracle passes a
     * side-effect-free shadow DAG. Optionally reports the schedule length in
     * cycles and the cumulated over-pressure (sum over cycles of
     * max(0, live - R): the spill proxy).
     */
    static std::vector<int> modelSchedule(const std::vector<LSOp>& ops, int lo, int hi, int R,
                                          int U, int* cyclesOut, long* overROut,
                                          int* peakOut = nullptr,
                                          const std::vector<std::string>* shapes = nullptr)
    {
        const int        RCALLEE = 8;
        int              n       = hi - lo;
        std::vector<int> order;
        order.reserve(n);
        std::vector<int>              pending(n, 0);
        std::vector<int>              consumers(n, 0);
        std::vector<std::vector<int>> users(n);
        for (int k = lo; k < hi; k++) {
            for (int d : ops[k].deps) {
                // a resident value is a register : it blocks nothing and
                // counts in no live profile
                if (d >= lo && d < hi && !ops[d].resident) {
                    pending[k - lo]++;
                    consumers[d - lo]++;
                    users[d - lo].push_back(k - lo);
                }
            }
        }
        std::vector<int> height(n, 0);
        for (int k = n - 1; k >= 0; k--) {
            for (int u : users[k]) {
                height[k] = std::max(height[k], height[u] + 1);
            }
        }
        std::vector<int>  remaining = consumers;  // unread results = live
        std::vector<bool> emitted(n, false);
        std::vector<int>  birth(n, 0);  // emission index of each producer
        std::vector<int>  emittedThisCycle;
        int  live = 0, done = 0, cycles = 0, peak = 0;
        long overR = 0;
        std::vector<int> ready;
        for (int k = 0; k < n; k++) {
            if (pending[k] == 0) {
                ready.push_back(k);
            }
        }
        while (done < n) {
            emittedThisCycle.clear();
            // ops becoming ready THIS cycle wait for the next one (latency 1)
            std::vector<int> readyNow = ready;
            for (int slot = 0; slot < U && !readyNow.empty();
                 /* advanced per emitted op's weight below */) {
                // pick the best candidate (k below is span-relative)
                int best = -1, bestScore = INT_MIN;
                for (size_t c = 0; c < readyNow.size(); c++) {
                    int k = readyNow[c];
                    // freed = deps whose last use this would be
                    int freed = 0;
                    for (int d : ops[lo + k].deps) {
                        if (d >= lo && d < hi && remaining[d - lo] == 1) {
                            freed++;
                        }
                    }
                    int creates = (consumers[k] > 0) ? 1 : 0;
                    int score;
                    if (live >= R + U) {
                        // DRAIN THE OLDEST : among pressure-relieving ops,
                        // prefer the one consuming the longest-lived value.
                        // Kernel banks feeding a mix chain are the motive :
                        // height-first postponed the mix, so every kernel
                        // output stayed live until the end (bells, 53/20) ;
                        // age-first folds each kernel into the mix as soon
                        // as it lands -- the natural tile. The R+U margin
                        // (one issue width, the fastest possible reaction)
                        // leaves populations that graze R untouched : at
                        // exactly R the height order was already healthy,
                        // and disturbing it cost fu 7% on the bells.
                        int age = 0;
                        for (int d : ops[lo + k].deps) {
                            if (d >= lo && d < hi && remaining[d - lo] > 0) {
                                age = std::max(age, done - birth[d - lo]);
                            }
                        }
                        score = 1000 * (freed - creates) + std::min(age, 900);
                    } else if (live >= R) {
                        score = 1000 * (freed - creates) + height[k];
                    } else {
                        score = 1000 * height[k] + freed;
                    }
                    // calls prefer low-live cycles: penalize a call issued
                    // while more than RCALLEE values are live
                    if (ops[lo + k].isCall && live > RCALLEE) {
                        score -= 500000;
                    }
                    // STICKY-SHAPE probe (spec LE-GROUPEMENT-HIERARCHIQUE,
                    // question 1) : a mid-order affinity for the last
                    // emitted op's shape -- does DECLARED adjacency pay in
                    // the completion ? Below the 1000-scale regime terms,
                    // above the freed tie-breaks.
                    if (shapes && !order.empty() &&
                        (*shapes)[k] == (*shapes)[order.back() - lo]) {
                        score += 500;
                    }
                    if (score > bestScore) {
                        bestScore = score;
                        best      = (int)c;
                    }
                }
                if (best < 0) {
                    break;
                }
                int k = readyNow[best];
                readyNow.erase(readyNow.begin() + best);
                emitted[k] = true;
                birth[k]   = done;
                done++;
                order.push_back(lo + k);
                emittedThisCycle.push_back(k);
                // composite ops (matrix rows) consume their weight in slots
                slot += ops[lo + k].weight;
                for (int d : ops[lo + k].deps) {
                    if (d >= lo && d < hi && !ops[d].resident) {
                        if (--remaining[d - lo] == 0) {
                            live--;
                        }
                    }
                }
                if (consumers[k] > 0) {
                    live++;
                }
            }
            // update the ready set: newly enabled ops become ready next cycle
            std::vector<int> newReady;
            for (int k : ready) {
                if (!emitted[k]) {
                    newReady.push_back(k);
                }
            }
            for (int k : emittedThisCycle) {
                for (int u : users[k]) {
                    if (--pending[u] == 0) {
                        newReady.push_back(u);
                    }
                }
            }
            ready = std::move(newReady);
            faustassert(!(emittedThisCycle.empty() && ready.empty() && done < n));
            cycles++;
            overR += std::max(0, live - R);
            peak = std::max(peak, live);
        }
        if (cyclesOut) {
            *cyclesOut = cycles;
        }
        if (overROut) {
            *overROut = overR;
        }
        if (peakOut) {
            *peakOut = peak;
        }
        return order;
    }

    /**
     * Fusion cost oracle: estimated per-chunk cost of running the given
     * member set as ONE loop. A side-effect-free shadow of walk() builds the
     * op/dependency structure (no CS on slow leaves, no table or UI
     * declarations, no code strings), the model scheduler prices it:
     *
     *   cost = N * (cycles + SPILL_W * overPressure) + C_L
     *
     * with N the chunk size, C_L the per-loop overhead and SPILL_W the
     * cycles charged per register-cycle above R (the spill proxy). The
     * merged-versus-separate comparison then accounts for both the saved
     * loop overhead and the pressure risk of oversized bodies.
     */
    // Build the reader tables the store price rests on. A materialized
    // member is written to its chunk buffer only if something outside the
    // loop that computes it will read it ; inside the loop its history
    // rides in the rotating locals. Called once, before the fusion oracle,
    // so that the oracle prices the stores the emission will actually write.
    void storeClasses(Tree L)
    {
        const std::vector<Tree>& mat = fSN.materialized();
        const int                n   = (int)mat.size();
        fReadersOf.assign(n, {});
        fStoreForced.assign(n, 0);
        auto resolve = [&](int ix) { return (fAliasIx[ix] >= 0) ? fAliasIx[ix] : ix; };
        for (int m = 0; m < n; m++) {
            for (int r : fSN.refs(m)) {
                fReadersOf[resolve(r)].push_back(m);
            }
            if (fAliasIx[m] >= 0) {
                fReadersOf[fAliasIx[m]].push_back(m);
            }
            // a read at a delay that is not a literal goes through the buffer
            std::set<Tree, treeorder> seen;
            std::function<void(Tree)> vr = [&](Tree u) {
                if (!seen.insert(u).second) {
                    return;
                }
                Tree x, y;
                int  lit;
                if (isSigDelay(u, x, y) && fSN.indexOf(x) >= 0 && !isSigInt(y, &lit)) {
                    fStoreForced[resolve(fSN.indexOf(x))] = 1;
                }
                Tree var, body;
                if (isRec(u, var, body)) {
                    if (body) {
                        vr(body);
                    }
                    return;
                }
                for (int k = 0; k < u->arity(); k++) {
                    vr(u->branch(k));
                }
            };
            vr(defOf(mat[m]));
        }
        // the outputs and the display captures read through the buffers,
        // wherever the members they read are placed
        auto forceIn = [&](Tree p) {
            std::set<Tree, treeorder> seen;
            std::function<void(Tree)> rec = [&](Tree u) {
                if (!seen.insert(u).second) {
                    return;
                }
                int ix = fSN.indexOf(u);
                if (ix >= 0) {
                    fStoreForced[resolve(ix)] = 1;
                    return;
                }
                Tree var, body;
                if (isRec(u, var, body)) {
                    if (body) {
                        rec(body);
                    }
                    return;
                }
                for (int k = 0; k < u->arity(); k++) {
                    rec(u->branch(k));
                }
            };
            rec(p);
        };
        for (Tree l1 = L; isList(l1); l1 = tl(l1)) {
            forceIn(hd(l1));
        }
        for (Tree p : fC->fDisplayCapturePoints) {
            forceIn(p);
        }
        // the row-op regime writes its members whatever their readers
        if (fRowOp) {
            fStoreForced.assign(n, 1);
        }
    }
    // does this member's value have to reach memory when the block holding
    // it is exactly `inSet` ? Under -ls-regstate a member read only inside
    // its own block keeps no buffer, so the oracle must not price a store
    // for it -- otherwise fusing two loops looks free of memory savings
    // while the emission drops the writes that joined them.
    bool storedIn(int m, const std::set<int>& inSet) const
    {
        if (!gGlobal->gLSRegState || fStoreForced.empty() || fStoreForced[m]) {
            // fStoreForced is empty until the classification runs : the
            // dissolve phase prices blocks before it, and there every
            // member is written, as the emission did until then
            return true;
        }
        if (fSN.maxDelayOf(fSN.materialized()[m]) > gGlobal->gMaxCopyDelay) {
            return true;  // a long line lives in memory anyway
        }
        for (int r : fReadersOf[m]) {
            if (inSet.count(r) == 0) {
                return true;
            }
        }
        return false;
    }
    long blockCostShadow(const std::vector<int>& members, long* overROut = nullptr,
                         int* peakOut = nullptr, bool constantsLive = true,
                         int loadWOverride = -1, bool* hasCallOut = nullptr,
                         std::vector<LSOp>* sopsOut = nullptr,
                         const std::set<int>* noBoundary = nullptr)
    {
        const long CL = gGlobal->gLSCl, SPILLW = gGlobal->gLSSpillW;
        const std::vector<Tree>& mat = fSN.materialized();
        std::vector<LSOp>        sops;
        std::map<Tree, int, treeorder>      memo;
        std::map<int, int>       rootOf;  // member -> shadow op index (-1: leaf)
        // member -> the m ops of its carried history window (see the
        // register-window pricing in the sigDelay case)
        std::map<int, std::vector<int>> carriedOps;
        std::set<int>            inSet(members.begin(), members.end());

        // a buffer load costs an issue slot (the model's Read): this is what
        // makes fusion visibly profitable to the oracle -- scalarized in-set
        // reads cost nothing, the same reads across a boundary cost a slot
        const int loadW = (loadWOverride >= 0) ? loadWOverride : gGlobal->gLSLoadW;
        // a reload of a spilled constant is a memory operand folded into the
        // arithmetic op that uses it : a memory-port operation, not an issue
        // slot and not a streamed buffer read -- its own weight (-ls-cload), on
        // the ports. Under the campaign tarif -ls-load 0 the shared weight made
        // 60 reloads a frame free and the greedy fused two blocks into one that
        // pays them (m99 : +15 % under g++ for two merges of model gain 4) ;
        // priced as issue slots instead, the 3 x 3 tile of m99 lost its election
        // to 2 x 5 against the measure (LES-TUILES 6.6)
        const int cloadW = (loadWOverride >= 0) ? loadWOverride : gGlobal->gLSCLoadW;
        // the row regime prices only member sets carrying a recurrence
        // (mirror of blockHasRecurrence : same criterion as emission)
        bool shadowRowRegime = false;
        if (fRowOp) {
            for (int s : members) {
                std::vector<int> st{s};
                std::set<int>    vis;
                while (!st.empty() && !shadowRowRegime) {
                    int u = st.back();
                    st.pop_back();
                    for (int v : fSN.refs(u)) {
                        if (v == s) {
                            shadowRowRegime = true;
                            break;
                        }
                        if (inSet.count(v) && vis.insert(v).second) {
                            st.push_back(v);
                        }
                    }
                }
                if (shadowRowRegime) {
                    break;
                }
            }
        }
        auto load = [&](Tree t, std::vector<int> deps) -> int {
            if (loadW == 0) {
                return -1;  // loads free (leaf)
            }
            int id = -1;
            for (int w = 0; w < loadW; w++) {
                LSOp o;
                o.shape = 11;
                if (id >= 0) {
                    o.deps.push_back(id);  // heavier loads: a chain of slots
                } else {
                    for (int d : deps) {
                        if (d >= 0) {
                            o.deps.push_back(d);
                        }
                    }
                }
                sops.push_back(o);
                id = (int)sops.size() - 1;
            }
            memo[t] = id;
            return id;
        };

        std::function<int(Tree, bool)> sw = [&](Tree t, bool root) -> int {
            if (!root) {
                auto sh = memo.find(t);
                if (sh != memo.end()) {
                    return sh->second;
                }
                int idx = fSN.indexOf(t);
                if (idx >= 0 && !(noBoundary && noBoundary->count(idx))) {
                    // in-set instantaneous reads are scalarized (the root
                    // value); everything else is a buffer load. A
                    // noBoundary index prices the Dissolve move : the
                    // walk descends into the definition instead.
                    if (inSet.count(idx) && rootOf.count(idx)) {
                        return rootOf[idx];
                    }
                    return load(t, {});
                }
            }
            int     i;
            int64_t i64;
            double  r;
            Tree    x, y, z, sel, ff, largs, tb, size, gen, wi, ws, ri, label;
            auto op = [&](std::vector<int> deps, bool call, int shp = 0) -> int {
                LSOp o;
                for (int d : deps) {
                    if (d >= 0) {
                        o.deps.push_back(d);
                    }
                }
                o.isCall = call;
                o.shape  = shp;
                sops.push_back(o);
                int id = (int)sops.size() - 1;
                memo[t] = id;
                return id;
            };
            // shape tag of an external name (userdata, foreign functions):
            // stable small hash, offset out of the fixed tags' range
            auto nameShape = [](const std::string& nm) -> int {
                int h = 0;
                for (char c : nm) {
                    h = (h * 31 + (unsigned char)c) % 700;
                }
                return 200 + h;
            };
            // constants and slow leaves are LIVE VALUES: materialized once
            // (one shadow op, no deps, memoized per distinct tree across the
            // whole member set) and consumed at each use -- the scheduler
            // tracks their liveness like any value. This is the pressure the
            // R=16 optimum revealed: ~90 live fConst in a big body occupy
            // registers the signal-only model did not count. Sharing a
            // constant across fused members is now a fusion benefit the
            // oracle can see. (Inputs stay free: per-iteration loads, not
            // resident values -- a separate refinement.)
            if (SuperNodeGraph::isNum(t)) {
                return constantsLive ? op({}, false, 10) : -1;
            }
            if (isSigInput(t, &i)) {
                return -1;
            }
            if (isSigAttach(t, x, y) && !SuperNodeGraph::isSlow(y)) {
                return op({sw(x, false), sw(y, false)}, false, 1);
            }
            if (SuperNodeGraph::isSlow(t)) {
                return constantsLive ? op({}, false, 10) : -1;
            }
            if (tvec V; kernelWorkVec(t, V)) {
                // FAITHFUL kernel body (the bells lesson : a 3-tap kernel
                // priced as one op made every fusion comparison a fiction).
                // Per non-zero tap : a source read -- carried window when
                // the source is a fused member with a short line, a buffer
                // load otherwise, exactly like sigDelay -- a multiply for
                // non-unit coefficients (the coefficient is a live slow
                // value), and the adds that chain the taps.
                int  ix     = fSN.indexOf(V[0]);
                bool inset  = (ix >= 0) && inSet.count(ix);
                bool window = inset && fSN.maxDelayOf(mat[ix]) <= gGlobal->gMaxCopyDelay;
                int  m      = (ix >= 0) ? fSN.maxDelayOf(mat[ix]) : 0;
                if (window && m > 0) {
                    auto& w = carriedOps[ix];
                    if (w.empty()) {
                        for (int k = 0; k < m; k++) {
                            LSOp o;
                            o.shape = 13;  // carried history value
                            sops.push_back(o);
                            w.push_back((int)sops.size() - 1);
                        }
                    }
                }
                int acc = -1;
                for (size_t k2 = 1; k2 < V.size(); k2++) {
                    if (isZero(V[k2])) {
                        continue;
                    }
                    int d   = int(k2) - 1;
                    int src = -1;
                    if (d == 0 && inset && rootOf.count(ix)) {
                        src = rootOf[ix];
                    } else if (window && d >= 1 && d <= m) {
                        src = carriedOps[ix][d - 1];
                    } else if (ix >= 0) {
                        src = load(t, {});
                    } else {
                        src = sw(V[0], false);  // inlined source, costed once
                    }
                    int prod = isOne(V[k2])
                                   ? src
                                   : op({src, sw(V[k2], false)}, false, 100 + kMul);
                    acc = (acc < 0) ? prod : op({acc, prod}, false, 100 + kAdd);
                }
                return (acc >= 0) ? acc : op({}, false, 7);
            }
            if (isSigDelay(t, x, y)) {
                int  dmin, dmax;
                bool dvar;
                SuperNodeGraph::delayBounds(y, dmin, dmax, dvar);
                int ix = fSN.indexOf(x);
                if (ix >= 0) {
                    if (inSet.count(ix) && dmin == 0 && !dvar && rootOf.count(ix)) {
                        return rootOf[ix];
                    }
                    if (inSet.count(ix) && !dvar &&
                        fSN.maxDelayOf(mat[ix]) <= gGlobal->gMaxCopyDelay) {
                        // Carried history window : inside the fused loop a
                        // short line (copy class, mxd <= mcd) rides in
                        // registers -- LLVM promotes the loop-carried
                        // reads -- so a read costs no load. It is not
                        // free either : the window is m RESIDENT VALUES,
                        // priced like the live constants, and the
                        // over-pressure penalty arbitrates -- a body that
                        // can afford mxd+1 registers fuses, one that
                        // cannot is refused by its own spill cost (the
                        // budget question, answered by the model instead
                        // of a rigid mxd threshold). Across blocks the
                        // same read pays the boundary load below ; a long
                        // ring stays a load on both sides (the line
                        // persists, fusion saves nothing there).
                        int   m = fSN.maxDelayOf(mat[ix]);
                        auto& w = carriedOps[ix];
                        if (w.empty()) {
                            for (int k = 0; k < m; k++) {
                                LSOp o;
                                o.shape = 13;  // carried history value
                                sops.push_back(o);
                                w.push_back((int)sops.size() - 1);
                            }
                        }
                        int d = std::min(std::max(dmin, 1), m);
                        return w[d - 1];
                    }
                    if (dvar && !SuperNodeGraph::isSlow(y)) {
                        return load(t, {sw(y, false)});  // indexed load
                    }
                    return load(t, {});  // constant-delay buffer load
                }
                return sw(x, false);
            }
            if (isSigBinOp(t, &i, x, y)) {
                bool call = (i == kRem) && (getCertifiedSigType(t)->nature() == kReal);
                return op({sw(x, false), sw(y, false)}, call, 100 + i);
            }
            if (getUserData(t)) {
                std::vector<int> deps;
                for (int k = 0; k < t->arity(); k++) {
                    deps.push_back(sw(t->branch(k), false));
                }
                const std::string nm = ((xtended*)getUserData(t))->name();
                return op(deps, SuperNodeGraph::isCallPrim(nm), nameShape(nm));
            }
            if (isSigFFun(t, ff, largs)) {
                std::vector<int> deps;
                for (int k = 0; k < ffarity(ff); k++) {
                    deps.push_back(sw(nth(largs, k), false));
                }
                return op(deps, true, nameShape(ffname(ff)));
            }
            if (isSigSelect2(t, sel, x, y)) {
                return op({sw(sel, false), sw(x, false), sw(y, false)}, false, 2);
            }
            if (isSigIntCast(t, x) || isSigBitCast(t, x) || isSigFloatCast(t, x)) {
                return op({sw(x, false)}, false, 3);
            }
            if (isSigRDTbl(t, tb, ri) && isSigWRTbl(tb, size, gen)) {
                return op({sw(ri, false)}, false, 4);
            }
            if (isSigVBargraph(t, label, x, y, z) || isSigHBargraph(t, label, x, y, z)) {
                return op({sw(z, false)}, false, 5);
            }
            if (isSigAssertBounds(t, x, y, z)) {
                return sw(z, false);
            }
            if (tvec V; isSigSum(t, V)) {
                if (fRowOp && fMatrix.isRow(t) &&
                    getCertifiedSigType(t)->nature() != kInt && shadowRowRegime) {
                    // MATRIX ROW OP : the shadow mirrors the emission --
                    // per term a live coefficient and the operand (the
                    // per-term product ops disappear into the composite),
                    // one op whose weight is the vectorized reduction
                    // tariff : ceil(n/4) multiply slots + ceil((n-1)/4)
                    // add slots.
                    std::vector<int> deps;
                    int              nz = 0;
                    for (Tree b : V) {
                        if (isZero(b)) {
                            continue;
                        }
                        nz++;
                        Tree a2, b2;
                        if (isSigMul(b, a2, b2) && (SuperNodeGraph::isSlow(a2) !=
                                                    SuperNodeGraph::isSlow(b2))) {
                            deps.push_back(sw(SuperNodeGraph::isSlow(a2) ? a2 : b2, false));
                            deps.push_back(sw(SuperNodeGraph::isSlow(a2) ? b2 : a2, false));
                        } else {
                            deps.push_back(sw(b, false));
                        }
                    }
                    int id           = op(deps, false, 14);
                    sops[id].weight  = std::max(1, (nz + 3) / 4 + (nz + 2) / 4);
                    return id;
                }
                std::vector<int> deps;
                for (Tree b : V) {
                    if (!isZero(b)) {
                        deps.push_back(sw(b, false));
                    }
                }
                return op(deps, false, 6);
            }
            if (tvec V; isSigIIR(t, V)) {
                // y = X + sum a_i * y@i : the state window is 'order'
                // RESIDENT VALUES (the transposed emission keeps them in
                // scalars), each non-zero tap a multiply by a live slow
                // coefficient and an add into the recurrence.
                int acc = sw(V[1], false);
                for (size_t k2 = 3; k2 < V.size(); k2++) {
                    if (isZero(V[k2])) {
                        continue;
                    }
                    LSOp st;
                    st.shape = 13;  // carried state value
                    sops.push_back(st);
                    int sid  = (int)sops.size() - 1;
                    int prod = isOne(V[k2])
                                   ? sid
                                   : op({sid, sw(V[k2], false)}, false, 100 + kMul);
                    acc = (acc >= 0) ? op({acc, prod}, false, 100 + kAdd) : prod;
                }
                return (acc >= 0) ? acc : op({}, false, 8);
            }
            return op({}, false, 9);  // unknown: one slot, no deps
        };

        for (int m : members) {
            Tree d      = SuperNodeGraph::defOf(mat[m]);
            int  r      = sw(d, d == mat[m]);
            rootOf[m]   = r;
            if (!storedIn(m, inSet)) {
                continue;  // register-resident in this block : no store to price
            }
            LSOp store;
            if (r >= 0) {
                store.deps.push_back(r);
            }
            store.isStore = true;
            store.shape   = 12;
            sops.push_back(store);
        }
        int  cycles = 0;
        long overR  = 0;
        int  peak   = 0;
        // under the latency term, the carried states of the member set are
        // register-resident for the whole iteration (they are read at the
        // top and written at the bottom), so the scheduler works against
        // the budget they leave : without this, seven 9-deep cascades
        // (126 states) were priced as fitting 32 registers
        int carried = 0;
        if (gGlobal->gLSLatency > 0 || gGlobal->gLSRegClasses) {
            for (const auto& kv : carriedOps) {
                carried += (int)kv.second.size();
            }
        }
        // THREE CLASSES OF REGISTERS (-ls-regs3). A value in a register is
        // one of three things, and they do not spill at the same price :
        //   the STATES, carried from one frame to the next, read at the top
        //   of the iteration and written at the bottom -- a spilled state
        //   costs a load and a store per frame, for ever, and it is the
        //   state in memory that serializes the frames ;
        //   the CONSTANTS, permanent too but never written -- a constant
        //   out of registers costs one pipelined load per use ;
        //   the TEMPORARIES, the intermediate results waiting for their
        //   consumers, a profile that rises and falls within the frame --
        //   a spill is a store at the definition and a load at the use.
        // One budget for the three (states + resident constants + the peak
        // of the temporaries within R), and the excess spills in the order
        // of the cheapest : constants first, the least used first, then
        // the temporaries at the spill weight, the states last. Without
        // this the model priced every excess as a spilled temporary and
        // could not tell 3 x 3 tiles (18 states, fits) from 3 x 9 (54
        // states, 119 stack operations per frame).
        int  states = 0, constLoads = 0, stateSpill = 0, cres = 0;
        if (gGlobal->gLSRegClasses) {
            states = carried;
            std::vector<int> uses;  // per constant, its number of uses
            {
                std::map<int, int> useOf;
                for (LSOp& o : sops) {
                    if (o.shape == 10 || o.shape == 13) {
                        o.resident = true;
                        o.weight   = 0;  // a register, no issue slot
                    }
                }
                for (const LSOp& o : sops) {
                    for (int d : o.deps) {
                        if (d >= 0 && sops[d].shape == 10) {
                            useOf[d]++;
                        }
                    }
                }
                for (const auto& kv : useOf) {
                    uses.push_back(kv.second);
                }
                for (size_t k = 0; k < sops.size(); k++) {
                    if (sops[k].shape == 10 && !useOf.count((int)k)) {
                        uses.push_back(0);  // materialized, never read
                    }
                }
            }
            const int R = gGlobal->gLSRegisters;
            // The TEMPORARIES first : they are the flow, scheduled against the
            // whole budget ; the states take what the flow leaves, then the
            // constants, and the rest spills. A spilled state costs its
            // traffic -- a load and a store per frame, two memory operations
            // and two issue slots -- and does NOT serialize the frames. The
            // former law (states first, the temporaries against what they
            // leave, and a spilled state serializing the frames) priced the
            // 3 x 9 tile of m99 (54 states over R = 40 : one register left to
            // the flow, over-pressure 504) at 34 times the 3 x 3, where the
            // measure says +3 to +35 % on three judges (LES-TUILES 6.1).
            modelSchedule(sops, 0, (int)sops.size(), R, gGlobal->gLSWidth, &cycles, &overR, &peak);
            const int statesResident = std::min(states, std::max(0, R - peak));
            stateSpill               = states - statesResident;
            // the constants take the registers left by the flow and the
            // resident states ; the least used ones go to memory first
            const int C = (int)uses.size();
            cres        = std::min(C, std::max(0, R - statesResident - peak));
            std::sort(uses.begin(), uses.end());
            for (int k = 0; k < C - cres; k++) {
                constLoads += uses[k];
            }
            peak += statesResident + cres;
        } else {
            modelSchedule(sops, 0, (int)sops.size(), std::max(1, gGlobal->gLSRegisters - carried),
                          gGlobal->gLSWidth, &cycles, &overR, &peak);
            peak += carried;
        }
        if (hasCallOut) {
            *hasCallOut = false;
            for (const LSOp& o : sops) {
                if (o.isCall) {
                    *hasCallOut = true;
                    break;
                }
            }
        }
        if (overROut) {
            *overROut = overR;
        }
        if (peakOut) {
            *peakOut = peak;
        }
        // The LATENCY term (-ls-latency k). One isolated iteration is bounded
        // by its critical path, and a loop whose body is a dependent chain
        // (a filter cascade : each stage waits for the previous one) fills
        // its slots poorly -- but the core overlaps consecutive frames as
        // long as the loop's states stay in registers and its body fits
        // the reorder window, so its steady state is the largest of the
        // resource bound, the memory bound, the loop-carried recurrence
        // bound and the critical path divided by the frames in flight.
        // Measured on a 9-deep cascade alone in its loop : 19 cycles per
        // frame against a 56-cycle critical path, 4 frames overlapped ;
        // the same loop serialized across frames runs 4 times slower. The
        // isolated-iteration price made a chain look 3 times dearer than
        // it is and handed the matrices to stage-major tiles, which pay
        // for their intra-frame overlap in buffers.
        long iter = cycles;
        long tAlu = 0, tMem = 0, tRec = 0, tOverlap = 1;  // the latency term's components, for the trace
        if (gGlobal->gLSRegClasses && gGlobal->gLSLatency == 0) {
            // the spilled classes, priced in slots under the isolated
            // iteration : a load per use of a spilled constant, a load and
            // a store per frame for a spilled state
            const int U = std::max(1, gGlobal->gLSWidth);
            iter += ((long)constLoads * cloadW + 2L * stateSpill + U - 1) / U;
        }
        if (gGlobal->gLSLatency > 0) {
            // The issue slots, with the SIMD PACKING the compiler will find :
            // isomorphic operations of the same dependency level are
            // independent and pack into one vector instruction, `lanes` at
            // a time (two doubles, four floats on a 128-bit unit). This is
            // what separates a square tile from a chain of the same area --
            // 3 x 3 gives every operation three independent copies (56
            // adjacent isomorphic pairs in the emitted loop, 18.3 cycles a
            // frame measured), 1 x 9 gives none (8 pairs, 20.8 cycles, its
            // scalar slot count exactly). Loads, stores, calls and composite
            // ops stay scalar.
            const int lanes = (gGlobal->gFloatSize == 2) ? 2 : 4;
            long slots = 0, memops = 0;
            {
                std::vector<int> level(sops.size(), 0);
                std::map<std::pair<int, int>, int> packs;  // (level, shape) -> count
                for (size_t k = 0; k < sops.size(); k++) {
                    const LSOp& o = sops[k];
                    for (int d : o.deps) {
                        if (d >= 0) {
                            level[k] = std::max(level[k], level[d] + 1);
                        }
                    }
                    if (o.shape == 12) {
                        memops++;  // a store, one memory port
                    } else if (o.weight == 1 && !o.isCall && o.shape != 11 && o.shape >= 100) {
                        packs[{level[k], o.shape}]++;  // a packable arithmetic op
                    } else {
                        slots += o.weight;  // a load, a call, a composite op : scalar slots
                    }
                }
                for (const auto& kv : packs) {
                    slots += (kv.second + lanes - 1) / lanes;
                }
            }
            // the spilled classes : a reload per use of a spilled constant
            // on the memory ports (a folded memory operand), a load and a
            // store per frame for a spilled state (two issue slots and the
            // memory ports)
            slots += 2L * stateSpill;
            memops += (long)constLoads * cloadW + 2L * stateSpill;
            const int  U   = std::max(1, gGlobal->gLSWidth);
            const long alu = (slots + U - 1) / U;
            const long mem = (memops + 2) / 3;  // three memory ports, the eval machine's M
            // Recurrence bound : PER STATE, the longest path from a member's
            // own carried history to its own root -- the length of the cycle
            // no overlap can shorten, since the value written this frame is
            // the one read the next. Taking instead the longest path from ANY
            // carried value made the bound grow when two stages of a chain
            // were fused, although neither state's own cycle had changed :
            // the path from the first stage's state through the second
            // stage's body is an intra-frame chain, already priced by the
            // critical path divided by the frames in flight. That reading
            // made fusion look harmful on chained filters -- on a matrix of
            // four chains of three, the oracle cut by stage (three loops,
            // twelve stores a frame) where one loop measured 34% faster.
            // The cycle is measured in LATENCY, not in operations : the
            // schedule's unit-latency machine bounds the issue, the recurrence
            // is bounded by the pipeline depths of the operations on the
            // cycle. A biquad's own cycle, five operations, counted 5 where
            // the measure gives 7 (the 1 x 1 tiles of m99 : 7 cycles a frame,
            // latency-bound). Contraction under fast-math halves the adds of a
            // multiply-add chain : an add after a multiply is priced 2.
            auto opLatency = [](const LSOp& o) -> int {
                if (o.isCall) {
                    return 20;
                }
                switch (o.shape) {
                    case 10: case 13: return 0;   // a resident value : ready
                    case 11: case 4: case 1: return 4;  // a load, a table read, a line read
                    case 12: return 1;            // a store
                    case 3: return 3;             // a cast
                    case 2: return 1;             // a selection
                    case 100 + kMul: return 4;
                    case 100 + kDiv: return 10;
                    case 100 + kRem: return 20;
                    case 100 + kAdd: case 100 + kSub: return o.isInt ? 1 : 2;
                    default: return (o.shape >= 100) ? (o.isInt ? 1 : 3) : 2;
                }
            };
            long rec = 0;
            for (const auto& kv : carriedOps) {
                auto it = rootOf.find(kv.first);
                if (it == rootOf.end() || it->second < 0) {
                    continue;
                }
                const std::set<int>      own(kv.second.begin(), kv.second.end());
                std::vector<int>         depth(sops.size(), -1);
                std::function<int(int)>  reach = [&](int o) -> int {
                    if (depth[o] >= 0) {
                        return depth[o] == INT_MAX ? -1 : depth[o];
                    }
                    depth[o] = INT_MAX;  // visiting : a cycle never reaches
                    int best = own.count(o) ? 0 : -1;
                    for (int d : sops[o].deps) {
                        int r = reach(d);
                        if (r >= 0) {
                            best = std::max(best, r + opLatency(sops[o]));
                        }
                    }
                    depth[o] = (best >= 0) ? best : INT_MAX;
                    return best;
                };
                int r = reach(it->second);
                if (r >= 0) {
                    rec = std::max(rec, (long)r);
                }
            }
            // the frames overlap as long as the states stay in registers ;
            // under the three classes a spilled temporary is stack traffic
            // within the frame, only a spilled state serializes the frames
            // the frames overlap as long as the flow stays in registers : under
            // the three classes a spilled state is traffic, not serialization
            const bool serialized = gGlobal->gLSRegClasses ? false : (overR > 0);
            const long overlap    = serialized ? 1 : gGlobal->gLSLatency;
            iter = std::max({alu, mem, rec, (long)((cycles + overlap - 1) / overlap)});
            tAlu = alu, tMem = mem, tRec = rec, tOverlap = overlap;
        }
        if (global::isOpt("FAUST_LS_TRACE")) {  // PROBE
            fprintf(stderr,
                    "  shadow [%zu members, %zu ops] cycles %d alu %ld mem %ld rec %ld overlap %ld iter %ld | "
                    "states %d cres %d constLoads %d stateSpill %d peak %d overR %ld -> %ld\n",
                    members.size(), sops.size(), cycles, tAlu, tMem, tRec, tOverlap, iter, states, cres,
                    constLoads, stateSpill, peak, overR, (long)gGlobal->gVecSize * (iter + SPILLW * overR) + CL);
        }
        if (sopsOut) {
            *sopsOut = std::move(sops);
        }
        return (long)gGlobal->gVecSize * (iter + SPILLW * overR) + CL;
    }

    /**
     * Normative scorer (CSFUSE par.4.1): replay ANY topological order of a
     * shadow on the (R, U) machine -- latency 1, U slots per cycle, empty
     * cycles impossible (latency 1 bounds a stall to the next cycle) --
     * with the liveness SAMPLED AT THE END OF EACH CYCLE, births counted
     * and deaths deducted. modelSchedule samples the same way; scoring
     * every scheduler's order through this one function is what makes the
     * portfolio's notes comparable by construction.
     */
    static void replayOrderScore(const std::vector<LSOp>& ops, const std::vector<int>& order,
                                 int R, int U, int* cyclesOut, long* overROut,
                                 int* peakOut = nullptr)
    {
        int              n = (int)ops.size();
        std::vector<int> consumers(n, 0);
        for (int k = 0; k < n; k++) {
            for (int d : ops[k].deps) {
                consumers[d]++;
            }
        }
        std::vector<int> remaining = consumers;
        std::vector<int> cyc(n, -1);
        int              cur = 0, slots = 0, live = 0, peak = 0;
        long             overR  = 0;
        auto             closeCycle = [&] {
            overR += std::max(0, live - R);
            peak = std::max(peak, live);
            cur++;
            slots = 0;
        };
        for (int o : order) {
            int lo = 0;
            for (int d : ops[o].deps) {
                lo = std::max(lo, cyc[d] + 1);
            }
            while (cur < lo || slots == U) {
                closeCycle();
            }
            cyc[o] = cur;
            slots++;
            for (int d : ops[o].deps) {
                if (--remaining[d] == 0 && consumers[d] > 0) {
                    live--;
                }
            }
            if (consumers[o] > 0) {
                live++;
            }
        }
        if (slots > 0) {
            closeCycle();  // the final partial cycle is sampled too
        }
        if (cyclesOut) {
            *cyclesOut = cur;
        }
        if (overROut) {
            *overROut = overR;
        }
        if (peakOut) {
            *peakOut = peak;
        }
    }

    /**
     * Order-sensitive SLP-visible features of a shadow order (RUM stage B
     * candidates): iso-adjacency and 4-packs mirror emitLoop's computation
     * with the shadow shape tag standing in for the digit-erased code
     * string ; dist is the mean order-distance from a value to its
     * consumers (x1000), the locality clang's window actually sees.
     */
    static void orderFeatures(const std::vector<LSOp>& ops, const std::vector<int>& order,
                              int* isoOut, int* packs4Out, long* distX1000Out)
    {
        int              isoadj = 0, packs4 = 0, runlen = 0, prevIx = -1;
        int              prevSh = -1;
        std::vector<int> pos(ops.size(), 0);
        for (size_t p = 0; p < order.size(); p++) {
            pos[order[p]] = (int)p;
        }
        long distSum = 0, distCnt = 0;
        for (int k : order) {
            bool dep = false;
            for (int d : ops[k].deps) {
                if (d == prevIx) {
                    dep = true;
                }
                distSum += pos[k] - pos[d];
                distCnt++;
            }
            int sh = ops[k].shape;
            if (prevIx >= 0 && sh == prevSh && !dep) {
                isoadj++;
                runlen++;
            } else {
                packs4 += (runlen + 1) / 4;
                runlen = 0;
            }
            prevSh = sh;
            prevIx = k;
        }
        packs4 += (runlen + 1) / 4;
        if (isoOut) {
            *isoOut = isoadj;
        }
        if (packs4Out) {
            *packs4Out = packs4;
        }
        if (distX1000Out) {
            *distX1000Out = distCnt ? (distSum * 1000) / distCnt : 0;
        }
    }
};

// -sng: the super-node DAG as graphviz clusters -- the -ls counterpart of
// -sg (signal graph) and -tg (task graph). One cluster per super-node,
// annotated with the model's view of its body (emission-isomorphic shadow:
// ops, peak pressure / R); one node per materialized signal (blue: recursive
// projection, green: delayed, yellow: shared instantaneous); solid edges:
// instantaneous reads (they order the members), dashed: delayed reads.
// Output loops and d >= chunk free reads are not part of the partition and
// do not appear.
void LoopSplitEmitter::dumpSuperNodesDot(std::ostream& out)
{
    const std::vector<Tree>& mat = fSN.materialized();
    out << "digraph supernodes {\n";
    out << "  rankdir=BT; node [style=filled, fontname=\"helvetica\"];\n";
    for (int b = 0; b < fSN.blockCount(); b++) {
        long overR = 0;
        int  peak  = 0;
        blockCostShadow(fSN.blockMembers(b), &overR, &peak, false, 0);
        out << "  subgraph cluster_" << b << " {\n";
        out << "    label=\"loop " << b << "  ·  " << fSN.opsEstimate(b)
            << " ops  ·  pressure " << peak << "/" << gGlobal->gLSRegisters
            << (overR > 0 ? "  ·  over-pressure!" : "") << "\";\n";
        out << "    style=rounded; color=\"#4477cc\";\n";
        for (int m : fSN.blockMembers(b)) {
            Tree        t = mat[m];
            int         i;
            Tree        w;
            const char* color = "#fdf1c9";  // shared instantaneous
            const char* kind  = "shared";
            if (isProj(t, &i, w)) {
                color = "#cfe0f5";  // recursive projection
                kind  = "rec";
            } else if (fSN.maxDelayOf(t) > 0) {
                color = "#d8ecd2";  // delayed
                kind  = "delayed";
            }
            out << "    s" << m << " [label=\"s" << m << " (" << kind;
            if (int d = fSN.maxDelayOf(t)) {
                out << ", maxd " << d;
            }
            out << ")\", fillcolor=\"" << color << "\"];\n";
        }
        out << "  }\n";
    }
    for (int i = 0; i < (int)mat.size(); i++) {
        for (int j : fSN.refs(i)) {
            bool inst = fSN.refs0(i).count(j) > 0;
            out << "  s" << j << " -> s" << i
                << (inst ? ";" : " [style=dashed, color=\"#cc7733\"];") << "\n";
        }
    }
    out << "}\n";
}

// ---- the families : bundles first (the width), their depth second ------------------
//
// A BUNDLE is a class of the partition refinement that starts from the shape
// classes and splits a class as soon as two of its members differ by the
// multiset of classes they read or feed, to the fixed point : the nodes that
// nothing distinguishes, by computation or by context. A stereo pair lands in
// one bundle, and what looked like fan-out at signal level is the bundle's
// WIDTH, not a branching (LA-FORME-ET-LE-PARTAGE, section 3). On the examples,
// 504 of the 539 tiles of width >= 2 are k x 1 : the width is the general case.
//
// A LINK u -> v is a read where v is u's only reader and u is v's only read,
// among blocks : links form disjoint paths. Two bundles A and B EXTEND each
// other when the links from A to B are a bijection ; a maximal chain of bundles
// so extended is a family of P chains and S stages, chains numbered by the
// serial of their first member (the order of everything else), stages by
// position.
std::vector<LoopSplitEmitter::Family> LoopSplitEmitter::detectFamilies(bool trace) const
{
    const std::vector<Tree>& mt = fSN.materialized();
    // The shape must be blind to the names of recursive variables : two
    // structurally identical filters carry distinct fresh symbols, and ocppShape
    // keeps them. The de Bruijn form is alpha-invariant by construction and,
    // being hash-consed, equal shapes are the same tree.
    std::map<Tree, Tree, treeorder> db;
    digraph<Tree>                   GT;
    for (Tree t : mt) {
        db[t] = sym2deBruijn(t);
        GT.add(db[t]);
    }
    auto      shapeOf = ocppShapeFunctor(GT);
    const int nb      = fSN.blockCount();
    std::vector<std::string> sig(nb);
    for (int b = 0; b < nb; b++) {
        std::ostringstream os;
        for (int m : fSN.blockMembers(b)) {
            os << shapeOf(db[mt[m]]) << ",";
        }
        sig[b] = os.str();
    }
    std::vector<std::set<int>> succ(nb), pred(nb);
    for (int b = 0; b < nb; b++) {
        pred[b] = fSN.blockDeps(b);
        succ[b] = fSN.blockConsumers(b);
        pred[b].erase(b);
        succ[b].erase(b);
    }
    // the bundles : partition refinement to the fixed point
    std::vector<int> cls(nb, 0);
    {
        std::map<std::string, int> byShape;
        for (int b = 0; b < nb; b++) {
            auto it = byShape.find(sig[b]);
            if (it == byShape.end()) {
                it = byShape.emplace(sig[b], (int)byShape.size()).first;
            }
            cls[b] = it->second;
        }
        for (int round = 0; round < nb + 2; round++) {
            std::map<std::string, int> key;
            std::vector<int>           nxt(nb);
            for (int b = 0; b < nb; b++) {
                std::vector<int> up, dn;
                for (int p : pred[b]) {
                    up.push_back(cls[p]);
                }
                for (int c : succ[b]) {
                    dn.push_back(cls[c]);
                }
                std::sort(up.begin(), up.end());
                std::sort(dn.begin(), dn.end());
                std::ostringstream k;
                k << cls[b] << "<";
                for (int x : up) {
                    k << x << ".";
                }
                k << ">";
                for (int x : dn) {
                    k << x << ".";
                }
                auto it = key.find(k.str());
                if (it == key.end()) {
                    it = key.emplace(k.str(), (int)key.size()).first;
                }
                nxt[b] = it->second;
            }
            bool same = true;
            {
                std::map<int, int> m;
                for (int b = 0; b < nb; b++) {
                    auto it = m.find(cls[b]);
                    if (it == m.end()) {
                        m[cls[b]] = nxt[b];
                    } else if (it->second != nxt[b]) {
                        same = false;
                    }
                }
            }
            cls = nxt;
            if (same) {
                break;
            }
        }
    }
    int ncls = 0;
    for (int b = 0; b < nb; b++) {
        ncls = std::max(ncls, cls[b] + 1);
    }
    std::vector<std::vector<int>> members(ncls);
    for (int b = 0; b < nb; b++) {
        members[cls[b]].push_back(b);
    }
    // the links, unique on both sides
    std::vector<int> link(nb, -1);
    for (int b = 0; b < nb; b++) {
        if (succ[b].size() == 1) {
            int v = *succ[b].begin();
            if (pred[v].size() == 1) {
                link[b] = v;
            }
        }
    }
    // the extensions : A -> B when the links of A are a bijection onto B
    std::vector<int> next(ncls, -1), prev(ncls, -1);
    for (int A = 0; A < ncls; A++) {
        int           B  = -1;
        bool          ok = true;
        std::set<int> targets;
        for (int b : members[A]) {
            if (link[b] < 0) {
                ok = false;
                break;
            }
            int c = cls[link[b]];
            if (B < 0) {
                B = c;
            } else if (B != c) {
                ok = false;
                break;
            }
            targets.insert(link[b]);
        }
        if (ok && B >= 0 && B != A && targets.size() == members[A].size() &&
            members[B].size() == members[A].size() && prev[B] < 0) {
            next[A] = B;
            prev[B] = A;
        }
    }
    // the families : maximal bundle chains of width P >= 2, chains ordered by the
    // serial of their first member
    treeorder            lt;
    auto                 firstTree = [&](int b) { return mt[fSN.blockMembers(b)[0]]; };
    std::vector<Family>  fams;
    for (int A = 0; A < ncls; A++) {
        if (prev[A] >= 0 || members[A].size() < 2) {
            continue;
        }
        std::vector<int> heads = members[A];
        std::sort(heads.begin(), heads.end(),
                  [&](int a, int b) { return lt(firstTree(a), firstTree(b)); });
        Family f;
        f.P = (int)heads.size();
        for (int b : heads) {
            std::vector<int> chain;
            for (int cur = b; cur >= 0; cur = (next[cls[cur]] >= 0) ? link[cur] : -1) {
                chain.push_back(fSN.blockMembers(cur)[0]);
            }
            f.rep.push_back(chain);
        }
        f.S = (int)f.rep[0].size();
        fams.push_back(f);
    }
    if (trace) {
        fprintf(stderr, "ls-families : %d blocks, %d bundles, %zu families\n", nb, ncls, fams.size());
        for (size_t i = 0; i < fams.size(); i++) {
            fprintf(stderr, "ls-family %zu : P=%d S=%d, chain 0 =", i, fams[i].P, fams[i].S);
            for (int m : fams[i].rep[0]) {
                fprintf(stderr, " m%d", m);
            }
            fprintf(stderr, "\n");
        }
    }
    return fams;
}

// ---- the forced tiling (-ls-tile k,d) : every family paved by (k, d) tiles, no
// oracle -- the calibration instrument. A tile becomes a block by contraction of
// its cells, the invariant of acyclicity making every contraction legal ; a
// refusal is traced, never fatal. Block ids shift at each contraction, so the
// tile's block is always re-read from its first cell's member.
// the current blocks of a tile's cells (a cell's block is read through its
// member : block ids shift under contraction)
std::vector<int> LoopSplitEmitter::tileBlocks(const Family& f, int c0, int s0, int k, int d) const
{
    std::vector<int> blocks;
    for (int c = c0; c < std::min(c0 + k, f.P); c++) {
        for (int s = s0; s < std::min(s0 + d, f.S); s++) {
            blocks.push_back(fSN.blockOf(f.rep[c][s]));
        }
    }
    return blocks;
}

// every tile of the (k, d) pavage of a family becomes a block by contraction of
// its cells, the invariant of acyclicity making every contraction legal ; a
// refusal is traced, never fatal
void LoopSplitEmitter::contractTiles(const Family& f, size_t i, int k, int d, bool trace)
{
    for (int c0 = 0; c0 < f.P; c0 += k) {
        for (int s0 = 0; s0 < f.S; s0 += d) {
            int cells = 1, refused = 0;
            for (int c = c0; c < std::min(c0 + k, f.P); c++) {
                for (int s = s0; s < std::min(s0 + d, f.S); s++) {
                    if (c == c0 && s == s0) {
                        continue;
                    }
                    int a = fSN.blockOf(f.rep[c0][s0]);
                    int b = fSN.blockOf(f.rep[c][s]);
                    if (a == b) {
                        cells++;
                        continue;
                    }
                    if (!fSN.canContract(a, b)) {
                        refused++;
                        continue;
                    }
                    fSN.contract(std::min(a, b), std::max(a, b));
                    cells++;
                }
            }
            if (trace) {
                fprintf(stderr, "ls-tile family %zu at (%d,%d) : %d cells in one block, %d refused\n", i,
                        c0, s0, cells, refused);
            }
        }
    }
}

void LoopSplitEmitter::tileFamilies(const std::vector<Family>& fams, int k, int d, bool trace)
{
    for (size_t i = 0; i < fams.size(); i++) {
        contractTiles(fams[i], i, k, d, trace);
    }
    fSN.retopo();
    if (trace) {
        // the MODEL's verdict on the pavage : the sum of the shadow costs of the
        // tile blocks (the calibration compares its ranking with the measure)
        for (size_t i = 0; i < fams.size(); i++) {
            const Family& f = fams[i];
            std::set<int> tiles;
            for (int c = 0; c < f.P; c++) {
                for (int s = 0; s < f.S; s++) {
                    tiles.insert(fSN.blockOf(f.rep[c][s]));
                }
            }
            long total = 0;
            for (int b : tiles) {
                total += blockCostShadow(fSN.blockMembers(b));
            }
            fprintf(stderr, "ls-tile-cost family %zu : %d x %d tiling, %zu tiles, model %ld\n", i, k, d,
                    tiles.size(), total);
        }
    }
}

// ---- the tiles oracle (-ls-tiles) : for each family, every (k, d) pavage is
// priced as the sum of the shadow costs of its tiles -- each tile concrete, no
// memoization (the shape forgets what the cost sees, LES-TUILES 4) -- and the
// cheapest is contracted before the greedy fusion, which then runs with the
// tiles as atoms. The pavage is a starting partition the pairwise moves cannot
// reach (a square tile cuts k chains by d stages at once) ; the greedy never
// splits a tile and never merges two (fTileMember) : the pavage is the loop
// decision for the family, the greedy only settles the foreign blocks around
// it (a tie goes to the larger tile, fewer loops).
void LoopSplitEmitter::electTilings(const std::vector<Family>& fams, bool trace)
{
    for (size_t i = 0; i < fams.size(); i++) {
        const Family& f          = fams[i];
        long          bestCost   = LONG_MAX, singletons = 0;
        int           bk         = 1, bd = 1;
        for (int k = 1; k <= f.P; k++) {
            for (int d = 1; d <= f.S; d++) {
                long cost = 0;
                // a tile is a loop : the election bills it its own loop cost
                // (-ls-tile-cl, calibrated at 100 : 3 x 3 over 2 x 5 on the 9 x 9
                // families under both judges, LES-TUILES 6.5) in place of the
                // greedy's -ls-cl that the shadow cost already carries -- the
                // greedy over-fuses at 100, the election under-tiles at 20
                const long tileCl = gGlobal->gLSTileCl - gGlobal->gLSCl;
                for (int c0 = 0; c0 < f.P; c0 += k) {
                    for (int s0 = 0; s0 < f.S; s0 += d) {
                        cost += blockCostShadow(fSN.orderedUnion(tileBlocks(f, c0, s0, k, d))) + tileCl;
                    }
                }
                if (k == 1 && d == 1) {
                    singletons = cost;
                }
                if (cost < bestCost || (cost == bestCost && k * d > bk * bd)) {
                    bestCost = cost;
                    bk       = k;
                    bd       = d;
                }
            }
        }
        if (trace) {
            fprintf(stderr, "ls-tiles family %zu (%d x %d) : elected %d x %d, model %ld (1 x 1 : %ld)\n", i,
                    f.P, f.S, bk, bd, bestCost, singletons);
        }
        if (bk * bd > 1) {
            contractTiles(f, i, bk, bd, trace);
            if (fTileMember.empty()) {
                fTileMember.assign(fSN.materialized().size(), 0);
            }
            for (int c = 0; c < f.P; c++) {
                for (int s = 0; s < f.S; s++) {
                    fTileMember[f.rep[c][s]] = 1;
                }
            }
        }
    }
    fSN.retopo();
}

void LoopSplitEmitter::emit(Tree L, const std::vector<Tree>& sched, int nouts)
{
    // 0. refuse unsupported constructs before writing anything
    {
        std::set<Tree, treeorder> seen;
        for (Tree l = L; isList(l); l = tl(l)) {
            prescan(hd(l), seen);
        }
        for (Tree p : fC->fDisplayCapturePoints) {
            prescan(p, seen);  // the display captures are emitted too
        }
    }

    // 0-bis. the matrix form : detect the families ON THE EMITTED LIST
    // (same trees the walk will see -- hash-consing makes the plan's keys
    // pointer-exact). The row-op regime is gated while experimental.
    if (gGlobal->gMatrixRows) {
        fMatrix = revealMatrix(L);
        fRowOp  = !fMatrix.families.empty();
    }

    // 1-2. the partition (materialization, reference graph, blocks).
    // References with certified delay >= the chunk size do not constrain
    // grouping: cycles with long feedback edges split legally (the d < N
    // restriction of LOOPMERGING.md)
    // the display captures (spec SIGNAUX-ATTACHES, split path) : each
    // capture point owns a vector -- FORCED materialization -- except an
    // input (read straight from the input buffer) and a constant-delay
    // read (the writer's history holds the value)
    {
        std::set<Tree, treeorder> forced;
        for (Tree p : fC->fDisplayCapturePoints) {
            int  k, dmin, dmax;
            bool dvar;
            Tree x, y;
            if (isSigInput(p, &k)) {
                continue;
            }
            if (isSigDelay(p, x, y)) {
                delayBounds(y, dmin, dmax, dvar);
                if (!dvar) {
                    continue;
                }
            }
            forced.insert(p);
        }
        fSN.setForced(std::move(forced));
    }
    fSN.build(L, sched, gGlobal->gVecSize);
    // under -ls-tile k,d the pavage is final : no dissolve, no greedy (2a-bis,
    // 2a-ter, 2b) -- the calibration compares a tiling with the measure
    const bool forcedTiling = gGlobal->gLSTileK > 0;
    const bool lsTrace = global::isOpt("FAUST_LS_TRACE");  // PROBE
    // 2a-bis. the Dissolve move : a signal materialized ONLY for sharing
    // (not a projection, never read delayed, not an output) may be
    // cheaper INLINED in each consumer than computed once and joined --
    // the bells' mode sum wants per-mode locality, freeverb's comb sum
    // wants the shared member (x0.97). No static rule separates them
    // (three falsified in one day) : the faithful shadow oracle prices
    // both worlds per candidate, duplication included.
    // PROBE : FAUST_OPT=FAUST_LS_NODISSOLVE measures the Dissolve move by its
    // absence (every shared member keeps its buffer)
    const bool noDissolve = global::isOpt("FAUST_LS_NODISSOLVE");
    if (gGlobal->gLSFuse && !forcedTiling && !noDissolve) {
        std::set<Tree, treeorder> outs;
        for (Tree l = L; isList(l); l = tl(l)) {
            outs.insert(hd(l));
        }
        const std::vector<Tree>&  mat = fSN.materialized();
        std::set<Tree, treeorder> dissolved;
        for (int m = 0; m < int(mat.size()); m++) {
            Tree t = mat[m];
            int  pi;
            Tree pw;
            if (isProj(t, &pi, pw) || fSN.maxDelayOf(t) > 0 || outs.count(t) ||
                fSN.isForced(t)) {
                continue;
            }
            int mb = fSN.blockOf(m);
            if (fSN.blockMembers(mb).size() != 1) {
                continue;  // v1 : only singleton blocks dissolve cleanly
            }
            // consumer blocks
            std::set<int> cbs;
            for (int i = 0; i < int(mat.size()); i++) {
                if (i != m && fSN.refs(i).count(m)) {
                    cbs.insert(fSN.blockOf(i));
                }
            }
            cbs.erase(mb);
            if (cbs.empty()) {
                continue;
            }
            std::set<int>  excl{m};
            long           with = blockCostShadow(fSN.blockMembers(mb));
            long           without = 0;
            for (int cb : cbs) {
                with += blockCostShadow(fSN.blockMembers(cb));
                without += blockCostShadow(fSN.blockMembers(cb), nullptr, nullptr, true, -1,
                                           nullptr, nullptr, &excl);
            }
            if (without < with) {
                dissolved.insert(t);
            }
        }
        if (!dissolved.empty()) {
            if (lsTrace) fprintf(stderr, "ls-dissolve : %zu members inlined into their consumers, graph rebuilt\n", dissolved.size());
            fSN.setExcluded(std::move(dissolved));
            fSN.reset();
            fSN.build(L, sched, gGlobal->gVecSize);
        }
    }
    // 2a-ter comes AFTER the dissolve : a dissolution rebuilds the graph
    // (reset + build), which would erase the tiles just contracted and
    // leave their member marks stale (seen at -ls-cl 100 : the oracle's 3 x 3
    // pavage vanished before the greedy, which then started from 82 blocks).


    // 2a-ter. the families (LES-TUILES) : read off the finest partition, before
    // any fusion move -- the recognition is a property of the program, not of
    // the cut. Under -ls-tile k,d every family is paved without oracle, and the
    // pavage is FINAL : the calibration compares a tiling with the measure, so
    // neither the dissolve move nor the greedy fusion runs after it (the
    // greedy only contracts, and would refuse or absorb the tiling at will --
    // under the campaign tarif every forced tiling measured the same). The
    // oracle of the tiles (section 4) is the one to run the greedy with tiles
    // as atoms.
    if (forcedTiling || gGlobal->gLSTiles || lsTrace) {
        std::vector<Family> fams = detectFamilies(lsTrace);
        if (forcedTiling) {
            tileFamilies(fams, gGlobal->gLSTileK, gGlobal->gLSTileD, lsTrace);
        } else if (gGlobal->gLSTiles && gGlobal->gLSFuse) {
            electTilings(fams, lsTrace);  // the oracle, then the greedy with tiles as atoms
        }
    }

    // every display capture must resolve to a vector (or the input
    // buffer) -- checked BEFORE anything is written, like the prescan, so
    // the classic emitter can still take over
    for (Tree p : fC->fDisplayCapturePoints) {
        if (!captureResolvable(p)) {
            throw LoopSplitUnsupported("display capture without a vector");
        }
    }

    // TAP ALIASING : a materialized member that is only a constant delay of
    // another one keeps no buffer -- its reads redirect into the producer's
    // history. Built here, before the oracle, because the store price rests
    // on it as much as the emission does.
    {
        const std::vector<Tree>& mat = fSN.materialized();
        const int                n   = (int)mat.size();
        fAliasIx.assign(n, -1);
        fAliasD.assign(n, 0);
        for (int i = 0; i < n; i++) {
            Tree x, y;
            if (fSN.maxDelayOf(mat[i]) != 0 || !isSigDelay(mat[i], x, y)) {
                continue;
            }
            int  dmin, dmax;
            bool dvar;
            delayBounds(y, dmin, dmax, dvar);
            int ix = fSN.indexOf(x);
            if (dvar || dmin != dmax || ix < 0) {
                continue;
            }
            fAliasIx[i] = ix;
            fAliasD[i]  = dmin;
        }
        for (int i = 0; i < n; i++) {  // resolve alias chains (delay of delay)
            while (fAliasIx[i] >= 0 && fAliasIx[fAliasIx[i]] >= 0) {
                fAliasD[i] += fAliasD[fAliasIx[i]];
                fAliasIx[i] = fAliasIx[fAliasIx[i]];
            }
        }
    }
    storeClasses(L);
    // 2b. greedy single-consumer fusion (-ls-fuse): contract a block into
    // its only consumer when legal (quotient stays acyclic) and the merged
    // body fits the op budget. The policy of the predictor, as a walk in
    // the lattice of legal partitions.
    if (gGlobal->gLSFuse && !forcedTiling) {
        std::map<int, long> costMemo;  // block id -> shadow cost (per campaign step)
        // -fir barrier : a KERNEL block is dominated by dense recognized-FIR
        // tap reads. Fusing kernel with non-kernel code destroys the
        // vectorizable form the informed delay-line layout just created ;
        // kernel+kernel stays legal (parallel kernels are the profitable
        // tiles). Only active when -fir filled the facts.
        // per-MEMBER tap counts, computed ONCE : contractions only merge
        // member lists, so a block's taps are the sum of its members'
        std::map<int, int> memberTaps;
        if (!fC->fFirFacts.empty()) {
            const std::vector<Tree>& matv = fSN.materialized();
            for (int m = 0; m < int(matv.size()); m++) {
                int                       taps = 0;
                std::set<Tree>            seen;
                std::function<void(Tree)> walkd = [&](Tree t) {
                    if (!seen.insert(t).second) {
                        return;
                    }
                    Tree x, y;
                    if (isSigDelay(t, x, y) && fC->fFirFacts.count(x)) {
                        // only DENSE kernels raise the barrier : a span < 4
                        // kernel is dust (bell modes, shelves) whose tap
                        // reads are ordinary reads -- barring their fusion
                        // left the resonator banks as separate buffered
                        // loops, twice the canonical fused time
                        if (fC->fFirFacts[x].first >= 4) {
                            taps++;
                        }
                    }
                    for (int k = 0; k < t->arity(); k++) {
                        Tree br = t->branch(k);
                        if (fSN.indexOf(br) >= 0) {
                            continue;  // other members' territory
                        }
                        walkd(br);
                    }
                };
                walkd(SuperNodeGraph::defOf(matv[m]));
                if (taps > 0) {
                    memberTaps[m] = taps;
                }
            }
        }
        // -- STREAM term of the oracle (prefetcher budget, measured
        // S ~ 10-16 on karplus : G4 has 9 streams and wins, G8 has 17 and
        // stalls). A stream : a real HISTORY buffer (maxDelay >= 16
        // floats -- small hot locals do not count, else the budget would
        // block the big winning fusions like frenchBell), read or
        // written, plus the input channels. Per-member keys computed
        // ONCE ; the refusal weighs the UNION of both blocks' streams.
        long streamBudget = 12;
        std::map<int, std::vector<long>> memberStreams;
        {
            const std::vector<Tree>& matv = fSN.materialized();
            for (int m = 0; m < int(matv.size()); m++) {
                std::set<long>            keys;
                std::set<Tree>            seen;
                std::function<void(Tree)> walks = [&](Tree t) {
                    if (!seen.insert(t).second) {
                        return;
                    }
                    Tree x, y;
                    int  ich;
                    if (isSigDelay(t, x, y)) {
                        int ix = fSN.indexOf(x);
                        if (ix >= 0 && fSN.maxDelayOf(matv[ix]) >= 16) {
                            interval I    = getCertifiedSigType(y)->getInterval();
                            int      dmin = int(I.lo());
                            keys.insert(long(ix) * 1000 + (dmin >= 1 ? dmin / 16 % 997 : 998));
                        }
                    } else if (isSigInput(t, &ich)) {
                        keys.insert(-1000 - ich);
                    }
                    for (int k = 0; k < t->arity(); k++) {
                        Tree br = t->branch(k);
                        if (fSN.indexOf(br) >= 0) {
                            continue;
                        }
                        walks(br);
                    }
                };
                walks(SuperNodeGraph::defOf(matv[m]));
                if (fSN.maxDelayOf(matv[m]) >= 16) {
                    keys.insert(long(m) * 1000 + 999);  // its own write
                }
                if (!keys.empty()) {
                    memberStreams[m] = std::vector<long>(keys.begin(), keys.end());
                }
            }
        }
        auto streamsUnion = [&](int b, int c) -> long {
            std::set<long> u;
            for (int blk : {b, c}) {
                for (int m : fSN.blockMembers(blk)) {
                    auto it = memberStreams.find(m);
                    if (it != memberStreams.end()) {
                        u.insert(it->second.begin(), it->second.end());
                    }
                }
            }
            return long(u.size());
        };
        auto isKernelBlock = [&](int b) -> bool {
            if (memberTaps.empty()) {
                return false;
            }
            int taps = 0;
            for (int m : fSN.blockMembers(b)) {
                auto mt = memberTaps.find(m);
                if (mt != memberTaps.end()) {
                    taps += mt->second;
                }
            }
            bool k = (taps >= 4) && (2 * taps >= fSN.opsEstimate(b));
            return k;
        };
        auto costOfBlock = [&](int b) -> long {
            auto it = costMemo.find(b);
            if (it != costMemo.end()) {
                return it->second;
            }
            long c      = blockCostShadow(fSN.blockMembers(b));
            costMemo[b] = c;
            return c;
        };
        // fuse iff the merged loop is estimated cheaper than the two
        // separate ones (the saved C_L and the over-pressure penalty are
        // both inside the shadow cost)
        auto tryContract = [&](int b, int c) -> bool {
            if (fSN.opsEstimate(b) + fSN.opsEstimate(c) > gGlobal->gLSFuseOps) {
                return false;  // compile-time guard only: the cost oracle decides
            }
            if (!fSN.canContract(b, c)) {
                return false;
            }
            if (isKernelBlock(b) != isKernelBlock(c)) {
                return false;  // -fir barrier
            }
            if (isTileBlock(b) && isTileBlock(c)) {
                return false;  // two elected tiles stay two loops
            }
            if (streamBudget > 0 && streamsUnion(b, c) > streamBudget) {
                return false;  // prefetcher stream budget
            }
            long costM = blockCostShadow(fSN.orderedUnion(b, c));
            if (costM >= costOfBlock(b) + costOfBlock(c)) {
                return false;
            }
            fSN.contract(std::min(b, c), std::max(b, c));
            costMemo.clear();  // block ids shifted
            return true;
        };
        // BEST-GAIN greedy: at each step, evaluate every candidate --
        // vertical (producer into its only consumer) and horizontal
        // (independent siblings sharing a consumer or an input) -- and apply
        // the contraction with the LARGEST estimated gain. First-win order
        // was path-dependent: on the 9x9 filter matrix it followed the
        // chains (vertical first) and locked out the measurably better
        // square tiles the oracle itself prefers when allowed to compare.
        auto gainOf = [&](int b, int c) -> long {
            if (fSN.opsEstimate(b) + fSN.opsEstimate(c) > gGlobal->gLSFuseOps) {
                if (lsTrace) fprintf(stderr, "ls-fuse %d+%d : refused, ops budget\n", b, c);
                return 0;  // compile-time guard only: the cost oracle decides
            }
            if (!fSN.canContract(b, c)) {
                if (lsTrace) fprintf(stderr, "ls-fuse %d+%d : refused, not contractible\n", b, c);
                return 0;
            }
            if (isKernelBlock(b) != isKernelBlock(c)) {
                if (lsTrace) fprintf(stderr, "ls-fuse %d+%d : refused, kernel barrier\n", b, c);
                return 0;  // -fir barrier
            }
            if (isTileBlock(b) && isTileBlock(c)) {
                if (lsTrace) fprintf(stderr, "ls-fuse %d+%d : refused, tile barrier\n", b, c);
                return 0;  // two elected tiles stay two loops
            }
            if (streamBudget > 0 && streamsUnion(b, c) > streamBudget) {
                if (lsTrace) fprintf(stderr, "ls-fuse %d+%d : refused, stream budget\n", b, c);
                return 0;  // prefetcher stream budget
            }
            long costM = blockCostShadow(fSN.orderedUnion(b, c));
            long cb = costOfBlock(b), cc = costOfBlock(c);
            if (lsTrace) fprintf(stderr, "ls-fuse %d+%d : cost %ld + %ld = %ld vs merged %ld -> gain %ld (ops %d + %d)\n", b, c, cb, cc, cb + cc, costM, cb + cc - costM, fSN.opsEstimate(b), fSN.opsEstimate(c));
            return costOfBlock(b) + costOfBlock(c) - costM;
        };
        bool changed = true;
        while (changed) {
            changed = false;
            int  nb = fSN.blockCount();
            std::set<std::pair<int, int>> cands;
            for (int b = 0; b < nb; b++) {
                std::set<int> cons = fSN.blockConsumers(b);
                if (cons.size() == 1) {
                    int c = *cons.begin();
                    cands.insert({std::min(b, c), std::max(b, c)});
                }
            }
            std::map<int, std::vector<int>> byConsumer;
            std::map<int, std::vector<int>> byInput;
            for (int b = 0; b < nb; b++) {
                for (int c : fSN.blockConsumers(b)) {
                    byConsumer[c].push_back(b);
                }
                for (int in : fSN.blockIns(b)) {
                    byInput[in].push_back(b);
                }
            }
            // third affinity: same topological depth. Disjoint parallel
            // chains (the 9x9 filter matrix: 9 ins, 9 outs, no shared sum)
            // offer no consumer/input affinity, yet same-stage segments
            // across chains are exactly the profitable square tiles. Window
            // the pairs to keep the candidate count linear.
            std::map<int, std::vector<int>> byDepth;
            {
                std::vector<int> depth(nb, 0);
                for (int b = 0; b < nb; b++) {  // blocks are topo-ordered
                    for (int d : fSN.blockDeps(b)) {
                        depth[b] = std::max(depth[b], depth[d] + 1);
                    }
                    byDepth[depth[b]].push_back(b);
                }
            }
            for (auto* groups : {&byConsumer, &byInput, &byDepth}) {
                for (auto& g : *groups) {
                    size_t win = (groups == &byDepth) ? 8 : g.second.size();
                    for (size_t i = 0; i < g.second.size(); i++) {
                        for (size_t j = i + 1; j < g.second.size() && j <= i + win; j++) {
                            cands.insert({std::min(g.second[i], g.second[j]),
                                          std::max(g.second[i], g.second[j])});
                        }
                    }
                }
            }
            long bestGain = 0;
            int  bestA = -1, bestB = -1;
            for (auto& bc : cands) {
                long g = gainOf(bc.first, bc.second);
                if (g > bestGain) {
                    bestGain = g;
                    bestA    = bc.first;
                    bestB    = bc.second;
                }
            }
            if (lsTrace) fprintf(stderr, "ls-fuse round : %d blocks, %zu candidates, best %d+%d gain %ld\n", nb, cands.size(), bestA, bestB, bestGain);
            if (bestA >= 0) {
                fSN.contract(bestA, bestB);
                costMemo.clear();
                changed = true;
            }
        }
        fSN.retopo();
    }
    if (gGlobal->gDrawSuperNodes) {
        std::ofstream dotfile(subst("$0-sn.dot", gGlobal->makeDrawPath()).c_str());
        dumpSuperNodesDot(dotfile);
    }

    // 2c. degenerate partition: everything in ONE super-node (or none), and
    // the model says the body fits the register bank with room to spare
    // (peak < R, no over-pressure). Splitting has nothing to offer -- there
    // is no partition to exploit -- and the -ls emission style only adds its
    // taxes: chunk buffers where the classic emission keeps short recurrences
    // in rotating locals that live in registers (measured x1.7 on a single
    // resonlp). So route to classic emission. When the body SATURATES the
    // bank (peak == R: frenchBell 20/20, x1.9 over classic) or overflows it
    // (over-pressure: fdnRev 0.877 vs classic), the register-aware order is
    // precisely what -ls brings: keep it.
    {
        // constantsLive = false and loads free here: this check compares the
        // -ls monobloc against CLASSIC emission, so the shadow must be
        // isomorphic to what -ls would EMIT (the per-loop annotation's DAG:
        // inline delayed reads, hoisted constants), not to the oracle's
        // fusion currency where loads and constants are priced. What
        // discriminates monobloc-vs-classic is the pressure of the flowing
        // temporaries alone: m33 13/20 (classic wins, measured) vs
        // frenchBell 20/20 (-ls wins x1.9, measured).
        //
        // Two further guards, both tied to the MECHANISM of the classic
        // advantage (short recurrences as rotating locals in registers,
        // where our chunk buffers pay memory traffic -- x1.7 on m11): it
        // only exists where every member's history is short enough for the
        // rotation idiom (maxDelay <= gMaxCopyDelay), and it is voided by
        // opaque calls, where the -ls order works around the callee-saved
        // register clobber (dbmeter, log10-saturated: fused 0.51 vs
        // classic; echo, ring-buffered long delay: 0.41 -- both measured
        // AGAINST the blind version of this rule).
        long overR   = 0;
        int  peak    = 0;
        bool hasCall = false;
        bool shortD  = true;
        if (fSN.blockCount() == 1) {
            blockCostShadow(fSN.blockMembers(0), &overR, &peak, false, 0, &hasCall);
            for (int m : fSN.blockMembers(0)) {
                if (fSN.maxDelayOf(fSN.materialized()[m]) > gGlobal->gMaxCopyDelay) {
                    shortD = false;
                    break;
                }
            }
        }
        // grain fin (spec GRAIN-FIN.md) : a single super-node may still be
        // worth splitting when the OUTPUT TAILS it feeds carry real work.
        // Emitted as separate loops they are stateless -- no carried
        // dependency -- and auto-vectorize (the vec mechanism : the four
        // shelving filters at 1.46, kernel+tail split measured at vec
        // parity). The scalar shadow cannot price SIMD, so the tail term
        // is explicit : serial ops saved, minus the vectorized cost at
        // width 4, minus a per-loop tax (buffer round-trip, loop
        // overhead). Split as soon as the sum gains.
        long tailGain = 0;
        if (fSN.blockCount() <= 1) {
            std::function<long(Tree, std::set<Tree>&)> tailOps = [&](Tree t,
                                                                     std::set<Tree>& seen) -> long {
                if (seen.count(t)) {
                    return 0;  // shared sub-expression : counted once
                }
                seen.insert(t);
                int  itmp;
                Tree ff, largs, ftype, fname, ffile;
                if (isNum(t) || isSlow(t) || isSigInput(t, &itmp) || fSN.indexOf(t) >= 0) {
                    return 0;  // buffer read, constant or slow : not tail work
                }
                if (fSN.isExcluded(t)) {
                    // a DISSOLVED member, recomputed where it is read : a
                    // producer's work, not tail work. Counted as tail, the
                    // dissolution inflated t91's tail to a gain of 39 and
                    // the split kept an output loop rereading ten buffers
                    // (10.6 ns against 5.9 classic, four judges)
                    return 0;
                }
                // descriptor-carrying signals : their structural branches
                // (signature, name, file) are not signals and must not be
                // walked -- only the real arguments count as tail work
                if (isSigFFun(t, ff, largs)) {
                    long n = 1;
                    for (Tree l = largs; isList(l); l = tl(l)) {
                        n += tailOps(hd(l), seen);
                    }
                    return n;
                }
                if (isSigFConst(t, ftype, fname, ffile) || isSigFVar(t, ftype, fname, ffile)) {
                    return 1;  // a plain external read, no signal branches
                }
                // widgets carry a label PATH (a list) among their branches :
                // a bargraph's only signal is its value arm, a soundfile
                // descriptor has none (the slow widgets never get here)
                Tree wpath, wmin, wmax, wval;
                if (isSigVBargraph(t, wpath, wmin, wmax, wval) ||
                    isSigHBargraph(t, wpath, wmin, wmax, wval)) {
                    return 1 + tailOps(wval, seen);
                }
                if (isSigSoundfile(t, wpath)) {
                    return 1;
                }
                long n = 1;
                for (int k = 0; k < t->arity(); k++) {
                    n += tailOps(t->branch(k), seen);
                }
                return n;
            };
            for (Tree l = L; isList(l); l = tl(l)) {
                std::set<Tree> seen;
                long           ops = tailOps(hd(l), seen);
                if (ops >= 2) {
                    tailGain += ops - (ops + 3) / 4 - 2;  // saved - simd cost - tax
                }
            }
        }
        // stream term : a monobloc that interleaves MANY output/input
        // streams in one loop defeats the prefetcher and the store
        // buffer even with ZERO compute ops (UITester : 30 constant
        // splats + 6 passthroughs, 9.9 ns monobloc against 2.2 split --
        // below -vec's 3.4). One stream at a time streams perfectly ;
        // the split-emission loops are exactly that. Threshold 8 : a
        // stereo program stays monobloc, the M-series prefetcher
        // tracks ~8 streams.
        bool manyStreams = (nouts + fC->fClass->inputs()) > 8;
        if (global::isOpt("FAUST_LS_TRACE")) {
            fprintf(stderr, "ls-monobloc : blocks %d overR %ld peak %d R %d hasCall %d shortD %d tailGain %ld manyStreams %d\n",
                    fSN.blockCount(), overR, peak, gGlobal->gLSRegisters, (int)hasCall, (int)shortD, tailGain, (int)manyStreams);
        }
        if (fSN.blockCount() <= 1 && overR == 0 && peak < gGlobal->gLSRegisters && !hasCall &&
            shortD && tailGain <= 0 && !manyStreams) {
            throw LoopSplitUnsupported("single super-node within the register budget", true);
        }
    }
    const std::vector<Tree>& mat = fSN.materialized();
    // -hg : the blocks, as they stand after fusion, drawn as a one-level
    // hierarchy of the materialized signals (HierarchyDot.hh) -- one cluster
    // per block, the reads as edges with their delays, the file beside the
    // -sg drawing. A debugging view of the cuts, nothing else reads it.
    if (gGlobal->gDrawHierarchy) {
        digraph<int> dg;
        for (int i = 0; i < int(mat.size()); i++) {
            dg.add(i);
        }
        for (int i = 0; i < int(mat.size()); i++) {
            for (int r : fSN.refs(i)) {
                // The edge's OWN delays. What the acyclicity test reads is
                // whether the set contains 0, and refs0 is exactly the
                // criterion the partition itself uses for that. A source
                // also read late contributes its maximal delay, so the
                // drawing keeps that information without weakening the
                // test. maxDelayOf alone, as this used to be, is the
                // largest delay the source is read with ANYWHERE : it hid
                // the 0 of an instantaneous edge as soon as another
                // consumer read the same source late.
                const bool instant = fSN.refs0(i).count(r) > 0;
                const int  dmax    = fSN.maxDelayOf(mat[r]);
                if (instant) {
                    dg.add(r, i, 0);
                }
                if (dmax > 0) {
                    dg.add(r, i, dmax);
                } else if (!instant) {
                    dg.add(r, i, 1);  // delayed, by an amount occurrences does not know
                }
            }
        }
        hierarchy<int, std::string> hg(dg);
        for (int b = 0; b < fSN.blockCount(); b++) {
            std::set<int, dgorder<int>> members(fSN.blockMembers(b).begin(), fSN.blockMembers(b).end());
            if (members.size() < mat.size()) {
                std::string why;
                if (auto next = hg.group(members, &why)) {
                    hg = next->label(members, "loop " + std::to_string(b) + " : " +
                                                  std::to_string(fSN.opsEstimate(b)) + " ops");
                } else {
                    std::cerr << "-hg : block " << b << " is not a group : " << why << std::endl;
                }
            }
        }
        std::ofstream dotfile(subst("$0-hier.dot", gGlobal->makeDrawPath()).c_str());
        hierarchyDot<int, std::string>(
            dotfile, hg, [](const int& i) { return "m" + std::to_string(i); },
            [&](const int& i) {
                std::ostringstream os;
                os << "m" << i << " " << mat[i]->node();
                return os.str();
            },
            [](const std::string& l) { return l; }, "loop split");
    }
    int                      n   = (int)mat.size();

    // 2d. the distributed sums (LES-SOMMES-DISTRIBUEES, step 1 : detection
    // and trace only, the emission does not change). A real n-ary sum whose
    // operands are computed in other blocks could be accumulated IN PLACE by
    // those blocks (acc[i] = p1 ; acc[i] += p2 ; ...) instead of read back
    // from one buffer per operand : the join loop and the operand buffers
    // disappear, the sum becomes an edge of the loop graph. Here : which sums,
    // how many contributor blocks, how many buffers would go.
    fAccPlans.clear();
    if (lsTrace || gGlobal->gLSAcc) {
        std::vector<AccPlan>&      plans = fAccPlans;
        std::set<Tree, treeorder>  sumsSeen;
        int                        sumsTotal = 0;
        // the external readers of every member (blocks other than its own), counted
        // as the buffers count them (storeClasses) : a read of a tap alias is a read
        // of its host, and an alias member reads its host. Counting only the direct
        // refs took a host read through an alias from another loop for a member
        // read by the sum alone : its history went block-local and the other loop
        // read "<regstate>[i]" (crossDelay2 under the greedy fusion, V15 binary too)
        std::vector<std::set<int>> extReaders(n);
        {
            auto host = [&](int ix) { return (fAliasIx[ix] >= 0) ? fAliasIx[ix] : ix; };
            for (int i = 0; i < n; i++) {
                for (int j : fSN.refs(i)) {
                    if (fSN.blockOf(i) != fSN.blockOf(host(j))) {
                        extReaders[host(j)].insert(i);
                    }
                }
                if (fAliasIx[i] >= 0 && fSN.blockOf(i) != fSN.blockOf(fAliasIx[i])) {
                    extReaders[fAliasIx[i]].insert(i);
                }
            }
        }
        // the members an operand reads INSTANTANEOUSLY (a delayed read goes
        // through a history buffer that exists anyway and binds nothing)
        // the members an operand reads instantaneously (mem) and with delay (dreads :
        // host, minimal delay). A delayed read binds the operand to no block, but it
        // is only FRESH in a block emitted after its host's, or at a delay of a whole
        // chunk (the reads of previous chunks) : FXChaine2's feedback matrix, moved
        // into an earlier loop, read the lines' outputs a chunk late and died.
        auto instantMembers = [&](Tree o, std::set<int>& mem, std::vector<std::pair<int, int>>* dreads) {
            std::set<Tree>            seen;
            std::function<void(Tree)> walk = [&](Tree t) {
                if (!seen.insert(t).second) {
                    return;
                }
                // a member first, whatever its node : a materialized delay line (a variable
                // delay on an input, crossDelay2's Delay(IN[1], ...)) is a member of its own
                // block. Testing the delay first took it for a delayed read of its input,
                // bound nothing, and moved the operand into a loop that then read the
                // line's buffer -- a register state there : "<regstate>[i]" (greedy fusion)
                {
                    int ix = fSN.indexOf(t);
                    if (ix >= 0) {
                        // an aliased tap is a delayed read of its host : it binds nothing
                        // (attributing it to the alias's block moved a self-history read of
                        // a register state into another loop : phaser_flanger)
                        if (fAliasIx[ix] < 0) {
                            mem.insert(ix);
                        } else if (dreads) {
                            dreads->push_back({fAliasIx[ix], fAliasD[ix]});
                        }
                        return;
                    }
                }
                Tree x, y;
                if (isSigDelay(t, x, y)) {
                    int hx = fSN.indexOf(x);
                    if (dreads && hx >= 0) {
                        int  dmin = 0, dmax = 0;
                        bool dvar = false;
                        delayBounds(y, dmin, dmax, dvar);
                        int host = (fAliasIx[hx] >= 0) ? fAliasIx[hx] : hx;
                        dreads->push_back({host, dmin + ((fAliasIx[hx] >= 0) ? fAliasD[hx] : 0)});
                    }
                    walk(y);
                    return;
                }
                for (int k = 0; k < t->arity(); k++) {
                    walk(t->branch(k));
                }
            };
            walk(o);
        };
        // a SUM here is a maximal tree of real additions and subtractions
        // (after -lsum the n-ary rows are lowered to combs of binary adds ;
        // without it the source's own association), or a kept n-ary row.
        // Its operands are the leaves of that tree.
        auto isAddSub = [](Tree t, Tree& x, Tree& y) -> bool {
            int op;
            return isSigBinOp(t, &op, x, y) && (op == kAdd || op == kSub) &&
                   getCertifiedSigType(t)->nature() == kReal;
        };
        auto flattenSum = [&](Tree root, std::vector<std::pair<Tree, int>>& ops) {
            std::function<void(Tree, int)> fl = [&](Tree t, int sign) {
                Tree x, y;
                int  op;
                if ((t == root || fSN.indexOf(t) < 0) && isAddSub(t, x, y)) {
                    isSigBinOp(t, &op, x, y);
                    fl(x, sign);
                    fl(y, (op == kSub) ? -sign : sign);
                    return;
                }
                ops.push_back({t, sign});
            };
            fl(root, +1);
        };
        for (int m = 0; m < n; m++) {
            if (fSN.isExcluded(mat[m])) {
                continue;
            }
            const int                 cb = fSN.blockOf(m);
            std::set<Tree>            seen;
            std::function<void(Tree)> find = [&](Tree t) {
                if (!seen.insert(t).second) {
                    return;
                }
                tvec                              V;
                std::vector<std::pair<Tree, int>> SV;  // the signed operands
                Tree                              x, y;
                bool isRow = isSigSum(t, V) && getCertifiedSigType(t)->nature() == kReal;
                bool rowop = isRow && fRowOp && fMatrix.rowOf.count(t) > 0;
                if (isRow) {
                    for (Tree o : V) {
                        SV.push_back({o, +1});
                    }
                } else if (isAddSub(t, x, y)) {
                    flattenSum(t, SV);
                }
                if (!rowop && SV.size() >= 2 && sumsSeen.insert(t).second) {
                    sumsTotal++;
                    AccPlan P;
                    P.sum      = t;
                    P.consumer = cb;
                    P.member   = m;
                    for (const auto& so : SV) {
                        Tree                             o = so.first;
                        std::set<int>                    mem;
                        std::vector<std::pair<int, int>> dreads;
                        instantMembers(o, mem, &dreads);
                        std::set<int> blocks;
                        for (int j : mem) {
                            blocks.insert(fSN.blockOf(j));
                        }
                        // an operand moves to a contributor block only if every delayed read it
                        // holds is fresh there : the host's block is emitted before (or is) that
                        // block, or the delay spans a whole chunk. This also keeps a register
                        // state's history (readable only inside its loop) in its loop.
                        bool fresh = true;
                        if (blocks.size() == 1) {
                            for (const auto& hd : dreads) {
                                if (fSN.blockOf(hd.first) > *blocks.begin() && hd.second < gGlobal->gVecSize) {
                                    fresh = false;
                                }
                            }
                        }
                        if (blocks.size() == 1 && *blocks.begin() != cb && fresh) {
                            P.contributors[*blocks.begin()].push_back(so);
                            for (int j : mem) {
                                // a member whose only outside reader is the sum's own member leaves the
                                // loop graph : its buffer goes (no delay), or its history becomes block-local
                                if (extReaders[j].size() == 1 && *extReaders[j].begin() == m) {
                                    (fSN.maxDelayOf(mat[j]) == 0 ? P.removable : P.internal).insert(j);
                                }
                            }
                        } else {
                            P.rest.push_back(so);  // no member, own block, or members of several blocks
                            // a member the rest reads (any delay) stays read from the consumer's loop
                            for (int j : mem) {
                                P.removable.erase(j);
                                P.internal.erase(j);
                            }
                            for (const auto& hd : dreads) {
                                P.removable.erase(hd.first);
                                P.internal.erase(hd.first);
                            }
                        }
                    }
                    for (const auto& so : P.rest) {  // (the rest may have been pushed before the member was marked)
                        std::set<int>                    mem2;
                        std::vector<std::pair<int, int>> dr2;
                        instantMembers(so.first, mem2, &dr2);
                        for (int j : mem2) {
                            P.removable.erase(j);
                            P.internal.erase(j);
                        }
                        for (const auto& hd : dr2) {
                            P.removable.erase(hd.first);
                            P.internal.erase(hd.first);
                        }
                    }
                    // a distribution pays only if it frees more chunk buffers than it writes
                    // accumulators : each contributor block writes the accumulator once per
                    // sample, each freed member (buffer removed, or history made block-local)
                    // saves one buffer write and the consumer's read of it. A sum that frees
                    // nothing (its operands' members are still read elsewhere) or one member
                    // per contributor block only moves the traffic and adds the consumer's
                    // read-modify-write : V15 at equal form, harpe x1.22, simpleFX x1.35,
                    // AdditiveSynth x1.35 (nothing or one per sum) against djembeMIDI and drums
                    // x0.67-0.73 on the five judges (one contributor block, ten histories made
                    // local). Replaces the two-contributor rule of 3.f, which also refused those.
                    if (!P.contributors.empty() &&
                        P.removable.size() + P.internal.size() >= P.contributors.size() + 1) {
                        // v1 : the accumulator is the consumer member's own buffer, so the
                        // member's definition must be the sum itself, or the sum under a
                        // scalar factor (a constant or a slow value : englishBell's 0.02)
                        Tree d = SuperNodeGraph::defOf(mat[m]);
                        Tree a, b2;
                        if (d == t) {
                            P.eligible = true;
                        } else if (isSigMul(d, a, b2) && (a == t || b2 == t)) {
                            Tree                             c = (a == t) ? b2 : a;
                            std::set<int>                    cm;
                            std::vector<std::pair<int, int>> cd;
                            instantMembers(c, cm, &cd);
                            if (cm.empty() && cd.empty()) {  // a constant or a slow value : no member at all
                                P.factor   = c;
                                P.eligible = true;
                            }
                        }
                        plans.push_back(P);
                    } else if (!P.contributors.empty()) {
                        plans.push_back(P);  // traced, never distributed (frees too little)
                    }
                    // the operands' own cones may hold sums of their own
                    for (const auto& so : SV) {
                        if (fSN.indexOf(so.first) < 0) {
                            find(so.first);
                        }
                    }
                    return;
                }
                for (int k = 0; k < t->arity(); k++) {
                    Tree br = t->branch(k);
                    if (fSN.indexOf(br) >= 0) {
                        continue;  // another member's territory
                    }
                    find(br);
                }
            };
            find(SuperNodeGraph::defOf(mat[m]));
        }
        int loopsTotal = 0, buffersTotal = 0, localTotal = 0;
        for (const AccPlan& P : plans) {
            if (!lsTrace) {
                break;
            }
            size_t nops = P.rest.size();
            for (const auto& kv : P.contributors) {
                nops += kv.second.size();
            }
            std::ostringstream os;
            for (const auto& kv : P.contributors) {
                os << " b" << kv.first << ":" << kv.second.size();
            }
            fprintf(stderr, "ls-acc : sum of %zu operands in block %d : %zu contributor blocks {%s }, rest %zu, buffers removable %zu, histories made local %zu%s\n",
                    nops, P.consumer, P.contributors.size(), os.str().c_str(), P.rest.size(), P.removable.size(), P.internal.size(),
                    P.eligible ? (P.factor ? ", eligible (factor)" : ", eligible")
                               : (P.removable.size() + P.internal.size() < P.contributors.size() + 1
                                      ? ", not distributed (frees fewer buffers than it writes accumulators)"
                                      : ", not eligible in v1 (sum below the member's root)"));
            loopsTotal += (int)P.contributors.size();
            buffersTotal += (int)P.removable.size();
            localTotal += (int)P.internal.size();
        }
        if (lsTrace) {
            fprintf(stderr, "ls-acc summary : blocks %d, real sums %d, distributable %zu, contributor blocks %d, buffers removable %d, histories made local %d\n",
                    fSN.blockCount(), sumsTotal, plans.size(), loopsTotal, buffersTotal, localTotal);
        }
    }

    // 3. buffers. Three flavors, by maxDelay m:
    //    m == 0                 chunk-local vector, no state
    //    0 < m <= gMaxCopyDelay class member of m+vecSize samples, the last m
    //                           shifted to the prefix at end of chunk
    //    m > gMaxCopyDelay      masked power-of-two ring buffer (a shift
    //                           would copy m samples per chunk), indexed by
    //                           the shared fLSIota advanced once per chunk
    fBufName.resize(n);
    fMaxD.resize(n);
    fIsInt.resize(n);
    fLocal.resize(n);
    fRing.resize(n);
    fRegState.assign(n, false);
    fRingMask.resize(n);
    // 3a. tap aliasing: a materialized CONSTANT-delay read of another
    // materialized signal owns no storage of its own -- the producer's
    // history already holds the value (the occurrences size it from this
    // very read), so every access redirects there: taps read the line.
    // The read must not be read with delay itself (maxDelayOf == 0).
    // The PARTITION is deliberately left untouched: removing taps from
    // the materialized set reshapes the greedy's affinity graph and was
    // measured +6% on the 9x9 filter matrix; emission-only elision was
    // measured time-neutral with the compute() stack divided by 3.
    // (the alias table is built before the fusion oracle : both the store
    // price and the emission need it)
    // -ls-regstate : the DEAD STORES of the split. Every materialized member
    // was written to its chunk buffer at every sample, even when nothing
    // outside its own loop ever reads it -- inside the loop its history
    // already rides in the rotating locals, and the buffer only carried
    // two values from one chunk to the next. Measured on o99 : 81 stores a
    // sample, 50 of them read by no other loop, against 46 in the hand
    // forged tile. A member read only inside its block, at constant delays
    // within the copy class, keeps no buffer : its history crosses the
    // chunks in maxDelay persistent scalars, seeded into the rotating
    // locals at the top of the loop and saved at its end.
    std::vector<bool> extRead(n, false), varRead(n, false);
    fCapD.assign(n, -1);
    if (gGlobal->gLSRegState) {
        auto resolve = [&](int ix) { return (fAliasIx[ix] >= 0) ? fAliasIx[ix] : ix; };
        // the reader tables were built for the oracle (storeClasses) : a
        // member is written iff something forces it -- an output, a capture,
        // a read at a variable delay -- or one of its readers sits in
        // another block. Reusing them keeps the price the oracle paid and
        // the code the emitter writes in step.
        // -ls-acc, step 3 : a member whose only outside reader is the sum it now
        // feeds from inside its own loop (its operand moved into its block) is no
        // longer read from outside -- the reader below is that sum's member
        std::map<int, int> accOnlyReader;  // member -> the sum member that was its only outside reader
        if (gGlobal->gLSAcc) {
            const char* only = getenv("FAUST_LS_ACC_ONLY");  // PROBE, see the emission
            for (const AccPlan& P : fAccPlans) {
                if (!P.eligible || fAliasIx[P.member] >= 0 || (only != nullptr && atoi(only) != P.member)) {
                    continue;
                }
                for (int j : P.removable) {
                    accOnlyReader[j] = P.member;
                }
                for (int j : P.internal) {
                    accOnlyReader[j] = P.member;
                }
            }
        }
        for (int m = 0; m < n; m++) {
            varRead[m] = fStoreForced[m];
            for (int r : fReadersOf[m]) {
                if (fSN.blockOf(r) != fSN.blockOf(m)) {
                    auto ar = accOnlyReader.find(m);
                    if (ar != accOnlyReader.end() && ar->second == r) {
                        continue;  // read only through its own loop's accumulation now
                    }
                    extRead[m] = true;
                }
            }
        }
        (void)resolve;
        // a display capture reads the value d samples before the last one
        // of the chunk : the member's rotation must run d+1 deep and be
        // saved, whatever its loop reads
        for (Tree p : fC->fDisplayCapturePoints) {
            Tree x, y;
            int  ix = fSN.indexOf(p), dd = 0;
            if (ix < 0 && isSigDelay(p, x, y)) {
                int  dmin, dmax;
                bool dvar;
                delayBounds(y, dmin, dmax, dvar);
                ix = fSN.indexOf(x);
                dd = dmin;
            }
            if (ix >= 0) {
                int h = resolve(ix);
                dd += (fAliasIx[ix] >= 0) ? fAliasD[ix] : 0;
                fCapD[h] = std::max(fCapD[h], dd);
            }
        }
        // the outputs read through the buffers, wherever they are placed
        for (Tree l1 = L; isList(l1); l1 = tl(l1)) {
            std::set<Tree, treeorder>   seen;
            std::function<void(Tree)> rec = [&](Tree u) {
                if (!seen.insert(u).second) {
                    return;
                }
                int ix = fSN.indexOf(u);
                if (ix >= 0) {
                    extRead[resolve(ix)] = true;
                    return;
                }
                Tree var, body;
                if (isRec(u, var, body)) {
                    if (body) {
                        rec(body);
                    }
                    return;
                }
                for (int k = 0; k < u->arity(); k++) {
                    rec(u->branch(k));
                }
            };
            rec(hd(l1));
        }
    }
    int vs = gGlobal->gVecSize;
    for (int i = 0; i < n; i++) {
        fMaxD[i]  = fSN.maxDelayOf(mat[i]);
        fIsInt[i] = getCertifiedSigType(mat[i])->nature() == kInt;
        fLocal[i] = (fMaxD[i] == 0);
        fRing[i]  = (fMaxD[i] > gGlobal->gMaxCopyDelay);
        // -fir consumer : a DENSE recognized FIR reads its whole window
        // every sample -- the linear layout (contiguous prefix reads, one
        // end-of-chunk shift) is the vectorizable form ; the masked ring
        // defeats it (measured x4.2 on par_fir_32). Sparse kernels
        // (tapiir) keep the ring.
        if (fRing[i]) {
            auto it = fC->fFirFacts.find(mat[i]);
            if (it != fC->fFirFacts.end()) {
                int span = it->second.first, nz = it->second.second;
                if (span == fMaxD[i] && span <= gGlobal->gMaxDenseDelay &&
                    100 * nz >= 50 * span) {
                    fRing[i] = false;
                }
            }
        }
        if (fAliasIx[i] >= 0) {
            fBufName[i] = "<aliased>";  // never emitted: accessCode redirects
            continue;
        }
        const char* ctype = fIsInt[i] ? "int" : ifloat();
        bool accTarget = false;
        if (gGlobal->gLSAcc) {
            const char* only = getenv("FAUST_LS_ACC_ONLY");  // PROBE, see the emission
            for (const AccPlan& P : fAccPlans) {
                if (P.eligible && P.member == i && (only == nullptr || atoi(only) == i)) {
                    accTarget = true;  // -ls-acc : the contributor loops write it, it needs its buffer
                }
            }
        }
        fRegState[i] = gGlobal->gLSRegState && !fRowOp && !fRing[i] &&
                       fMaxD[i] <= gGlobal->gMaxCopyDelay && !extRead[i] && !varRead[i] && !accTarget;
        if (fRegState[i]) {
            // no buffer : maxDelay+1 persistent scalars carry the history
            // across the chunks, the last one serving the display captures
            // (lastCode) ; a maxDelay-0 member keeps one, its last value
            fBufName[i] = "<regstate>";  // never emitted: the reads are the rotating locals
            for (int d = 1; d <= fMaxD[i] + 1; d++) {
                fClass->addDeclCode(subst("$0 \tfWr$1d$2;", ctype, T(i), T(d)));
                fClass->addClearCode(subst("fWr$0d$1 = 0;", T(i), T(d)));
            }
            continue;
        }
        std::string base  = fC->getFreshID("Wls");
        if (fLocal[i]) {
            fBufName[i] = base;
            fClass->addZone2b(subst("$0 $1[$2];", ctype, base, T(vs)));
        } else if (fRing[i]) {
            int sz = 1;
            while (sz < fMaxD[i] + vs) {
                sz *= 2;
            }
            fRingMask[i] = sz - 1;
            fBufName[i]  = "f" + base;
            fClass->addDeclCode(subst("$0 \t$1[$2];", ctype, fBufName[i], T(sz)));
            fClass->addClearCode(
                subst("for (int k=0; k<$1; k++) $0[k] = 0;", fBufName[i], T(sz)));
            fHasRing = true;
        } else {
            fBufName[i] = "f" + base;
            fClass->addDeclCode(subst("$0 \t$1[$2];", ctype, fBufName[i], T(vs + fMaxD[i])));
            fClass->addClearCode(subst("for (int k=0; k<$1; k++) $0[k] = 0;", fBufName[i],
                                       T(vs + fMaxD[i])));
            // end-of-block shift: keep the last maxDelay samples as prefix
            fClass->addZone3Post(subst("for (int k=0; k<$1; k++) $0[k] = $0[count+k];",
                                       fBufName[i], T(fMaxD[i])));
        }
    }
    if (fHasRing) {
        fClass->addDeclCode("int \tfLSIota;");
        fClass->addClearCode("fLSIota = 0;");
        fClass->addZone3Post("fLSIota += count;");
    }

    // ---- output placement : under fusion, outputs are ordinary
    // candidates rather than one pinned loop per channel (the
    // state-space lesson : the pinned C rows sat at 43% occupancy,
    // re-reading the same streams once per channel). Each output gets a
    // HOME block -- the one producing most of the member streams it
    // reads -- and joins that block's loop when the machine model
    // accepts the pressure ; the leftovers merge with each other under
    // the same rule. Without -ls-fuse the former one-loop-per-channel
    // behaviour is kept (the plain split stays the reference).
    struct OutPlan {
        Tree expr;
        int  chan;
        int  home;
        bool placed;
    };
    std::vector<OutPlan> outPlans;
    {
        int i = 0;
        for (Tree l1 = L; isList(l1); l1 = tl(l1), i++) {
            int home = -1;
            if (gGlobal->gLSFuse) {
                std::set<Tree>            seen;
                std::map<int, int>        byBlock;
                std::function<void(Tree)> rec = [&](Tree u) {
                    if (!seen.insert(u).second) {
                        return;
                    }
                    int ix = fSN.indexOf(u);
                    if (ix >= 0) {
                        byBlock[fSN.blockOf((fAliasIx[ix] >= 0) ? fAliasIx[ix] : ix)]++;
                        return;
                    }
                    Tree var, body;
                    if (isRec(u, var, body)) {
                        if (body) {
                            rec(body);
                        }
                        return;
                    }
                    for (int k = 0; k < u->arity(); k++) {
                        rec(u->branch(k));
                    }
                };
                rec(hd(l1));
                // the LEGAL home is the LAST producing block : adopted
                // there, every stream the output reads -- at any delay --
                // has already been written this chunk (an earlier-block
                // home would read the previous chunk : bells/karplus32
                // caught it at the gate)
                for (auto& [b2, nn] : byBlock) {
                    (void)nn;
                    if (b2 > home) {
                        home = b2;
                    }
                }
            }
            outPlans.push_back({hd(l1), i, home, false});
        }
        faustassert(i == nouts);
    }
    // the unconditional build of one output's ops in the current range
    auto buildOutput = [&](OutPlan& q, int curScc) {
        fCurWriteStreams.insert(-2000 - q.chan);
        Operand          root = walk(q.expr, curScc, false);
        std::vector<int> deps;
        addDep(deps, root);
        newOp(subst("output$0[i] = $2$1;", T(q.chan), operandCode(root), xcast()), deps, true,
              false, false);
    };
    // tentative adoption : build, ask the model, roll back on refusal
    auto adoptOutput = [&](OutPlan& q, int lo, int curScc) -> bool {
        auto savedReads  = fCurReadStreams;
        auto savedWrites = fCurWriteStreams;
        auto savedRot    = fCurRotDepth;
        int  lo2         = (int)fOps.size();
        buildOutput(q, curScc);
        int  cycles = 0, peak = 0;
        long overR = 0;
        modelSchedule(fOps, lo, (int)fOps.size(), gGlobal->gLSRegisters, gGlobal->gLSWidth,
                      &cycles, &overR, &peak);
        if (overR == 0) {
            return true;  // the model absorbs it : adopted
        }
        // rollback : the merged body would spill
        fOps.resize(lo2);
        for (auto it = fOpOf.begin(); it != fOpOf.end();) {
            it = (it->second >= lo2) ? fOpOf.erase(it) : std::next(it);
        }
        fCurReadStreams  = savedReads;
        fCurWriteStreams = savedWrites;
        fCurRotDepth     = savedRot;
        return false;
    };

    // 4. loop bodies, one per block, in dependencies-first order (members
    // already come in instantaneous-dependency order) ; each block then
    // adopts the outputs it is home to, if the model accepts
    // -ls-acc : the distributed sums that will be emitted -- consumer member ->
    // plan. The accumulator is the member's own buffer, so the member must
    // have one (not a register state, not an aliased tap).
    std::map<int, int> accOf;
    if (gGlobal->gLSAcc) {
        for (int k = 0; k < (int)fAccPlans.size(); k++) {
            const AccPlan& P = fAccPlans[k];
            if (P.eligible && (fRegState[P.member] || fAliasIx[P.member] >= 0) && lsTrace) {
                fprintf(stderr, "ls-acc : eligible sum into member %d skipped in v1 : the member has no buffer (%s)\n", P.member,
                        fRegState[P.member] ? "register state" : "aliased tap");
            }
            // PROBE : FAUST_LS_ACC_ONLY=<member> distributes that one plan only (bisection of a wrong output)
            const char* only = getenv("FAUST_LS_ACC_ONLY");
            if (only != nullptr && atoi(only) != P.member) {
                continue;
            }
            if (P.eligible && !fRegState[P.member] && fAliasIx[P.member] < 0 && !accOf.count(P.member)) {
                accOf[P.member] = k;
                if (lsTrace) {
                    fprintf(stderr, "ls-acc : distributing a sum of %zu operands over %zu blocks into member %d's buffer (block %d), rest %zu%s\n",
                            [&] { size_t c = P.rest.size(); for (auto& kv : P.contributors) c += kv.second.size(); return c; }(),
                            P.contributors.size(), P.member, P.consumer, P.rest.size(), P.factor ? ", under a scalar factor" : "");
                }
            }
        }
    }
    // the partial sum of some operands of a plan, in one block : the operands in
    // the sum's order, under the plan's factor if any
    auto accPartial = [&](const AccPlan& P, const std::vector<std::pair<Tree, int>>& ops, int b, std::vector<int>& deps) -> std::string {
        std::string sum;
        for (const auto& so : ops) {
            Operand oo = walk(so.first, b, false);
            addDep(deps, oo);
            if (sum.empty()) {
                sum = (so.second < 0 ? "-" : "") + operandCode(oo);
            } else {
                sum += (so.second < 0 ? " - " : " + ") + operandCode(oo);
            }
        }
        if (P.factor != nullptr) {
            Operand fo = walk(P.factor, b, false);
            addDep(deps, fo);
            return subst("($0 * ($1))", operandCode(fo), sum);
        }
        return subst("($0)", sum);
    };
    std::ostringstream loops;
    for (int b = 0; b < fSN.blockCount(); b++) {
        int lo = (int)fOps.size();
        fOpOf.clear();  // tls temporaries are loop-scoped
        fMatGather.clear();
        fMatResolved.clear();
        fCurReadStreams.clear();
        fCurWriteStreams.clear();
        fCurRotDepth.clear();
        fResidentHistory.clear();
        for (int m : fSN.blockMembers(b)) {
            if (fAliasIx[m] >= 0) {
                continue;  // aliased tap: no body, no store -- reads redirect
            }
            if (auto ap = accOf.find(m); ap != accOf.end()) {
                // the consumer of a distributed sum : its buffer already holds
                // the contributions ; only the rest is added here, and the
                // block's own readers read the completed buffer
                const AccPlan& P = fAccPlans[ap->second];
                if (P.rest.empty()) {
                    Operand r;
                    r.code     = storeCode(m);
                    fRootOf[m] = r;
                    continue;
                }
                std::vector<int> deps;
                std::string      rest = accPartial(P, P.rest, b, deps);
                int v = newOp(subst("($0 + $1)", storeCode(m), rest), deps, false, false, fIsInt[m]);
                fCurWriteStreams.insert(m);
                int st = newOp(subst("$0 = tls$1;", storeCode(m), T(v)), {v}, true, false, fIsInt[m]);
                Operand r;
                r.op       = v;
                fRootOf[m] = r;
                fStoreOf[m] = st;
                continue;
            }
            Tree             d    = defOf(mat[m]);
            Operand          root = walk(d, b, d == mat[m]);
            if (fRegState[m]) {
                // no store : the value lives in its op, the rotation reads
                // it at the end of the sample (an inline leaf becomes an op)
                if (root.op < 0) {
                    root.op = newOp(root.code, {}, false, false, fIsInt[m]);
                    root.code.clear();
                }
                fRootOf[m] = root;
                continue;
            }
            fCurWriteStreams.insert(m);
            fRootOf[m] = root;
            std::vector<int> deps;
            addDep(deps, root);
            int st = newOp(subst("$0 = $1;", storeCode(m), operandCode(root)), deps, true,
                           false, fIsInt[m]);
            fStoreOf[m] = st;
        }
        // the contributions of this block to the distributed sums : after its
        // own stores, one accumulation per plan -- '=' from the first
        // contributor block in emission order, '+=' from the others
        for (const auto& kv : accOf) {
            const AccPlan& P  = fAccPlans[kv.second];
            auto           it = P.contributors.find(b);
            if (it == P.contributors.end()) {
                continue;
            }
            std::vector<int> deps;
            std::string      part = accPartial(P, it->second, b, deps);
            const bool       first = (b == P.contributors.begin()->first);
            fCurWriteStreams.insert(P.member);
            newOp(subst("$0 $1 $2;", storeCode(P.member), first ? "=" : "+=", part), deps, true, false, fIsInt[P.member]);
        }
        for (int m : fSN.blockMembers(b)) {
            if (fRegState[m] && fCapD[m] >= 0) {
                // a captured member rotates one deeper than its capture
                // reads, so that the saved scalar holds that value after
                // the loop ; the others rotate exactly as their loop reads
                // (one live local more per member cost 7% on m99)
                int& dep = fCurRotDepth[m];
                dep      = std::max(dep, fCapD[m] + 1);
            }
        }
        // output adoption is OPT-IN (-ls-adopt) : the campaign that
        // followed its unconditional landing measured x1.26-1.83 fusion
        // regressions on ten programs (six bells, wfs, drums, djembe,
        // modularInterp) -- two extra output stores in a large host
        // flipped clang's vectorization of the whole body -- against a
        // single -2% win (statespace fibfu, a non-elected lane). The
        // oracle that accepted it prices registers and slots, not
        // clang's SLP moods : the urns arbitrate instead.
        if (gGlobal->gLSAdopt) {
            for (auto& q : outPlans) {
                if (!q.placed && q.home == b && adoptOutput(q, lo, b)) {
                    q.placed = true;
                }
            }
        }
        int hi = (int)fOps.size();
        emitLoop(loops, lo, hi);
    }

    // 5. leftover output loops : merged greedily while the model accepts
    {
        for (size_t k = 0; k < outPlans.size(); k++) {
            if (outPlans[k].placed) {
                continue;
            }
            int lo = (int)fOps.size();
            fOpOf.clear();
            fMatGather.clear();
            fMatResolved.clear();
            fCurReadStreams.clear();
            fCurWriteStreams.clear();
            fCurRotDepth.clear();
        fResidentHistory.clear();
            buildOutput(outPlans[k], -1);
            outPlans[k].placed = true;
            if (gGlobal->gLSFuse && gGlobal->gLSAdopt) {
                for (size_t j = k + 1; j < outPlans.size(); j++) {
                    if (!outPlans[j].placed && adoptOutput(outPlans[j], lo, -1)) {
                        outPlans[j].placed = true;
                    }
                }
            }
            emitLoop(loops, lo, (int)fOps.size());
        }
    }

    fClass->addZone3(loops.str());

    // 6. the display captures : once per chunk, AFTER the loops and before
    // the Zone3Post shifts, each capture scalar takes the last element of
    // its vector ; the block-rate tail (Zone4, emitted by the compiler once
    // the emission is done) computes the crowns from these scalars
    emitDisplayCaptures();
}

void LoopSplitEmitter::emitDisplayCaptures()
{
    int k = 0;
    for (Tree p : fC->fDisplayCapturePoints) {
        Type        ty    = getCertifiedSigType(p);
        std::string ctype = (ty->nature() == kInt) ? "int" : ifloat();
        std::string name  = subst("fDpyCap$0", T(k++));
        fClass->addZone2(subst("$0 \t$1;", ctype, name));
        fClass->addZone3(subst("$0 = $1;", name, captureCode(p)));
        fC->fDisplayCaptures[p] = name;
    }
}

// emit one inner loop covering ops [lo, hi) under the selected strategy,
// annotated with the model estimate of its quality: a perfect loop keeps
// its peak pressure within R and occupies every issue unit (occupancy 100%)
void LoopSplitEmitter::emitLoop(std::ostringstream& out, int lo, int hi)
{
    if (lo == hi) {
        return;
    }
    std::vector<int> order = scheduleSpan(lo, hi);
    int  R = (gGlobal->gLSSchedRegisters > 0) ? gGlobal->gLSSchedRegisters : gGlobal->gLSRegisters,
         U = gGlobal->gLSWidth;
    int  cycles = 0, peak = 0;
    long overR = 0;
    modelSchedule(fOps, lo, hi, R, U, &cycles, &overR, &peak);
    int n   = hi - lo;
    int occ = (cycles > 0) ? (100 * n) / (cycles * U) : 0;
    // iso runs at the op grain : digit-erased code strings as shapes,
    // a run breaks on shape change or direct dependency
    int isoadj = 0, packs4 = 0, runlen = 0, prevIx = -1;
    std::string prevSh;
    std::vector<int> harvest;  // solver-formed iso runs (size >= 4)
    for (int k : order) {
        std::string sh;
        sh.reserve(fOps[k].code.size());
        for (char ch : fOps[k].code) {
            if (!isdigit((unsigned char)ch)) {
                sh += ch;
            }
        }
        bool dep = false;
        if (prevIx >= 0) {
            for (int d : fOps[k].deps) {
                if (d == prevIx) {
                    dep = true;
                }
            }
        }
        if (prevIx >= 0 && sh == prevSh && !dep) {
            isoadj++;
            runlen++;
        } else {
            packs4 += (runlen + 1) / 4;
            if (runlen + 1 >= 4) {
                harvest.push_back(runlen + 1);
            }
            runlen = 0;
        }
        prevSh = sh;
        prevIx = k;
    }
    packs4 += (runlen + 1) / 4;
    if (runlen + 1 >= 4) {
        harvest.push_back(runlen + 1);
    }
    out << "// loop " << fLoopNo++ << ": " << n << " ops, model(R=" << R << ",U=" << U << "): " << cycles
        << " cycles, pressure " << peak << "/" << R << ", occupancy " << occ << "%"
        << ", iso " << isoadj << " adj / " << packs4 << " packs4"
        << ", streams " << fCurReadStreams.size() << "r+" << fCurWriteStreams.size() << "w";
    if (overR > 0) {
        out << ", over-pressure " << overR << " (spill risk)";
    }
    for (const auto& rot : fCurRotDepth) {
        // seam init : local d holds the value stored d iterations before
        // i == 0, i.e. the buffer's carried history at h - d
        for (int d = 1; d <= rot.second; d++) {
            out << "\n\t\t\t" << (fIsInt[rot.first] ? "int" : ifloat()) << " wr" << rot.first
                << "d" << d << " = ";
            if (fRegState[rot.first]) {
                out << "fWr" << rot.first << "d" << d << ";";  // the scalar that crossed the chunks
            } else {
                out << fBufName[rot.first] << "[" << (fMaxD[rot.first] - d) << "];";
            }
        }
    }
    for (const auto& d : fMatDecls) {
        // operand vectors of the matrix families gathered in this span
        if (d.first >= lo && d.first < hi) {
            out << "\n\t\t\t" << ifloat() << " " << d.second.first << "[" << d.second.second
                << "];";
        }
    }
    out << "\n\t\t\tfor (int i=0; i<count; i++) {";
    for (int k : order) {
        const LSOp& op = fOps[k];
        out << "\n\t\t\t\t";
        if (op.isStore) {
            out << op.code;
        } else {
            out << (op.isInt ? "int" : ifloat()) << " tls" << k << " = " << op.code << ";";
        }
    }
    for (const auto& rot : fCurRotDepth) {
        // rotate LAST : during the body every local still holds the
        // previous iteration's chain, whatever order the scheduler chose
        for (int d = rot.second; d >= 2; d--) {
            out << "\n\t\t\t\twr" << rot.first << "d" << d << " = wr" << rot.first << "d"
                << (d - 1) << ";";
        }
        const Operand& r = fRootOf.at(rot.first);
        if (r.op >= 0) {
            out << "\n\t\t\t\twr" << rot.first << "d1 = tls" << r.op << ";";
        } else {
            // root inlined as pure code : read the freshly stored slot back
            out << "\n\t\t\t\twr" << rot.first << "d1 = " << fBufName[rot.first] << "["
                << fMaxD[rot.first] << "+i];";
        }
    }
    out << "\n\t\t\t}";
    for (const auto& rot : fCurRotDepth) {
        if (fRegState[rot.first]) {
            // the history crosses to the next chunk in the persistent scalars
            for (int d = 1; d <= rot.second; d++) {
                out << "\n\t\t\tfWr" << rot.first << "d" << d << " = wr" << rot.first << "d" << d
                    << ";";
            }
        }
    }
    out << "\n\t\t\t";
}

// weighted depth of the tight (distance-1) recursion nests -- the
// per-sample recurrence bound II >= recMII no schedule can beat. The
// static selector of the auto-regime hybrid (-ss 10).
static int ocppTightRecMII(Tree L)
{
    auto lat2 = [](Tree t) -> int {
        int  op, i;
        Tree x, y, ff, largs;
        if (isSigInput(t, &i) || isSigDelay(t, x, y)) {
            return 4;
        }
        if (isSigBinOp(t, &op, x, y)) {
            return (op == kDiv || op == kRem)                    ? 10
               : (op == kMul || op == kAdd || op == kSub)        ? 3
                                                                 : 2;
        }
        if (isSigFFun(t, ff, largs)) {
            return 25;
        }
        return 2;
    };
    auto H      = graph2dag(cut(fullGraph(L), 2));
    int  recmii = 0;
    for (const auto& scc : H.nodes()) {
        if (scc.nodes().size() > 1) {
            auto                sk = cut(scc, 1);
            schedule<Tree>      ds = dfschedule(sk);
            std::map<Tree, int> depth;
            for (const auto& n : ds.elements()) {
                int d = 0;
                for (const auto& e : sk.destinations(n)) {
                    auto it = depth.find(e.first);
                    if (it != depth.end()) {
                        d = std::max(d, it->second);
                    }
                }
                depth[n] = d + lat2(n);
                recmii   = std::max(recmii, depth[n]);
            }
        }
    }
    return recmii;
}

/*****************************************************************************
 compileMultiSignal
 *****************************************************************************/

void ScalarCompiler::compileMultiSignal(Tree L)
{
    if (gGlobal->gLazySelect) {
        // the guarded (conditional) region is NOT pre-compiled by the
        // scheduler : it compiles in ONE recursive plunge at the first
        // guarded statement. With deep conditions kept (atom limit 8)
        // and table-index cones conditional, dx7's cascade overflows any
        // ordinary stack -- same remedy as the reveal section : a thread
        // with a 2 GB stack. Lazy-select only, the default path is
        // untouched.
        std::function<void()> body = [&]() { compileMultiSignalAux(L); };
        callWithLargeStack(body);
        return;
    }
    compileMultiSignalAux(L);
}

void ScalarCompiler::compileMultiSignalAux(Tree L)
{
    // contextor recursivness(0);
    L = prepare(L);  // optimize, share and annotate expression
    censusAdjacentReads(L);
    if (gGlobal->gFamilyForm && !fFamPlanned) {
        planFamilies();  // -fam : after the annotations, before the schedule (members' private nodes never compiled alone)
    }
    fMainCompilePhase = true;

    for (int i = 0; i < fClass->inputs(); i++) {
        fClass->addZone3(subst("$1* input$0 = &input[$0][index]; // Zone 3", T(i), xfloat()));
        // Deactivated for now
        // if (gGlobal->gInPlace) {
        //     CS(sigInput(i));
        // }
    }
    for (int i = 0; i < fClass->outputs(); i++) {
        fClass->addZone3(subst("$1* output$0 = &output[$0][index]; // Zone 3", T(i), xfloat()));
    }

    // -fir : signal-level FIR/IIR recognition, SIDE-CHANNEL ONLY at this
    // stage -- the reveal passes run on a copy of the signal list, the
    // recognized kernels are counted and reported, and the copy is
    // discarded : the emitted code is unchanged to the byte. The
    // information exists (oracle barriers, bank seeding, auto selector
    // are the intended consumers) ; emission changes are a later,
    // separately-judged stage.
    if (gGlobal->gReconstructFIRIIRs) {
        // The reveal traversals and the dependency analysis recurse as
        // deep as the signal graph ; on large programs (thunder,
        // drumkit) this exceeds the default 8 MB main stack. The whole
        // side channel therefore runs in a dedicated thread with a
        // comfortable stack, joined immediately : still one thread at a
        // time in tlib.
        std::function<void()> sideChannel = [&]() {
        // revealSum first : the FIR-merge rule of revealFIR only listens
        // to n-ary SigSum nodes, never to the binary sigAdd chains of the
        // normal form (fir18 pipeline order). revealIIR last : it needs
        // the recursive definitions already in Sum-of-FIR form. The
        // typing probe below runs on Lf (pre-IIR) : IIR nodes have no
        // typing rule yet (recursive equation, fixpoint-domain rule).
        // The input arrives already normalized : normalizeRecGroups runs
        // unconditionally at the birth of the symbolic form (normalform.cpp),
        // so the letrecs are minimal and the IIR hosts are exactly the
        // single-definition self-recursive groups.
        Tree Lf = L;  // Sum and FIR are already revealed by prepare (injection)
        Tree Li = Lf;  // IIRs revealed by prepare (stage-2 injection)
        int  nfir = 0, niir = 0, maxtaps = 0;
        long taps = 0;
        std::set<Tree>    seen;
        std::vector<Tree> work;
        for (Tree l = Li; isList(l); l = tl(l)) {
            work.push_back(hd(l));
        }
        // the display roots too : the frontier rooted the stateful parts
        // of the harvested display cones (kernels included) OUTSIDE L,
        // and the facts must describe every kernel the emitters meet --
        // a kernel without facts is fused like plain code and laid out
        // without the informed delay line (spectralLevel under -fir :
        // fifteen band kernels, SS_FIR 15 -> 0, loop 0 440 -> 618 ops)
        for (Tree sd : fDisplayStateful) {
            work.push_back(sd);
        }
        for (Tree p : fDisplayCapturePoints) {
            work.push_back(p);
        }
        while (!work.empty()) {
            Tree t = work.back();
            work.pop_back();
            if (!seen.insert(t).second) {
                continue;
            }
            tvec cs;
            if (kernelWorkVec(t, cs)) {
                nfir++;
                taps += long(cs.size()) - 1;
                maxtaps = std::max(maxtaps, int(cs.size()) - 1);
                // bridge : record the kernel on its source (branch 0). The
                // reveal leaves non-FIR sources untouched, so the pointer
                // matches the prepared tree the emitters work on.
                // branches = [S, c0..cN] : N+1 coefficients cover delays
                // 0..N, so the read span in delay terms is size-2
                int span = int(cs.size()) - 2;
                int nz   = 0;
                for (unsigned int k = 1; k < cs.size(); k++) {
                    if (!isZero(cs[k])) {
                        nz++;
                    }
                }
                // aggregate PER SOURCE : kernels reading the same delay
                // line pool their taps (siblings on one source merge in
                // the reveal, but distinct outputs can still share a
                // source, and their union is what the delay line serves)
                auto& f = fFirFacts[cs[0]];
                f.first = std::max(f.first, span);
                f.second += nz;
            } else if (isSigIIR(t, cs)) {
                niir++;
            }
            for (int k = 0; k < t->arity(); k++) {
                work.push_back(t->branch(k));
            }
        }
        std::cerr << "SS_FIR fir=" << nfir << " iir=" << niir << " taps=" << taps
                  << " maxtaps=" << maxtaps << " sources=" << fFirFacts.size() << std::endl;
        };
        callWithLargeStack(sideChannel);
    }

    // -ss 10 : auto-regime hybrid -- the tight-nest recurrence bound
    // picks the pole of the bank-compositional family : deep nests want
    // locality (small R), shallow programs want bursts (large R)
    if (gGlobal->gSchedulingStrategy == 10) {
        int  rec      = ocppTightRecMII(L);
        bool locality = (rec >= 45);
        gGlobal->gLSRegisters        = locality ? 2 : 16;
        gGlobal->gLSWidth            = 4;
        gGlobal->gSchedulingStrategy = 9;
        std::cerr << "SS_AUTO recMII=" << rec
                  << " regime=" << (locality ? "localite(R2U4)" : "rafales(R16U4)")
                  << std::endl;
    }
    // force a specific compilation order. The display-stateful roots (S)
    // join the graph so they are scheduled and compiled at audio rate
    // even when the audio path never reads them -- but ONLY the
    // display-EXCLUSIVE ones : an S node the audio graph already reaches
    // is scheduled anyway, and rooting it again reorders the scheduler's
    // seeds, which reshuffles the whole order and the order-sensitive
    // mono elections with it (flanger : +70% for a bargraph displaying
    // the very delays the audio uses).
    Tree Lg = L;
    // under -ls the CAPTURE POINTS join the schedule too : the split
    // emitter reads each one as the last element of a materialized
    // vector, and only a scheduled signal gets a vector. Same
    // display-exclusive rule ; an input needs no vector (the capture
    // reads the input buffer directly)
    const bool rootCaptures = gGlobal->gLoopSplit && !fDisplayCapturePoints.empty();
    if (!fDisplayStateful.empty() || rootCaptures) {
        auto GA = immediateGraph(L);
        for (Tree sd : fDisplayStateful) {
            if (GA.nodes().count(sd) == 0) {
                Lg = cons(sd, Lg);
            }
        }
        if (rootCaptures) {
            int k;
            for (Tree p : fDisplayCapturePoints) {
                if (!isSigInput(p, &k) && GA.nodes().count(p) == 0) {
                    Lg = cons(p, Lg);
                }
            }
        }
    }
    auto G = immediateGraph(Lg);
    if (gGlobal->gFamilyForm) {
        famScheduleEdges(G);  // -fam : the loop of a family, emitted at its first host, needs every input of every member
    }
    int rfAdded = 0;
    {
        // READERS FIRST (default since 2026-08-12) : for every delayed
        // read t = sigDelay(x, y) with dmin >= 1, one SOFT edge x -> t
        // ("x depends on t" : the reader of the OLD value passes before
        // the writer overwrites it). Since the write is emitted at its
        // own scheduling position (generateDelayAccess no longer
        // compiles the writer), the order alone makes the scalar legal —
        // the scalarization peephole harvests. An edge that would close
        // a cycle is DROPPED : each preference cycle imposes one
        // sacrificed state, whose vector plays the temporary.
        // Corpus verdict (campaign-readersfirst-20260812) : 199/199
        // bit-exact, geomean 0.9978, cycles rare and always single
        // (78 of 9847 edges). The env var above is the forensic
        // opt-out for A/B comparisons, not a supported mode.
        auto reaches = [&G](Tree from, Tree to) -> bool {
            std::set<Tree>    seen;
            std::vector<Tree> work{from};
            while (!work.empty()) {
                Tree n = work.back();
                work.pop_back();
                if (n == to) {
                    return true;
                }
                if (!seen.insert(n).second) {
                    continue;
                }
                for (const auto& c : G.destinations(n)) {
                    work.push_back(c.first);
                }
            }
            return false;
        };
        int added = 0, dropped = 0;
        std::vector<std::pair<Tree, Tree>> soft;
        for (const Tree& t : G.nodes()) {
            Tree x, y;
            if (isSigDelay(t, x, y)) {
                interval I = getCertifiedSigType(y)->getInterval();
                if (int(I.lo()) >= 1 && G.nodes().count(x)) {
                    soft.push_back({x, t});
                }
            }
        }
        for (auto& p : soft) {
            if (reaches(p.second, p.first)) {
                dropped++;
                fRFSacrificedWriters.insert(p.first);
                continue;
            }
            G.add(p.first, p.second, 0);
            added++;
            fRFKeptWriters.insert(p.first);
        }
        // a writer with edges on both sides is sacrificed, not promised
        for (Tree s2 : fRFSacrificedWriters) {
            fRFKeptWriters.erase(s2);
        }
        rfAdded = added;
    }
    auto S = ocppSchedule(G);
    // THE PRESSURE GAUGE (PILE 24). Preferences are worth honoring only if
    // the program can host their liveness : the readers moved early keep
    // their values alive longer, and a program whose resident floor
    // already crowds the registers has nothing to offer them (nylonGuitar :
    // floor 26, peak 52 -> 65, -8.6% for three scalars). Both schedules
    // are computed and the FACT decides : the preferences are refused
    // whenever their peak exceeds both the budget and the baseline peak
    // by more than the margin. Stage-3 elections stand down with them.
    if (rfAdded > 0 && gGlobal->gSchedulingStrategy == 0) {
        // the gauge reschedules from scratch : affordable for the default
        // df, wasteful for the experimental strategies (ss 11 runs a full
        // compositional search) -- those run ungated
        int budget = 48, margin = 4;
        // the baseline is REBUILT from scratch : digraph copies share their
        // internal graph (shared_ptr), a plain copy would alias the mutated
        // one -- the very bug that made the gauge blind on its first run
        auto G0   = immediateGraph(Lg);  // the SAME roots as G (display S included)
        if (gGlobal->gFamilyForm) {
            famScheduleEdges(G0);
        }
        auto memf = std::function<bool(const Tree&)>(ocppIsMemNode);
        auto sq1  = squality(G, S.elements(), 8, 4, ocppShapeFunctor(G), memf, 3);
        auto S0   = ocppSchedule(G0);
        auto sq0  = squality(G0, S0.elements(), 8, 4, ocppShapeFunctor(G0), memf, 3);
        bool gated = sq1.peak > std::max(budget, sq0.peak + margin);
        if (gated) {
            G = G0;
            S = S0;
            fRFKeptWriters.clear();
            fRFSacrificedWriters.clear();
        }
    }
    // the FACT for the stage-3 mono election : the emitted order is S
    fSchedPos.clear();
    fConsumerMaxPos.clear();
    {
        int p2 = 0;
        for (const Tree& n2 : S.elements()) {
            fSchedPos[n2] = p2++;
        }
        if (gGlobal->gFamilyForm) {
            checkFamilyOrder();  // -fam : a family whose inputs come after its first host is dismantled
        }
        // last consumer slot of every delayed-read node : a consumer's
        // emission pastes the read's value at the consumer's own slot,
        // so the read is order-protected iff its LAST consumer precedes
        // the writer (stage-3 necessity check for the forced temporary)
        for (const Tree& n2 : G.nodes()) {
            auto pn = fSchedPos.find(n2);
            if (pn == fSchedPos.end()) {
                continue;
            }
            for (const auto& d2 : G.destinations(n2)) {
                Tree xx, yy;
                if (isSigDelay(d2.first, xx, yy)) {
                    auto& mx = fConsumerMaxPos[d2.first];
                    mx       = std::max(mx, pn->second);
                }
            }
        }
    }
    // self-describing artifact : the schedule's quality vector, on the
    // COMMON evaluation machine (R=8, U=4, M=3), as a comment at the top
    // of compute() -- campaigns and archaeology read it straight from
    // the generated code, no environment needed
    {
        schedquality q = squality(G, S.elements(), 8, 4, ocppShapeFunctor(G),
                                  std::function<bool(const Tree&)>(ocppIsMemNode), 3);
        double fill = (q.cycles > 0) ? 100.0 * double(S.size()) / (double(q.cycles) * 4) : 0;
        // windowed stream peak : how many distinct memory streams does a
        // window of W consecutive instructions touch ? A stream :
        // (source, delay/16) for reads -- delays within one cache line
        // merge --, the source itself for writes (its buffer advances at
        // [i]), one per input channel. ORDER-sensitive : df visits the
        // buffers one by one, a level order interleaves them all -- the
        // prefetcher only follows a small number of streams.
        int speak = 0;
        double savg = 0;
        {
            int W = 64;
            struct Key { long a, b; bool operator<(const Key& o) const { return a != o.a ? a < o.a : b < o.b; } };
            std::vector<std::vector<Key>> touch;
            for (const auto& n : S.elements()) {
                std::vector<Key> ks;
                Tree x, y;
                int  ich;
                // a buffer that fits in one cache line (16 floats) has
                // fixed addresses : not a stream
                auto isStreamBuf = [&](Tree b) {
                    Occurrences* ob = fOccMarkup->retrieve(b);
                    return ob && ob->getMaxDelay() >= 16;
                };
                if (isSigDelay(n, x, y)) {
                    if (isStreamBuf(x)) {
                        interval I = getCertifiedSigType(y)->getInterval();
                        int dmin = int(I.lo());
                        // variable delay (or not certified >= 1) : still a
                        // stream, with its own key -- the read advances
                        ks.push_back({(long)(size_t)(void*)x, dmin >= 1 ? dmin / 16 : -1});
                    }
                } else if (isSigInput(n, &ich)) {
                    ks.push_back({-1000 - ich, 0});
                }
                if (isStreamBuf(n)) {
                    ks.push_back({(long)(size_t)(void*)n, -7});  // the buffer write
                }
                touch.push_back(ks);
            }
            int nwin = 0;
            for (size_t w0 = 0; w0 < touch.size(); w0 += 16) {
                std::set<Key> win;
                for (size_t k = w0; k < touch.size() && k < w0 + W; k++) {
                    for (const auto& key : touch[k]) {
                        win.insert(key);
                    }
                }
                speak = std::max(speak, int(win.size()));
                savg += double(win.size());
                nwin++;
            }
            if (nwin > 0) {
                savg /= nwin;
            }
        }
        std::ostringstream qc;
        qc << "// schedule: ss=" << gGlobal->gSchedulingStrategy << " nodes=" << S.size()
           << " cycles=" << q.cycles << " fill=" << int(fill) << "% peak=" << q.peak
           << " isoadj=" << q.isoadj << " packs4=" << q.packs4 << " aluMII=" << q.aluMII
           << " memMII=" << q.memMII << " recMII=" << ocppTightRecMII(L)
           << " streams(peak/avg,win64)=" << speak << "/" << int(savg + 0.5)
           << " (eval machine R=8 U=4 M=3)";
        fClass->addZone3(qc.str());
    }

    // -sig : the program's static signature, one line on stdout -- the raw
    // material of the automatic selector (layer 1 of fcautotool). Everything
    // computes without a bench : size, recurrence bound, compute/memory
    // counts, streams (total and windowed peak on the df order), shapes.
    if (gGlobal->gPrintSignature) {
        int nalu = 0, nmem = 0;
        for (const auto& n : G.nodes()) {
            if (ocppIsMemNode(n)) {
                nmem++;
            } else {
                nalu++;
            }
        }
        // streams : real keys (buffers >= 16), total + windowed peak (64)
        std::set<std::pair<long, long>> allk;
        int         speak = 0;
        {
            const int W = 64;
            std::vector<std::vector<std::pair<long, long>>> touch;
            for (const auto& n : S.elements()) {
                std::vector<std::pair<long, long>> ks;
                Tree x, y;
                int  ich;
                Occurrences* ob;
                if (isSigDelay(n, x, y) && (ob = fOccMarkup->retrieve(x)) && ob->getMaxDelay() >= 16) {
                    interval I = getCertifiedSigType(y)->getInterval();
                    int dmin = int(I.lo());
                    ks.push_back({(long)(size_t)(void*)x, dmin >= 1 ? dmin / 16 : -1});
                } else if (isSigInput(n, &ich)) {
                    ks.push_back({-1000 - ich, 0});
                }
                Occurrences* o = fOccMarkup->retrieve(n);
                if (o && o->getMaxDelay() >= 16) {
                    ks.push_back({(long)(size_t)(void*)n, -7});
                }
                for (auto& k : ks) {
                    allk.insert(k);
                }
                touch.push_back(ks);
            }
            for (size_t w0 = 0; w0 < touch.size(); w0 += 16) {
                std::set<std::pair<long, long>> win;
                for (size_t k = w0; k < touch.size() && k < w0 + W; k++) {
                    for (const auto& key : touch[k]) {
                        win.insert(key);
                    }
                }
                speak = std::max(speak, int(win.size()));
            }
        }
        // shapes : classes, bankable share (multiplicity >= 4), top-3
        std::map<long, int> cls;
        auto shf = ocppShapeFunctor(G);
        for (const auto& n : G.nodes()) {
            cls[shf(n)]++;
        }
        std::vector<int> sizes;
        long bank = 0;
        for (auto& [k, c] : cls) {
            sizes.push_back(c);
            if (c >= 4) {
                bank += c;
            }
        }
        std::sort(sizes.rbegin(), sizes.rend());
        // selects : the static signal of the -lazyselect dimension
        int nselect = 0;
        for (const auto& n : G.nodes()) {
            Tree sel_, sx_, sy_;
            if (isSigSelect2(n, sel_, sx_, sy_)) {
                nselect++;
            }
        }
        std::cout << "SS_SIG nodes=" << G.nodes().size() << " recmii=" << ocppTightRecMII(L)
                  << " nselect=" << nselect
                  << " nalu=" << nalu << " nmem=" << nmem << " nstreams=" << allk.size()
                  << " speak64=" << speak << " distinct=" << cls.size()
                  << " bankablepct=" << (100 * bank / std::max<size_t>(G.nodes().size(), 1))
                  << " top1=" << (sizes.size() > 0 ? sizes[0] : 0)
                  << " top2=" << (sizes.size() > 1 ? sizes[1] : 0)
                  << " top3=" << (sizes.size() > 2 ? sizes[2] : 0) << std::endl;
    }

    // register the compilation order S for debug purposes
    {
        int jj = 0;
        for (auto& s : S.elements()) {
            int  pnum;
            Tree rg;
            fScheduleOrder[s] = ++jj;
#if 0
            if (isProj(s, &pnum, rg)) {
                if (isSignalRecursive(s)) {
                    // std::cerr << jj << " proj " << pnum << " of " << *rg << " is recursive"
                    //<< std::endl;
                } else {
                    std::cerr << jj << " proj " << pnum << " of " << *rg
                              << " is NOT recursive and could be simplified: "
                              /*<< ppsig(getProjDefinition(s))*/
                              << std::endl;
                }
            }
#endif
        }
    }


#ifdef TRACE
    std::cerr << "\nBEFORE COMPILING" << std::endl;
    std::cerr << G << std::endl;
    std::cerr << S << std::endl;

    std::cerr << "\nCOMPILE SCHEDULE" << std::endl;
#endif
    // experimental loop-split emission (-ls): the materialized DAG becomes
    // separate loops; on unsupported constructs, fall back to classic
    // emission (the pre-scan throws before anything has been written)
    bool loopSplitDone = false;
    if (gGlobal->gLoopSplit) {
        try {
            LoopSplitEmitter(this, fOccMarkup, fSharingKey)
                .emit(L, S.elements(), fClass->outputs());
            loopSplitDone = true;
            // spec SIGNAUX-ATTACHES : the captures were taken by the
            // emitter (last element of each vector, once per chunk) ; the
            // block-rate display stores follow (Zone4, once per compute)
            emitDisplayWidgets();
        } catch (LoopSplitUnsupported& e) {
            if (e.fIntentional) {
                std::cerr << "NOTE : -ls chooses classic emission (" << e.fWhat << ")"
                          << std::endl;
            } else {
                std::cerr << "WARNING : -ls falls back to classic emission (" << e.fWhat << ")"
                          << std::endl;
            }
        }
    }

    if (!loopSplitDone) {
        // gGlobal->gSTEP = 0;
        for (auto& s : S.elements()) {
            if (isNil(s)) {
                std::cerr << "NOT SUPPOSED TO HAPPEN: We have a Nil in the schedule !"
                          << std::endl;
                faustassert(false);
            }
            int lSTEP = gGlobal->gSTEP;  // conveninient for debug
            if (gGlobal->gFamilyForm && !fFamGroup.empty()) {
                // the automaton, at the first read of its group's current
                // generation in the schedule (its inputs come before, by the
                // scheduling edges) -- a private read included : a cell's
                // read of a border is private to the family, and compiled
                // on demand before the emission it would be a delay line the
                // automaton never declares. A read of a previous generation
                // is the family's arrays, wherever it comes.
                for (auto& kv : fFamGroup) {
                    if (famReadsGroupNow(s, kv.first)) {
                        emitFamily(fFamilies[kv.second]);
                    }
                }
            }
            if (gGlobal->gFamilyForm && fFamPrivate.count(s)) {
                gGlobal->gSTEP++;
                continue;  // -fam : compiled inside its family's loop, when the sum is reached
            }
            CS(s);
            gGlobal->gSTEP++;
        }

        if (gGlobal->gFamilyForm) {
            // the families among the outputs : one loop each, its results in
            // an array, each member channel reading its cell (LA-FORME-FAMILLE)
            for (FamPlan& f : fFamilies) {
                if (!f.trees.empty() && f.hosts.size() == 1 && f.hosts[0] == nullptr) {
                    emitFamily(f);
                }
            }
            // an automaton whose current generation nobody reads (its
            // projections read at a delay only) : after everything
            for (auto& kv : fFamGroup) {
                if (!fFamilies[kv.second].emitted) {
                    emitFamily(fFamilies[kv.second]);
                }
            }
        }
        std::map<Tree, int, treeorder> firstChan;
        for (int i = 0; isList(L); L = tl(L), i++) {
            Tree s = hd(L);
            if (auto dup = firstChan.find(s);
                dup != firstChan.end()) {
                // THE DUPLICATE-CHANNEL LAW (the bells dig) : storing the
                // SAME value to two arrays in one loop body poisons
                // clang's SLP vectorization of the WHOLE body -- the
                // stereo idiom output0[i] = output1[i] = mix cost the
                // modal banks their SIMD (englishBell under its elected
                // options : 36.9 -> 16.3 ns once split, x2.26). Value
                // identity is the trigger (different values are fine, a
                // +0.0f relay folds back and stays poisoned), so the
                // duplicate channels LEAVE the loop : a trivial copy
                // loop after it, reading the first channel back.
                fClass->addZone3Post(subst(
                    "for (int k=0; k<count; k++) output$0[k] = output$1[k];", T(i),
                    T(dup->second)));
                continue;
            }
            firstChan[s] = i;
            fClass->addExecCode(Statement("", subst("output$0[i] = $2($1);  // Zone Exec Code",
                                                    T(i), generateCacheCode(s, CS(s)), xcast())));
        }

        // spec SIGNAUX-ATTACHES : captures at end of loop body, then the
        // block-rate display stores (Zone4, once per compute)
        emitDisplayList();
        emitAdjacentUpdates();

        // schedule-verified scalarization : a [2]-vector whose delayed reads
        // all precede its write in the EMITTED order degrades to a plain
        // scalar and its rotation dies. This restores what the group-wise
        // emission used to grant : freeverb's one-pole comb states live in
        // 2-definition groups, which the kMonoDelay criterion (singleton
        // self-recursions only) cannot serve.
        {
            int done = 0;
            for (const auto& v : fSingleDelayScalarCandidates) {
                done += fClass->scalarizeSingleDelay(v);
            }
        }
    }

    generateMetaData();
    generateUserInterfaceTree(fUITree.prepareUserInterfaceTree(), true);
    generateMacroInterfaceTree("", fUITree.prepareUserInterfaceTree());
    if (fDescription) {
        fDescription->ui(fUITree.prepareUserInterfaceTree());
    }

    if (gGlobal->gPrintJSONSwitch) {
        ofstream xout(subst("$0.json", gGlobal->makeDrawPath()).c_str());
        xout << fJSON.JSON();
    }

    ensureIotaCode();
}

/*****************************************************************************
 compileSingleSignal
 *****************************************************************************/

void ScalarCompiler::compileSingleSignal(Tree sig)
{
    // contextor recursivness(0);
    sig = prepare2(sig);  // optimize and annotate expression

#ifdef TRACE
    std::cerr << "\nSTART COMPILING SINGLE SIGNAL: " << ppsig(sig, 20) << std::endl;
#endif
    // force a specific compilation order
    auto G = immediateGraph(cons(sig, gGlobal->nil));
    auto S = ocppSchedule(G);
#ifdef TRACE
    std::cerr << "\nBEFORE COMPILING SINGLE SIGNAL" << std::endl;
    std::cerr << G << std::endl;
    std::cerr << S << std::endl;
#endif
    // register the compilation order S for debug purposes
    {
        int jj = 1000;
        for (auto& s : S.elements()) {
            fScheduleOrder[s] += ++jj;
        }
    }
#ifdef TRACE
    std::cerr << "\nCOMPILE SINGLE SIGNAL SCHEDULE" << std::endl;
#endif
    for (auto& s : S.elements()) {
        if (isNil(s)) {
            std::cerr << "NOT SUPPOSED TO HAPPEN: We have a Nil in the schedule !" << std::endl;
            faustassert(false);
        }
        int lSTEP = gGlobal->gSTEP;  // convenient for debug
        CS(s);
        gGlobal->gSTEP++;
    }

    fClass->addExecCode(Statement("", subst("output[i] = $0;", CS(sig))));
    generateUserInterfaceTree(fUITree.prepareUserInterfaceTree(), true);
    generateMacroInterfaceTree("", fUITree.prepareUserInterfaceTree());
    if (fDescription) {
        fDescription->ui(fUITree.prepareUserInterfaceTree());
    }

    ensureIotaCode();
}

/*****************************************************************************
 generateCode : dispatch according to signal
 *****************************************************************************/
/**
 * Main code generator dispatch.
 * @param sig the signal expression to compile.
 * @return the C code translation of sig
 */

/**
 * spec LE-SELECTN, emission : one result variable, one guarded
 * assignment per index -- the dispatch atoms are disjoint and covering
 * (saturating ends), so exactly one branch assigns per sample. Each
 * branch cone was condition-annotated with the SAME atom, so its own
 * statements land in the same guarded block (printlines groups equal
 * adjacent conditions) : native laziness through the existing
 * machinery, no switch printer needed. Delays and sharing of the root
 * ride the ordinary generateCacheCode.
 */
string ScalarCompiler::generateSelectN(Tree sig, const SelectNInfo& info)
{
    string selc = CS(info.selEff);
    Type   t    = getCertifiedSigType(sig);
    string vname, ctype;
    getTypedNames(t, "Sel", ctype, vname);
    // block-local, zero-init : the value is always assigned before any
    // read in the same sample (dominated placement, the lazyselect form)
    fClass->addZone2(subst("$0 \t$1 = 0;", ctype, vname));
    for (const auto& lf : info.leaves) {
        // the SAME CND path as the annotation : byte-identical condition
        // strings, so the branch cone's guarded statements group with the
        // final assignment into one if block
        Tree cnd = gGlobal->nil;
        for (Tree a : lf.atoms) {
            cnd = _AND_(cnd, _CND_(a));
        }
        string cond = CND2CODE(cnd);
        string bexp = CS(lf.branch);
        fClass->addExecCode(Statement(cond, subst("$0 = $1;", vname, bexp)));
    }
    return generateCacheCode(sig, vname);
}

string ScalarCompiler::generateCode(Tree sig)
{
    int     i;
    int64_t i64;
    double  r;
    Tree    size, gen, wi, ws, ri, c, sel, x, y, z, label, tb, ff, largs, type, name, file, sf;

    // printf("compilation of %p : ", sig); print(sig); printf("\n");

    if (gGlobal->gSelectN) {
        // spec LE-SELECTN : a certified root compiles as an N-way
        // multiplex ; its select2 spine below is dead from this path.
        // Sample-rate roots only : a slow root multiplexed in the loop
        // would drag block-rate work to sample rate (drumkit) -- slow
        // spellings keep their ordinary zone-2 compilation.
        auto it = fSelectNInfo.find(sig);
        if (it != fSelectNInfo.end() &&
            getCertifiedSigType(sig)->variability() == kSamp) {
            return generateSelectN(sig, it->second);
        }
    }
    if (gGlobal->gFamilyForm && !fFamHost.empty() && fFamHost.count(sig)) {
        // the host of a family : its loop, then the accumulator and the
        // operands outside the family (a binary add of the tree under -fam
        // alone, where the plan's view flattened it ; the n-ary sum
        // otherwise, generateSum)
        bool        ok = false;
        std::string c  = generateFamilySum(sig, tvec(), ok);
        if (ok) {
            return c;
        }
    }
    if (getUserData(sig)) {
        return generateXtended(sig);
    } else if (isSigInt(sig, &i)) {
        return generateNumber(sig, T(i));
    } else if (isSigInt64(sig, &i64)) {
        return generateNumber(sig, T(i64));
    } else if (isSigReal(sig, &r)) {
        return generateNumber(sig, realLiteral(r));
    } else if (isSigWaveform(sig)) {
        return generateWaveform(sig);
    } else if (isSigInput(sig, &i)) {
        return generateInput(sig, T(i));
    } else if (isSigOutput(sig, &i, x)) {
        return generateOutput(sig, T(i), CS(x));
    }

    else if (isSigTemp(sig, x)) {
        // the staging barrier : compile x, then FORCE its materialization
        // into a named temporary whatever its sharing count (see
        // placeTemps.cpp for who decides where the barriers go)
        return forceCacheCode(sig, CS(x));
    } else if (isSigDelay(sig, x, y)) {
        return generateDelayAccess(sig, x, y);
    } else if (tvec V; kernelWorkVec(sig, V)) {
        // the source's literal delay re-spelled as leading zeros : the
        // FIR emission serves the working vector
        return generateFIR(sig, V);
    } else if (tvec V; isSigIIR(sig, V)) {
        return generateIIR(sig, V);
    } else if (tvec subs; isSigSum(sig, subs)) {
        return generateSum(sig, subs);
    } else if (isSigPrefix(sig, x, y)) {
        return generatePrefix(sig, x, y);
    } else if (isSigBinOp(sig, &i, x, y)) {
        return generateBinOp(sig, i, x, y);
    } else if (isSigFFun(sig, ff, largs)) {
        return generateFFun(sig, ff, largs);
    } else if (isSigFConst(sig, type, name, file)) {
        return generateFConst(sig, tree2str(file), tree2str(name));
    } else if (isSigFVar(sig, type, name, file)) {
        return generateFVar(sig, tree2str(file), tree2str(name));
    }

    else if (isSigWRTbl(sig, size, gen, wi, ws)) {
        return generateWRTbl(sig, size, gen, wi, ws);
    } else if (isSigRDTbl(sig, tb, ri)) {
        return generateRDTbl(sig, tb, ri);
    } else if (isSigGen(sig, x)) {
        return generateSigGen(sig, x);
    }

    else if (isSigSelect2(sig, sel, x, y)) {
        return generateSelect2(sig, sel, x, y);
    }

    else if (isProj(sig, &i, x)) {
        return generateRecProj(sig, x, i);
    }

    else if (isSigIntCast(sig, x)) {
        return generateIntCast(sig, x);
    } else if (isSigBitCast(sig, x)) {
        return generateBitCast(sig, x);
    } else if (isSigFloatCast(sig, x)) {
        return generateFloatCast(sig, x);
    }

    else if (isSigButton(sig, label)) {
        return generateButton(sig, label);
    } else if (isSigCheckbox(sig, label)) {
        return generateCheckbox(sig, label);
    } else if (isSigVSlider(sig, label, c, x, y, z)) {
        return generateVSlider(sig, label, c, x, y, z);
    } else if (isSigHSlider(sig, label, c, x, y, z)) {
        return generateHSlider(sig, label, c, x, y, z);
    } else if (isSigNumEntry(sig, label, c, x, y, z)) {
        return generateNumEntry(sig, label, c, x, y, z);
    }

    else if (isSigVBargraph(sig, label, x, y, z)) {
        return generateVBargraph(sig, label, x, y, CS(z));
    } else if (isSigHBargraph(sig, label, x, y, z)) {
        return generateHBargraph(sig, label, x, y, CS(z));
    }

    else if (isSigSoundfile(sig, label)) {
        return generateSoundfile(sig, label);
    } else if (isSigSoundfileLength(sig, sf, x)) {
        std::string ssf = CS(sf);
        std::string sx  = CS(x);
        return generateCacheCode(sig, subst("$0cache->fLength[$1]", ssf, sx));
    } else if (isSigSoundfileRate(sig, sf, x)) {
        std::string ssf = CS(sf);
        std::string sx  = CS(x);
        return generateCacheCode(sig, subst("$0cache->fSR[$1]", ssf, sx));
    } else if (isSigSoundfileBuffer(sig, sf, x, y, z)) {
        std::string ssf = CS(sf);
        std::string sx  = CS(x);
        std::string sy  = CS(y);
        std::string sz  = CS(z);
        return generateCacheCode(sig, subst("(($1)$0cache->fBuffers)[$2][$0cache->fOffset[$3]+$4]",
                                            ssf, ifloatptrptr(), sx, sy, sz));
    }

    else if (isSigAttach(sig, x, y)) {
        CS(y);
        return generateCacheCode(sig, CS(x));
    } else if (isSigControl(sig, x, y)) {
        return generateControl(sig, x, y);
    } else if (isSigAssertBounds(sig, x, y, z)) {
        /* no debug option for the moment */
        return generateCode(z);
    }
    /* we should not have any control at this stage */
    else {
        cerr << "ASSERT : when compiling, unrecognized signal : " << *sig << endl;
        faustassert(false);
    }
    return "error in generated code";
}

/*****************************************************************************
 NUMBERS
 *****************************************************************************/

string ScalarCompiler::generateNumber(Tree sig, const string& exp)
{
    string       ctype, vname;
    Occurrences* o = fOccMarkup->retrieve(sig);

    // check for number occuring in delays
    if (o->getMaxDelay() > 0) {
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay(), o->getDelayCount());
    }
    return exp;
}

/*****************************************************************************
 FOREIGN CONSTANTS
 *****************************************************************************/

string ScalarCompiler::generateFConst(Tree sig, const string& file, const string& exp_aux)
{
    // Special case for 02/25/19 renaming
    string exp = (exp_aux == "fSamplingFreq") ? "fSampleRate" : exp_aux;

    string       ctype, vname;
    Occurrences* o = fOccMarkup->retrieve(sig);

    addIncludeFile(file);

    if (o->getMaxDelay() > 0) {
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay(), o->getDelayCount());
    }
    return exp;
}

/*****************************************************************************
 FOREIGN VARIABLES
 *****************************************************************************/

string ScalarCompiler::generateFVar(Tree sig, const string& file, const string& exp)
{
    string ctype, vname;

    addIncludeFile(file);
    return generateCacheCode(sig, exp);
}

/*****************************************************************************
 INPUTS - OUTPUTS
 *****************************************************************************/

string ScalarCompiler::generateInput(Tree sig, const string& idx)
{
    if (gGlobal->gInPlace) {
        // inputs must be cached for in-place transformations
        return forceCacheCode(sig, subst("$1input$0[i]", idx, icast()));
    } else {
        return generateCacheCode(sig, subst("$1input$0[i]", idx, icast()));
    }
}

string ScalarCompiler::generateOutput(Tree sig, const string& idx, const string& arg)
{
    string dst = subst("output$0[i]", idx);
    fClass->addExecCode(Statement("", subst("$0 = $2$1;", dst, arg, xcast())));
    return dst;
}

/*****************************************************************************
 BINARY OPERATION
 *****************************************************************************/

// A spelling that costs nothing to repeat : a variable name or a literal
// (no operator, no call, no subscript)
static bool isSimpleSpelling(const std::string& code)
{
    for (char c : code) {
        if (!isalnum((unsigned char)c) && c != '_' && c != '.' && c != '-') {
            return false;
        }
    }
    return true;
}

string ScalarCompiler::generateBinOp(Tree sig, int opcode, Tree arg1, Tree arg2)
{
    // Special case for -1*a2 and a1*-1 : the negation is emitted as a
    // unary minus, inline even when shared (it costs nothing). Inlining
    // is legal only while nobody reads the node's history : a delayed
    // reader spells the node as a delay vector, and that vector is
    // declared by generateCacheCode alone, so a negation with a delayed
    // occurrence takes the cache route like every other operation.
    const char* wrap =
        (getCertifiedSigType(sig)->nature() == kInt) ? wrapHelper(opcode) : nullptr;
    if ((opcode == kMul) && (isMinusOne(arg1) || isMinusOne(arg2)) && !wrap) {
        std::string res = CS(isMinusOne(arg1) ? arg2 : arg1);
        std::string neg = ((res[0] == '(') || (res[0] == 'f') || (res[0] == 'i'))
                              ? subst("-$0", res)
                              : subst("-($0)", res);
        // A slow negation of a non-trivial spelling takes the cache route
        // too : the argument, slow in a slow context, is inlined by the
        // sharing rule, and only the negation (slow in a fast context) is
        // marked shared -- skipping the cache here would inline the whole
        // slow expression in the sample loop (a division per sample on the
        // gains rebuilt by the kernel reconstruction).
        Occurrences* o = fOccMarkup->retrieve(sig);
        const bool   slowDeep =
            (getCertifiedSigType(sig)->variability() < kSamp) && !isSimpleSpelling(res);
        return ((o && o->getMaxDelay() > 0) || slowDeep) ? generateCacheCode(sig, neg) : neg;
    }
    // CS compiles a whole subtree ; two of them as arguments of one call ran in
    // the order the C++ compiler picks. Sequenced left to right (see the same
    // change in InstructionsCompiler::generateBinOp).
    std::string s1 = CS(arg1);
    std::string s2 = CS(arg2);
    if (wrap) {
        return generateCacheCode(sig, subst("$0($1, $2)", wrap, s1, s2));
    }
    return generateCacheCode(sig, subst("($0 $1 $2)", s1, gBinOpTable[opcode]->fName, s2));
}

/*****************************************************************************
 Primitive Operations
 *****************************************************************************/

string ScalarCompiler::generateFFun(Tree sig, Tree ff, Tree largs)
{
    addIncludeFile(ffincfile(ff));  // printf("inc file %s\n", ffincfile(ff));
    addLibrary(fflibfile(ff));      // printf("lib file %s\n", fflibfile(ff));

    string code = ffname(ff);
    code += '(';
    string sep = "";
    for (int i = 0; i < ffarity(ff); i++) {
        code += sep;
        code += CS(nth(largs, i));
        sep = ", ";
    }
    code += ')';
    return generateCacheCode(sig, code);
}

/*****************************************************************************
 CACHE CODE
 *****************************************************************************/

void ScalarCompiler::getTypedNames(Type t, const string& prefix, string& ctype, string& vname)
{
    if (t->nature() == kInt) {
        ctype = "int";
        vname = subst("i$0", getFreshID(prefix));
    } else {
        ctype = ifloat();
        vname = subst("f$0", getFreshID(prefix));
    }
}

/**
 * @brief Avoid multiple computation of the same iota expression
 *
 * @param iota expression
 * @return variable name
 */
string ScalarCompiler::generateIotaCache(const std::string& exp, bool headSafe)
{
    if (fIotaCache.find(exp) == fIotaCache.end()) {
        string vname = getFreshID("vIota");
        if (gGlobal->gRingPreload && headSafe) {
            // ring-preload prototype : an index whose delay amount is
            // sub-sample-rate (a literal, a sampling-rate constant, a
            // block-rate value -- everything already computed before the
            // loop) is a pure function of IOTA within the body, so it
            // declares at the HEAD, available to the preloaded ring reads
            // batched there. A per-sample amount stays at its slot : at the
            // head it would read the PREVIOUS tick's value of its inputs --
            // the one-sample class of bug, caught by the suite on
            // comb_delay2 when this hoist was unconditional.
            fClass->addPreCode(Statement("", subst("int $0 = $1;", vname, exp)));
            fIotaHeadNames.insert(vname);
        } else {
            fClass->addExecCode(Statement("", subst("int $0 = $1;", vname, exp)));
        }
        fIotaCache[exp] = vname;
    }
    return fIotaCache[exp];
}

/**
 * -xtemp : would the cache store this node ? The cache's own rule, read on the
 * annotated tree before emission : a node of a kind whose generator consults
 * the cache, shared without delay (sharing count > 1, or occurrences in
 * several places or in a faster context), or shared with delay. Numbers,
 * constants, outputs, projections, tables, generators, prefix, IIR, widgets
 * and temp nodes have their own storage and never reach the cache ; the
 * inputs do (generateInput asks it), and are covered.
 */
bool ScalarCompiler::passCoversKind(Tree sig)
{
    int     i;
    int64_t i64;
    double  r;
    Tree    x, y, z, label, type, name, file, size, gen, wi, ws;
    if (isSigTemp(sig, x) || isSigInt(sig, &i) || isSigInt64(sig, &i64) || isSigReal(sig, &r) ||
        isSigOutput(sig, &i, x) || isProj(sig, &i, x) ||
        isSigFConst(sig, type, name, file) || isSigPrefix(sig, x, y) || isSigGen(sig, x) ||
        isSigWRTbl(sig, size, gen) || isSigWRTbl(sig, size, gen, wi, ws) || isSigSoundfile(sig, label) ||
        isSigAssertBounds(sig, x, y, z) || isList(sig) || isNil(sig) || sig->arity() == 0) {
        return false;
    }
    if (tvec V; isSigIIR(sig, V)) {
        return false;
    }
    // the widgets and the display decorations are matched BARE by the UI
    // traversals and by the display list (a bargraph wrapped in temp is no
    // longer a bargraph to emitDisplayList : its cone went unmarked, and
    // vumeter crashed in generateDelayAccess) ; their storage is theirs
    {
        Tree lbl, cur, mn, mx, st;
        if (isSigButton(sig, lbl) || isSigCheckbox(sig, lbl) || isSigHSlider(sig, lbl, cur, mn, mx, st) ||
            isSigVSlider(sig, lbl, cur, mn, mx, st) || isSigNumEntry(sig, lbl, cur, mn, mx, st) ||
            isSigHBargraph(sig, lbl, mn, mx, x) || isSigVBargraph(sig, lbl, mn, mx, x) ||
            isSigAttach(sig, x, cur) || isSigEnable(sig, x, cur) || isSigControl(sig, x, cur)) {
            return false;
        }
    }
    // left to the cache in step 1 : the delayed READS (generateDelayAccess
    // caches them or not according to the delay type, elected on the
    // schedule, unknown before emission) and the negations (cached iff
    // delayed or slow-and-deep, a property of the emitted spelling)
    if (isSigDelay(sig, x, y)) {
        return false;
    }
    if (isSigBinOp(sig, &i, x, y) && i == kMul && (isMinusOne(x) || isMinusOne(y))) {
        return false;
    }
    return true;
}

bool ScalarCompiler::cacheWouldStore(Tree sig)
{
    if (!passCoversKind(sig)) {
        return false;
    }
    Occurrences* o = fOccMarkup->retrieve(sig);
    if (!o) {
        return false;
    }
    int sharing = getSharingCount(sig, fSharingKey);
    if (o->getMaxDelay() > 0) {
        return sharing > 1;
    }
    return (sharing > 1) || o->hasMultiOccurrences();
}

string ScalarCompiler::generateCacheCode(Tree sig, const string& exp)
{
    string code;

    // check reentrance
    if (getCompiledExpression(sig, code)) {
        return code;
    }

    string       vname, ctype;
    int          sharing = getSharingCount(sig, fSharingKey);
    Occurrences* o       = fOccMarkup->retrieve(sig);
    faustassert(o);
    if (gGlobal->gExplicitTemps) {
        // -xtemp : a temp node reaching the cache (the delay-line path asks
        // the cache about its source) is stored as forceCacheCode would ;
        // a node of a kind the pass covers is never stored here (its delay
        // line, if any, stays) ; the other kinds keep the cache's rule
        Tree tx;
        if (isSigTemp(sig, tx)) {
            return forceCacheCode(sig, exp);
        }
        if (passCoversKind(sig)) {
            if (o->getMaxDelay() > 0) {
                getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
                return generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay(), o->getDelayCount());
            }
            return exp;
        }
    }

    // check for expression occuring in delays
    if (o->getMaxDelay() > 0) {
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        if (sharing > 1) {
            return generateDelayVec(sig, generateVariableStore(sig, exp), ctype, vname,
                                    o->getMaxDelay(), o->getDelayCount());
        } else {
            return generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay(), o->getDelayCount());
        }

    } else if ((sharing > 1) || (o->hasMultiOccurrences())) {
        return generateVariableStore(sig, exp);

    } else if (sharing == 1) {
        // -stage <K> : a DEEP single-use expression gains a temporary too.
        // Two motivations, one mechanism : (1) in one-sample recursive
        // loops, staged temps let the C compiler interleave independent
        // work inside the latency shadow of the recurrence chain, where a
        // mega-expression tends to be emitted as one contiguous block
        // (measured x1.3-1.46 on the oberheim/korg35 family after the
        // letrec dissolution removed the projection boundaries that used
        // to stage them accidentally) ; (2) named stages are schedulable
        // units for the intra-loop model -- a mega-expression is opaque
        // to it. The size proxy is free : this emitter parenthesizes
        // every operation, so counting '(' counts operations.
        if (gGlobal->gStagingOps > 0 &&
            std::count(exp.begin(), exp.end(), '(') >= gGlobal->gStagingOps) {
            return generateVariableStore(sig, exp);
        }
        return exp;

    } else {
        cerr << "ASSERT : sharing count (" << sharing << ") for " << *sig << endl;
        faustassert(false);
        return {};
    }
}

// like generateCacheCode but we force caching like if sharing was always > 1
string ScalarCompiler::forceCacheCode(Tree sig, const string& exp)
{
    string code;

    // check reentrance
    if (getCompiledExpression(sig, code)) {
        return code;
    }

    string       vname, ctype;
    Occurrences* o = fOccMarkup->retrieve(sig);
    faustassert(o);

    // check for expression occuring in delays
    if (o->getMaxDelay() > 0) {
        getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
        return generateDelayVec(sig, generateVariableStore(sig, exp), ctype, vname,
                                o->getMaxDelay(), o->getDelayCount());
    } else {
        return generateVariableStore(sig, exp);
    }
}

// Definition of variables: Const (computed at init time), Slow (computed at control rate) and
// "Temp" (computed at sample rate)
string ScalarCompiler::generateVariableStore(Tree sig, const string& exp)
{
    string       vname, vname_perm, ctype;
    Type         t = getCertifiedSigType(sig);
    Occurrences* o = fOccMarkup->retrieve(sig);
    faustassert(o);

    switch (t->variability()) {
        case kKonst:
            getTypedNames(t, "Const", ctype, vname);
            // The variable is used in compute (kBlock or kSamp), so define is as a field in the DSP
            // struct
            if (o->getOccurrence(kBlock) || o->getOccurrence(kSamp)) {
                fClass->addDeclCode(subst("$0 \t$1; // step: $2", ctype, vname, T(gGlobal->gSTEP)));
                fClass->addInitCode(subst("$0 = $1; // step: $2", vname, exp, T(gGlobal->gSTEP)));
            } else {
                // Otherwise it can stay as a local variable
                // fClass->addInitCode(subst("$0 \t$1 = $2; // step: $3", ctype, vname, exp,
                // T(gGlobal->gSTEP))); FIX Bug const ???
                fClass->addDeclCode(subst("$0 \t$1; // step: $2", ctype, vname, T(gGlobal->gSTEP)));
                fClass->addInitCode(subst("$0 = $1; // step: $2", vname, exp, T(gGlobal->gSTEP)));
            }
            break;

        case kBlock:
            getTypedNames(t, "Slow", ctype, vname);
            fClass->addFirstPrivateDecl(vname);
            fClass->addZone2(
                subst("$0 \t$1 = $2; // step: $3", ctype, vname, exp, T(gGlobal->gSTEP)));
            break;

        case kSamp:
            getTypedNames(t, "Temp", ctype, vname);
            if (getConditionCode(sig) == "") {
                fClass->addExecCode(Statement(
                    "", subst("$0 \t$1 = $2; // step: $3", ctype, vname, exp, T(gGlobal->gSTEP))));
            } else if (fMainCompilePhase && !fHasEnableControl) {
                // dominated placement : without enable/control in the
                // program, a condition can only come from select2 branch
                // annotation, and every consumer then SELECTS this value
                // away outside the condition -- a stale or zero value is
                // read by the ternary but never used. An ordinary
                // block-local assigned under guard suffices ; the TempPerm
                // form below (permanent field + per-block copies) exists
                // for enable/control's hold semantics only, where the
                // consumer genuinely uses the last computed value.
                // Adjacent same-condition assignments group into a single
                // if block at print time.
                fClass->addZone2(
                    subst("$0 \t$1 = 0; // step: $2", ctype, vname, T(gGlobal->gSTEP)));
                fClass->addExecCode(
                    Statement(getConditionCode(sig), subst("$0 = $1;", vname, exp)));
            } else {
                getTypedNames(t, "TempPerm", ctype, vname_perm);
                // need to be preserved because of new enable and control primitives
                fClass->addDeclCode(subst("$0 \t$1;", ctype, vname_perm));
                fClass->addInitCode(subst("$0 = 0;", vname_perm));
                // copy the object variable to the local one
                fClass->addZone2(subst("$0 \t$1 = $2;", ctype, vname, vname_perm));
                // execute the code
                fClass->addExecCode(
                    Statement(getConditionCode(sig), subst("$0 = $1;", vname, exp)));
                // copy the local variable to the object one
                fClass->addZone4(subst("$0 = $1;", vname_perm, vname));
            }
            break;
    }
    return vname;
}

/*****************************************************************************
 CASTING
 *****************************************************************************/

// The functional casts carry a unary plus : "(float(int(id)))" is a valid
// TYPE-ID (function type, id as parameter name), and in cast position --
// after '*', '+', '(' -- C++ resolves the ambiguity in favour of the type
// (insects : "(-1) * (float(int(fTemp116))) + ..." swallowed the tail as
// the cast operand). "+id" cannot be a declarator, closing the parse class
// whatever parenthesization the consumers add. Unary plus is an exact
// no-op on arithmetic values.
string ScalarCompiler::generateIntCast(Tree sig, Tree x)
{
    return generateCacheCode(sig, subst("int(+$0)", CS(x)));
}

string ScalarCompiler::generateBitCast(Tree sig, Tree x)
{
    if (gGlobal->gFloatSize == 1) {
        return generateCacheCode(sig, subst("(*(int*)&$0)", CS(x)));
    } else if (gGlobal->gFloatSize == 2) {
        return generateCacheCode(sig, subst("((*(int64_t*)&$0)", CS(x)));
    } else {
        faustassert(false);
        return "";
    }
}

string ScalarCompiler::generateFloatCast(Tree sig, Tree x)
{
    return generateCacheCode(sig, subst("$1(+$0)", CS(x), ifloat()));
}

/*****************************************************************************
 User interface elements
 *****************************************************************************/

string ScalarCompiler::generateButton(Tree sig, Tree path)
{
    string varname = getFreshID("fbutton");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    fClass->addInitUICode(subst("$0 = 0.0;", varname));
    Tree uipath   = reverse(tl(path));
    Tree uiwidget = uiWidget(hd(path), tree(varname), sig);
    fUITree.addUIWidget(uipath, uiwidget);

    // return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

string ScalarCompiler::generateCheckbox(Tree sig, Tree path)
{
    string varname = getFreshID("fcheckbox");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    fClass->addInitUICode(subst("$0 = 0.0;", varname));
    Tree uipath   = reverse(tl(path));
    Tree uiwidget = uiWidget(hd(path), tree(varname), sig);
    fUITree.addUIWidget(uipath, uiwidget);

    // return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

string ScalarCompiler::generateVSlider(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
    string varname = getFreshID("fslider");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    fClass->addInitUICode(subst("$0 = $1;", varname, T(tree2double(cur))));
    Tree uipath   = reverse(tl(path));
    Tree uiwidget = uiWidget(hd(path), tree(varname), sig);
    fUITree.addUIWidget(uipath, uiwidget);

    // return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

string ScalarCompiler::generateHSlider(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
    string varname = getFreshID("fslider");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    fClass->addInitUICode(subst("$0 = $1;", varname, T(tree2double(cur))));
    Tree uipath   = reverse(tl(path));
    Tree uiwidget = uiWidget(hd(path), tree(varname), sig);
    fUITree.addUIWidget(uipath, uiwidget);

    // return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

string ScalarCompiler::generateNumEntry(Tree sig, Tree path, Tree cur, Tree min, Tree max,
                                        Tree step)
{
    string varname = getFreshID("fentry");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    fClass->addInitUICode(subst("$0 = $1;", varname, T(tree2double(cur))));
    Tree uipath   = reverse(tl(path));
    Tree uiwidget = uiWidget(hd(path), tree(varname), sig);
    fUITree.addUIWidget(uipath, uiwidget);

    // return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

//-----------------------------------------------------------------------------------------
// The display frontier (spec SIGNAUX-ATTACHES) : the display list D.
//
// Harvest (recursive, one treeRewritePaired pass) : attach(x,y) dissolves
// into x -- the rebuilt y is walked for its bargraphs and otherwise
// DROPPED (the elimination rule : a display signal without a bargraph
// feeds no widget and computes nothing observable) ; every bargraph node
// dissolves into its pass-through and its REBUILT form joins D. Nested
// attaches and bargraphs are handled by the rewrite recursion itself :
// the harvest reaches its fixpoint in one pass.
//-----------------------------------------------------------------------------------------
Tree ScalarCompiler::harvestDisplay(Tree L)
{
    // Conditioned subtrees keep the LEGACY path : under enable/control the
    // old bargraph store is conditional -- the widget latches its last
    // value when the condition is off, and downstream audio reads the
    // latch. The block-rate transformation would compute always : a
    // semantic change the impulse suite catches (the enable family).
    // A pre-scan marks every node under a sigEnable/sigControl body ;
    // marked attaches and bargraphs are left untouched.
    std::set<Tree> conditioned;
    {
        std::set<Tree>    seen;
        std::vector<Tree> work{L};
        bool              under = false;
        std::function<void(Tree, bool)> scan = [&](Tree t, bool u) {
            auto it = seen.find(t);
            if (it != seen.end() && !u) {
                return;  // already walked unconditioned ; conditioned walk may still need to mark
            }
            if (u && conditioned.count(t)) {
                return;
            }
            seen.insert(t);
            if (u) {
                conditioned.insert(t);
            }
            Tree a, b, var, body;
            if (isRec(t, var, body)) {
                if (body != nullptr) {
                    scan(body, u);
                }
                return;
            }
            bool cu = u || isSigEnable(t, a, b) || isSigControl(t, a, b);
            for (int k = 0; k < t->arity(); k++) {
                scan(t->branch(k), cu);
            }
        };
        scan(L, false);
    }
    // An attach dissolves ONLY when its attached cone is fully
    // harvestable : at least one bargraph (otherwise dropping the cone
    // would also drop its input widgets from the built interface -- an
    // observable UI change : the virtualAnalog "gain" slider, a
    // MIDI-mapped name, exists only through its attach), and none of its
    // bargraphs conditioned (a conditioned bargraph stays legacy in
    // place ; dropping the cone would silently lose its widget). Every
    // other attach stays on the legacy path, widgets declared as before.
    // bgMask bit 1 : cone holds a harvestable bargraph ; bit 2 : cone
    // holds a conditioned one.
    std::map<Tree, char>     bgMemo;
    std::function<int(Tree)> bgMask = [&](Tree t) -> int {
        auto it = bgMemo.find(t);
        if (it != bgMemo.end()) {
            return (it->second < 0) ? 0 : it->second;  // in-progress : cycles add nothing
        }
        bgMemo[t] = -1;
        Tree p, mn, mx, x, var, body;
        int  m = 0;
        if (isSigVBargraph(t, p, mn, mx, x) || isSigHBargraph(t, p, mn, mx, x)) {
            m |= conditioned.count(t) ? 2 : 1;
        }
        if (isRec(t, var, body)) {
            if (body != nullptr) {
                m |= bgMask(body);
            }
        } else {
            for (int k = 0; k < t->arity(); k++) {
                m |= bgMask(t->branch(k));
            }
        }
        bgMemo[t] = (char)m;
        return m;
    };
    std::vector<Tree>                rakes;
    std::set<Tree>                   visitedP;
    std::function<void(Tree)>        collectPreserved = [&](Tree t) {
        if (!visitedP.insert(t).second) {
            return;
        }
        Tree p, c1, mn, mx, c2, x2, y2, var, body;
        if (isSigButton(t, p) || isSigCheckbox(t, p) || isSigVSlider(t, p, c1, mn, mx, c2) ||
            isSigHSlider(t, p, c1, mn, mx, c2) || isSigNumEntry(t, p, c1, mn, mx, c2)) {
            fDisplayPreserved.insert(t);
        }
        if (isSigAttach(t, x2, y2)) {
            collectPreserved(x2);
            if (bgMask(y2) == 1) {
                collectPreserved(y2);  // an inner eliminated cone (mask 0) dies whole
            }
            return;
        }
        if (isRec(t, var, body)) {
            if (body != nullptr) {
                collectPreserved(body);
            }
            return;
        }
        for (int k = 0; k < t->arity(); k++) {
            collectPreserved(t->branch(k));
        }
    };
    bool                             changed = false;
    std::unordered_map<Tree, Tree>   memo;
    std::function<Tree(Tree, Tree)>  rule = [&](Tree orig, Tree rebuilt) -> Tree {
        Tree x, y, path, mn, mx, c1, c2;
        if (isSigButton(orig, path) || isSigCheckbox(orig, path) ||
            isSigVSlider(orig, path, c1, mn, mx, c2) ||
            isSigHSlider(orig, path, c1, mn, mx, c2) ||
            isSigNumEntry(orig, path, c1, mn, mx, c2)) {
            // UI preservation : every input widget is recorded. A widget
            // whose cone a dissolving attach drops (the midiTester MIDI
            // clock checkboxes feed no bargraph) is declared at emission
            // time -- declaration only, no computation ; widgets the
            // audio path or a harvested bargraph compiles are skipped
            // there. Recording is not a change (collected BEFORE the
            // conditioned cut so conditioned cones lose nothing).
            rakes.push_back(rebuilt);
            return rebuilt;
        }
        if (conditioned.count(orig)) {
            return rebuilt;  // legacy path for the enable family
        }
        if (isSigAttach(orig, x, y)) {
            int m = bgMask(y);
            if (m & 2) {
                return rebuilt;  // conditioned bargraph in the cone : legacy attach
            }
            if (m == 1) {
                // harvestable cone : its bargraphs are already collected ;
                // its input widgets are marked PRESERVED so the emission
                // declares the strays no path compiles (midiTester)
                collectPreserved(y);
            }
            // m == 0 : the aggressive elimination -- an attach without a
            // bargraph computes nothing observable, the cone dies whole,
            // dead input widgets included (the virtualAnalog "gain"
            // slider goes away WITH its per-sample smoothing)
            changed = true;
            return rebuilt->branch(0);
        }
        if (isSigVBargraph(orig, path, mn, mx, x) || isSigHBargraph(orig, path, mn, mx, x)) {
            rakes.push_back(rebuilt);      // the widget store, block-rate
            changed = true;
            return rebuilt->branch(3);     // the pass-through stays audio
        }
        return rebuilt;
    };
    Tree L2 = treeRewritePaired(L, rule, memo);
    if (!changed) {
        // nothing harvested : keep the ORIGINAL tree, not the rebuild
        // (the rewrite is not always pointer-identity on rec-heavy trees,
        // and a spurious rebuild shifts the schedule by a node -- dx7)
        return L;
    }
    Tree D  = gGlobal->nil;
    for (auto it = rakes.rbegin(); it != rakes.rend(); ++it) {
        D = cons(*it, D);
    }
    fDisplayList = D;
    return L2;
}

// The frontier of D : walking each display cone through branches, stop at
// (a) sub-sample-rate nodes -- inlined at emission through the normal
// machinery ; (b) the CAPTURE POINTS -- stateful signals (delayed or
// recursive : the list S of the spec, also made scheduling roots so they
// compile at audio rate), inputs, and any construct the block-rate tail
// emitter does not carry (tables, generators...) : those are computed
// in-loop and captured at the end of the loop body.
// The stateless operators the display frontier walks through : they are
// computed in the block-rate tail, from the captures below them.
static bool displayTailCarries(Tree t)
{
    int  op;
    Tree x, y, sel;
    return isSigBinOp(t, &op, x, y) || isSigIntCast(t, x) || isSigFloatCast(t, x) || isSigSelect2(t, sel, x, y) ||
           isSigSum(t) || (getUserData(t) != nullptr && t->arity() > 0);
}

void ScalarCompiler::computeDisplayFrontier()
{
    if (fDisplayList == nullptr || !isList(fDisplayList)) {
        return;
    }
    std::set<Tree> seenS, seenC, walked, walkedNoCap;
    // (node, captures allowed) : below an explicit temporary the descent
    // only ROOTS the stateful parts, it captures nothing
    std::vector<std::pair<Tree, bool>> work;
    for (Tree l = fDisplayList; isList(l); l = tl(l)) {
        Tree path, mn, mx, x;
        if (isSigVBargraph(hd(l), path, mn, mx, x) || isSigHBargraph(hd(l), path, mn, mx, x)) {
            work.push_back({x, true});
        }
    }
    auto tailCarries = displayTailCarries;
    while (!work.empty()) {
        auto [t, cap] = work.back();
        work.pop_back();
        // a node walked WITH captures covers a later walk without them ;
        // the converse does not hold (a shared node under a temporary
        // and on a direct display path is still captured on that path)
        if (cap ? !walked.insert(t).second : (walked.count(t) > 0 || !walkedNoCap.insert(t).second)) {
            continue;
        }
        if (getCertifiedSigType(t)->variability() < kSamp) {
            continue;  // consts and slow : inlined at emission
        }
        int  i;
        Tree x, y, g;
        tvec V;
        if (isSigTemp(t, x)) {
            // an explicit temporary is a stored variable : captured as
            // such (the capture reads the variable), and nothing below it
            // is captured again -- its cone is computed in the loop. The
            // stateful parts below still need rooting : the descent goes
            // on without captures.
            if (cap && seenC.insert(t).second) {
                fDisplayCapturePoints.push_back(t);
            }
            work.push_back({x, false});
            continue;
        }
        // the STATEFUL parts of a display cone (the design of
        // SIGNAUX-ATTACHES restated 2026-08-29) : projections, delays,
        // prefixes -- and the FIR/IIR kernels, which carry the state of
        // the delays they absorbed. Every stateful part is ROOTED (it
        // joins the scheduling and marking lists ; the immediate graph
        // then orders its whole cone, kernel sources included), and the
        // stateless crown stays in the block-rate tail.
        bool stateful = isProj(t, &i, g) || isSigDelay(t, x, y) || isSigPrefix(t, x, y) ||
                        isSigFIR(t, V) || isSigIIR(t, V);
        if (stateful) {
            // the SCHEDULING root is the WRITER under the read : a delayed
            // read has no immediate edge to its writer, so rooting the
            // read alone would never compile (nor declare) the line. The
            // read itself stays the capture point.
            Tree root = t;
            Tree dx, dy;
            while (isSigDelay(root, dx, dy)) {
                root = dx;
            }
            if (seenS.insert(root).second) {
                fDisplayStateful.push_back(root);
            }
            if (cap && seenC.insert(t).second) {
                fDisplayCapturePoints.push_back(t);
            }
            continue;
        }
        if (!tailCarries(t)) {
            // inputs, tables, generators... : computed in-loop, captured.
            // The DESCENT CONTINUES below the capture : a captured node
            // may sit above stateful parts (spectralLevel : fifteen
            // octave-band kernels under the level computation), and only
            // the frontier can root them -- stopping here left them to a
            // schedule-less compilation referencing undeclared vectors.
            if (cap && seenC.insert(t).second) {
                fDisplayCapturePoints.push_back(t);
            }
        }
        for (int k = 0; k < t->arity(); k++) {
            work.push_back({t->branch(k), cap});
        }
    }
}

// The block-rate tail : builds the expression string of a display signal
// from capture variables, slow values (normal machinery) and the
// stateless operators the frontier walked through.
std::string ScalarCompiler::displayExpr(Tree t)
{
    if (auto it = fDisplayCaptures.find(t); it != fDisplayCaptures.end()) {
        return it->second;
    }
    if (getCertifiedSigType(t)->variability() < kSamp) {
        return CS(t);  // const or slow : loop-independent by construction
    }
    int  op;
    Tree x, y, sel;
    if (isSigBinOp(t, &op, x, y)) {
        const char* wrap =
            (getCertifiedSigType(t)->nature() == kInt) ? wrapHelper(op) : nullptr;
        std::string sx = displayExpr(x);
        std::string sy = displayExpr(y);
        return wrap ? subst("$0($1, $2)", wrap, sx, sy)
                    : subst("($0 $1 $2)", sx, gBinOpTable[op]->fName, sy);
    }
    if (isSigIntCast(t, x)) {
        return subst("int(+$0)", displayExpr(x));
    }
    if (isSigFloatCast(t, x)) {
        return subst("$1(+$0)", displayExpr(x), ifloat());
    }
    if (isSigSelect2(t, sel, x, y)) {
        std::string ssel = displayExpr(sel);
        std::string sy   = displayExpr(y);
        std::string sx   = displayExpr(x);
        return subst("(($0) ? $1 : $2)", ssel, sy, sx);
    }
    if (tvec V; isSigSum(t, V)) {
        // the n-ary sum of the normal form (revealSum), chained left like
        // generateSum -- same association, bit-exact ; int sums wrap
        // pairwise through unsigned arithmetic. Without this arm a
        // level-in-dB crown (20*log10(...) + offset) was a capture,
        // computed per sample on both emitters (spectralLevel).
        const bool  wrapInt = (getCertifiedSigType(t)->nature() == kInt);
        std::string acc;
        for (Tree b : V) {
            if (isZero(b)) {
                continue;
            }
            std::string a = displayExpr(b);
            if (acc.empty()) {
                acc = a;
            } else if (wrapInt) {
                acc = subst("faust_wrap_add($0, $1)", acc, a);
            } else {
                acc = subst("($0 + $1)", acc, a);
            }
        }
        return acc.empty() ? std::string("0") : acc;
    }
    if (getUserData(t) != nullptr && t->arity() > 0) {
        xtendedCodegen*          p = static_cast<xtendedCodegen*>((xtended*)getUserData(t));
        std::vector<std::string> args;
        std::vector<Type>        types;
        for (int k = 0; k < t->arity(); k++) {
            args.push_back(displayExpr(t->branch(k)));
            types.push_back(getCertifiedSigType(t->branch(k)));
        }
        return p->generateCode(fClass, args, types);
    }
    std::stringstream err;
    err << "ERROR : DISPLAYBLOCK tail cannot carry " << ppsig(t, 32) << "\n";
    throw faustexception(err.str());
}

// Emission : the capture stores at the end of the loop body, then one
// Zone4 store per widget -- the whole display list evaluates once per
// compute, on the block-final values.
void ScalarCompiler::emitDisplayList()
{
    if (fDisplayList == nullptr || !isList(fDisplayList)) {
        return;
    }
    int k = 0;
    for (Tree p : fDisplayCapturePoints) {
        Type        ty    = getCertifiedSigType(p);
        std::string ctype = (ty->nature() == kInt) ? "int" : ifloat();
        std::string name  = subst("fDpyCap$0", T(k++));
        fClass->addZone2(subst("$0 \t$1;", ctype, name));
        fClass->addExecCode(Statement("", subst("$0 = $1;", name, CS(p))));
        fDisplayCaptures[p] = name;
    }
    emitDisplayWidgets();
}

// The widget stores : one Zone4 store per harvested bargraph, computed
// from the capture scalars -- taken at the end of the loop body on the
// classic path, as the last element of each vector on the split path.
void ScalarCompiler::emitDisplayWidgets()
{
    if (fDisplayList == nullptr || !isList(fDisplayList)) {
        return;
    }
    for (Tree l = fDisplayList; isList(l); l = tl(l)) {
        Tree d = hd(l);
        Tree path, mn, mx, x;
        if (!isSigVBargraph(d, path, mn, mx, x) && !isSigHBargraph(d, path, mn, mx, x)) {
            // input widget item : declare it if nothing else will (the UI
            // must not lose a control), compute nothing. The compiled
            // expression is registered so a later CS on the same widget
            // (a slider under a harvested bargraph) reuses the name
            // instead of re-declaring it.
            Tree        c, stp;
            std::string done;
            if (getCompiledExpression(d, done)) {
                continue;  // audio (or an earlier item) declared it
            }
            if (fDisplayPreserved.count(d) == 0) {
                continue;  // only a widget of a HARVESTED cone earns the
                           // declaration ; one whose only life was an
                           // eliminated attach cone dies with it
            }
            std::string vn, init;
            if (isSigButton(d, path)) {
                vn   = getFreshID("fbutton");
                init = "0.0";
            } else if (isSigCheckbox(d, path)) {
                vn   = getFreshID("fcheckbox");
                init = "0.0";
            } else if (isSigVSlider(d, path, c, mn, mx, stp) ||
                       isSigHSlider(d, path, c, mn, mx, stp)) {
                vn   = getFreshID("fslider");
                init = T(tree2double(c));
            } else if (isSigNumEntry(d, path, c, mn, mx, stp)) {
                vn   = getFreshID("fentry");
                init = T(tree2double(c));
            } else {
                continue;
            }
            fClass->addDeclCode(subst("$1 \t$0;", vn, xfloat()));
            fClass->addInitUICode(subst("$0 = $1;", vn, init));
            Tree uipath   = reverse(tl(path));
            Tree uiwidget = uiWidget(hd(path), tree(vn), d);
            fUITree.addUIWidget(uipath, uiwidget);
            setCompiledExpression(d, subst("$1($0)", vn, ifloat()));
            continue;
        }
        std::string varname = getFreshID("fbargraph");
        fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
        Tree uipath   = reverse(tl(path));
        Tree uiwidget = uiWidget(hd(path), tree(varname), d);
        fUITree.addUIWidget(uipath, uiwidget);
        fClass->addZone4(subst("$0 = $1;", varname, displayExpr(x)));
    }
}

string ScalarCompiler::generateVBargraph(Tree sig, Tree path, Tree min, Tree max, const string& exp)
{
    string varname = getFreshID("fbargraph");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    Tree uipath   = reverse(tl(path));
    Tree uiwidget = uiWidget(hd(path), tree(varname), sig);
    fUITree.addUIWidget(uipath, uiwidget);

    Type t = getCertifiedSigType(sig);
    switch (t->variability()) {
        case kKonst:
            fClass->addInitUICode(subst("$0 = $1;", varname, exp));
            break;

        case kBlock:
            fClass->addZone2(subst("$0 = $1;", varname, exp));
            break;

        case kSamp:
            fClass->addExecCode(Statement(getConditionCode(sig), subst("$0 = $1;", varname, exp)));
            break;
    }

    // return varname;
    return generateCacheCode(sig, varname);
}

string ScalarCompiler::generateHBargraph(Tree sig, Tree path, Tree min, Tree max, const string& exp)
{
    string varname = getFreshID("fbargraph");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    Tree uipath   = reverse(tl(path));
    Tree uiwidget = uiWidget(hd(path), tree(varname), sig);
    fUITree.addUIWidget(uipath, uiwidget);

    Type t = getCertifiedSigType(sig);
    switch (t->variability()) {
        case kKonst:
            fClass->addInitUICode(subst("$0 = $1;", varname, exp));
            break;

        case kBlock:
            fClass->addZone2(subst("$0 = $1;", varname, exp));
            break;

        case kSamp:
            fClass->addExecCode(Statement(getConditionCode(sig), subst("$0 = $1;", varname, exp)));
            break;
    }

    // return varname;
    return generateCacheCode(sig, varname);
}

/*****************************************************************************
 Soundfile
 *****************************************************************************/

string ScalarCompiler::generateSoundfile(Tree sig, Tree path)
{
    string varname = getFreshID("fSoundfile");

    Tree uipath   = reverse(tl(path));

    Tree uiwidget = uiWidget(hd(path), tree(varname), sig);

    fUITree.addUIWidget(uipath, uiwidget);

    // the pointer is read before any UI writes it (instanceResetUserInterface
    // tests it for null) : an indeterminate value there is undefined
    // behaviour, and clang -O2 has been seen deleting the exit of the table
    // fill loop that precedes the read (faustlibraries loop_test)
    fClass->addDeclCode(subst("Soundfile* \t$0 = nullptr;", varname));

    fClass->addInitUICode(subst("if (uintptr_t($0) == 0) $0 = defaultsound;", varname));
    fClass->addFirstPrivateDecl(subst("$0cache", varname));

    fClass->addZone2(subst("Soundfile* $0cache = $0;", varname));
    fClass->addZone4(subst("$0 = $0cache;", varname));
    return varname;
}

/*****************************************************************************
                                TABLES
 *****************************************************************************/

/*----------------------------------------------------------------------------
                        sigGen : initial table content
----------------------------------------------------------------------------*/

string ScalarCompiler::generateSigGen(Tree sig, Tree content)
{
    string klassname = getFreshID("SIG");
    string signame   = getFreshID("sig");

    fClass->addSubKlass(signal2klass(fClass, klassname, content));
    fClass->addInitCode(subst("$0 $1;", klassname, signame));
    fInstanceInitProperty.set(content, pair<string, string>(klassname, signame));

    return signame;
}

string ScalarCompiler::generateStaticSigGen(Tree sig, Tree content)
{
    string klassname = getFreshID("SIG");
    string signame   = getFreshID("sig");

    fClass->addSubKlass(signal2klass(fClass, klassname, content));
    fClass->addStaticInitCode(subst("$0 $1;", klassname, signame));
    fStaticInitProperty.set(content, pair<string, string>(klassname, signame));

    return signame;
}

/*----------------------------------------------------------------------------
                        sigTable : table declaration
----------------------------------------------------------------------------*/

string ScalarCompiler::generateTable(Tree sig, Tree tsize, Tree content)
{
    int  size;
    bool res = isSigInt(tsize, &size);
    // Size type is previously checked in sigWriteReadTable or sigReadOnlyTable
    faustassert(res);

    string generator(CS(content));
    Tree   g;
    string cexp;
    string ctype, vname;

    // Already compiled but check if we need to add declarations
    faustassert(isSigGen(content, g));
    pair<string, string> kvnames;
    if (!fInstanceInitProperty.get(g, kvnames)) {
        // Not declared here, we add a declaration
        bool b = fStaticInitProperty.get(g, kvnames);
        faustassert(b);
        fClass->addInitCode(subst("$0 $1;", kvnames.first, kvnames.second));
    }

    // Define table name and type
    getTypedNames(getCertifiedSigType(content), "tbl", ctype, vname);

    // Table declaration
    fClass->addDeclCode(subst("$0 \t$1[$2];", ctype, vname, T(size)));

    // Initialization of the content generator
    fClass->addInitCode(subst("$0.init(sample_rate);", generator));
    // Filling the table
    fClass->addInitCode(subst("$0.fill($1,$2);", generator, T(size), vname));

    // Returning the table name
    return vname;
}

string ScalarCompiler::generateStaticTable(Tree sig, Tree tsize, Tree content)
{
    int  size;
    bool res = isSigInt(tsize, &size);
    // Size type is previously checked in sigWriteReadTable or sigReadOnlyTable
    faustassert(res);

    Tree   g;
    string cexp;
    string ctype, vname;

    faustassert(isSigGen(content, g));

    if (!getCompiledExpression(content, cexp)) {
        cexp = setCompiledExpression(content, generateStaticSigGen(content, g));
    } else {
        // already compiled but check if we need to add declarations
        pair<string, string> kvnames;
        if (!fStaticInitProperty.get(g, kvnames)) {
            // not declared here, we add a declaration
            bool b = fInstanceInitProperty.get(g, kvnames);
            faustassert(b);
            fClass->addStaticInitCode(subst("$0 $1;", kvnames.first, kvnames.second));
        }
    }

    // Define table name and type
    getTypedNames(getCertifiedSigType(content), "tbl", ctype, vname);

    // Table declaration
    if (gGlobal->gMemoryManager >= 0) {
        fClass->addDeclCode(subst("static $0* \t$1;", ctype, vname));
        fClass->addStaticFields(subst("$0* \t$1::$2 = 0;", ctype, fClass->getClassName(), vname));
        fClass->addStaticInitCode(subst(
            "$0 = static_cast<$1*>(fManager->allocate(sizeof($1) * $2));", vname, ctype, T(size)));
        fClass->addStaticDestroyCode(subst("fManager->destroy($0);", vname));
    } else {
        fClass->addDeclCode(subst("static $0 \t$1[$2];", ctype, vname, T(size)));
        fClass->addStaticFields(
            subst("$0 \t$1::$2[$3];", ctype, fClass->getClassName(), vname, T(size)));
    }

    // Initialization of the content generator
    fClass->addStaticInitCode(subst("$0.init(sample_rate);", cexp));
    // Filling the table
    fClass->addStaticInitCode(subst("$0.fill($1,$2);", cexp, T(size), vname));

    // Returning the table name
    return vname;
}

/*----------------------------------------------------------------------------
                        sigWRTable : table assignement
----------------------------------------------------------------------------*/

string ScalarCompiler::generateWRTbl(Tree sig, Tree size, Tree gen, Tree wi, Tree ws)
{
    string tblName = generateTable(sig, size, gen);
    // std::cerr << "wi = " << *wi << " ws = " << *ws << "\n";
    std::string swi = CS(wi);
    std::string sws = CS(ws);

    switch (getCertifiedSigType(sig)->variability()) {
        case kKonst:
            fClass->addInitCode(subst("$0[$1] = $2;", tblName, swi, sws));
            break;
        case kBlock:
            fClass->addZone2(subst("$0[$1] = $2;", tblName, swi, sws));
            break;
        default:
            fClass->addExecCode(
                Statement(getConditionCode(sig), subst("$0[$1] = $2;", tblName, swi, sws)));
            break;
    }

    // Return table access
    return tblName;
}

/*----------------------------------------------------------------------------
                        sigRDTable : table access
----------------------------------------------------------------------------*/

string ScalarCompiler::generateRDTbl(Tree sig, Tree tbl, Tree ri)
{
    // Test the special case of a read only table that can be compiled as a static member
    Occurrences* o = fOccMarkup->retrieve(sig);
#ifdef TRACE
    std::cerr << "generateRDTbl : " << sig << "; mxd=" << o->getMaxDelay()
              << "; delay count=" << o->getDelayCount() << "\n";
#endif
    Tree size, gen;
    if (isSigWRTbl(tbl, size, gen)) {
        // rdtable
        string tblname;
        if (!getCompiledExpression(tbl, tblname)) {
            tblname = setCompiledExpression(tbl, generateStaticTable(tbl, size, gen));
        }
        std::string ricode = CS(ri);
        std::string instr  = subst("$0[$1]", tblname, ricode);
        std::string result = generateCacheCode(sig, instr);
        return result;
    } else {
        // rwtable
        std::string tblcode = CS(tbl);
        std::string ricode  = CS(ri);
        return generateCacheCode(sig, subst("$0[$1]", tblcode, ricode));
    }
}

/*****************************************************************************
                               RECURSIONS
*****************************************************************************/

/**
 * Generate code for a projection of a group of mutually recursive definitions
 */
string ScalarCompiler::generateRecProj(Tree sig, Tree r, int i)
{
    string pname, ctype;
    Tree   var, le;

    if (gGlobal->gFamilyForm) {
        // a definition of an automaton's group that the cells do not need
        // (LES-AUTOMATES) : computed where the schedule places it, into the
        // family's current generation, after the family (it may read the
        // cells' current generation ; the family is emitted at the first
        // read of the group's current generation, this one included), and
        // after its own inputs -- compiled at the family's emission it would
        // read a signal of the same sample before its write (the plucking
        // position of triangleMesh, one sample late)
        if (auto it = fFamGroup.find(r); it != fFamGroup.end()) {
            FamPlan& f = fFamilies[it->second];
            if (std::find(f.defsAfter.begin(), f.defsAfter.end(), i) != f.defsAfter.end()) {
                if (!f.emitted) {
                    emitFamily(f);
                }
                faustassert(isRec(r, var, le));
                std::string cell = subst("fFam$0New[$1]", T(f.id), T(i));
                fClass->addExecCode(Statement("", subst("$0 = $1;", cell, CS(nth(le, i)))));
                return cell;
            }
        }
    }

    // if (!getVectorNameProperty(sig, vname)) {
    //     faustassert(isRec(r, var, le));
    //     // generateRec(r, var, le);
    //     // faustassert(getVectorNameProperty(sig, vname));
    //     std::string ctype;
    //     Type        ty = getCertifiedSigType(sig);
    //     getTypedNames(ty, "Reec", ctype, vname);
    //     setVectorNameProperty(sig, vname);
    //     int  delay = fOccMarkup->retrieve(sig)->getMaxDelay();
    //     int  count = fOccMarkup->retrieve(sig)->getDelayCount();
    //     bool mono  = isSigSimpleRec(sig);
    //     Tree def   = nth(le, i);
    //     fClass->addDeclCode(subst("// Recursion delay $0 is of type $1", vname,
    //     nameDelayType(analyzeDelayType(sig)))); fClass->addDeclCode(subst("// While its
    //     definition is of type $0", nameDelayType(analyzeDelayType(def))));
    //     generateDelayLine(analyzeDelayType(sig), ctype, vname, delay, count, mono, CS(def),
    //     getConditionCode(def));
    // }

    Type ty = getCertifiedSigType(sig);
    getTypedNames(ty, "Riiic", ctype, pname);
    string vecname = ensureVectorNameProperty(pname, sig);
    int    delay   = fOccMarkup->retrieve(sig)->getMaxDelay();
    int    count   = fOccMarkup->retrieve(sig)->getDelayCount();
    bool   mono    = isSigSimpleRec(sig);

    faustassert(isRec(r, var, le));
    Tree def = nth(le, i);
    fClass->addDeclCode(subst("// Recursion delay $0 is of type $1", vecname,
                              nameDelayType(analyzeDelayType(sig))));
    fClass->addDeclCode(
        subst("// While its definition is of type $0", nameDelayType(analyzeDelayType(def))));
    DelayType   dtype = analyzeDelayType(sig);
    std::string code  = CS(def);
    std::string cond  = getConditionCode(def);
    std::string dl0   = generateDelayLine(dtype, ctype, vecname, delay, count, mono, code, cond);

    return dl0;
}

/**
 * @brief Check if sig is a simple recursive signal that can be expressed using a single variable
 *
 * @param sig the signal to analyse, typically proj(i,X)
 * @return true if sig is of type x = f(x') and x' is used only once. In this case the same variable
 * can be used both for x and x'
 * @return false
 */
bool ScalarCompiler::isSigSimpleRec(Tree sig)
{
    int  i;
    Tree x;

    // sig is a recursive projection
    if (isProj(sig, &i, x)) {
        Tree var, le;
        // the recursive group contains only one recursive signal
        if (isRec(x, var, le) && (len(le) == 1)) {
            int mxd   = fOccMarkup->retrieve(sig)->getMaxDelay();
            int count = fOccMarkup->retrieve(sig)->getDelayCount();
            // The maximum delay of sig is 1 and the delay count is 1
            if ((mxd == 1) && (count == 1)) {
                // sig@1 has only a single occurence (therefore in the definition of sig)
                Tree f = sigDelay(sig, sigInt(1));  // check if it is a delay
                if (fOccMarkup->retrieve(f)) {
                    // this projection is used
                    return !fOccMarkup->retrieve(f)->hasMultiOccurrences();
                }
            }
        }
    }
    return false;
}

/**
 * @brief is the node needle contained in the tree def ? Projections are
 * opaque leaves : the walk must not escape into sibling definitions
 * through the recursive node.
 */
static bool occursWithin(Tree needle, Tree def)
{
    std::set<Tree>    seen;
    std::vector<Tree> work{def};
    while (!work.empty()) {
        Tree t = work.back();
        work.pop_back();
        if (t == needle) {
            return true;
        }
        if (!seen.insert(t).second) {
            continue;
        }
        int  i;
        Tree g;
        if (isProj(t, &i, g)) {
            continue;
        }
        for (int k = 0; k < t->arity(); k++) {
            work.push_back(t->branch(k));
        }
    }
    return false;
}

/**
 * @brief indicate best delay implementation type for a signal according to its max delay and
 * various compilation options.
 *
 * @param sig
 * @return DelayType
 */
DelayType ScalarCompiler::analyzeDelayType(Tree sig)
{
    DelayType dt = analyzeDelayTypeAux(sig);
    return dt;
}

DelayType ScalarCompiler::analyzeDelayTypeAux(Tree sig)
{
    Occurrences* occ = fOccMarkup->retrieve(sig);
    faustassert(occ != nullptr);
    int mxd   = occ->getMaxDelay();
    int count = occ->getDelayCount();

    if (mxd == 0) {
        return DelayType::kZeroDelay;
    }
    if (mxd == 1) {
        // The mono election, in three stages of decreasing comfort. A state
        // of depth 1 can live in one scalar iff every read of its OLD value
        // is emitted before its write.
        if (hasKernelDelayedTap(sig)) {
            // a kernel reads the old value through an internal tap : that
            // read is inseparable from the kernel's tap 0, so it can never
            // precede the write -- and it is invisible to the delayed-read
            // counters below (the readers are sigDelay nodes)
            return DelayType::kSingleDelay;
        }
        int  i;
        Tree x, var, le;
        if (isProj(sig, &i, x) && isRec(x, var, le)) {
            Tree         f  = sigDelay(sig, sigInt(1));
            Occurrences* fo = fOccMarkup->retrieve(f);
            if (gGlobal->gExplicitTemps) {
                // -xtemp : the delayed read may be wrapped in temp(f) -- its
                // readers are the temp's ; the election looks through it
                if (Occurrences* to = fOccMarkup->retrieve(sigTemp(f))) {
                    fo = to;
                }
            }
            if (fo) {
                bool unique = (count == 1) && !fo->hasMultiOccurrences();
                // stage 1 -- singleton group, unique delayed read : the only
                // reader of the old value is the definition itself
                if (unique && len(le) == 1) {
                    return DelayType::kMonoDelay;
                }
                // stage 2 -- mutual group, but the unique delayed read lives
                // in sig's own definition : safe whatever the member order
                if (unique && occursWithin(f, nth(le, i))) {
                    return DelayType::kMonoDelay;
                }
                // stage 3 -- cross readers : safe iff the readers-first
                // promise holds for this writer (every soft edge kept), the
                // write is unconditional, and the schedule is the witness.
                // The node f is computed once at its scheduled position and
                // FORCED into a temporary there (generateDelayAccess) : the
                // soft edge only orders the node, an inlined read would be
                // emitted at its consumer's slot, possibly after the write
                // (nylonGuitar under -ss 11 : the noise state read moved
                // past its own update).
                if (fRFKeptWriters.count(sig) && !fRFSacrificedWriters.count(sig) &&
                    getConditionCode(sig).empty()) {
                    auto pf = fSchedPos.find(f);
                    auto px = fSchedPos.find(sig);
                    if (pf != fSchedPos.end() && px != fSchedPos.end()) {
                        // the witness : a kept edge sig -> f is a schedule
                        // constraint ; its violation is a scheduler bug
                        faustassert(pf->second < px->second);
                        // the election requires the ORDER to protect every
                        // read site : the last consumer of f must precede
                        // the write, because an inlined read is emitted at
                        // its consumer's slot. When a consumer sits after
                        // the write, we do NOT elect -- the kSingleDelay
                        // fallback ([2]-vector, rotation) is order-robust
                        // by distinct cells and costs the same storage as
                        // mono + a forced capture, without hoisting a live
                        // range across the body (brassMIDI +30% when the
                        // capture was forced instead).
                        auto cm = fConsumerMaxPos.find(f);
                        if (cm == fConsumerMaxPos.end() || cm->second < px->second) {
                            fRFStage3Elected.insert(sig);
                            return DelayType::kMonoDelay;
                        }
                    }
                }
            }
        }
        return DelayType::kSingleDelay;
    }
    if (mxd <= gGlobal->gMaxCopyDelay) {
        return DelayType::kCopyDelay;
    }
    int dnsty = (100 * count) / mxd;
    if ((mxd <= gGlobal->gMaxDenseDelay) && (dnsty >= gGlobal->gMinDensity)) {
        return DelayType::kDenseDelay;
    }
    if (mxd <= gGlobal->gMaskDelayLineThreshold) {
        return DelayType::kMaskRingDelay;
    }
    return DelayType::kSelectRingDelay;
}

/**
 * Generate code for a group of mutually recursive definitions
 */
void ScalarCompiler::generateRec(Tree sig, Tree var, Tree le)
{
    faustassert(false);

    int N = len(le);

    vector<bool>   used(N);
    vector<int>    delay(N);
    vector<int>    count(N);
    vector<Tree>   exp(N);
    vector<string> vname(N);
    vector<string> ctype(N);
    vector<bool>   mono(N);

    // prepare each element of a recursive definition
    for (int i = 0; i < N; i++) {
        Tree e = sigProj(i, sig);  // recreate each recursive definition
        if (fOccMarkup->retrieve(e)) {
            // this projection is used
            used[i] = true;
            getTypedNames(getCertifiedSigType(e), "Rec", ctype[i], vname[i]);
            setVectorNameProperty(e, vname[i]);
            delay[i] = fOccMarkup->retrieve(e)->getMaxDelay();
            count[i] = fOccMarkup->retrieve(e)->getDelayCount();
            mono[i]  = isSigSimpleRec(e);
            exp[i]   = e;

        } else {
            // this projection is not used therefore
            // we should not generate code for it
            used[i] = false;
        }
    }
    // generate delayline for each element of a recursive definition
    for (int i = 0; i < N; i++) {
        if (used[i]) {
            Tree def = nth(le, i);
            fClass->addDeclCode(subst("// Recursion delay $0 is of type $1", vname[i],
                                      nameDelayType(analyzeDelayType(exp[i]))));
            fClass->addDeclCode(subst("// While its definition is of type $0",
                                      nameDelayType(analyzeDelayType(def))));
            DelayType   dtype = analyzeDelayType(exp[i]);
            std::string code  = CS(def);
            std::string cond  = getConditionCode(def);
            generateDelayLine(dtype, ctype[i], vname[i], delay[i], count[i], mono[i], code, cond);
        }
    }
}

/*****************************************************************************
 Control
 *****************************************************************************/

string ScalarCompiler::generateControl(Tree sig, Tree x, Tree y)
{
    CS(y);
    return generateCacheCode(x, CS(x));
}

/*****************************************************************************
 PREFIX, DELAY A PREFIX VALUE
 *****************************************************************************/

string ScalarCompiler::generatePrefix(Tree sig, Tree x, Tree e)
{
    string vperm = getFreshID("pfPerm");
    string vtemp = getFreshID("pfTemp");
    string type  = (getCertifiedSigType(sig)->nature() == kInt) ? "int" : ifloat();

    fClass->addDeclCode(subst("$0 \t$1;", type, vperm));
    fClass->addInitCode(subst("$0 = $1;", vperm, CS(x)));

    fClass->addExecCode(
        Statement(getConditionCode(sig), subst("$0 \t$1 = $2;", type, vtemp, vperm)));

    /*
    string res = CS(e);
    string vname;
    if (getVectorNameProperty(e, vname)) {
        setVectorNameProperty(sig, vname);
    } else {
        faustassert(false);
    }
    */

    std::string cond = getConditionCode(sig);
    std::string ve   = CS(e);
    fClass->addExecCode(Statement(cond, subst("$0 = $1;", vperm, ve)));
    return vtemp;
}

/*****************************************************************************
 SELECT
 *****************************************************************************/

string ScalarCompiler::generateSelect2(Tree sig, Tree sel, Tree s1, Tree s2)
{
    std::string csel = CS(sel);
    std::string cs2  = CS(s2);
    std::string cs1  = CS(s1);
    return generateCacheCode(sig, subst("(($0) ? $1 : $2)", csel, cs2, cs1));
}

/*****************************************************************************
 EXTENDED
 *****************************************************************************/

string ScalarCompiler::generateXtended(Tree sig)
{
    xtendedCodegen* p = static_cast<xtendedCodegen*>((xtended*)getUserData(sig));
    vector<string> args;
    vector<Type>   types;

    for (int i = 0; i < sig->arity(); i++) {
        args.push_back(CS(sig->branch(i)));
        types.push_back(getCertifiedSigType(sig->branch(i)));
    }

    if (p->needCache()) {
        return generateCacheCode(sig, p->generateCode(fClass, args, types));
    } else {
        return p->generateCode(fClass, args, types);
    }
}

/*****************************************************************************
 N-SAMPLE FIXED DELAY : sig = exp@delay

 case 1-sample max delay :
 Y(t-0)	Y(t-1)
 V[0]	V[1]

 case max delay < gMaxCopyDelay :
 Y(t-0)	Y(t-1)	Y(t-2)  ...
 V[0]	V[1]	V[2]	...

 case max delay >= gMaxCopyDelay :
 Y(t-0)	Y(t-1)	Y(t-2)  ...
 V[0]	V[1]	V[2]	...

 *****************************************************************************/

/**
 * Generate code for accessing a delayed signal. The generated code depend of
 * the maximum delay attached to exp.
 */
/**
 * Raw access to a delayed signal with a string index -- used by the FIR
 * accumulation loop. No caching : the index may be the loop variable.
 */
/**
 * Adjacent-pair collapse, census side (spec PAIRE-ADJACENTE) : record every
 * CONSTANT, UNCONDITIONAL read delay per delayed signal. Pairs (d-1, d)
 * found here turn the d read into a carried scalar at emission time.
 */
void ScalarCompiler::censusAdjacentReads(Tree L)
{
    std::set<Tree>            seen;
    std::function<void(Tree)> walkT = [&](Tree t) {
        if (!seen.insert(t).second) {
            return;
        }
        Tree x, y, var, body;
        int  d;
        if (isSigDelay(t, x, y) && isSigInt(y, &d) && d >= 1 && getConditionCode(t).empty()) {
            fAdjDelaySets[x].insert(d);
        }
        if (isSigEnable(t, x, y) || isSigControl(t, x, y)) {
            fHasEnableControl = true;
        }
        if (isRec(t, var, body)) {
            // recursive groups do not expose their definitions through
            // arity() -- the cycle ; every walker descends explicitly
            if (body != nullptr) {
                walkT(body);
            }
            return;
        }
        for (int k = 0; k < t->arity(); k++) {
            walkT(t->branch(k));
        }
    };
    walkT(L);
}

/**
 * Adjacent-pair collapse, refresh side : at the end of every loop body the
 * carried scalars shift, HIGHEST delay first in the EMITTED text (a chain
 * d+2, d+1 must move before its source is overwritten -- and postcode is
 * a stack, so the append order is the reverse). Runs after the whole schedule
 * compiled, so every source variable exists ; iteration follows CREATION
 * order (the schedule's), never a pointer-keyed map -- determinism.
 * The IOTA increment is itself an earlier post statement, so the memory
 * fallback reads at d, not d-1 (the index has already advanced).
 */
void ScalarCompiler::emitAdjacentUpdates()
{
    std::vector<Tree> exps;
    for (const auto& h : fAdjHighs) {
        if (std::find(exps.begin(), exps.end(), h.exp) == exps.end()) {
            exps.push_back(h.exp);
        }
    }
    for (Tree e : exps) {
        std::vector<const AdjHigh*> hs;
        for (const auto& h : fAdjHighs) {
            if (h.exp == e) {
                hs.push_back(&h);
            }
        }
        // addPostCode STACKS (push_front, printed in reverse of addition) :
        // append lowest delay first so the EMITTED order is highest first,
        // each link reading its source before that source's own refresh.
        // Appending highest first emits the chain reversed and the fresh
        // value floods every carried scalar (guitarix : the 133-tap
        // cabinet convolution collapsed onto its most recent samples).
        std::sort(hs.begin(), hs.end(),
                  [](const AdjHigh* a, const AdjHigh* b) { return a->d < b->d; });
        for (const AdjHigh* h : hs) {
            std::string src;
            for (const auto& hh : fAdjHighs) {
                if (hh.exp == e && hh.d == h->d - 1) {
                    src = hh.name;
                }
            }
            if (src.empty()) {
                for (const auto& lo : fAdjLows) {
                    if (lo.exp == e && lo.d == h->d - 1) {
                        src = lo.var;
                    }
                }
            }
            if (src.empty()) {
                // safety net : re-read from memory, post-increment index
                std::string vecname;
                if (!getVectorNameProperty(e, vecname)) {
                    continue;
                }
                int N = pow2limit(fOccMarkup->retrieve(e)->getMaxDelay() + 1);
                src   = subst("$0[faust_wrap_sub(IOTA, $1)&$2]", vecname, T(h->d), T(N - 1));
            }
            fClass->addPostCode(Statement("", subst("$0 = $1;", h->name, src)));
        }
    }
}

string ScalarCompiler::generateDelayAccessRaw(Tree sig, Tree exp, const string& delayidx)
{
    std::string ctype, pname;
    getTypedNames(getCertifiedSigType(sig), "Veeec", ctype, pname);
    string    vecname = ensureVectorNameProperty(pname, exp);
    int       mxd     = fOccMarkup->retrieve(exp)->getMaxDelay();
    DelayType dt      = analyzeDelayType(exp);
    switch (dt) {
        case DelayType::kNotADelay:
            faustexception("Try to compile as a delay something that is not a delay");
            return "";
        case DelayType::kZeroDelay:
        case DelayType::kMonoDelay:
            return vecname;
        case DelayType::kSingleDelay:
        case DelayType::kCopyDelay:
        case DelayType::kDenseDelay:
            return subst("$0[$1]", vecname, delayidx);
        case DelayType::kMaskRingDelay:
        case DelayType::kSelectRingDelay:
        default: {
            int N = pow2limit(mxd + 1);
            // the index cannot be cached : it may depend on the loop variable
            return subst("$0[faust_wrap_sub(IOTA, $1)&$2]", vecname, delayidx, T(N - 1));
        }
    }
}

// FAMILIES FIRST, KERNELS AFTER (LES-AUTOMATES §9). The kernels are formed
// per site (the retiming law, the factorization, the hoisting look at the
// sharing around a site), so two isomorphic cells came out with different
// kernel decompositions and stopped being isomorphic (the 2-D plate : 96
// cells in classes of 16, 16, 16, 6 and 6 ; the hammered string, the glass
// harmonica : no automaton at all under -fam -fir). The families are
// therefore recognized on the bare tree ; then the kernel passes run on the
// rest of the tree, the families' subtrees FROZEN into opaque leaves they
// cannot look into ; and each family's template gets its kernels once,
// alone, the same decision for every member.

// the opaque leaf standing for a frozen subtree : an audio input for an
// audio real node, a slow slider for a slow real one (the kernel passes ask
// whether a coefficient is audio or not, nothing else), an int cast of either
// for an int node ; typed later with the tree they stand in
static Tree famPlaceholder(Tree t, int n, bool typed)
{
    Tree ph = sigInput(1000000 + n);
    if (typed) {
        Type ty = getCertifiedSigType(t);
        if (ty->variability() < kSamp) {
            // one tree per statement : the arguments' creation order is the C++ compiler's choice
            Tree label = tree(Node(unique("fam_frozen_")));
            Tree init  = sigReal(0.0);
            Tree lo    = sigReal(-1.0);
            Tree hi    = sigReal(1.0);
            Tree step  = sigReal(0.01);
            ph         = sigHSlider(label, init, lo, hi, step);
        }
        if (ty->nature() == kInt) {
            ph = sigIntCast(ph);
        }
    }
    return ph;
}

// the frozen nodes replaced by their placeholders, back : placeholder -> node
Tree ScalarCompiler::famFreeze(Tree root, const std::set<Tree>& frozen, std::unordered_map<Tree, Tree>& back, bool typed)
{
    std::unordered_map<Tree, Tree> memo, fwd;
    int                            n = 0;
    auto pre = [&](Tree t) -> std::optional<Tree> {
        if (!frozen.count(t)) {
            return std::nullopt;
        }
        auto it = fwd.find(t);
        if (it == fwd.end()) {
            Tree ph = famPlaceholder(t, n++, typed);
            fwd[t]  = ph;
            back[ph] = t;
            it = fwd.find(t);
        }
        return it->second;
    };
    auto rule    = [](Tree, Tree rebuilt) -> Tree { return rebuilt; };
    auto defRule = [](Tree, Tree rebuilt) -> Tree { return rebuilt; };
    return treeRewritePaired(root, pre, rule, memo, defRule);
}

// the placeholders replaced by the nodes they stood for, which come back as
// they were (the cut returns the node itself : nothing inside is rebuilt)
Tree ScalarCompiler::famThaw(Tree root, const std::unordered_map<Tree, Tree>& back)
{
    std::unordered_map<Tree, Tree> memo;
    auto pre = [&](Tree t) -> std::optional<Tree> {
        auto it = back.find(t);
        return it == back.end() ? std::nullopt : std::optional<Tree>(it->second);
    };
    auto rule    = [](Tree, Tree rebuilt) -> Tree { return rebuilt; };
    auto defRule = [](Tree, Tree rebuilt) -> Tree { return rebuilt; };
    return treeRewritePaired(root, pre, rule, memo, defRule);
}

// -fam -fir : the kernel pipeline (the one of -fir, revealSum first, the
// lowering last under -lsum) on the tree with the families frozen : the hosts
// of the sum families, every projection of an automaton's group, the members
// of the output families. What the passes rebuild outside is theirs ; what
// they never saw comes back untouched, so the plan's nodes are still the
// tree's. The lowering cannot reach a family's sums either : famKeepSums is
// not needed on this path.
// the tree's nodes a rewrite must not look into once the families are
// planned : see famKernelizeOutside for what they are
std::set<Tree> ScalarCompiler::famFrozenSet(Tree L2)
{
    std::set<Tree> frozen;
    std::set<Tree> groups;
    // what a family reads from outside (its slots, audio slots and commons)
    // is frozen with it : the loop reads the tree's node, and a node the
    // passes had rebuilt would be compiled twice, the family's copy with
    // states of its own that nothing writes (bowed, wrong from sample 2)
    auto freezeLeaf = [&](Tree v) {
        Tree t = famOrig(v);
        int  pi;
        Tree g;
        if (!getSigType(t) || isNum(t) || (isProj(t, &pi, g) && groups.count(g))) {
            return;
        }
        frozen.insert(t);
    };
    for (FamPlan& f : fFamilies) {
        if (f.trees.empty()) {
            continue;
        }
        if (f.group) {
            groups.insert(famOrig(f.group));
        } else if (!f.hosts.empty() && f.hosts[0]) {
            for (Tree h : f.hosts) {
                frozen.insert(famOrig(h));
            }
        } else {
            for (Tree t : f.trees) {
                frozen.insert(famOrig(t));
            }
        }
    }
    for (FamPlan& f : fFamilies) {
        if (f.trees.empty()) {
            continue;
        }
        for (auto& v : f.slots) {
            for (Tree t : v) {
                freezeLeaf(t);
            }
        }
        for (auto& v : f.aslots) {
            for (Tree t : v) {
                freezeLeaf(t);
            }
        }
        for (Tree t : f.commons) {
            freezeLeaf(t);
        }
        for (Tree t : f.borderInputs) {
            freezeLeaf(t);
        }
    }
    // A frozen node inside the body of a recursive group freezes the whole
    // group : the rewrite gives every group a fresh variable, and a frozen
    // subtree kept as it is would still refer to the old one -- two
    // instances of the recursion, the host of bowed applied twice. The
    // enclosing groups, to the fixpoint (a frozen group's projections may
    // sit inside another group).
    {
        std::map<Tree, Tree> enclosing;  // node -> the innermost group whose body holds it
        std::set<Tree>       seen;
        std::function<void(Tree, Tree)> walk = [&](Tree t, Tree g) {
            if (!seen.insert(t).second) {
                return;
            }
            if (g && !enclosing.count(t)) {
                enclosing[t] = g;
            }
            Tree id, body;
            if (isRec(t, id, body)) {
                if (body) {
                    walk(body, t);
                }
                return;
            }
            for (int k = 0; k < t->arity(); k++) {
                walk(t->branch(k), g);
            }
        };
        walk(L2, nullptr);
        for (Tree sd : fDisplayStateful) {
            walk(sd, nullptr);
        }
        bool more = true;
        while (more) {
            more = false;
            for (Tree t : frozen) {
                auto it = enclosing.find(t);
                if (it != enclosing.end() && !groups.count(it->second)) {
                    groups.insert(it->second);
                    more = true;
                }
            }
            // the projections of the frozen groups are frozen ; if one sits inside a group, that group too
            std::set<Tree>    seen2;
            std::vector<Tree> st{L2};
            for (Tree sd : fDisplayStateful) {
                st.push_back(sd);
            }
            while (!st.empty()) {
                Tree t = st.back();
                st.pop_back();
                if (!seen2.insert(t).second) {
                    continue;
                }
                int  i;
                Tree g, id, body;
                if (isProj(t, &i, g) && groups.count(g)) {
                    if (frozen.insert(t).second) {
                        more = true;
                    }
                    continue;  // nothing below a frozen projection is the passes' business
                }
                if (isRec(t, id, body)) {
                    if (body) {
                        st.push_back(body);
                    }
                    continue;
                }
                for (int k = 0; k < t->arity(); k++) {
                    st.push_back(t->branch(k));
                }
            }
        }
        // a node inside a frozen group is frozen with it : it needs no placeholder of its own
        for (auto it = frozen.begin(); it != frozen.end();) {
            int  i;
            Tree g;
            auto e = enclosing.find(*it);
            it     = (e != enclosing.end() && groups.count(e->second) && !(isProj(*it, &i, g) && groups.count(g))) ? frozen.erase(it) : std::next(it);
        }
    }
    return frozen;
}

// a rewrite of the tree around the planned families : frozen, rewritten,
// thawed (the late rewrites of the preparation -- the delay floor, the
// reassociation, the staging temporaries -- would rebuild the families'
// nodes and the plan would be dismantled after the harvest : englishBell
// under -temp 8 lost its family, 6 -> 43 ns)
Tree ScalarCompiler::famAround(Tree L2, const std::function<Tree(Tree)>& pass)
{
    std::set<Tree> frozen = famFrozenSet(L2);
    if (frozen.empty()) {
        return pass(L2);
    }
    std::unordered_map<Tree, Tree> back;
    Tree                           L = famFreeze(L2, frozen, back, false);
    typeAnnotation(L, false);
    L = pass(L);
    L = famThaw(L, back);
    famEmitterStructures();
    return L;
}

Tree ScalarCompiler::famKernelizeOutside(Tree L2)
{
    const bool     trace  = getenv("FAUST_FAM_TRACE") != nullptr;
    std::set<Tree> frozen = famFrozenSet(L2);
    if (frozen.empty()) {
        if (trace) {
            std::cerr << "fam kernels : no family, the kernel passes run on the whole tree" << std::endl;
        }
    }
    std::unordered_map<Tree, Tree> back;
    Tree                           L = frozen.empty() ? L2 : famFreeze(L2, frozen, back, false);
    typeAnnotation(L, false);  // the placeholders, and the rebuilt nodes around them
    std::function<void()> passes = [&]() {
        L = revealSum(L, gGlobal->gLowerSums);
        L = revealFIR(L);
        L = revealIIR(L);
        if (gGlobal->gFIRHoist) {
            L = hoistCommonNumerators(L);
        }
        L = factorizeFIRs(L);
        if (!gGlobal->gLoopSplit && gGlobal->gLowerSums) {
            L = dissolveUnitKernels(L);
        }
        L = kernelCandidacy(L);
        if (gGlobal->gLowerSums) {
            std::set<Tree> keepRows;
            if (gGlobal->gMatrixRows) {
                for (auto& [row, id] : revealMatrix(L).rowOf) {
                    keepRows.insert(row);
                }
            }
            L = lowerSums(L, keepRows.empty() ? nullptr : &keepRows);
        }
    };
    callWithLargeStack(passes);
    if (!frozen.empty()) {
        L = famThaw(L, back);
    }
    famEmitterStructures();  // the emitter's structures, keyed by the tree's nodes (the frozen ones are the plan's)
    if (trace) {
        std::cerr << "fam kernels : " << frozen.size() << " frozen subtree(s) of " << fFamilies.size() << " families, the kernel passes ran around them" << std::endl;
    }
    return L;
}

// -fam -fir : the family's template gets its kernels, once, alone -- its slot
// leaves and commons frozen into opaque leaves typed like them (a slow slot
// is a coefficient the kernel passes may take, an audio slot never), the
// pipeline of -fir on the template as a program of its own, the leaves
// thawed by the loop generator (FamCtx::th). The same decision for every
// member, by construction.
void ScalarCompiler::famKernelizeTemplate(FamPlan& plan)
{
    const bool     trace = getenv("FAUST_FAM_TRACE") != nullptr;
    std::set<Tree> frozen;
    // What is frozen : every slot, audio slot and common -- the passes see
    // them as opaque leaves, a coefficient or an audio input, and can neither
    // open them (a slow expression they would respell into nodes the loop
    // generator does not know) nor fold a value of the template's member
    // into a kernel that every member then runs. A LITERAL is never frozen :
    // a hash-consed int is also an opcode, a projection index, a delay (the
    // frozen 2 of the bells was the multiplication) ; a uniform literal is
    // the same for every member and may stay ; a literal that differs
    // between members leaves the template unkernelized (a real one could be
    // frozen, an int one -- a delay, an index -- cannot be told apart from
    // the structure).
    for (size_t k = 0; k < plan.leaves.size(); k++) {
        Tree l = plan.leaves[k];
        if (!getSigType(l)) {
            continue;  // a structural leaf (the nil tail of a group's definitions)
        }
        if (isNum(l)) {
            bool uniform = true;
            for (size_t m = 1; m < plan.slots.size() && uniform; m++) {
                uniform = (k < plan.slots[m].size() && plan.slots[m][k] == l);
            }
            if (!uniform) {
                if (trace) {
                    std::cerr << "fam kernels : template of family " << plan.id << " : a literal slot differs between members, no kernel" << std::endl;
                }
                return;
            }
            continue;
        }
        frozen.insert(l);
    }
    for (Tree l : plan.aleaves) {
        if (getSigType(l) && !isNum(l)) {
            frozen.insert(l);
        }
    }
    for (Tree l : plan.commons) {
        if (getSigType(l) && !isNum(l)) {
            frozen.insert(l);
        }
    }
    std::unordered_map<Tree, Tree> back;
    Tree                           t = famFreeze(plan.tmpl ? plan.tmpl : plan.trees[0], frozen, back, true);
    Tree                           L = cons(t, gGlobal->nil);
    typeAnnotation(L, false);
    std::function<void()> passes = [&]() {
        L = revealSum(L, false);
        L = revealFIR(L);
        L = revealIIR(L);
        if (gGlobal->gFIRHoist) {
            L = hoistCommonNumerators(L);
        }
        L = factorizeFIRs(L);
        if (!gGlobal->gLoopSplit && gGlobal->gLowerSums) {
            L = dissolveUnitKernels(L);
        }
        L = kernelCandidacy(L);
    };
    callWithLargeStack(passes);
    typeAnnotation(L, false);
    plan.ktemplate = hd(L);
    plan.thaw      = back;
    if (trace) {
        int kernels = 0;
        std::set<Tree>    seen;
        std::vector<Tree> st{plan.ktemplate};
        while (!st.empty()) {
            Tree u = st.back();
            st.pop_back();
            if (!seen.insert(u).second) {
                continue;
            }
            tvec V;
            kernels += isSigFIR(u, V) || isSigIIR(u, V);
            Tree id, body;
            if (isRec(u, id, body)) {
                if (body) {
                    st.push_back(body);
                }
                continue;
            }
            for (int k = 0; k < u->arity(); k++) {
                st.push_back(u->branch(k));
            }
        }
        std::cerr << "fam kernels : template of family " << plan.id << " : " << kernels << " kernel(s), " << back.size() << " frozen leaves" << std::endl;
    }
}

// The plan was made before the harvest (families first) : a family whose
// host, group or members are no longer nodes of the tree (rebuilt by a later
// pass) is dismantled, its private nodes given back to the schedule
void ScalarCompiler::famCheckPlanned(Tree L2)
{
    std::set<Tree>    nodes;
    std::vector<Tree> st{L2};
    for (Tree sd : fDisplayStateful) {
        st.push_back(sd);
    }
    while (!st.empty()) {
        Tree t = st.back();
        st.pop_back();
        if (!nodes.insert(t).second) {
            continue;
        }
        Tree id, body;
        if (isRec(t, id, body)) {
            if (body) {
                st.push_back(body);
            }
            continue;
        }
        for (int k = 0; k < t->arity(); k++) {
            st.push_back(t->branch(k));
        }
    }
    for (FamPlan& f : fFamilies) {
        if (f.trees.empty()) {
            continue;
        }
        bool ok = true;
        if (f.group) {
            ok = nodes.count(famOrig(f.group)) > 0;
        } else if (!f.hosts.empty() && f.hosts[0]) {
            for (Tree h : f.hosts) {
                ok = ok && nodes.count(famOrig(h)) > 0;
            }
        } else {
            for (Tree t : f.trees) {
                ok = ok && nodes.count(famOrig(t)) > 0;
            }
        }
        if (ok) {
            continue;
        }
        if (getenv("FAUST_FAM_TRACE")) {
            std::cerr << "fam dismantled : family of " << f.trees.size() << ", its nodes were rebuilt after the plan" << std::endl;
        }
        for (Tree t : f.priv) {
            fFamPrivate.erase(famOrig(t));
            if (auto it = fFamConsumed.find(t); it != fFamConsumed.end()) {
                for (Tree c : it->second) {
                    fFamPrivate.erase(c);
                }
            }
        }
        for (Tree h : f.hosts) {
            if (h) {
                fFamHost.erase(famOrig(h));
                if (auto it = fFamConsumed.find(h); it != fFamConsumed.end()) {
                    for (Tree c : it->second) {
                        fFamPrivate.erase(c);
                    }
                }
            }
        }
        if (f.group) {
            fFamGroup.erase(famOrig(f.group));
        }
        f.trees.clear();
    }
}

// a node that accesses a group : one of its projections, or a delayed read of one
static bool famAccessesGroup(Tree n, Tree group)
{
    int  pi;
    Tree g, x, y;
    if (isProj(n, &pi, g) && g == group) {
        return true;
    }
    return isSigDelay(n, x, y) && isProj(x, &pi, g) && g == group;
}

// a node that reads a group's CURRENT generation : a projection, or a read of
// one at delay 0. Those are the automaton's hosts : the family is emitted at
// the first of them in the schedule, after its inputs. A read at delay 1 or
// more is a previous generation, in the family's arrays during the whole
// sample (the shift is the last thing of the sample) : it needs nothing.
static bool famReadsGroupNow(Tree n, Tree group)
{
    int  pi;
    Tree g, x, y;
    if (isProj(n, &pi, g) && g == group) {
        return true;
    }
    return isSigDelay(n, x, y) && isZero(y) && isProj(x, &pi, g) && g == group;
}

// a read of an automaton's projection (LES-AUTOMATES) at a constant delay :
// the family's arrays, never a delay line of its own (a kernel's history of
// a projection would be written at the kernel's position, stale by a sample)
bool ScalarCompiler::famAutoRead(Tree exp, int delay, std::string& out)
{
    if (fFamGroup.empty()) {
        return false;
    }
    Tree x, y, g;
    int  i, d = 0;
    if (isSigDelay(exp, x, y) && isSigInt(y, &d) && d >= 1) {
        exp = x;
    } else {
        d = 0;
    }
    if (!isProj(exp, &i, g)) {
        return false;
    }
    auto it = fFamGroup.find(g);
    if (it == fFamGroup.end()) {
        return false;
    }
    const int k = d + delay;
    FamPlan&  f = fFamilies[it->second];
    if (k == 0) {
        if (std::find(f.defsAfter.begin(), f.defsAfter.end(), i) != f.defsAfter.end()) {
            out = CS(exp);  // a definition computed after the loop : its projection (generateRecProj)
            return true;
        }
        if (!f.emitted) {
            emitFamily(f);  // the current generation, read before the schedule reached a host
        }
    }
    out = (k == 0) ? subst("fFam$0New[$1]", T(f.id), T(i)) : subst("fFam$0S_$1[$2]", T(f.id), T(k), T(i));
    faustassert(k <= f.groupDepth);
    return true;
}

string ScalarCompiler::generateDelayAccessRaw(Tree sig, Tree exp, int delay)
{
    std::string cell;
    if (gGlobal->gFamilyForm && famAutoRead(exp, delay, cell)) {
        return cell;
    }
    return generateDelayAccessRaw(sig, exp, T(delay));
}

// density of the non-zero coefficients of a FIR, from its first non-zero one
static float firDensity(const tvec& coefs)
{
    unsigned int fnz = 0;
    for (unsigned int i = 1; i < coefs.size(); ++i) {
        if (!isZero(coefs[i])) {
            fnz = i;
            break;
        }
    }
    unsigned int cnz = 0;
    for (unsigned int i = fnz; i < coefs.size(); ++i) {
        if (!isZero(coefs[i])) {
            cnz++;
        }
    }
    faustassert(cnz > 0);
    return float(cnz) / float(coefs.size() - fnz);
}

/**
 * Generate code for a n-ary sum node (revealed by revealSum) : a flat
 * parenthesis-free addition, the association left to the C compiler.
 */
/**
 * Generate code for an IIR kernel IIR[nil,X,C0=0,C1..Cn] :
 * y = X + C1*y@1 + ... + Cn*y@n. The node reads ITSELF through the
 * standard delay machinery (its occurrences case declares the self reads,
 * which size the delay line). Ported from fir18 (compile_scal_iir.cpp) ;
 * reversed coefficient order kept ("seems faster").
 */
/**
 * The code of a kernel coefficient. The reveal builds the coefficients as
 * new trees over the program's constants ; those trees were never seen by
 * the sharing analysis, so CS() spelled them inline in the sample loop
 * (pow, divisions, per sample : the -fir -iirt emission ran 1.66 times
 * slower than the default on every synthetic matrix). A coefficient
 * whose variability is below sample rate is stored once, at the rate of
 * its variability (a constant at init, a slow value per block), like any
 * cached slow signal ; memoized through the compiled-expression property.
 */
// What a family reads from outside its loop is compiled as the tree's node
// (famOrig), so the code outside the families stays the default's. The view
// also holds nodes of its own making, which no analysis of the tree knows :
// the subtracted operands it negated (-1 * s, s a node of the tree) and the
// constants it folded that way. Those are spelled here.
std::string ScalarCompiler::famCS(Tree t)
{
    Tree o = famOrig(t);
    if (o != t || fOccMarkup->retrieve(o)) {
        return CS(o);
    }
    int    i;
    double r;
    if (isSigInt(t, &i)) {
        return T(i);
    }
    if (isSigReal(t, &r)) {
        return realLiteral(r);
    }
    Tree a, b;
    if (isSigMul(t, a, b) && isMinusOne(a)) {
        return "(-" + famCS(b) + ")";
    }
    std::cerr << "ASSERT : a family reads a node the tree does not hold : " << ppsig(t, 40) << std::endl;
    faustassert(false);
    return "0";
}

std::string ScalarCompiler::famCoef(Tree t)
{
    Tree o = famOrig(t);
    if (o != t || fOccMarkup->retrieve(o)) {
        return coefCode(o);
    }
    return famCS(t);  // a literal or a negation the view made : already a simple spelling
}

string ScalarCompiler::coefCode(Tree coef)
{
    auto memo = fHoistedCoef.find(coef);
    if (memo != fHoistedCoef.end()) {
        return memo->second;
    }
    string code = CS(coef);
    // CS may hold an INLINE spelling of this tree (a coefficient built by
    // the kernel reconstruction, unknown to the sharing analysis, compiled
    // once as a sample-rate operand) : a slow spelling that is neither a
    // variable nor a literal is stored once, computed at its own rate
    if (!isSimpleSpelling(code) && getCertifiedSigType(coef)->variability() < kSamp) {
        code = generateVariableStore(coef, code);
        setCompiledExpression(coef, code);
    }
    fHoistedCoef[coef] = code;
    return code;
}

string ScalarCompiler::generateIIR(Tree sig, const tvec& coefs)
{
    Type         ty = getCertifiedSigType(sig);
    Occurrences* o  = fOccMarkup->retrieve(sig);
    faustassert(o);
    faustassert(coefs.size() > 3);

    std::string vname, ctype;
    getTypedNames(ty, "IIR", ctype, vname);

    const int order = int(coefs.size()) - 3;
    if (sig->getProperty(tree(symbol("SIGIIRTRANSPOSED"))) != nullptr) {
        // TRANSPOSED all-pole (DF-IIt pole half) : y = X + s1' ;
        // si = ci*y + s(i+1)' ; sk = ck*y. The states are 1-delay
        // scalars updated in order (each reads the OLD next state) ; the
        // kernel never reads its own history -- its occurrences case
        // declared no self reads under this flag. External delayed
        // readers of the node still go through generateDelayVec below.
        std::vector<std::string> sname(order);
        for (int i2 = 0; i2 < order; i2++) {
            std::string dummy;
            getTypedNames(ty, "St", dummy, sname[i2]);
            fClass->addDeclCode(subst("$0 \t$1State; // IIRt state", ctype, sname[i2]));
            fClass->addClearCode(subst("$0State = 0;", sname[i2]));
            fClass->addZone2(subst("$0 \t$1;", ctype, sname[i2]));
            fClass->addZone3(subst("$0 = $0State;", sname[i2]));
            fClass->addZone3Post(subst("$0State = $0;", sname[i2]));
        }
        std::string y = subst("($0 + $1)", coefCode(coefs[1]), sname[0]);
        // no external delayed reader -> plain sample variable (the self
        // reads that sized the direct form's line are gone by design)
        std::string ycached =
            (o->getMaxDelay() > 0)
                ? generateDelayVec(sig, y, ctype, vname, o->getMaxDelay(), o->getDelayCount())
                : generateVariableStore(sig, y);
        for (int i2 = 0; i2 < order; i2++) {
            Tree        c    = coefs[3 + i2];
            std::string prod = isZero(c)      ? std::string("0")
                               : isOne(c)     ? ycached
                                              : subst("($0) * $1", CS(c), ycached);
            std::string ccs = getConditionCode(sig);
            if (i2 < order - 1) {
                fClass->addExecCode(
                    Statement(ccs, subst("$0 = $1 + $2; /* IIRt */", sname[i2], prod, sname[i2 + 1])));
            } else {
                fClass->addExecCode(Statement(ccs, subst("$0 = $1; /* IIRt */", sname[i2], prod)));
            }
        }
        return ycached;
    }

    std::ostringstream oss;
    oss << coefCode(coefs[1]);
    for (unsigned int i = coefs.size() - 1; i >= 3; i--) {
        if (isZero(coefs[i])) {
            continue;
        }
        string access = generateDelayAccessRaw(sig, sig, int(i) - 2);
        if (isOne(coefs[i])) {
            oss << " + " << access;
        } else {
            oss << " + (" << coefCode(coefs[i]) << ") * " << access;
        }
    }
    return generateDelayVec(sig, oss.str(), ctype, vname, o->getMaxDelay(), o->getDelayCount());
}

string ScalarCompiler::generateSum(Tree sig, const tvec& subs)
{
    faustassert(subs.size() > 1);
    if (gGlobal->gFamilyForm) {
        bool              ok   = false;
        const std::string code = generateFamilySum(sig, subs, ok);
        if (ok) {
            return code;
        }
    }
    // INT sums wrap through the faust_wrap_add helper, like every Int32
    // add/sub/mul of this emitter : a flat signed chain is UB on overflow,
    // and clang -O3 reassociates it under the no-overflow assumption --
    // false for anything that lives off the wrap (the LCG noise family :
    // bit-exact under -fwrapv, garbage without).
    const bool wrapInt = (getCertifiedSigType(sig)->nature() == kInt);
    ostringstream oss;
    string        sep   = "";
    int           terms = 0;
    oss << '(';
    if (!wrapInt) {
        // negative-weight terms (mul(-1, x)) render as subtractions after
        // the positive ones -- the reveal spells a - b as a + (-1)*b, and
        // emitting the multiply costs a real op per sample. The unsigned
        // int path keeps its uniform spelling (the LCG wrap families).
        std::vector<Tree> pos, neg;
        for (Tree t : subs) {
            if (isZero(t)) {
                continue;
            }
            Tree a, b;
            tvec fc;
            if (isSigMul(t, a, b) && isMinusOne(a)) {
                neg.push_back(b);
            } else if (isSigMul(t, a, b) && isMinusOne(b)) {
                neg.push_back(a);
            } else if (isSigFIR(t, fc) && fc.size() == 2 && isMinusOne(fc[1])) {
                // the reveal spells -x as a gain kernel FIR[x, -1]
                neg.push_back(fc[0]);
            } else {
                pos.push_back(t);
            }
        }
        if (!pos.empty()) {
            for (Tree t : pos) {
                oss << sep << CS(t);
                terms++;
                sep = " + ";
            }
            for (Tree t : neg) {
                oss << " - " << CS(t);
                terms++;
            }
            oss << " /* Sum */)";
            return generateCacheCode(sig, oss.str());
        }
    }
    if (wrapInt) {
        // pairwise faust_wrap_add chain, left-associated like the real
        // case (mod-2^32 addition is associative : any order agrees)
        std::string acc;
        for (Tree t : subs) {
            if (isZero(t)) {
                continue;
            }
            acc = acc.empty() ? CS(t) : subst("faust_wrap_add($0, $1)", acc, CS(t));
            terms++;
        }
        oss << (terms == 0 ? std::string("0") : acc) << " /* Sum */)";
        return generateCacheCode(sig, oss.str());
    }
    for (unsigned int i = 0; i < subs.size(); ++i) {
        if (!isZero(subs[i])) {
            oss << sep << CS(subs[i]);
            terms++;
            sep = " + ";
        }
    }
    if (terms == 0) {
        oss << "0";
    }
    oss << " /* Sum */)";
    return generateCacheCode(sig, oss.str());
}

//----------------------------------------------------------------------
// The family form, step 2 : emission (-fam, LA-FORME-FAMILLE)
//----------------------------------------------------------------------
//
// The strict isomorphism of emission : a slow or constant subtree on both sides is
// ALWAYS a coefficient slot (even when both sides are the same node : the slots of
// every member then line up whatever coincidences the coefficients have), an
// audio-rate subtree that is the same node on both sides is a common input, and the
// rest -- operators, own recursions -- is private to the member.
namespace {
// slow : computed per block or once, not per sample. Typed, the certified
// variability ; untyped (before prepare), the order -- with the caveat that
// the generator's init-time recursions poison the kind bits (factorizeFIRs,
// isSlowFactor), so a table read whose index is slow IS slow
static bool famSlow(Tree t)
{
    if (AudioType* ty = (AudioType*)t->getType(); ty != nullptr) {
        return ty->variability() < kSamp;
    }
    Tree tb, ri;
    return sigs::sigOrder(t) <= 2 || (isSigRDTbl(t, tb, ri) && sigs::sigOrder(ri) <= 2);
}

struct FamShapes;
struct FamIso2 {
    std::map<Tree, Tree>                  bind;
    std::map<Tree, Tree>                  leafBind;  // a slot leaf of the template -> the member's leaf at that slot
    std::map<std::pair<Tree, Tree>, bool> memo;
    std::vector<Tree>                     slotA, slotB;
    std::vector<Tree>                     aslotA, aslotB;  // audio slots : an input, or a hole, on both sides
    std::set<Tree>                        commonA, privA, privB;
    const std::set<Tree>*                 holes = nullptr;  // the rare closed subtrees, computed outside the loop
    Tree                                  topA = nullptr, topB = nullptr;  // the members themselves : never holes

    bool iso(Tree a, Tree b)
    {
        auto key = std::make_pair(a, b);
        if (auto it = memo.find(key); it != memo.end()) {
            return it->second;
        }
        memo[key] = true;
        bool r    = walk(a, b);
        memo[key] = r;
        return r;
    }

   public:
    bool collided = false;  // the walk failed on a shared leaf, not on the shape : another template may do

   private:
    static bool slow(Tree t) { return famSlow(t); }
    // A slot is a leaf of the template, and the loop reads the member's value
    // by that leaf : a leaf the template shares between two positions (two
    // coefficients that happen to be equal in the first member) must be
    // shared the same way by the member, or its two columns would read one
    // table (the collision of META-ANALYSE 12.2). The member may share more.
    bool bindLeaf(Tree a, Tree b)
    {
        auto it = leafBind.find(a);
        if (it != leafBind.end()) {
            collided = collided || it->second != b;
            return it->second == b;
        }
        leafBind[a] = b;
        return true;
    }
    bool walk(Tree a, Tree b)
    {
        bool sa = slow(a), sb = slow(b);
        if (sa && sb) {
            if (!bindLeaf(a, b)) {
                return false;
            }
            slotA.push_back(a);
            slotB.push_back(b);
            return true;
        }
        int        ka, kb;
        const bool ha = isSigInput(a, &ka) || (holes && a != topA && holes->count(a));
        const bool hb = isSigInput(b, &kb) || (holes && b != topB && holes->count(b));
        if (ha && hb) {
            if (!bindLeaf(a, b)) {
                return false;
            }
            aslotA.push_back(a);  // an audio slot, even when both read the same node :
            aslotB.push_back(b);  // the slots of every member then line up (uniform = a common)
            return true;
        }
        if (a == b) {
            commonA.insert(a);
            return true;
        }
        if (sa != sb) {
            return false;
        }
        Tree ia, ba, ib, bb;
        if (isRec(a, ia, ba) && isRec(b, ib, bb)) {
            if (auto it = bind.find(ia); it != bind.end()) {
                return it->second == ib;
            }
            bind[ia] = ib;
            privA.insert(a);
            privB.insert(b);
            return iso(ba, bb);
        }
        if (isRef(a, ia) && isRef(b, ib)) {
            auto it = bind.find(ia);
            privA.insert(a);
            privB.insert(b);
            return it != bind.end() && it->second == ib;
        }
        if (!(a->node() == b->node()) || a->arity() != b->arity()) {
            return false;
        }
        privA.insert(a);
        privB.insert(b);
        if (shapes && isSigSum(a)) {
            // the operands paired in a structural order (shape, lowest
            // projection index read, serial), not positionally : the revealer
            // lists them in the order of their creation, which differs from cell
            // to cell once the products are shared
            const std::vector<Tree> oa = ordered(a), ob = ordered(b);
            for (size_t k = 0; k < oa.size(); k++) {
                if (!iso(oa[k], ob[k])) {
                    return false;
                }
            }
            return true;
        }
        for (int k = 0; k < a->arity(); k++) {
            if (!iso(a->branch(k), b->branch(k))) {
                return false;
            }
        }
        return true;
    }

   public:
    FamShapes*        shapes = nullptr;  // the shapes, for the structural order of a sum's operands
    std::vector<Tree> ordered(Tree sum);
    std::map<Tree, int> projMemo;
    int                 lowestProj(Tree t)
    {
        if (auto it = projMemo.find(t); it != projMemo.end()) {
            return it->second;
        }
        int  r = INT_MAX, i;
        Tree g, id, body;
        if (isProj(t, &i, g)) {
            r = i;
        } else if (!isRec(t, id, body)) {
            for (int k = 0; k < t->arity(); k++) {
                r = std::min(r, lowestProj(t->branch(k)));
            }
        }
        return projMemo[t] = r;
    }
};
}  // namespace

// The abstract shape of a signal (LA-FORME-FAMILLE) : a hash-consed tree
// computed bottom-up, the
// same operators and arities with the children replaced by their shapes,
// and three kinds of holes where the members of a family may differ -- a
// slow or constant subtree (a coefficient slot), an audio input (an audio
// slot), and a recursive reference, labelled by its binding depth and its
// projection (the member's own output, read delayed : a state). The integer
// literals stay structural (a projection index, a delay), and a recursive
// group is its body's shape. Two nodes are of the same shape iff their
// shapes are the same tree.
namespace {
// A shape is an INTERNED key (an int), never a tree : building shapes as
// hash-consed trees consumed serials, and the serial is the scheduler's
// tie-break -- the analysis alone reordered the emitted code of fdnRev
// under -fam -lsum (x1.95 under clang 22 for the same computation).
using Shape = int;
struct FamShapes {
    std::map<std::string, Shape>     intern;  // key -> id
    std::vector<std::string>         keys;    // id -> key
    std::vector<int>                 sizes;   // id -> nodes of the shape
    std::vector<std::string>         ops;     // id -> the operator (for the trace)
    std::vector<std::vector<Shape>>  kids;    // id -> the children (for the trace)
    Shape                            SLOW, AUDIO;
    std::map<Tree, Shape>            memo;   // closed subtrees only
    std::vector<Tree>                stack;  // the enclosing groups (their identifiers), innermost last
    FamShapes()
    {
        SLOW  = make("SLOW", 1, "", {});
        AUDIO = make("AUDIO", 1, "", {});
    }
    Shape make(const std::string& key, int size, const std::string& op, const std::vector<Shape>& br)
    {
        if (auto it = intern.find(key); it != intern.end()) {
            return it->second;
        }
        keys.push_back(key);
        sizes.push_back(size);
        ops.push_back(op);
        kids.push_back(br);
        return intern[key] = (Shape)keys.size() - 1;
    }
    int size(Shape s) const { return sizes[s]; }
    // a readable form, bounded : a shape is a dag, its full expansion is not
    std::string print(Shape s, int budget = 100) const
    {
        if (s == SLOW || s == AUDIO) {
            return "";
        }
        std::string r = ops[s];
        if (kids[s].empty() || budget <= 0) {
            return kids[s].empty() ? r : r + "(...)";
        }
        r += "(";
        std::string sep;
        for (Shape b : kids[s]) {
            r += sep + print(b, budget / (int)kids[s].size() - 1);
            sep = ",";
            if ((int)r.size() > budget) {
                return r + "...";
            }
        }
        return r + ")";
    }
    // the boundary (the occurrence rule) : a closed audio subtree whose shape
    // is rare, fewer occurrences than a family needs, is computed outside
    // the loops of its parents, which see it as an audio input. The node
    // keeps its own shape : it may still head a family of its own.
    std::set<Tree> holes;

    static bool slow(Tree t) { return famSlow(t); }
    // A recursive group and its reference are the SAME node (the body is a
    // property) : met inside its own body, the node is a reference. The
    // groups a subtree names (its projections, bodies not entered) are
    // structural ; a subtree naming an enclosing group is open here, its
    // shape depends on the context and is not memoized.
    std::map<Tree, std::set<Tree>> refs;
    const std::set<Tree>& groupsOf(Tree t)
    {
        if (auto it = refs.find(t); it != refs.end()) {
            return it->second;
        }
        std::set<Tree> r;
        Tree           id, body;
        if (isRec(t, id, body)) {
            r.insert(id);
        } else {
            for (int k = 0; k < t->arity(); k++) {
                const std::set<Tree>& c = groupsOf(t->branch(k));
                r.insert(c.begin(), c.end());
            }
        }
        return refs[t] = r;
    }
    bool openHere(Tree t)
    {
        for (Tree id : stack) {
            if (groupsOf(t).count(id)) {
                return true;
            }
        }
        return false;
    }
    Shape shapeOf(Tree t)
    {
        const bool closed = !openHere(t);
        if (closed) {
            if (auto it = memo.find(t); it != memo.end()) {
                return it->second;
            }
        }
        Shape r = compute(t);
        if (closed) {
            memo[t] = r;
        }
        return r;
    }
    Shape compute(Tree t)
    {
        int  i, d;
        Tree id, body, x, y;
        if (isSigInt(t, &i)) {
            return make("I" + std::to_string(i), 1, std::to_string(i), {});  // an integer literal is structural
        }
        if (isRec(t, id, body)) {
            int level = 0;
            for (auto it = stack.rbegin(); it != stack.rend(); ++it, level++) {
                if (*it == id) {
                    return make("REF" + std::to_string(level), 1, "REF" + std::to_string(level), {});  // an enclosing group
                }
            }
            if (!body) {
                return make("REF-1", 1, "REF-1", {});
            }
            stack.push_back(id);
            Shape b = shapeOf(body);
            stack.pop_back();
            return make("REC(" + std::to_string(b) + ")", 1 + size(b), "REC", {b});
        }
        if (slow(t)) {
            return SLOW;
        }
        if (isSigInput(t, &i)) {
            return AUDIO;
        }
        if (isSigDelay(t, x, y) && isZero(y)) {
            return holes.count(x) ? AUDIO : shapeOf(x);  // a delay of zero is its signal
        }
        std::vector<Shape> br;
        for (int k = 0; k < t->arity(); k++) {
            Tree c = t->branch(k);
            br.push_back(holes.count(c) ? AUDIO : shapeOf(c));  // a hole is opaque to its parent only
        }
        if (isSigSum(t)) {
            // a sum's operands in a structural order : two cells whose products
            // were created in different orders have the same shape (the
            // isomorphism walk pairs the operands the same way)
            std::sort(br.begin(), br.end());
        }
        std::ostringstream key, opss;
        opss << t->node();
        const std::string op = opss.str();
        key << op << "#" << t->arity();
        int sz = 1;
        for (Shape b : br) {
            key << "," << b;
            sz += size(b);
        }
        return make(key.str(), sz, op, br);
    }
};

std::vector<Tree> FamIso2::ordered(Tree sum)
{
    tvec ops;
    isSigSum(sum, ops);
    std::vector<std::tuple<int, int, int, Tree>> keyed;
    for (Tree o : ops) {
        keyed.push_back({shapes->shapeOf(o), lowestProj(o), o->serial(), o});
    }
    std::sort(keyed.begin(), keyed.end(), [](const auto& x, const auto& y) {
        return std::tie(std::get<0>(x), std::get<1>(x), std::get<2>(x)) < std::tie(std::get<0>(y), std::get<1>(y), std::get<2>(y));
    });
    std::vector<Tree> r;
    for (auto& k : keyed) {
        r.push_back(std::get<3>(k));
    }
    return r;
}

// every audio node reachable from the root, with its shape ; the classes are
// the shapes shared by several nodes
struct FamClasses {
    std::map<Shape, std::vector<Tree>> members;  // shape -> nodes, in serial order
    std::map<Tree, Shape>              shapeOfNode;
    // The occurrence rule, from the leaves up. A node whose shape has fewer
    // than 4 occurrences and whose children are all settled -- a leaf, a
    // hole, or a node of 4 occurrences or more whose own subtree is settled
    // -- is a hole : its parents see an audio input, their shapes coarsen,
    // and the count is redone until no hole is added. The holes grow from
    // the bottom through the rare regions (an oscillator feeding the bands,
    // an excitation, a source), so a chain rare only because of a rare
    // subtree is a member once that subtree is a hole. Inside a recursive
    // group the nodes are open (they name the group) : the group is settled
    // when every closed node under its body is, a reference to the group
    // itself being a leaf. One layer of holes per round, on the holes of the
    // previous round : a node made a hole coarsens its parent, whose count
    // must be redone before it is judged. Monotone, hence finite.
    void collectWithHoles(Tree root, FamShapes& S, bool trace)
    {
        for (int round = 0; round < 256; round++) {
            members.clear();
            shapeOfNode.clear();
            S.memo.clear();
            collect(root, S);
            std::map<Tree, bool> settled;
            std::set<Tree>       fresh;
            for (auto& kv : shapeOfNode) {
                int k;
                if (members[kv.second].size() < 4 && !isSigInput(kv.first, &k) && !S.holes.count(kv.first)) {
                    std::set<Tree> active;
                    if (childrenSettled(kv.first, S, settled, active)) {
                        fresh.insert(kv.first);
                    }
                }
            }
            if (trace) {
                int big = 0;
                for (auto& kv : members) {
                    big += kv.second.size() >= 4;
                }
                std::cerr << "fam shapes round " << round << " : " << shapeOfNode.size() << " audio nodes, " << members.size() << " shapes, "
                          << big << " classes of 4 or more, " << fresh.size() << " holes added (" << S.holes.size() + fresh.size() << ")"
                          << std::endl;
            }
            if (fresh.empty()) {
                break;
            }
            S.holes.insert(fresh.begin(), fresh.end());
        }
    }
    bool rare(Tree t)
    {
        auto it = shapeOfNode.find(t);
        return it != shapeOfNode.end() && members[it->second].size() < 4;
    }
    // settled : a leaf (a literal, a slow signal, an input), a hole, a node
    // of 4 occurrences or more whose children are settled, or a recursive
    // group whose body is settled
    bool isSettled(Tree c, FamShapes& S, std::map<Tree, bool>& memo, std::set<Tree>& active)
    {
        int  i;
        Tree id, body;
        if (isSigInt(c, &i) || FamShapes::slow(c) || isSigInput(c, &i) || S.holes.count(c)) {
            return true;
        }
        if (isRec(c, id, body)) {
            if (!body || active.count(id)) {
                return true;  // a self-reference is a leaf
            }
            active.insert(id);
            bool r = childrenSettled(body, S, memo, active);  // the group : what its body reads
            active.erase(id);
            return r;
        }
        bool inside = false;  // naming an active group : part of it, transparent
        for (Tree g : active) {
            inside = inside || S.groupsOf(c).count(g);
        }
        if (inside) {
            return childrenSettled(c, S, memo, active);
        }
        if (auto it = memo.find(c); it != memo.end()) {
            return it->second;
        }
        bool r  = !rare(c) && childrenSettled(c, S, memo, active);  // a regular node over settled children
        memo[c] = r;
        return r;
    }
    bool childrenSettled(Tree n, FamShapes& S, std::map<Tree, bool>& memo, std::set<Tree>& active)
    {
        Tree id, body;
        if (isRec(n, id, body)) {
            return isSettled(n, S, memo, active);
        }
        for (int b = 0; b < n->arity(); b++) {
            if (!isSettled(n->branch(b), S, memo, active)) {
                return false;
            }
        }
        return true;
    }
    void collect(Tree root, FamShapes& S)
    {
        std::set<Tree>    seen;
        std::vector<Tree> st{root};
        while (!st.empty()) {
            Tree t = st.back();
            st.pop_back();
            if (!seen.insert(t).second) {
                continue;
            }
            Tree id, body;
            if (isRec(t, id, body) && body) {
                st.push_back(body);
                continue;
            }
            if (!isList(t) && !FamShapes::slow(t)) {
                Shape sh         = S.shapeOf(t);
                shapeOfNode[t]   = sh;
                members[sh].push_back(t);
            }
            for (int k = 0; k < t->arity(); k++) {
                st.push_back(t->branch(k));
            }
        }
        for (auto& kv : members) {
            std::sort(kv.second.begin(), kv.second.end(), [](Tree a, Tree b) { return a->serial() < b->serial(); });
        }
    }
};
}  // namespace

static void traceFamShapes(Tree root)
{
    FamShapes  S;
    FamClasses C;
    C.collectWithHoles(root, S, true);
    std::vector<std::pair<Shape, std::vector<Tree>>> all(C.members.begin(), C.members.end());
    std::sort(all.begin(), all.end(), [&S](const auto& a, const auto& b) {
        return a.second.size() != b.second.size() ? a.second.size() > b.second.size() : S.size(a.first) > S.size(b.first);
    });
    std::cerr << "fam shapes : " << C.shapeOfNode.size() << " audio nodes, " << C.members.size() << " shapes, " << S.holes.size() << " holes"
              << std::endl;
    int shown = 0;
    for (auto& kv : all) {
        if (shown++ >= 40) {
            break;
        }
        std::cerr << "   " << kv.second.size() << " x shape of " << S.size(kv.first) << " nodes : " << S.print(kv.first)
                  << "\n      e.g. " << ppsig(kv.second[0], 100) << std::endl;
    }
}

struct ScalarCompiler::FamCtx {
    int                                        id = 0, P = 0, locals = 0;
    // the automaton (LES-AUTOMATES) : the group, the members' first definition
    // index, and per audio slot the offset of the projection read (INT_MIN : a table)
    Tree                                       autoGroup = nullptr;
    int                                        autoDef0  = 0;
    std::vector<int>                           autoBase;
    std::set<int>                              autoTables;
    std::set<int>                              autoBefore;  // the definitions computed before the loop (readable at the current step)
    std::set<int>                              preSlots;    // audio slots that are delayed reads : captured at the top of the sample
    std::set<int>                              usedPreSlots;
    std::string                                ty;  // the real type of the members
    const FamPlan*                             plan = nullptr;
    // -fam -fir : the slow subtrees the kernel passes wrote into the template
    // (a coefficient that is a product of two slots) : computed once per
    // block outside the loop, a table when a slot inside differs between
    // members, a scalar otherwise (famSlowCode)
    std::vector<std::pair<Tree, bool>>         derived;
    std::map<Tree, std::string>                derivedName;
    const std::unordered_map<Tree, Tree>*      thaw = nullptr;  // -fam -fir : the kernelized template's opaque leaves -> the slot leaves and commons
    Tree                                       th(Tree t) const
    {
        if (thaw) {
            if (auto it = thaw->find(t); it != thaw->end()) {
                return it->second;
            }
        }
        return t;
    }
    std::map<Tree, int>                        slotIndex;  // template leaf -> slot
    std::vector<bool>                          uniform;    // the slot is the same tree in every member
    std::set<int>                              usedSlots;
    std::map<Tree, int>                        aslotIndex;  // template leaf -> audio slot
    std::vector<bool>                          auniform;    // the same tree in every member : a common
    std::vector<bool>                          ahostUniform;  // the same tree within every host's members : a scalar per host loop
    std::set<int>                              usedHostASlots;
    std::set<int>                              usedASlots;
    std::set<Tree>                             commons;
    std::map<Tree, int>                        uses;  // parents inside the template
    std::map<Tree, std::string>                val;
    std::vector<std::string>                   body;
    std::map<Tree, int>                        groupState;  // 1 computing, 2 done
    std::map<std::pair<Tree, int>, std::string> projVal;
    std::map<std::string, int>                 need;        // state -> deepest history read
    std::map<std::string, std::string>         stateValue;  // state -> its current value
    std::vector<std::string>                   stateOrder;
    std::map<Tree, int>                        sid;
    bool                                       failed = false;
    std::string                                reason;

    std::string local() { return subst("fFam$0L$1", T(id), T(locals++)); }
    std::string stateKey(Tree node, int j)
    {
        auto it = sid.find(node);
        int  n  = (it == sid.end()) ? (sid[node] = (int)sid.size()) : it->second;
        return subst("fFam$0S$1_$2", T(id), T(n), T(j));
    }
    void fail(const std::string& why)
    {
        if (!failed) {
            failed = true;
            reason = why;
        }
    }
};

// hosts : the sums the members feed ; outputs : the members may also be
// output channels, whose parents are the cells of the output list
bool ScalarCompiler::famPrivateOnly(const std::set<Tree>& priv, const std::set<Tree>& hosts, bool outputs, Tree group)
{
    if (!fFamParentsBuilt) {
        fFamParentsBuilt = true;
        fFamDefCell.clear();
        std::set<Tree>    seen;
        std::vector<Tree> st;
        if (fFamRoot) {
            st.push_back(fFamRoot);
        }
        while (!st.empty()) {
            Tree t = st.back();
            st.pop_back();
            if (!seen.insert(t).second) {
                continue;
            }
            Tree id, body;
            if (isRec(t, id, body) && body) {
                fFamParents[body].insert(t);
                int k = 0;
                for (Tree l = body; isList(l); l = tl(l), k++) {
                    fFamDefCell[l] = {t, k};  // the cells of the definition list belong to the group
                }
                st.push_back(body);
                continue;
            }
            for (int k = 0; k < t->arity(); k++) {
                fFamParents[t->branch(k)].insert(t);
                st.push_back(t->branch(k));
            }
        }
    }
    // a private node read from outside its member : refused, unless it holds
    // no state (no recursive group, no kernel, no projection of another
    // group) -- the reader then recomputes it, the group's own projections
    // having their expressions in the family's arrays (the automaton's
    // borders share their neighbours' products with the cells)
    auto stateless = [&](Tree n) {
        std::set<Tree>    seen;
        std::vector<Tree> st{n};
        while (!st.empty()) {
            Tree t = st.back();
            st.pop_back();
            if (!seen.insert(t).second || !priv.count(t)) {
                continue;
            }
            Tree id, body, x, y, g;
            int  i;
            tvec V;
            if (isRec(t, id, body) || isSigIIR(t, V) || isSigFIR(t, V) || (isProj(t, &i, x) && x != group)) {
                return false;
            }
            if (isSigDelay(t, x, y) && !(isProj(x, &i, g) && g == group)) {
                return false;  // a delay line the family never emits
            }
            for (int k = 0; k < t->arity(); k++) {
                st.push_back(t->branch(k));
            }
        }
        return true;
    };
    for (Tree n : priv) {
        auto it = fFamParents.find(n);
        if (it == fFamParents.end()) {
            continue;
        }
        for (Tree p : it->second) {
            if (!hosts.count(p) && !priv.count(p) && !(outputs && isList(p)) && !(group && stateless(n))) {
                return false;  // a private node read from outside its member
            }
        }
    }
    return true;
}

std::string ScalarCompiler::famHist(FamCtx& g, Tree x, int k)
{
    if (g.failed) {
        return "0";
    }
    x = g.th(x);
    if (k == 0) {
        return famExpr(g, x);
    }
    Tree x2, y;
    int  d;
    if (isSigDelay(x, x2, y) && isSigInt(y, &d)) {
        return famHist(g, x2, k + d);
    }
    tvec V;
    if (isSigIIR(x, V)) {
        famExpr(g, x);  // the state must be updated this iteration
        const std::string key = g.stateKey(x, 0);
        g.need[key]           = std::max(g.need[key], k);
        return subst("$0_$1[c]", key, T(k));
    }
    int  i;
    Tree grp;
    if (isProj(x, i, grp) && g.autoGroup && grp == g.autoGroup) {
        // the automaton : the neighbourhood, read in the group's state arrays at
        // the previous generations -- S_k[c + base] (affine) or through a table
        auto it = g.aslotIndex.find(x);
        if (it == g.aslotIndex.end()) {
            g.fail("a projection of the automaton's group that is not an audio slot");
            return "0";
        }
        const int base = g.autoBase[it->second];
        if (base == INT_MIN) {
            g.autoTables.insert(it->second);
            return subst("fFam$0S_$1[fFam$0Idx$2[c]]", T(g.id), T(k), T(it->second));
        }
        return subst("fFam$0S_$1[c + o$2]", T(g.id), T(k), base == 0 ? std::string() : (base > 0 ? " + " + T(base) : " - " + T(-base)));
    }
    if (isProj(x, i, grp)) {
        // in tlib a symbolic recursive group IS its reference ref(W), carrying its
        // definitions as a property : the same node inside and outside the group
        Tree W, defs;
        if (!isRec(grp, W, defs)) {
            g.fail("projection of a non recursive group");
            return "0";
        }
        if (g.groupState[grp] == 0) {
            famExpr(g, x);
        }
        const std::string key = g.stateKey(grp, i);
        g.need[key]           = std::max(g.need[key], k);
        return subst("$0_$1[c]", key, T(k));
    }
    g.fail("history of a node that is not a state");
    return "0";
}

// The code of a slow subtree of the kernelized template for member m : the
// placeholders are the member's own slot values (or the commons), the rest
// is spelled from the structure. ok is cleared on a node it cannot spell.
std::string ScalarCompiler::famSlowCode(FamCtx& g, Tree t, int m, bool& ok, bool& perMember)
{
    Tree u = g.th(t);
    if (u != t || g.slotIndex.count(u) || g.commons.count(u)) {
        // a leaf of the template
        if (auto it = g.slotIndex.find(u); it != g.slotIndex.end()) {
            if (!g.uniform[it->second]) {
                perMember = true;
            }
            return famCoef(g.plan->slots[m][it->second]);
        }
        if (g.commons.count(u)) {
            return famCoef(u);
        }
        ok = false;
        return "0";
    }
    int    i;
    double r;
    if (isSigInt(t, &i)) {
        return T(i);
    }
    if (isSigReal(t, &r)) {
        return realLiteral(r);
    }
    int  op;
    Tree a, b, x;
    if (isSigBinOp(t, &op, a, b)) {
        std::string ca = famSlowCode(g, a, m, ok, perMember);
        std::string cb = famSlowCode(g, b, m, ok, perMember);
        return subst("($0 $1 $2)", ca, gBinOpTable[op]->fName, cb);
    }
    if (isSigIntCast(t, x)) {
        return subst("int($0)", famSlowCode(g, x, m, ok, perMember));
    }
    if (isSigFloatCast(t, x)) {
        return subst("$0($1)", ifloat(), famSlowCode(g, x, m, ok, perMember));
    }
    if (getUserData(t) != nullptr && t->arity() > 0) {
        xtendedCodegen*          p = static_cast<xtendedCodegen*>((xtended*)getUserData(t));
        std::vector<std::string> args;
        std::vector<Type>        types;
        for (int k = 0; k < t->arity(); k++) {
            args.push_back(famSlowCode(g, t->branch(k), m, ok, perMember));
            types.push_back(getCertifiedSigType(t->branch(k)));
        }
        return p->generateCode(fClass, args, types);
    }
    ok = false;
    return "0";
}

std::string ScalarCompiler::famExpr(FamCtx& g, Tree t)
{
    if (g.failed) {
        return "0";
    }
    if (g.thaw && !g.thaw->count(t) && t->arity() > 0 && getSigType(t) && getCertifiedSigType(t)->variability() < kSamp) {
        // a slow subtree the kernel passes wrote into the template : once per
        // block, outside the loop, if it can be spelled per member
        if (auto it = g.derivedName.find(t); it != g.derivedName.end()) {
            return it->second;
        }
        bool        ok = true, perMember = false;
        std::string probe = famSlowCode(g, t, 0, ok, perMember);
        if (ok) {
            const int   n    = (int)g.derived.size();
            std::string name = perMember ? subst("fFam$0D$1[c]", T(g.id), T(n)) : subst("fFam$0D$1", T(g.id), T(n));
            g.derived.push_back({t, perMember});
            g.derivedName[t] = name;
            return g.val[t] = name;
        }
    }
    t = g.th(t);  // an opaque leaf of the kernelized template is its slot leaf or common
    if (auto it = g.val.find(t); it != g.val.end()) {
        return it->second;
    }
    auto keep = [&](const std::string& e) {
        if (g.uses[t] > 1) {
            const std::string l = g.local();
            g.body.push_back(subst("$0 $1 = $2;", (getCertifiedSigType(t)->nature() == kInt) ? "int" : g.ty, l, e));
            return g.val[t] = l;
        }
        return g.val[t] = e;
    };
    if (auto it = g.slotIndex.find(t); it != g.slotIndex.end()) {
        if (g.uniform[it->second]) {
            return g.val[t] = famCoef(t);
        }
        g.usedSlots.insert(it->second);
        return g.val[t] = subst("fFam$0T$1[c]", T(g.id), T(it->second));
    }
    if (g.commons.count(t)) {
        return g.val[t] = famCS(t);  // what the family reads from outside is the tree's node
    }
    if (auto it = g.aslotIndex.find(t); it != g.aslotIndex.end()) {
        if (g.autoGroup) {
            int  pi;
            Tree pg;
            if (isProj(t, &pi, pg) && pg == g.autoGroup && g.autoBase[it->second] != INT_MAX) {
                // a neighbour read at the current step : refused at plan time
                // unless every member reads a definition outside the family --
                // that definition is computed before the loop, its New cell
                // is read like any common or input (the slot's code below)
                if (!g.autoBefore.count(pi)) {
                    g.fail("a cell reads a projection of its group at the current step");
                    return "0";
                }
            }
        }
        if (g.auniform[it->second]) {
            return g.val[t] = famCS(t);  // every member reads the same input : a common
        }
        if (g.preSlots.count(it->second)) {
            g.usedPreSlots.insert(it->second);  // captured at the top of the sample, before any write
            return g.val[t] = subst("fFam$0Pre$1[c]", T(g.id), T(it->second));
        }
        if (it->second < (int)g.ahostUniform.size() && g.ahostUniform[it->second]) {
            g.usedHostASlots.insert(it->second);  // the same input within each host : a scalar set before each host loop
            return g.val[t] = subst("fFam$0In$1v", T(g.id), T(it->second));
        }
        g.usedASlots.insert(it->second);
        return g.val[t] = subst("fFam$0In$1[c]", T(g.id), T(it->second));
    }
    tvec V;
    if (isSigIIR(t, V)) {
        std::ostringstream oss;
        oss << "(" << famExpr(g, V[1]);
        for (size_t i = 3; i < V.size(); i++) {
            auto sl = g.slotIndex.find(V[i]);
            if (sl != g.slotIndex.end() && g.uniform[sl->second] && isZero(V[i])) {
                continue;
            }
            const std::string key = g.stateKey(t, 0);
            int               k   = int(i) - 2;
            g.need[key]           = std::max(g.need[key], k);
            oss << " + " << famExpr(g, V[i]) << " * " << subst("$0_$1[c]", key, T(k));
        }
        oss << ")";
        const std::string l = g.local();
        g.body.push_back(subst("$0 $1 = $2;", g.ty, l, oss.str()));
        g.stateValue[g.stateKey(t, 0)] = l;
        return g.val[t] = l;
    }
    if (isSigFIR(t, V)) {
        std::ostringstream oss;
        std::string        sep;
        oss << "(";
        for (size_t i = 1; i < V.size(); i++) {
            auto sl      = g.slotIndex.find(V[i]);
            bool uniform = (sl != g.slotIndex.end() && g.uniform[sl->second]);
            if (uniform && isZero(V[i])) {
                continue;
            }
            const std::string h = famHist(g, V[0], int(i) - 1);
            if (uniform && isOne(V[i])) {
                oss << sep << h;
            } else {
                oss << sep << famExpr(g, V[i]) << " * " << h;
            }
            sep = " + ";
        }
        if (sep.empty()) {
            oss << "0";
        }
        oss << ")";
        return keep(oss.str());
    }
    Tree x, y;
    int  d;
    if (isSigDelay(t, x, y)) {
        if (!isSigInt(y, &d)) {
            g.fail("variable delay inside a member");
            return "0";
        }
        return keep(famHist(g, x, d));
    }
    int  i;
    Tree grp;
    if (isProj(t, i, grp)) {
        Tree W, defs;
        if (!isRec(grp, W, defs)) {
            g.fail("projection of a non recursive group");
            return "0";
        }
        if (g.groupState[grp] == 1) {
            g.fail("instantaneous self reference");
            return "0";
        }
        if (g.groupState[grp] == 0) {
            g.groupState[grp]  = 1;
            int  j             = 0;
            for (Tree l = defs; isList(l); l = tl(l), j++) {
                if (getCertifiedSigType(hd(l))->nature() != kReal) {
                    g.fail("non real recursion");
                    return "0";
                }
                const std::string e  = famExpr(g, hd(l));
                const std::string lv = g.local();
                g.body.push_back(subst("$0 $1 = $2;", g.ty, lv, e));
                g.projVal[{grp, j}]              = lv;
                g.stateValue[g.stateKey(grp, j)] = lv;
            }
            g.groupState[grp] = 2;
        }
        auto it = g.projVal.find({grp, i});
        if (it == g.projVal.end()) {
            g.fail("projection out of its group");
            return "0";
        }
        return g.val[t] = it->second;
    }
    int    i2;
    double r2;
    if (isSigInt(t, &i2)) {
        return g.val[t] = T(i2);  // a literal the kernel passes wrote into the template (a coefficient, a sign)
    }
    if (isSigReal(t, &r2)) {
        return g.val[t] = realLiteral(r2);
    }
    int  op;
    Tree a, b;
    if (isSigBinOp(t, &op, a, b)) {
        if (getCertifiedSigType(t)->nature() == kInt && !isBoolOpcode(op)) {
            g.fail("integer arithmetic inside a member");
            return "0";
        }
        // famExpr names temporaries in its own order : one call per statement
        std::string ca = famExpr(g, a);
        std::string cb = famExpr(g, b);
        return keep(subst("($0 $1 $2)", ca, gBinOpTable[op]->fName, cb));
    }
    tvec subs;
    if (isSigSum(t, subs)) {
        if (getCertifiedSigType(t)->nature() != kReal) {
            g.fail("integer sum inside a member");
            return "0";
        }
        std::ostringstream oss;
        std::string        sep;
        oss << "(";
        for (Tree u : subs) {
            oss << sep << famExpr(g, u);
            sep = " + ";
        }
        oss << ")";
        return keep(oss.str());
    }
    Tree sel, s0, s1;
    if (isSigSelect2(t, sel, s0, s1)) {
        std::string csel = famExpr(g, sel);
        std::string c1   = famExpr(g, s1);
        std::string c0   = famExpr(g, s0);
        return keep(subst("(($0) ? $1 : $2)", csel, c1, c0));
    }
    if (getUserData(t) != nullptr && t->arity() > 0 && getCertifiedSigType(t)->nature() == kReal) {
        // a math primitive (abs, pow, log10, max...) : its own generator, on
        // the members' expressions
        xtendedCodegen*          p = static_cast<xtendedCodegen*>((xtended*)getUserData(t));
        std::vector<std::string> args;
        std::vector<Type>        types;
        for (int k = 0; k < t->arity(); k++) {
            args.push_back(famExpr(g, t->branch(k)));
            types.push_back(getCertifiedSigType(t->branch(k)));
        }
        return keep(p->generateCode(fClass, args, types));
    }
    if (isSigFloatCast(t, x)) {
        return keep(subst("$0($1)", ifloat(), famExpr(g, x)));
    }
    std::ostringstream what;
    what << "unsupported node " << *(t->node().getSym() ? (Tree)tree(t->node()) : t) << "/" << t->arity() << " : " << ppsig(t, 12);
    g.fail(what.str().substr(0, 300));
    return "0";
}

// what famExpr can generate, decided at planning time : a family is planned only if
// its template is generable, since its private nodes then leave the schedule and a
// refusal at generation time would compile them out of order
static bool famIsState(Tree x)
{
    Tree x2, y, W, defs;
    int  d, i;
    tvec V;
    if (isSigDelay(x, x2, y)) {
        return isSigInt(y, &d) && famIsState(x2);
    }
    return isSigIIR(x, V) || (isProj(x, i, x2) && isRec(x2, W, defs));
}

// typed : false before the typing, where every nature test passes (the plan
// then only tells which sums the lowering must keep)
static bool famCheck(Tree t, const std::set<Tree>& slots, const std::set<Tree>& commons, std::set<Tree>& seen, bool typed)
{
    if (slots.count(t) || commons.count(t) || !seen.insert(t).second) {
        return true;
    }
    auto real = [&](Tree u) { return !typed || getCertifiedSigType(u)->nature() == kReal; };
    tvec V;
    if (isSigIIR(t, V)) {
        for (size_t i = 1; i < V.size(); i++) {
            if (i != 2 && !famCheck(V[i], slots, commons, seen, typed)) {
                return false;
            }
        }
        return real(t);
    }
    if (isSigFIR(t, V)) {
        if (V.size() > 2 && !famIsState(V[0])) {
            return false;  // a history of a node that is not a state
        }
        for (size_t i = 0; i < V.size(); i++) {
            if (!famCheck(V[i], slots, commons, seen, typed)) {
                return false;
            }
        }
        return true;
    }
    Tree x, y, grp, W, defs;
    int  d, i;
    if (isSigDelay(t, x, y)) {
        return isSigInt(y, &d) && (d == 0 || famIsState(x)) && famCheck(x, slots, commons, seen, typed);
    }
    if (isProj(t, i, grp)) {
        if (!isRec(grp, W, defs)) {
            return false;
        }
        if (seen.count(grp)) {
            return true;
        }
        seen.insert(grp);
        for (Tree l = defs; isList(l); l = tl(l)) {
            if (!real(hd(l)) || !famCheck(hd(l), slots, commons, seen, typed)) {
                return false;
            }
        }
        return true;
    }
    int  op;
    Tree a, b;
    if (isSigBinOp(t, &op, a, b)) {
        return (real(t) || isBoolOpcode(op)) && famCheck(a, slots, commons, seen, typed) && famCheck(b, slots, commons, seen, typed);
    }
    if (isSigSum(t, V)) {
        if (!real(t)) {
            return false;
        }
        for (Tree u : V) {
            if (!famCheck(u, slots, commons, seen, typed)) {
                return false;
            }
        }
        return true;
    }
    Tree sel, s0, s1;
    if (isSigSelect2(t, sel, s0, s1)) {
        return famCheck(sel, slots, commons, seen, typed) && famCheck(s0, slots, commons, seen, typed) && famCheck(s1, slots, commons, seen, typed);
    }
    if (getUserData(t) != nullptr && t->arity() > 0) {
        if (!real(t)) {
            return false;  // a math primitive : real results only
        }
        for (int k = 0; k < t->arity(); k++) {
            if (!famCheck(t->branch(k), slots, commons, seen, typed)) {
                return false;
            }
        }
        return true;
    }
    if (isSigFloatCast(t, x)) {
        return famCheck(x, slots, commons, seen, typed);
    }
    return false;
}

// A shape class as a family : nodes of the same abstract shape, planned against
// the first one as the template (slots, audio slots, common inputs, private
// recursions), their hosts read in the graph -- the sums they feed, or the
// output list -- and the members grouped by host. typed : the tree carries its
// types (the ordinary call, after prepare) ; false before typing, where the
// plan only says which sums the lowering must keep n-ary.
bool ScalarCompiler::planFamilyClass(const std::vector<Tree>& nodes0, FamPlan& plan, bool typed, std::string& why, const std::set<Tree>* holes,
                                     void* shapesp)
{
    FamShapes* shapes = static_cast<FamShapes*>(shapesp);
    if (nodes0.size() < 4) {
        why = "fewer than 4 members";
        return false;
    }
    // ---- the hosts : one parent per member, a sum or the output list
    std::set<Tree> dummy;
    famPrivateOnly(dummy, dummy, false);  // builds the parent map
    std::map<Tree, int> hostIndex;
    std::vector<Tree>   hosts;
    std::vector<int>    memberHost;
    std::vector<int>    memberDef;  // the automaton : the definition index of each member
    Tree                group = nullptr;
    bool                outputs = false, sums = false;
    for (Tree m : nodes0) {
        auto it = fFamParents.find(m);
        if (it == fFamParents.end()) {
            why = "a member read by several nodes";
            return false;
        }
        // the member's own delayed self-reads (Delay(m, d >= 1), inside its
        // recursion) are not readers ; a read of that delay from outside is a
        // private node read elsewhere, refused below
        std::vector<Tree> readers;
        for (Tree r : it->second) {
            Tree x, y;
            int  d;
            if (isSigDelay(r, x, y) && x == m && isSigInt(y, &d) && d >= 1) {
                continue;
            }
            readers.push_back(r);
        }
        if (readers.size() != 1) {
            why = "a member read by several nodes";
            return false;
        }
        Tree p = readers[0];
        Tree h;
        if (auto dc = fFamDefCell.find(p); isList(p) && dc != fFamDefCell.end()) {
            // a definition of a recursive group : the automaton, the group is the host
            if (group && group != dc->second.first) {
                why = "members defined in two groups";
                return false;
            }
            group = dc->second.first;
            h     = group;
            memberDef.push_back(dc->second.second);
        } else if (isList(p)) {
            h       = nullptr;
            outputs = true;
        } else if (isSigSum(p)) {
            h    = p;
            sums = true;
        } else {
            why = "a member read by something else than a sum, the outputs or a group";
            return false;
        }
        auto hi = hostIndex.find(h);
        if (hi == hostIndex.end()) {
            hi = hostIndex.emplace(h, (int)hosts.size()).first;
            hosts.push_back(h);
        }
        memberHost.push_back(hi->second);
    }
    if ((outputs && sums) || (group && (outputs || sums))) {
        why = "members feeding hosts of two kinds";
        return false;
    }
    // ---- members grouped by host, hosts in serial order
    std::vector<int> order(nodes0.size());
    for (size_t i = 0; i < order.size(); i++) {
        order[i] = (int)i;
    }
    if (group) {
        std::stable_sort(order.begin(), order.end(), [&](int a, int b) { return memberDef[a] < memberDef[b]; });
    } else {
        std::stable_sort(order.begin(), order.end(), [&](int a, int b) { return memberHost[a] < memberHost[b]; });
    }
    std::vector<Tree> nodes;
    std::vector<int>  mh, md;
    for (int i : order) {
        nodes.push_back(nodes0[i]);
        mh.push_back(memberHost[i]);
        if (group) {
            md.push_back(memberDef[i]);
        }
    }
    if (typed && (getCertifiedSigType(nodes[0])->nature() != kReal || !getConditionCode(nodes[0]).empty())) {
        why = "not real, or conditional";
        return false;
    }
    // ---- slots, audio slots, commons, private nodes : every member against the template.
    // The template is the first member, unless a leaf it shares between two
    // positions is not shared by the others (two coefficients equal in it
    // alone) : then the first member whose sharing every other member
    // respects is the template, and the first member is one of its members.
    std::vector<FamIso2> isos(nodes.size());
    std::set<Tree>       hostSet(hosts.begin(), hosts.end());
    hostSet.erase(nullptr);
    plan = FamPlan();
    size_t tj    = 0;
    bool   found = false;
    for (bool retry = true; tj < nodes.size() && retry && !found; tj += found ? 0 : 1) {
        // another template is tried only after a sharing collision, never after a shape mismatch
        Tree t0    = nodes[tj];
        bool first = true, ok = true;
        retry      = false;
        for (size_t m = 0; m < nodes.size() && ok; m++) {
            if (m == tj) {
                continue;
            }
            isos[m]        = FamIso2();
            isos[m].holes  = holes;
            isos[m].shapes = shapes;
            isos[m].topA   = t0;
            isos[m].topB   = nodes[m];
            if (!isos[m].iso(t0, nodes[m])) {
                why   = isos[m].collided ? "a leaf the template shares is not shared by a member" : "a member is not isomorphic to the template (shape without audio slots)";
                ok    = false;
                retry = isos[m].collided;
            } else if (first) {
                plan.leaves  = isos[m].slotA;
                plan.aleaves = isos[m].aslotA;
                plan.commons = isos[m].commonA;
                plan.priv    = isos[m].privA;
                first        = false;
            } else if (isos[m].slotA != plan.leaves || isos[m].aslotA != plan.aleaves || isos[m].commonA != plan.commons) {
                why = "the members do not line up on the same slots and commons";
                ok  = false;
            }
        }
        if (ok) {
            found = true;
            continue;
        }
        plan.leaves.clear();
        plan.aleaves.clear();
        plan.commons.clear();
        plan.priv.clear();
    }
    if (!found) {
        if (getenv("FAUST_FAM_TRACE")) {
            std::cerr << "fam : no template among " << nodes.size() << " members (" << why << ")" << std::endl;
        }
        return false;
    }
    Tree t0   = nodes[tj];
    plan.tmpl = t0;
    for (size_t m = 0; m < nodes.size(); m++) {
        if (m != tj) {
            plan.priv.insert(isos[m].privB.begin(), isos[m].privB.end());
        }
    }
    if (getenv("FAUST_FAM_TRACE") && tj != 0) {
        std::cerr << "fam template : member " << tj << " (the first member shares a leaf the others do not)" << std::endl;
    }
    if (plan.leaves.empty() && plan.aleaves.empty()) {
        why = "the members differ by nothing";
        return false;
    }
    if (!famPrivateOnly(plan.priv, hostSet, outputs, group)) {
        why = "a private node of a member is read elsewhere";
        return false;
    }
    {
        std::set<Tree> slotSet(plan.leaves.begin(), plan.leaves.end()), seen, com = plan.commons;
        com.insert(plan.aleaves.begin(), plan.aleaves.end());  // an audio slot is a leaf for the loop
        if (!famCheck(t0, slotSet, com, seen, typed)) {
            why = "the template holds a construct the family loop cannot generate";
            return false;
        }
    }
    plan.trees = nodes;
    for (size_t m = 0; m < nodes.size(); m++) {
        plan.slots.push_back(m == tj ? plan.leaves : isos[m].slotB);
        plan.aslots.push_back(m == tj ? plan.aleaves : isos[m].aslotB);
    }
    // a member fed, through a hole, by another member of the class (two
    // stages of one chain, the same shape once their inputs are holes) : the
    // loop reads its input arrays before its first iteration, so the audio
    // slots must not depend on the members
    {
        std::set<Tree>    memberSet(nodes.begin(), nodes.end()), seen;
        std::vector<Tree> st;
        for (auto& v : plan.aslots) {
            for (Tree t : v) {
                int  pi;
                Tree pg;
                if (group && isProj(t, &pi, pg) && pg == group) {
                    continue;  // the automaton's neighbourhood : a state of the group, read at the previous generation (checked below)
                }
                st.push_back(t);
            }
        }
        while (!st.empty()) {
            Tree t = st.back();
            st.pop_back();
            if (!seen.insert(t).second) {
                continue;
            }
            if (memberSet.count(t)) {
                why = "a member is fed by another member of the class";
                return false;
            }
            Tree id, body;
            if (isRec(t, id, body)) {
                if (body) {
                    st.push_back(body);
                }
                continue;
            }
            for (int k = 0; k < t->arity(); k++) {
                st.push_back(t->branch(k));
            }
        }
    }
    plan.hosts      = hosts;
    plan.memberHost = mh;
    for (size_t i = 0; i < nodes.size(); i++) {
        plan.members.push_back((int)i);
    }
    if (group) {
        // the automaton : contiguous definitions, every audio slot a projection
        // of the group read at delay >= 1 (the members' Delay nodes are private,
        // their operand the slot), the same delay for every member, and the
        // projection read at a constant offset from the member's own definition
        // (affine : S_d[c + base]) or through a table
        Tree gid, defs;
        isRec(group, gid, defs);
        int n = 0;
        for (Tree l = defs; isList(l); l = tl(l)) {
            n++;
        }
        plan.group     = group;
        plan.groupSize = n;
        plan.memberDef = md;
        // the cells in runs of contiguous definitions (a 2-D grid : one run per
        // row of interior cells) : one loop per run, the same body
        plan.runs.clear();
        for (size_t m = 0; m < md.size(); m++) {
            if (m == 0 || md[m] != md[m - 1] + 1) {
                plan.runs.push_back({(int)m, (int)m + 1});
            } else {
                plan.runs.back().second = (int)m + 1;
            }
        }
        if (plan.runs.size() > 64) {
            why = "the automaton's cells are scattered over too many runs";
            return false;
        }
        if (4 * (int)md.size() < n) {
            // the whole group moves into the arrays : worth it only when the
            // loop covers a good part of its definitions (a plate whose cells
            // split into classes of six over 200 definitions stays with the
            // classic emitter ; its 90 interior cells of 200, in six rows, go)
            why = "the automaton's cells are fewer than a quarter of the group's definitions";
            return false;
        }
        if (!plan.commons.empty()) {
            for (Tree t : plan.commons) {
                int  i;
                Tree g;
                if (isProj(t, &i, g) && g == group) {
                    why = "a cell reads one projection of the group for every member (not a neighbourhood)";
                    return false;
                }
            }
        }
        plan.aslotBase.assign(plan.aleaves.size(), INT_MIN);
        std::set<Tree> slotSet(plan.aleaves.begin(), plan.aleaves.end());
        for (size_t m = 1; m < nodes.size(); m++) {
            slotSet.insert(plan.aslots[m].begin(), plan.aslots[m].end());
        }
        for (Tree t : plan.priv) {
            // every delayed read of a projection : a Delay(proj, d) private node,
            // d >= 1 (an int literal, a uniform slot), or a kernel over one (its
            // taps reach d + taps - 1) ; the deepest sizes the arrays
            Tree x, y;
            int  d;
            tvec V;
            if (isSigDelay(t, x, y) && slotSet.count(x)) {
                if (!isSigInt(y, &d) || d < 0) {
                    why = "a cell reads a projection of its group at a variable delay";
                    return false;
                }
                plan.groupDepth = std::max(plan.groupDepth, d);  // d == 0 : a current-step read, judged below
            }
            if (isSigFIR(t, V) && V.size() > 2) {
                Tree src = V[0];
                int  d0  = 0;
                if (isSigDelay(src, x, y) && isSigInt(y, &d0)) {
                    src = x;
                }
                if (slotSet.count(src)) {
                    plan.groupDepth = std::max(plan.groupDepth, d0 + (int)V.size() - 2);
                }
            }
        }
        for (size_t k = 0; k < plan.aleaves.size(); k++) {
            // a slot is either the neighbourhood (every member reads a projection
            // of the group : affine or a table) or an ordinary input (INT_MAX :
            // the input array of the family form)
            int  base  = INT_MIN;
            int  kinds = 0;
            for (size_t m = 0; m < nodes.size(); m++) {
                int  j;
                Tree g;
                Tree v = plan.aslots[m][k];
                if (!isProj(v, &j, g) || g != group) {
                    kinds |= 2;
                    continue;
                }
                kinds |= 1;
                int off = j - md[m];
                if (m == 0) {
                    base = off;
                } else if (off != base) {
                    base = INT_MIN;  // not affine : a table
                }
            }
            if (kinds == 3) {
                why = "an audio slot mixes the group's projections and other inputs";
                return false;
            }
            plan.aslotBase[k] = (kinds == 2) ? INT_MAX : base;
        }
        // The projections read at the current step. By a cell : allowed only
        // of a definition outside the family (a hammer, a bow, a bridge),
        // which is then computed BEFORE the loop ; of another cell it would be
        // sequential, refused. The other definitions are ordered by their own
        // current-step reads : those the cells need before the loop, the rest
        // after it (they may read the cells' current generation).
        std::set<Tree>    memberSet(nodes.begin(), nodes.end());
        std::set<int>     cellSet(md.begin(), md.end());
        std::set<int>     needed;  // definitions the cells read at the current step
        for (Tree t : plan.priv) {
            Tree x, y;
            int  d;
            const bool delayed = isSigDelay(t, x, y) && isSigInt(y, &d) && d >= 1;  // Delay(proj, 0) counts as a current-step read
            for (int b = 0; b < t->arity(); b++) {
                Tree ch = t->branch(b);
                int  i;
                Tree g;
                if (isProj(ch, &i, g) && g == group && !(delayed && b == 0)) {
                    if (cellSet.count(i)) {
                        why = "a cell reads another cell at the current step : not an automaton";
                        return false;
                    }
                    needed.insert(i);
                }
            }
        }
        // the current-step reads of every definition outside the family
        std::vector<std::set<int>> deps(n);
        {
            int j = 0;
            for (Tree l = defs; isList(l); l = tl(l), j++) {
                if (cellSet.count(j)) {
                    continue;
                }
                std::set<Tree>    seen;
                std::vector<Tree> st{hd(l)};
                while (!st.empty()) {
                    Tree t = st.back();
                    st.pop_back();
                    if (!seen.insert(t).second) {
                        continue;
                    }
                    Tree x, y, id, body;
                    int  i, d;
                    if (isProj(t, &i, id) && id == group) {
                        deps[j].insert(i);
                        continue;
                    }
                    if (isSigDelay(t, x, y) && isSigInt(y, &d) && d >= 1) {
                        continue;  // a previous generation : a state
                    }
                    if (isRec(t, id, body)) {
                        continue;  // another group : its own affair
                    }
                    for (int b = 0; b < t->arity(); b++) {
                        st.push_back(t->branch(b));
                    }
                }
            }
        }
        // the inputs from outside the group (a hammer's force, an excitation),
        // compiled on demand where the family is emitted : whatever they read
        // of the group at the current step must be computed before the loop
        // (a definition outside the family, added to the needs) ; a cell read
        // that way would be a cycle at the current step, refused
        {
            std::set<Tree>    seen;
            std::vector<Tree> st(plan.commons.begin(), plan.commons.end());
            for (auto& v : plan.aslots) {
                for (Tree t : v) {
                    int  pi;
                    Tree pg;
                    if (!(isProj(t, &pi, pg) && pg == group)) {
                        st.push_back(t);
                    }
                }
            }
            while (!st.empty()) {
                Tree t = st.back();
                st.pop_back();
                if (!seen.insert(t).second) {
                    continue;
                }
                Tree x, y, id, body;
                int  i, d;
                if (isProj(t, &i, id) && id == group) {
                    if (cellSet.count(i)) {
                        why = "an input of the cells reads a cell at the current step";
                        return false;
                    }
                    needed.insert(i);
                    continue;
                }
                if (isSigDelay(t, x, y) && isSigInt(y, &d) && d >= 1) {
                    continue;
                }
                if (isRec(t, id, body)) {
                    if (body) {
                        st.push_back(body);
                    }
                    continue;
                }
                for (int b = 0; b < t->arity(); b++) {
                    st.push_back(t->branch(b));
                }
            }
        }
        // before : the closure of what the cells need ; after : the rest ; both in dependency order
        std::set<int> before;
        {
            std::vector<int> st(needed.begin(), needed.end());
            while (!st.empty()) {
                int j = st.back();
                st.pop_back();
                if (!before.insert(j).second) {
                    continue;
                }
                for (int i : deps[j]) {
                    if (cellSet.count(i)) {
                        why = "a definition the cells need at the current step reads a cell at the current step";
                        return false;
                    }
                    st.push_back(i);
                }
            }
        }
        auto topo = [&](const std::set<int>& which, std::vector<int>& out) {
            std::map<int, int> state;  // 0 new, 1 open, 2 done
            std::function<bool(int)> visit = [&](int j) {
                if (state[j] == 2) {
                    return true;
                }
                if (state[j] == 1) {
                    return false;  // a cycle at the current step : not causal, cannot happen
                }
                state[j] = 1;
                for (int i : deps[j]) {
                    if (which.count(i) && !visit(i)) {
                        return false;
                    }
                }
                state[j] = 2;
                out.push_back(j);
                return true;
            };
            for (int j : which) {
                if (!visit(j)) {
                    return false;
                }
            }
            return true;
        };
        std::set<int> after;
        for (int j = 0; j < n; j++) {
            if (!cellSet.count(j) && !before.count(j)) {
                after.insert(j);
            }
        }
        if (!topo(before, plan.defsBefore) || !topo(after, plan.defsAfter)) {
            why = "a cycle at the current step among the group's definitions";
            return false;
        }
        // what the definitions computed before the loop read from outside
        // the group : the largest subtrees reading nothing of the group's
        // current generation (a read of a previous generation is the
        // family's arrays, valid during the whole sample, so a subtree
        // reading only those is an input like any other). They are compiled
        // on demand where the family is emitted, so the schedule must place
        // them before its first host, like the members' inputs (a
        // variable-delay read of a line compiled before the line is written
        // would read the previous lap at delay 0 : glassHarmonica at 14 kHz,
        // its waveguides shorter than a sample).
        {
            std::map<Tree, bool> touches;  // the subtree reads the group's current generation
            std::function<bool(Tree)> walk = [&](Tree t) -> bool {
                if (auto it = touches.find(t); it != touches.end()) {
                    return it->second;
                }
                touches[t] = false;  // a cycle through a rec body : no access on that path
                if (famAccessesGroup(t, group)) {
                    touches[t] = famReadsGroupNow(t, group);
                    return touches[t];  // a previous generation is not looked into
                }
                bool r = false;
                Tree id, body;
                if (isRec(t, id, body)) {
                    r = body && walk(body);
                } else {
                    for (int b = 0; b < t->arity(); b++) {
                        r = walk(t->branch(b)) || r;
                    }
                }
                touches[t] = r;
                return r;
            };
            std::set<Tree>           roots;
            std::function<void(Tree)> collect = [&](Tree t) {
                if (famAccessesGroup(t, group)) {
                    return;
                }
                if (!walk(t)) {
                    roots.insert(t);
                    return;
                }
                Tree id, body;
                if (isRec(t, id, body)) {
                    if (body) {
                        collect(body);
                    }
                    return;
                }
                for (int b = 0; b < t->arity(); b++) {
                    collect(t->branch(b));
                }
            };
            for (int j : plan.defsBefore) {
                Tree l = defs;
                for (int k = 0; k < j; k++) {
                    l = tl(l);
                }
                collect(hd(l));
            }
            plan.borderInputs.assign(roots.begin(), roots.end());
        }
    }
    return true;
}

// the work of a member : its private nodes, an n-ary sum counting for its
// n - 1 additions, so that the count does not depend on the spelling of the
// sums (n-ary before the lowering, binary after)
static int famWork(const std::set<Tree>& priv, int members)
{
    int w = 0;
    for (Tree t : priv) {
        tvec ops;
        if (isSigSum(t, ops)) {
            w += std::max(1, (int)ops.size() - 1);
        } else if (isSigFIR(t, ops) || isSigIIR(t, ops)) {
            w += std::max(1, (int)ops.size() - 1);  // a kernel : one multiply-add per tap
        } else if (getUserData(t) != nullptr && t->arity() > 0 && getUserData(t) != (void*)gGlobal->gAbsPrim &&
                   getUserData(t) != (void*)gGlobal->gMinPrim && getUserData(t) != (void*)gGlobal->gMaxPrim) {
            w += 4;  // a transcendental function (log10, pow, exp...) : a call
        } else {
            w += 1;
        }
    }
    return w / std::max(1, members);
}

// the states of a member : its private recursive groups and kernels
static int famStates(const std::set<Tree>& priv, int members)
{
    int n = 0;
    for (Tree t : priv) {
        Tree id, body;
        tvec V;
        n += (isRec(t, id, body) || isSigIIR(t, V) || (isSigFIR(t, V) && V.size() > 2)) ? 1 : 0;
    }
    return n / std::max(1, members);
}

// The family form and the dispatch of the sums : lowerSums turns every
// n-ary sum into binary adds, and a family is an n-ary sum of isomorphic
// operands -- lowered, it is not seen. Planned BEFORE the lowering, on the
// untyped tree, the family sums and the sums private to their members are
// handed to lowerSums as rows to keep : the members stay isomorphic and the
// plan is redone, typed, after prepare. Nothing of the plan is kept here :
// the lowering rebuilds the tree.
std::set<Tree> ScalarCompiler::famKeepSums(Tree L)
{
    std::set<Tree>       keep;
    std::vector<FamPlan> fams;
    planFamilyClasses(L, fams, false);
    for (const FamPlan& f : fams) {
        for (Tree u : f.priv) {
            if (isSigSum(u)) {
                keep.insert(u);
            }
        }
        for (Tree h : f.hosts) {
            if (h) {
                keep.insert(h);
            }
        }
    }
    if (getenv("FAUST_FAM_TRACE")) {
        std::cerr << "fam keep : " << keep.size() << " sum(s) left n-ary through the lowering" << std::endl;
    }
    return keep;
}

// The families of a tree, by shape class : the classes of four nodes or more,
// widest first, the outermost of equal width first ; a class whose members are
// already inside an accepted family is skipped (compiled by the outer loop),
// and a class narrower than a family inside its members steps aside (four
// output sums of P chains : the loop of P, not the loop of four).
void ScalarCompiler::planFamilyClasses(Tree root, std::vector<FamPlan>& out, bool typed)
{
    const bool trace = getenv("FAUST_FAM_TRACE") != nullptr;
    fFamRoot         = root;
    fFamParentsBuilt = false;
    fFamParents.clear();
    FamShapes  S;
    FamClasses C;
    C.collectWithHoles(root, S, trace);
    std::vector<std::pair<Shape, std::vector<Tree>>> classes;
    for (auto& kv : C.members) {
        if (kv.second.size() >= 4) {
            classes.push_back(kv);
        }
    }
    std::sort(classes.begin(), classes.end(), [&S](const auto& a, const auto& b) {
        if (a.second.size() != b.second.size()) {
            return a.second.size() > b.second.size();
        }
        int sa = S.size(a.first), sb = S.size(b.first);
        return sa != sb ? sa > sb : a.second[0]->serial() < b.second[0]->serial();
    });
    // every class is planned first : the selection needs the coverage of
    // each one (its work, host reductions included)
    struct Cand {
        FamPlan plan;
        int     coverage;
        bool    outputs;
    };
    std::vector<Cand> cands;
    for (auto& kv : classes) {
        FamPlan     plan;
        std::string why;
        if (!planFamilyClass(kv.second, plan, typed, why, &S.holes, &S)) {
            if (trace) {
                std::cerr << "fam refused : class of " << kv.second.size() << " (" << S.size(kv.first) << " nodes) : " << why << std::endl;
            }
            continue;
        }
        // every member must carry a state : a family without one is per-sample
        // arithmetic on inputs filled every sample, which the C++ compiler
        // already packs as straight-line code (StiffString : 100 products
        // through three input arrays of 100, x1.84 under g++). An output
        // family competes with the compiler's own packing of parallel
        // channels, which keeps shallow states in registers : its members
        // must also carry enough work
        const bool outputs = !plan.hosts.empty() && plan.hosts[0] == nullptr;
        const int  work = famWork(plan.priv, (int)plan.trees.size()), states = famStates(plan.priv, (int)plan.trees.size());
        if ((states < 1 && !plan.group) || (outputs && (work < gGlobal->gFamilyMinOut || plan.trees.size() < 8))) {
            // an automaton's state is its group ; an output or display family
            // needs eight members at least (a loop of six chains with three
            // input arrays lost to the compiler's packing : spectralLevel x1.15)
            if (trace) {
                std::cerr << "fam refused : " << (outputs ? "outputs, " : "") << "family of " << plan.trees.size() << " : " << work
                          << " operations and " << states << " states per member (one state"
                          << (outputs ? " and " + T(gGlobal->gFamilyMinOut) + " operations, eight members" : "") << " needed)" << std::endl;
            }
            continue;
        }
        int coverage = famWork(plan.priv, 1);
        for (Tree h : plan.hosts) {
            tvec ops;
            if (h && isSigSum(h, ops)) {
                coverage += std::max(1, (int)ops.size() - 1);  // the reduction is part of the form
            }
        }
        cands.push_back({plan, coverage, outputs});
    }
    // The candidates by coverage, the most work first : the loop of 32 bands
    // (1215 operations) before the loop of the 64 biquads inside them (704),
    // the 13 analyzer chains before the 28 squares they contain. A candidate
    // whose members are the host sums of a wider candidate steps aside : four
    // output sums of eight chains, or the 32 chains and their reductions --
    // the loop of 32 (a rule by coverage alone, nearly equal here, once
    // preferred 20 inner recursions to the 19 modes of djembeMIDI : x2.9).
    std::sort(cands.begin(), cands.end(), [](const Cand& a, const Cand& b) {
        if (a.coverage != b.coverage) {
            return a.coverage > b.coverage;
        }
        return a.plan.trees.size() != b.plan.trees.size() ? a.plan.trees.size() > b.plan.trees.size()
                                                          : a.plan.trees[0]->serial() < b.plan.trees[0]->serial();
    });
    std::set<Tree> covered;  // the private nodes of the accepted families
    for (size_t i = 0; i < cands.size(); i++) {
        FamPlan& plan = cands[i].plan;
        bool     inside = false;
        for (Tree m : plan.trees) {
            inside = inside || covered.count(m);
        }
        if (inside) {
            continue;  // compiled by the loop of an accepted family
        }
        bool aside = false;
        for (size_t j = i + 1; j < cands.size() && !aside; j++) {
            if (cands[j].plan.trees.size() <= plan.trees.size()) {
                continue;
            }
            std::set<Tree> hostsOfJ(cands[j].plan.hosts.begin(), cands[j].plan.hosts.end());
            bool           hosts = true;
            for (Tree m : plan.trees) {
                hosts = hosts && hostsOfJ.count(m);
            }
            aside = hosts;
        }
        if (aside) {
            if (trace) {
                std::cerr << "fam : a family of " << plan.trees.size() << " (" << cands[i].coverage
                          << " operations) steps aside : its members are the host sums of a wider one" << std::endl;
            }
            plan.trees.clear();
            continue;
        }
        // a family whose members hold an accepted (wider, planned first) family
        // steps aside : the loop of P chains, not the loop of four sums of P
        bool swallows = false;
        for (Tree t : plan.priv) {
            swallows = swallows || covered.count(t);
        }
        if (swallows) {
            if (trace) {
                std::cerr << "fam : a family of " << plan.trees.size() << " steps aside for a wider one inside its members" << std::endl;
            }
            plan.trees.clear();
            continue;
        }
        if (plan.group) {
            bool taken = false;
            for (const FamPlan& g : out) {
                taken = taken || g.group == plan.group;
            }
            if (taken) {
                if (trace) {
                    std::cerr << "fam refused : automaton of " << plan.trees.size() << " : its group already has one" << std::endl;
                }
                plan.trees.clear();
                continue;
            }
        }
        covered.insert(plan.priv.begin(), plan.priv.end());
        if (trace) {
            std::cerr << "fam planned : " << plan.trees.size() << " members, " << plan.hosts.size()
                      << (plan.group ? " group" : (cands[i].outputs ? " output" : " sum"))
                      << " host(s), " << plan.leaves.size() << " slots, " << plan.aleaves.size() << " audio slots, " << plan.commons.size()
                      << " commons, " << plan.priv.size() << " private nodes, " << cands[i].coverage << " operations" << std::endl;
        }
        out.push_back(plan);
    }
    fFamRoot         = nullptr;
    fFamParentsBuilt = false;
    fFamParents.clear();
}

void ScalarCompiler::planFamilies()
{
    fFamilies.clear();
    fFamHost.clear();
    fFamGroup.clear();
    fFamPrivate.clear();
    fFamComputed.clear();
    if (!fFamRoot) {
        return;
    }
    // the stateful roots of the harvested display cones join the outputs :
    // computed in the loop, captured at its end through CS, a family among
    // them stores its members in an array like an output family (the
    // spectrum analyzers : one chain per band, one bargraph each)
    Tree root = fFamRoot;
    for (Tree sd : fDisplayStateful) {
        root = cons(sd, root);
    }
    fFamOrigin.clear();
    fFamConsumed.clear();
    if (gGlobal->gReconstructFIRIIRs || !gGlobal->gLowerSums) {
        // -fam alone, and -fam -fir (families first) : the plan reads a VIEW of the tree, its audio sums
        // revealed n-ary (the families' hosts and their members' isomorphic
        // operands), typed for the plan's own needs ; the tree itself, the
        // one the schedule and the emitter see, is untouched -- every node
        // of the view reaches its tree node through famOrig (revealSum
        // records the origins), so the plan's hosts, private nodes, groups
        // and inputs are carried over to the tree below
        startTiming("family view");
        root = revealSum(root, false, &fFamOrigin, &fFamConsumed);
        typeAnnotation(root, false);
        endTiming("family view");
    }
    if (getenv("FAUST_FAM_SHAPES")) {
        traceFamShapes(root);
    }
    planFamilyClasses(root, fFamilies, true);
    fFamRoot = root;
    famEmitterStructures();
}

// The emitter's structures from the plan : the hosts, the groups, the private
// nodes and the automata's registrations, keyed by the TREE's nodes (famOrig : the
// origins ; under -fam -fir this is run again after the kernel passes, the
// frozen nodes being the plan's)
void ScalarCompiler::famEmitterStructures()
{
    Tree root = fFamRoot;
    fFamHost.clear();
    fFamGroup.clear();
    fFamPrivate.clear();
    fFamComputed.clear();
    for (size_t i = 0; i < fFamilies.size(); i++) {
        FamPlan& f = fFamilies[i];
        if (f.group) {
            // the automaton : every projection of its group, at every delay
            // read anywhere in the tree, will get its expression in the
            // family's arrays when the family is emitted, at the first access
            // of the group in the schedule (nothing compiles a projection
            // before) ; a read at a variable delay leaves the group to the
            // classic emitter
            std::set<Tree>    seen;
            std::vector<Tree> st{root};
            std::vector<std::pair<Tree, std::string>> regs;
            bool                                      ok = true;
            int                                       depth = f.groupDepth;
            if (f.id < 0) {
                f.id = fFamCount++;
            }
            while (!st.empty() && ok) {
                Tree t = st.back();
                st.pop_back();
                if (!seen.insert(t).second) {
                    continue;
                }
                Tree x, y, id, body;
                int  pi, d;
                tvec V;
                const auto after = [&](int j) {
                    return std::find(f.defsAfter.begin(), f.defsAfter.end(), j) != f.defsAfter.end();
                };
                if (isSigDelay(t, x, y) && isProj(x, &pi, id) && id == f.group) {
                    if (!isSigInt(y, &d) || d < 0) {
                        ok = false;
                        break;
                    }
                    depth = std::max(depth, d);
                    if (d > 0) {
                        regs.push_back({famOrig(t), subst("fFam$0S_$1[$2]", T(f.id), T(d), T(pi))});
                    } else if (!after(pi)) {
                        regs.push_back({famOrig(t), subst("fFam$0New[$1]", T(f.id), T(pi))});
                    }
                    // a read at delay 0 of a definition computed after the loop : famAutoRead, through its projection
                } else if (isProj(t, &pi, id) && id == f.group && !after(pi)) {
                    regs.push_back({famOrig(t), subst("fFam$0New[$1]", T(f.id), T(pi))});
                    // a definition computed after the loop : generateRecProj, at its own position
                }
                if (isSigFIR(t, V) && V.size() > 2) {
                    // a kernel over a projection : its taps read the arrays (famAutoRead)
                    Tree src = V[0];
                    int  d0  = 0;
                    if (isSigDelay(src, x, y) && isSigInt(y, &d0)) {
                        src = x;
                    }
                    if (isProj(src, &pi, id) && id == f.group) {
                        depth = std::max(depth, d0 + (int)V.size() - 2);
                    }
                }
                if (isRec(t, id, body) && body) {
                    st.push_back(body);
                    continue;
                }
                for (int k = 0; k < t->arity(); k++) {
                    st.push_back(t->branch(k));
                }
            }
            if (!ok) {
                if (getenv("FAUST_FAM_TRACE")) {
                    std::cerr << "fam dismantled : automaton of " << f.trees.size() << ", a projection of its group is read at a variable delay" << std::endl;
                }
                f.trees.clear();
                continue;
            }
            f.groupDepth = depth;
            f.regs       = regs;
            fFamGroup[famOrig(f.group)] = (int)i;  // the emitter's structures are keyed by the tree's nodes
        }
        // the binary chains the view flattened into a host or into a
        // member's sum are the tree's nodes : skipped with the family
        auto absorbed = [&](Tree v) {
            if (auto it = fFamConsumed.find(v); it != fFamConsumed.end()) {
                for (Tree c : it->second) {
                    fFamPrivate.insert(famOrig(c));
                }
            }
        };
        for (Tree h : f.hosts) {
            if (h && !f.group) {
                fFamHost[famOrig(h)] = (int)i;
                absorbed(h);
            }
        }
        for (Tree t : f.priv) {
            fFamPrivate.insert(famOrig(t));
            absorbed(t);
        }
    }
    if (getenv("FAUST_FAM_TRACE")) {
        std::cerr << "fam plan : " << fFamilies.size() << " families, " << fFamHost.size() << " host sums, private nodes " << fFamPrivate.size()
                  << std::endl;
    }
}

// Before the schedule : the loop of a family is emitted at its first host,
// and every audio input of every member (audio slots, commons) must be
// computed by then. Every host depends on every input : an edge per pair,
// unless it would close a cycle (an input reading a host through a delay),
// in which case the check after the schedule dismantles the family.
void ScalarCompiler::famScheduleEdges(digraph<Tree>& G)
{
    auto reaches = [&G](Tree from, Tree to) -> bool {
        std::set<Tree>    seen;
        std::vector<Tree> work{from};
        while (!work.empty()) {
            Tree n = work.back();
            work.pop_back();
            if (n == to) {
                return true;
            }
            if (!seen.insert(n).second) {
                continue;
            }
            for (const auto& c : G.destinations(n)) {
                work.push_back(c.first);
            }
        }
        return false;
    };
    int added = 0, dropped = 0;
    for (FamPlan& f : fFamilies) {
        // the plan's nodes are those of the view, the graph's those of the tree : through the origins
        std::set<Tree> inputs;
        for (Tree t : f.commons) {
            inputs.insert(famOrig(t));
        }
        for (auto& v : f.aslots) {
            for (Tree t : v) {
                inputs.insert(famOrig(t));
            }
        }
        std::vector<Tree> hosts;
        for (Tree h : f.hosts) {
            hosts.push_back(h ? famOrig(h) : h);
        }
        const Tree group = f.group ? famOrig(f.group) : nullptr;
        if (group) {
            // the automaton : every read of its group's current generation
            // (a projection, a read of one at delay 0) is a host, since the
            // family is emitted at the first of them ; a read of a previous
            // generation is the arrays, ordered by nothing ; the inputs are
            // the members' and those of the definitions computed before the
            // loop ; the group's own projections read as neighbours are
            // states, not inputs
            hosts.clear();
            for (const Tree& n : G.nodes()) {
                if (famReadsGroupNow(n, group)) {
                    hosts.push_back(n);
                }
            }
            for (Tree t : f.borderInputs) {
                inputs.insert(famOrig(t));
            }
            for (auto it = inputs.begin(); it != inputs.end();) {
                it = famAccessesGroup(*it, group) ? inputs.erase(it) : std::next(it);
            }
        }
        for (Tree h : hosts) {
            if (!h || !G.nodes().count(h)) {
                continue;
            }
            for (Tree i : inputs) {
                int k;
                if (isSigInput(i, &k) || !G.nodes().count(i) || i == h) {
                    continue;
                }
                if (reaches(i, h)) {
                    dropped++;
                    continue;
                }
                G.add(h, i, 0);  // h depends on i
                added++;
            }
        }
    }
    if (getenv("FAUST_FAM_TRACE") && (added || dropped)) {
        std::cerr << "fam schedule : " << added << " host-input edge(s) added, " << dropped << " dropped (cycle)" << std::endl;
    }
}

// After the schedule : a family whose inputs still come after its first host
// (an edge dropped for a cycle) is dismantled, its nodes go back to the
// schedule and are compiled one by one.
void ScalarCompiler::checkFamilyOrder()
{
    for (size_t i = 0; i < fFamilies.size(); i++) {
        FamPlan& f = fFamilies[i];
        if (f.trees.empty()) {
            continue;  // dismantled already
        }
        int        first = INT_MAX;
        const Tree group = f.group ? famOrig(f.group) : nullptr;  // the schedule holds the tree's nodes
        for (Tree h : f.hosts) {
            if (h && !f.group) {
                if (auto it = fSchedPos.find(famOrig(h)); it != fSchedPos.end()) {
                    first = std::min(first, it->second);
                }
            }
        }
        if (group) {
            for (auto& kv : fSchedPos) {
                if (famReadsGroupNow(kv.first, group)) {
                    first = std::min(first, kv.second);
                }
            }
        }
        if (first == INT_MAX) {
            continue;  // output family, or an automaton read at a delay only : emitted after the whole schedule
        }
        int  latest = -1;
        Tree culprit = nullptr;
        auto seen    = [&](Tree v) {
            int  k, d;
            Tree x, y;
            Tree t = famOrig(v);
            if (isSigInput(t, &k) || (group && famAccessesGroup(t, group))) {
                return;  // an input of the program is read from its buffer ; an access of the automaton's own group is a state (its arrays) or a definition computed before the loop
            }
            if (group && isSigDelay(t, x, y) && isSigInt(y, &d) && d >= 1) {
                return;  // an automaton's delayed input is captured at the top of the sample, whatever the order
            }
            if (auto it = fSchedPos.find(t); it != fSchedPos.end() && it->second > latest) {
                latest  = it->second;
                culprit = t;
            }
        };
        // the audio inputs only : the slow slots are computed per block, before the loop
        for (Tree t : f.commons) {
            seen(t);
        }
        for (auto& v : f.aslots) {
            for (Tree t : v) {
                seen(t);
            }
        }
        for (Tree t : f.borderInputs) {
            seen(t);  // compiled on demand where the family is emitted, like the members' inputs
        }
        if (latest > first) {
            if (getenv("FAUST_FAM_TRACE")) {
                std::cerr << "fam dismantled : family of " << f.trees.size() << ", an input (" << ppsig(culprit, 40)
                          << ") is scheduled after its first host (positions " << latest << " > " << first << ")" << std::endl;
            }
            auto release = [&](Tree v) {
                if (auto it = fFamConsumed.find(v); it != fFamConsumed.end()) {
                    for (Tree c : it->second) {
                        fFamPrivate.erase(c);
                    }
                }
            };
            for (Tree t : f.priv) {
                fFamPrivate.erase(famOrig(t));
                release(t);
            }
            for (Tree h : f.hosts) {
                if (h) {
                    fFamHost.erase(famOrig(h));
                    release(h);
                }
            }
            if (group) {
                fFamGroup.erase(group);  // nothing registered yet (the projections' expressions are registered at the emission)
            }
            f.trees.clear();  // an empty family : never emitted
        }
    }
}

// The family loop : states in arrays, coefficients in tables, the inputs
// that differ per member in arrays filled just before, one statement list per
// member ; reduce : the members' results are accumulated (name = the
// accumulator) ; otherwise stored in an array (name = the array), one cell
// per member. why : the refusal, when it fails.
bool ScalarCompiler::emitFamilyLoop(FamPlan& plan, bool reduce, std::string& name, std::string& why,
                                    const std::vector<std::pair<int, int>>* ranges)
{
    const bool                            trace   = getenv("FAUST_FAM_TRACE") != nullptr;
    const std::vector<std::vector<Tree>>& slots   = plan.slots;
    const std::vector<Tree>&              leaves  = plan.leaves;
    const std::set<Tree>&                 commons = plan.commons;
    Tree                                  t0      = plan.ktemplate ? plan.ktemplate : plan.tmpl ? plan.tmpl : plan.trees[0];
    const int                             P       = (int)plan.trees.size();
    FamCtx g;
    g.id      = plan.id >= 0 ? plan.id : fFamCount;
    g.P       = P;
    g.ty      = ifloat();
    g.commons = commons;
    g.thaw    = plan.ktemplate ? &plan.thaw : nullptr;
    g.plan    = &plan;
    if (plan.group) {
        g.autoGroup = plan.group;
        g.autoDef0  = plan.memberDef.empty() ? 0 : plan.memberDef[0];
        g.autoBase  = plan.aslotBase;
        g.autoBefore.insert(plan.defsBefore.begin(), plan.defsBefore.end());
        for (size_t k = 0; k < plan.aleaves.size(); k++) {
            // an input that is a delayed read (d >= 1, of anything but the
            // group) is captured at the top of the sample : the previous
            // sample's value whatever the order of its writer and the loop
            bool pre = plan.aslotBase[k] == INT_MAX;
            for (int m = 0; pre && m < P; m++) {
                Tree x, y;
                int  d;
                pre = isSigDelay(plan.aslots[m][k], x, y) && isSigInt(y, &d) && d >= 1;
            }
            if (pre) {
                g.preSlots.insert((int)k);
            }
        }
    }
    g.uniform.assign(leaves.size(), true);
    for (size_t k = 0; k < leaves.size(); k++) {
        if (!g.slotIndex.count(leaves[k])) {
            g.slotIndex[leaves[k]] = (int)k;
        }
        for (int m = 1; m < P; m++) {
            if (slots[m][k] != leaves[k]) {
                g.uniform[k] = false;
            }
        }
    }
    g.auniform.assign(plan.aleaves.size(), true);
    for (size_t k = 0; k < plan.aleaves.size(); k++) {
        if (!g.aslotIndex.count(plan.aleaves[k])) {
            g.aslotIndex[plan.aleaves[k]] = (int)k;
        }
        for (int m = 1; m < P; m++) {
            if (plan.aslots[m][k] != plan.aleaves[k]) {
                g.auniform[k] = false;
            }
        }
    }
    if (reduce && ranges) {
        // an input that is the same within every host's members (the four
        // sums of eight chains of E, two program inputs) : no array
        g.ahostUniform.assign(plan.aleaves.size(), true);
        for (size_t k = 0; k < plan.aleaves.size(); k++) {
            for (const auto& r : *ranges) {
                for (int m = r.first + 1; m < r.second; m++) {
                    if (plan.aslots[m][k] != plan.aslots[r.first][k]) {
                        g.ahostUniform[k] = false;
                    }
                }
            }
        }
    }
    {  // parents inside the template, to name shared subexpressions once
        std::set<Tree>    seen;
        std::vector<Tree> st{t0};
        while (!st.empty()) {
            Tree t = st.back();
            st.pop_back();
            Tree u = g.th(t);
            if (!seen.insert(t).second || g.slotIndex.count(u) || g.aslotIndex.count(u) || commons.count(u)) {
                continue;
            }
            Tree id, body;
            if (isRec(t, id, body) && body) {
                st.push_back(body);
                continue;
            }
            for (int k = 0; k < t->arity(); k++) {
                g.uses[t->branch(k)]++;
                st.push_back(t->branch(k));
            }
        }
    }
    const std::string term = famExpr(g, t0);
    for (const auto& kv : g.need) {
        if (!g.stateValue.count(kv.first)) {
            g.fail("a state read but never computed");
        }
    }
    if (g.failed) {
        why = g.reason;
        return false;
    }
    if (plan.id < 0) {
        fFamCount++;
    }
    // the automaton's index tables, for the neighbourhoods that are not affine
    for (int k : g.autoTables) {
        fClass->addDeclCode(subst("int \tfFam$0Idx$1[$2];", T(g.id), T(k), T(P)));
        for (int m = 0; m < P; m++) {
            int  j;
            Tree pg;
            isProj(plan.aslots[m][k], &j, pg);
            fClass->addInitCode(subst("fFam$0Idx$1[$2] = $3;", T(g.id), T(k), T(m), T(j)));
        }
    }
    // states : declared, cleared, shifted at the end of each member iteration
    std::ostringstream shifts;
    for (const auto& kv : g.need) {
        for (int k = 1; k <= kv.second; k++) {
            fClass->addDeclCode(subst("$0 \t$1_$2[$3];", g.ty, kv.first, T(k), T(P)));
            fClass->addClearCode(subst("for (int c = 0; c < $1; c++) { $0_$2[c] = 0; }", kv.first, T(P), T(k)));
        }
        for (int k = kv.second; k >= 2; k--) {
            shifts << subst(" $0_$1[c] = $0_$2[c];", kv.first, T(k), T(k - 1));
        }
        shifts << subst(" $0_1[c] = $1;", kv.first, g.stateValue[kv.first]);
    }
    // the slow subtrees of the kernelized template : a table per member or a scalar, once per block
    for (int n = 0; n < (int)g.derived.size(); n++) {
        Tree              t  = g.derived[n].first;
        const std::string ct = (getCertifiedSigType(t)->nature() == kInt) ? "int" : g.ty;
        bool              ok = true, pm = false;
        if (g.derived[n].second) {
            fClass->addDeclCode(subst("$0 \tfFam$1D$2[$3];", ct, T(g.id), T(n), T(P)));
            for (int m = 0; m < P; m++) {
                fClass->addZone3(subst("fFam$0D$1[$2] = $3;", T(g.id), T(n), T(m), famSlowCode(g, t, m, ok, pm)));
            }
        } else {
            fClass->addZone3(subst("$0 \tfFam$1D$2 = $3;", ct, T(g.id), T(n), famSlowCode(g, t, 0, ok, pm)));
        }
    }
    // coefficient tables, filled once per block
    for (int k : g.usedSlots) {
        const std::string ctype = (getCertifiedSigType(leaves[k])->nature() == kInt) ? "int" : g.ty;
        fClass->addDeclCode(subst("$0 \tfFam$1T$2[$3];", ctype, T(g.id), T(k), T(P)));
        for (int m = 0; m < P; m++) {
            const std::string cc = famCoef(slots[m][k]);
            fClass->addZone3(subst("fFam$0T$1[$2] = $3;", T(g.id), T(k), T(m), cc));
        }
    }
    // the delayed inputs of an automaton : captured at the top of the sample
    for (int k : g.usedPreSlots) {
        fClass->addDeclCode(subst("$0 \tfFam$1Pre$2[$3];", g.ty, T(g.id), T(k), T(P)));
        for (int m = 0; m < P; m++) {
            fClass->addPreCode(Statement("", subst("fFam$0Pre$1[$2] = $3;", T(g.id), T(k), T(m), famCS(plan.aslots[m][k]))));
        }
    }
    // the inputs that differ per member : an array filled every sample, before the loop
    std::ostringstream fill;
    for (int k : g.usedASlots) {
        fill << g.ty << " " << subst("fFam$0In$1[$2];", T(g.id), T(k), T(P));
        for (int m = 0; m < P; m++) {
            fill << subst(" fFam$0In$1[$2] = $3;", T(g.id), T(k), T(m), famCS(plan.aslots[m][k]));
        }
    }
    std::ostringstream loop;
    loop << fill.str();
    // a short loop with a heavy body (a 2-D automaton's rows of six cells,
    // a hundred operations each) carries the marker that keeps clang from
    // unrolling it before the vectorizer sees it : unrolled, its body stays
    // scalar (the plate x2.9). A long loop is vectorized as it is, and the
    // marker would only cost it the unrolling of its vector loop (the
    // vocoder's 32 cells : x1.23) ; a light body or a run of one to three
    // cells is better off unrolled than masked into one vector iteration
    // (the small automata x1.3 to x2.1). The weight is the number of private
    // nodes per cell.
    const int kFamLoopMarkerMax  = 16;
    const int kFamLoopMarkerMin  = 4;
    const int kFamLoopWeightMin  = 20;
    const int weight             = (int)plan.priv.size() / std::max(1, P);
    if (trace) {
        std::cerr << "FAM LOOP family " << g.id << " : " << P << " cells, weight " << weight << " (" << plan.priv.size()
                  << " private nodes)" << std::endl;
    }
    auto body = [&](const std::string& acc, int lo, int hi) {
        const int cells = hi - lo;
        if (cells >= kFamLoopMarkerMin && cells < kFamLoopMarkerMax && weight >= kFamLoopWeightMin) {
            fClass->rememberNeedFamLoop();
            loop << (cells >= 8 ? " FAUST_FAM_LOOP8" : " FAUST_FAM_LOOP");
        }
        loop << " for (int c = " << lo << "; c < " << hi << "; c++) {";
        for (const std::string& l : g.body) {
            loop << " " << l;
        }
        if (acc.empty()) {
            loop << " " << name << "[c" << (plan.group ? " + o" : "") << "] = " << term << ";";
        } else {
            loop << " " << acc << " += " << term << ";";
        }
        loop << shifts.str() << " }";
    };
    if (plan.group) {
        // the automaton : the cells write the group's current generation, in
        // the New array declared by emitFamily, at their definition index c + o,
        // one loop per run of contiguous definitions (o : the run's offset)
        name = subst("fFam$0New", T(g.id));
        for (const auto& r : plan.runs) {
            loop << " { const int o = " << (plan.memberDef[r.first] - r.first) << ";";
            body("", r.first, r.second);
            loop << " }";
        }
    } else if (reduce && ranges) {
        // one accumulating loop per host over its contiguous members : the
        // same body, the same arrays ; no result array and no reduction
        name = subst("fFam$0H", T(g.id));
        for (int k : g.usedHostASlots) {
            loop << g.ty << " " << subst("fFam$0In$1v;", T(g.id), T(k));
        }
        for (size_t h = 0; h < ranges->size(); h++) {
            for (int k : g.usedHostASlots) {
                loop << " " << subst("fFam$0In$1v = $2;", T(g.id), T(k), famCS(plan.aslots[(*ranges)[h].first][k]));
            }
            loop << " " << g.ty << " " << name << h << " = 0;";
            body(name + T((int)h), (*ranges)[h].first, (*ranges)[h].second);
        }
    } else if (reduce) {
        name = subst("fFam$0Acc", T(g.id));
        loop << g.ty << " " << name << " = 0;";
        body(name, 0, P);
    } else {
        name = subst("fFam$0Out", T(g.id));
        loop << g.ty << " " << name << "[" << P << "];";
        body("", 0, P);
    }
    fClass->addExecCode(Statement("", loop.str()));
    if (trace) {
        std::cerr << "fam emitted : family " << g.id << ", " << P << " members, " << g.need.size() << " states, " << g.usedSlots.size()
                  << " tables, " << g.usedASlots.size() << " input arrays, " << g.usedHostASlots.size() << " inputs per host, "
                  << g.body.size() << " statements per member, "
                  << (plan.group ? "an automaton over " + T(plan.groupSize) + " definitions, depth " + T(plan.groupDepth)
                                 : (reduce ? (ranges ? "accumulated per host (" + T((int)ranges->size()) + " loops)" : "accumulated") : "stored in an array"))
                  << std::endl;
    }
    return true;
}

// The family as its hosts see it : host sums -> one accumulating loop per
// host over its contiguous members, the same body and arrays (the results
// in an array then one reduction per host cost E, four sums of eight
// chains, 7 to 17 % against four loops of eight) ; the outputs and the
// displays -> the array, each channel or capture reading its cell. Emitted
// once.
void ScalarCompiler::emitFamily(FamPlan& plan)
{
    if (plan.emitted || plan.trees.empty()) {
        return;
    }
    plan.emitted = true;
    const bool trace = getenv("FAUST_FAM_TRACE") != nullptr;
    std::string name, why;
    // the loop from the template : under -fir the template gets its kernels
    // first, formed once for the family ; a kernelized template the loop
    // cannot generate falls back to the plain one
    auto famLoop = [&](bool reduce, std::string& nm, std::string& w, const std::vector<std::pair<int, int>>* ranges) {
        if (gGlobal->gReconstructFIRIIRs && !plan.ktemplate) {
            famKernelizeTemplate(plan);
        }
        bool ok = emitFamilyLoop(plan, reduce, nm, w, ranges);
        if (!ok && plan.ktemplate) {
            if (trace) {
                std::cerr << "fam kernels : the kernelized template is refused (" << w << "), the plain template is used" << std::endl;
            }
            plan.ktemplate = nullptr;
            plan.thaw.clear();
            ok = emitFamilyLoop(plan, reduce, nm, w, ranges);
        }
        return ok;
    };
    if (plan.group) {
        // The automaton (LES-AUTOMATES) : the group's state arrays, one per
        // generation read, and the current generation ; the cells in the loop,
        // the other definitions (the borders) in scalar code, all writing the
        // current generation ; the shift at the end of the sample, where the
        // classic emitter shifts its copy delays, so every delayed read of the
        // group, before or after the family in the order, sees the previous
        // generations. The projections' expressions were registered at plan time.
        const int         N = plan.groupSize, D = plan.groupDepth;
        const std::string id = T(plan.id);
        for (auto& r : plan.regs) {
            setCompiledExpression(r.first, r.second);  // the projections, at every delay : the arrays
            Tree x, y;
            fFamComputed.insert(isSigDelay(r.first, x, y) ? x : r.first);
        }
        for (int d = 1; d <= D; d++) {
            fClass->addDeclCode(subst("$0 \tfFam$1S_$2[$3];", ifloat(), id, T(d), T(N)));
            fClass->addClearCode(subst("for (int j = 0; j < $2; j++) { fFam$0S_$1[j] = 0; }", id, T(d), T(N)));
        }
        fClass->addZone2(subst("$0 \tfFam$1New[$2];", ifloat(), id, T(N)));
        Tree gid, defs;
        isRec(famOrig(plan.group), gid, defs);  // the tree's group : its definitions compile with the tree's spelling
        auto def = [&](int j) {
            Tree l = defs;
            for (int k = 0; k < j; k++) {
                l = tl(l);
            }
            return hd(l);
        };
        for (int j : plan.defsBefore) {  // what the cells read at the current step
            fClass->addExecCode(Statement("", subst("fFam$0New[$1] = $2;", id, T(j), CS(def(j)))));
        }
        if (!famLoop(false, name, why, nullptr)) {
            if (trace) {
                std::cerr << "fam refused : automaton of " << plan.trees.size() << " : " << why << std::endl;
            }
            faustassert(false);  // the plan validated the loop : a refusal here would leave the group uncompiled
            return;
        }
        // the other definitions (defsAfter) are computed where the schedule
        // places their projections, after the family (generateRecProj)
        std::ostringstream shift;
        shift << "for (int j = 0; j < " << N << "; j++) {";
        for (int d = D; d >= 2; d--) {
            shift << subst(" fFam$0S_$1[j] = fFam$0S_$2[j];", id, T(d), T(d - 1));
        }
        shift << subst(" fFam$0S_1[j] = fFam$0New[j]; }", id);
        fClass->addPostCode(Statement("", shift.str()));
        plan.outName = name;
        return;
    }
    const bool  sums = !plan.hosts.empty() && plan.hosts[0] != nullptr;
    std::vector<std::pair<int, int>> ranges;
    if (sums) {
        for (size_t h = 0; h < plan.hosts.size(); h++) {
            int lo = -1, hi = -1;
            for (size_t m = 0; m < plan.memberHost.size(); m++) {
                if (plan.memberHost[m] == (int)h) {
                    lo = (lo < 0) ? (int)m : lo;
                    hi = (int)m + 1;
                }
            }
            ranges.push_back({lo, hi});
        }
    }
    if (!famLoop(sums, name, why, sums ? &ranges : nullptr)) {
        if (trace) {
            std::cerr << "fam refused : family of " << plan.trees.size() << " : " << why << std::endl;
        }
        return;
    }
    plan.outName = name;
    if (sums) {
        for (size_t h = 0; h < plan.hosts.size(); h++) {
            plan.hostExpr.push_back(name + T((int)h));
        }
        return;
    }
    for (size_t k = 0; k < plan.trees.size(); k++) {
        setCompiledExpression(famOrig(plan.trees[k]), subst("$0[$1] /* Family */", name, T((int)k)));
        fFamComputed.insert(famOrig(plan.trees[k]));
    }
}

// sig is the tree's node of a family host : the n-ary sum itself (-fam -fir,
// -fam -lsum : the plan's view is the tree), or the top of the binary chain
// the view flattened (-fam alone). The terms come from the view's sum ; the
// ones outside the family keep their normal code, the tree's
std::string ScalarCompiler::generateFamilySum(Tree sig, const tvec&, bool& ok)
{
    ok      = false;
    auto hi = fFamHost.find(sig);
    if (hi == fFamHost.end()) {
        return "";
    }
    FamPlan& plan = fFamilies[hi->second];
    emitFamily(plan);
    if (!plan.emitted || plan.hostExpr.empty()) {
        return "";
    }
    int h = 0;
    for (size_t k = 0; k < plan.hosts.size(); k++) {
        if (plan.hosts[k] && famOrig(plan.hosts[k]) == sig) {
            h = (int)k;
        }
    }
    tvec terms;
    if (!isSigSum(plan.hosts[h], terms)) {
        return "";
    }
    std::set<Tree> in(plan.trees.begin(), plan.trees.end());
    std::ostringstream oss;
    oss << "(" << plan.hostExpr[h];
    for (Tree t : terms) {
        if (in.count(t) || isZero(t)) {
            continue;
        }
        oss << " + " << famCS(t);  // a subtracted operand, negated by the view, spells (-x)
    }
    oss << " /* Family */)";
    ok = true;
    return generateCacheCode(sig, oss.str());
}

/**
 * Generate code for a FIR kernel FIR[X,C0,C1,...] = C0.X + C1.X@1 + ...
 * Three regimes : simple gain (2 coefs), unrolled sum (small or sparse),
 * loop over a coefficient table (large and dense). Ported from the fir18
 * branch (compile_scal_fir.cpp), HLS pragmas left out.
 */

// an all-ones CONTIGUOUS FIR from tap 0 with at least 4 taps : a moving
// sum, eligible for the O(1) sliding emission (y = y' + x - x@T)
static bool isSlidingSumFIR(const tvec& coef, int& T)
{
    if (coef.size() < 5) {
        return false;  // fewer than 4 taps
    }
    for (size_t i = 1; i < coef.size(); i++) {
        if (!isOne(coef[i])) {
            return false;
        }
    }
    T = int(coef.size()) - 1;
    return true;
}

string ScalarCompiler::generateFIR(Tree sig, const tvec& coefs)
{
    faustassert(coefs.size() > 1);
    constexpr int kFirLoopSize = 4;  // below this many taps, no loop
    float         density      = firDensity(coefs);
    if (coefs.size() == 2) {
        // simple gain
        std::string gain = coefCode(coefs[1]);
        std::string in   = coefCode(coefs[0]);
        return generateCacheCode(sig, subst("($0) * ($1)", gain, in));
    }
    if (int T; isSlidingSumFIR(coefs, T) && getConditionCode(sig).empty()) {
        // MOVING SUM : y(t) = y(t-1) + x(t) - x(t-T), O(1) whatever T.
        // The accumulator is a scalar state (same idiom as kMonoDelay) ;
        // its occurrences case declared the x@T read that feeds the exit.
        // Numerics : exact for ints ; float accumulators drift (judged by
        // the -double discriminator like every reassociation).
        Type        ty = getCertifiedSigType(sig);
        std::string ctype, aname;
        getTypedNames(ty, "Slide", ctype, aname);
        fClass->addDeclCode(subst("$0 \t$1State; // Sliding sum", ctype, aname));
        fClass->addClearCode(subst("$0State = 0;", aname));
        fClass->addZone2(subst("$0 \t$1;", ctype, aname));
        fClass->addZone3(subst("$0 = $0State;", aname));
        std::string enter = coefCode(coefs[0]);
        std::string leave = generateDelayAccessRaw(sig, coefs[0], T);
        fClass->addExecCode(
            Statement("", subst("$0 = $0 + $1 - $2; /* Sliding sum */", aname, enter, leave)));
        fClass->addZone3Post(subst("$0State = $0;", aname));
        return generateCacheCode(sig, aname);
    }
    {
        // LINEAR PHASE : symmetric coefficients (c_t == c_{T-1-t}) pre-add
        // the mirrored taps before multiplying -- half the products
        const int T = int(coefs.size()) - 1;
        bool      sym = (T >= 4);
        for (int t = 0; sym && t < T / 2; t++) {
            sym = (coefs[1 + t] == coefs[1 + (T - 1 - t)]);
        }
        if (sym) {  // (the sliding case returned above)
            std::ostringstream oss;
            string             sep = "";
            Tree               exp = coefs[0];
            oss << '(';
            for (int t = 0; t < T / 2; t++) {
                if (isZero(coefs[1 + t])) {
                    continue;
                }
                string left  = generateDelayAccessRaw(sig, exp, t);
                string right = generateDelayAccessRaw(sig, exp, T - 1 - t);
                string pair  = "(" + left + " + " + right + ")";
                if (isOne(coefs[1 + t])) {
                    oss << sep << pair;
                } else {
                    oss << sep << coefCode(coefs[1 + t]) << " * " << pair;
                }
                sep = " + ";
            }
            if (T % 2 == 1 && !isZero(coefs[1 + T / 2])) {
                oss << sep;
                if (!isOne(coefs[1 + T / 2])) {
                    oss << coefCode(coefs[1 + T / 2]) << " * ";
                }
                oss << generateDelayAccessRaw(sig, exp, T / 2);
            }
            oss << ") /* symmetric FIR */";
            return generateCacheCode(sig, oss.str());
        }
    }
    bool r1 = density * 100 < gGlobal->gMinDensity;
    bool r2 = int(coefs.size()) - 1 < kFirLoopSize;
    if (r1 || r2) {
        // unrolled : small or low-density FIR
        std::ostringstream oss;
        string             sep = "";
        Tree               exp = coefs[0];
        std::string        comment = " /* ";
        comment += r1 ? "low-density " : "";
        comment += r2 ? "small " : "";
        comment += "FIR */";
        oss << '(';
        for (unsigned int i = 1; i < coefs.size(); ++i) {
            if (isZero(coefs[i])) {
                continue;
            }
            string access = generateDelayAccessRaw(sig, exp, int(i) - 1);
            if (isOne(coefs[i])) {
                oss << sep << access;
            } else if (Tree x, y; isSigAdd(coefs[i], x, y) || isSigSub(coefs[i], x, y)) {
                oss << sep << '(' << coefCode(coefs[i]) << ") * " << access;
            } else {
                oss << sep << coefCode(coefs[i]) << " * " << access;
            }
            sep = " + ";
        }
        oss << ')' << comment;
        return generateCacheCode(sig, oss.str());
    }
    // loop over a coefficient table
    Type tc;
    for (unsigned int i = 1; i < coefs.size(); ++i) {
        Type t = getCertifiedSigType(coefs[i]);
        tc     = (i == 1) ? t : (tc | t);
    }
    std::string ctype, ctable;
    getTypedNames(tc, "FIRCoefs", ctype, ctable);

    int                mnzc = 1 << 20;  // first non-zero coefficient
    std::ostringstream coefInitStream;
    coefInitStream << "{";
    for (unsigned int i = 1; i < coefs.size(); ++i) {
        if (i > 1) {
            coefInitStream << ", ";
        }
        if (!isZero(coefs[i]) && (int(i) < mnzc)) {
            mnzc = i;
        }
        // numeric cells are spelled directly : CS's generateNumber
        // consults an occurrence mark that fresh literals (the shifted
        // kernels' leading zeros) never received (the DNN table lesson,
        // paid again by guitarix's 133-tap table)
        Tree    cf = coefs[i];
        int     ci;
        int64_t cl;
        double  cr;
        if (isSigInt(cf, &ci)) {
            coefInitStream << T(ci);
        } else if (isSigInt64(cf, &cl)) {
            coefInitStream << T(cl);
        } else if (isSigReal(cf, &cr)) {
            coefInitStream << T(cr);
        } else {
            coefInitStream << CS(cf);
        }
    }
    coefInitStream << "}";
    std::string coefInit   = coefInitStream.str();
    std::string csize      = T(int(coefs.size() - 1));
    std::string ctabledecl = subst("const $0 \t$1[$2] = $3;", ctype, ctable, csize, coefInit);
    switch (tc->variability()) {
        case kKonst:
            if (tc->computability() == kComp) {
                fClass->addDeclCode(ctabledecl);
            } else {
                // constants only computable at init time
                fClass->addDeclCode(subst("$0 \t$1[$2];", ctype, ctable, csize));
                fClass->addInitCode(
                    subst("const $0 \t$1tmp[$2] = $3;", ctype, ctable, csize, coefInit));
                fClass->addInitCode(
                    subst("for (int i = 0; i < $0; i++) { $1[i] = $1tmp[i]; }", csize, ctable));
            }
            break;
        case kBlock:
            fClass->addZone2(ctabledecl);
            break;
        case kSamp:
            fClass->addExecCode(Statement("", ctabledecl));
            break;
        default:
            faustassert(false);
    }

    Tree        exp       = coefs[0];
    std::string idxaccess = generateDelayAccessRaw(sig, exp, "ii");
    Type        ty        = getCertifiedSigType(sig);
    std::string ftype, facc;
    getTypedNames(ty, "Acc", ftype, facc);
    fClass->addExecCode(Statement("", subst("$0 \t$1 = 0;", ftype, facc)));
    std::string accloop =
        subst("for (int ii = $4; ii < $0; ii++) { $1 += $2[ii] * $3; } /* FIR acc. */",
              T(int(coefs.size() - 1)), facc, ctable, idxaccess, T(mnzc - 1));
    fClass->addExecCode(Statement("", accloop));
    return generateCacheCode(sig, facc);
}

string ScalarCompiler::generateDelayAccess(Tree sig, Tree exp, Tree delay)
{
#if OLDDELAY
    // cerr << "ScalarCompiler::generateDelayAccess sig = " << *sig << endl;
    // cerr << "ScalarCompiler::generateDelayAccess exp = " << *exp << endl;
    // cerr << "ScalarCompiler::generateDelayAccess del = " << *delay << endl;

    string code  = CS(exp);  // ensure exp is compiled to have a vector name
    int    mxd   = fOccMarkup->retrieve(exp)->getMaxDelay();
    int    count = fOccMarkup->retrieve(exp)->getDelayCount();
    bool   mono  = isSigSimpleRec(exp);
    string vecname;

    if (!getVectorNameProperty(exp, vecname)) {
        if (mxd == 0) {
            // cerr << "it is a pure zero delay : " << code << endl;
            return code;
        } else {
            cerr << "ASSERT : no vector name for : " << ppsig(exp, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }
    }

    if (mono || mxd == 0) {
        // not a real vector name but a scalar name
        return vecname;

    } else if (mxd <= count * gGlobal->gMaxCopyDelay) {
        return generateCacheCode(sig, subst("$0[$1]", vecname, CS(delay)));
#if 0 
        int d;
        if (isSigInt(delay, &d)) {
            return subst("$0[$1]", vecname, CS(delay));
        } else {
            return generateCacheCode(sig, subst("$0[$1]", vecname, CS(delay)));
        }
#endif
    } else {
        int         N   = pow2limit(mxd + 1);
        std::string idx = subst("faust_wrap_sub(IOTA, $0)&$1", CS(delay), T(N - 1));
        return generateCacheCode(sig, subst("$0[$1]", vecname, generateIotaCache(idx)));
    }
#else
    // FIX: We don't compile the delayed signal anymore. This is done by the general scheduling.
    // But we make sure the delayed signal has a vector name.

    // string    code = CS(exp);  // ensure exp is compiled to have a vector name
    std::string ctype, pname;
    getTypedNames(getCertifiedSigType(sig), "Veeec", ctype, pname);
    string    vecname = ensureVectorNameProperty(pname, exp);
    if (gGlobal->gFamilyForm) {
        // a projection of an automaton, at a constant delay : the family's
        // arrays, the family emitted first if the schedule has not reached
        // an access of its group yet (never a delay line of its own)
        std::string cell;
        int         d;
        if (isSigInt(delay, &d) && famAutoRead(exp, d, cell)) {
            return cell;
        }
    }
    if (gGlobal->gFamilyForm && isZero(delay) && fFamComputed.count(exp)) {
        // a read at delay 0 of a signal a family computes (a member of an
        // output or display family, a projection of an automaton) : its
        // expression, never a vector of its own (a display capture point
        // Delay(proj, 0) of a smoother in a family) ; the name is allocated
        // above all the same, so the numbering of the other lines stays.
        // Those signals only : any other read keeps the delay machinery
        // below, its temporaries included (the code outside the families
        // is the default's)
        std::string c;
        if (getCompiledExpression(exp, c)) {
            return c;
        }
    }
    int       mxd     = fOccMarkup->retrieve(exp)->getMaxDelay();
    DelayType dt      = analyzeDelayType(exp);
#ifdef TRACE
    std::cerr << "\nDELAYED: We expect this delayed signal to be compiled elsewhere at step "
              << fScheduleOrder[exp] << " -- " << exp << " :: " << ppsig(exp, 10) << std::endl;
#endif
    std::string result;
    switch (dt) {
        case DelayType::kNotADelay:
            faustexception("Try to compile has a delay something that is not a delay");
            result = "";
            break;

        case DelayType::kZeroDelay:
            // nobody reads this signal's history, so no vector is ever
            // declared for it : a read at delay 0 is the signal itself,
            // whatever code its own compilation produced (a name or an
            // inline expression)
            result = CS(exp);
            break;

        case DelayType::kMonoDelay:
            // stage-3 elections are only granted when the schedule places
            // every consumer of the old-value read BEFORE the write
            // (analyzeDelayTypeAux) : the bare name is order-protected,
            // no capture is ever emitted.
            result = vecname;
            break;

        case DelayType::kSingleDelay:
        case DelayType::kCopyDelay:
        case DelayType::kDenseDelay:
            result = subst("$0[$1]", vecname, CS(delay));
            break;

        case DelayType::kMaskRingDelay:
        case DelayType::kSelectRingDelay: {
            int N  = pow2limit(mxd + 1);
            int dc = 0;
            // adjacent-pair collapse (spec PAIRE-ADJACENTE) : ring@d when
            // ring@(d-1) is also read. The value at d THIS iteration is
            // the value the d-1 read produced ONE iteration earlier --
            // same cell, same bits. Seeded from memory at the tile head,
            // refreshed at the end of every loop body.
            bool cst = isSigInt(delay, &dc);
            auto has = [&](int d) {
                auto it = fAdjDelaySets.find(exp);
                return it != fAdjDelaySets.end() && it->second.count(d) > 0;
            };
            if (cst && dc >= 1 && getConditionCode(sig).empty() && has(dc) && has(dc - 1)) {
                std::string aname = getFreshID("fAdj");
                fClass->addZone2(subst("$1 \t$0;", aname, ctype));
                fClass->addZone3(
                    subst("$0 = $1[faust_wrap_sub(IOTA, $2)&$3];", aname, vecname, T(dc), T(N - 1)));
                fAdjHighs.push_back({exp, dc, aname});
                result = aname;
                break;
            }
            std::string idx = subst("faust_wrap_sub(IOTA, $0)&$1", CS(delay), T(N - 1));
            bool headSafe   = getCertifiedSigType(delay)->variability() < kSamp;
            result          = subst("$0[$1]", vecname, generateIotaCache(idx, headSafe));
            if (cst && getConditionCode(sig).empty() && has(dc + 1)) {
                // the LOW of a pair : the carried scalar one delay above
                // refreshes from whatever this read compiles to -- the
                // ORACLE path (no forced cache, zero churn) ; a raw access
                // string stays valid in the post zone, its vIota body
                // local is still in scope and pre-increment
                std::string v = generateCacheCode(sig, result);
                fAdjLows.push_back({exp, dc, v});
                return v;
            }
            break;
        }
    }
    return generateCacheCode(sig, result);

#endif
}

/**
 * Generate code for the delay mechanism. The generated code depend of the
 * maximum delay attached to exp and the "less temporaries" switch
 */
string ScalarCompiler::generateDelayVec(Tree sig, const string& exp, const string& ctype,
                                        const string& vname, int mxd, int count)
{
    string s = generateDelayVecNoTemp(sig, exp, ctype, vname, mxd, count);
    if (getCertifiedSigType(sig)->variability() < kSamp) {
        return exp;
    } else {
        return s;
    }
}

/**
 * Generate code for the delay mechanism without using temporary variables
 */

/*
    DlCodeGen g(ctype, vname, gGlobal->gVecSize, mxd);
    fClass->addDeclCode(g.globalDeclare());
    fClass->addClearCode(g.globalInit());
    fClass->addZone2(g.localDeclare());
    fClass->addZone3(g.pointerSetup());
    fClass->addZone3(g.copyGlobalToLocal());
    fClass->addPostCode(Statement(ccs, g.advance()));
    fClass->addZone3Post(g.copyLocalToGlobal());
*/
string ScalarCompiler::generateDelayVecNoTemp(Tree sig, const string& exp, const string& ctype,
                                              const string& pname, int mxd, int count)
{
    faustassert(mxd > 0);

    // We make sure to use the vector name associated with signal, or we provide one
    std::string vecname = ensureVectorNameProperty(pname, sig);
    bool        mono    = isSigSimpleRec(sig);
    // bool odocc = fOccMarkup->retrieve(sig)->hasOutDelayOccurrences();
    string    ccs = getConditionCode(sig);
    DelayType dt  = analyzeDelayType(sig);
    // fClass->addDeclCode(subst("// Normal delay $0 is of type $1", vname, nameDelayType(dt)));
    string access = generateDelayLine(dt, ctype, vecname, mxd, count, mono, exp, ccs);
    // setVectorNameProperty(sig, vname);
    return access;
#if 0
#if OLDDELAY
    if (mono) {
        return vname;
    } else if (mxd <= count * gGlobal->gMaxCopyDelay) {
        return subst("$0[0]", vname);
    } else {
        int         N   = pow2limit(mxd + 1);
        std::string idx = subst("IOTA&$0", T(N - 1));
        return subst("$0[$1]", vname, generateIotaCache(idx));
    }
#else
    switch (dt) {
        case DelayType::kZeroDelay:
            return vname;

        case DelayType::kMonoDelay:
            return vname;

        case DelayType::kSingleDelay:
        case DelayType::kCopyDelay:
        case DelayType::kDenseDelay:
            return subst("$0[0]", vname);

        case DelayType::kMaskRingDelay:
        case DelayType::kSelectRingDelay:
            int         N   = pow2limit(mxd + 1);
            std::string idx = subst("IOTA&$0", T(N - 1));
            return subst("$0[$1]", vname, generateIotaCache(idx));
    }
#endif
#endif
}

// is the compiled expression exactly a ring access, name[vIotaN] ? (the
// ring-preload form guard : such an expression reads past-tick memory
// through its index and nothing else). On success, ixname receives the
// index variable -- the caller checks it belongs to the HEAD-hoisted
// family before preloading.
static bool isPureRingAccess(const std::string& exp, std::string& ixname)
{
    std::size_t b = exp.find("[vIota");
    if (b == std::string::npos || b == 0 || exp.back() != ']') {
        return false;
    }
    for (std::size_t i = 0; i < b; i++) {
        if (!isalnum(exp[i]) && exp[i] != '_') {
            return false;
        }
    }
    for (std::size_t i = b + 6; i + 1 < exp.size(); i++) {
        if (!isdigit(exp[i])) {
            return false;
        }
    }
    ixname = exp.substr(b + 1, exp.size() - b - 2);
    return true;
}

/**
 * Generate code for the delay mechanism without using temporary variables
 */

string ScalarCompiler::generateDelayLine(DelayType dt, const string& ctype, const string& vname,
                                         int mxd, int count, bool mono, const string& exp,
                                         const string& ccs)
{
#if OLDDELAY
    if (mxd == 0) {
        cerr << "MXD==0 :  " << vname << " := " << exp << endl;
        // no need for a real vector
        if (ccs == "") {
            fClass->addExecCode(Statement(ccs, subst("$0 \t$1 = $2;", ctype, vname, exp)));
        } else {
            fClass->addZone2(subst("$0 \t$1 = 0;", ctype, vname));
            fClass->addExecCode(Statement(ccs, subst("\t$0 = $1;", vname, exp)));
        }

    } else if (mono || (mxd <= count * gGlobal->gMaxCopyDelay)) {
        // Generate code for short or dense delay lines
        DlCodeGen g(ctype, vname, gGlobal->gVecSize, mxd, mono);
        fClass->addDeclCode(g.globalDeclare());
        fClass->addClearCode(g.globalInit());
        fClass->addZone2(g.localDeclare());
        fClass->addZone3(g.pointerSetup());
        fClass->addZone3(g.copyGlobalToLocal());
        if (mono) {
            fClass->addExecCode(Statement(ccs, subst("$0 = $1;", vname, exp)));
        } else {
            fClass->addExecCode(Statement(ccs, subst("$0[0] = $1;", vname, exp)));
        }
        fClass->addPostCode(Statement(ccs, g.advance()));
        fClass->addZone3Post(g.copyLocalToGlobal());

    } else {
        // generate code for a long delay : we use a ring buffer of size N = 2**x > mxd
        int N = pow2limit(mxd + 1);

        // we need an iota index
        fMaxIota = 0;

        // declare and init
        fClass->addDeclCode(subst("$0 \t$1[$2];", ctype, vname, T(N)));
        fClass->addClearCode(subst("for (int i=0; i<$1; i++) $0[i] = 0;", vname, T(N)));

        // execute
        std::string idx = subst("IOTA&$0", T(N - 1));
        fClass->addExecCode(
            Statement(ccs, subst("$0[$1] = $2;", vname, generateIotaCache(idx), exp)));
    }
#else
    std::string preIx;  // ring-preload : the index name of a pure ring access
    switch (dt) {
        case DelayType::kNotADelay:
            faustexception("Try to compile has a delay something that is not a delay");
            return "";

        case DelayType::kZeroDelay:
            // cerr << "MXD==0 :  " << vname << " := " << exp << endl;
            // no need for a real vector
            if (ccs == "") {
                fClass->addExecCode(
                    Statement(ccs, subst("$0 \t$1 = $2; // Zero delay", ctype, vname, exp)));
            } else {
                fClass->addZone2(subst("$0 \t$1 = 0;", ctype, vname));
                fClass->addExecCode(Statement(ccs, subst("\t$0 = $1;", vname, exp)));
            }
            return vname;

        case DelayType::kMonoDelay:
            fClass->addDeclCode(subst("$0 \t$1State; // Mono Delay", ctype, vname));
            fClass->addClearCode(subst("$0State = 0;", vname));
            fClass->addZone2(subst("$0 \t$1;", ctype, vname));
            fClass->addZone3(subst("$0 = $0State;", vname));
            if (gGlobal->gRingPreload && ccs.empty() && isPureRingAccess(exp, preIx) &&
                fIotaHeadNames.count(preIx)) {
                // Ring-preload prototype (the freeverb family) : the ring
                // LOAD issues at the head of the loop body, where the whole
                // family batches -- the cache misses overlap instead of
                // serializing one per stage -- while the architectural
                // update of the mono scalar stays at its original slot as a
                // register move : every consumer keeps reading exactly the
                // value it read before, no one-sample shift. The guard is
                // the FORM : only an expression that is exactly
                // name[vIotaN] moves -- its only inputs are the head-hoisted
                // index and past-tick memory -- a compound expression has
                // per-sample dependencies not yet computed at the head.
                fClass->addZone2(subst("$0 \t$1Pre;", ctype, vname));
                fClass->addPreCode(Statement(ccs, subst("$0Pre = $1;", vname, exp)));
                fClass->addExecCode(Statement(ccs, subst("$0 = $0Pre;", vname)));
            } else {
                fClass->addExecCode(Statement(ccs, subst("$0 = $1;", vname, exp)));
            }
            fClass->addZone3Post(subst("$0State = $0;", vname));
            return vname;

        case DelayType::kSingleDelay:
            if (ccs.empty()) {
                // candidate for the schedule-verified demotion to scalar
                // (see the peephole at the end of compileMultiSignal)
                fSingleDelayScalarCandidates.push_back(vname);
            }
            fClass->addDeclCode(subst("$0 \t$1State; // Single Delay", ctype, vname));
            fClass->addClearCode(subst("$0State = 0;", vname));
            fClass->addZone2(subst("$0 \t$1[$2];", ctype, vname, T(mxd + 1)));
            fClass->addZone3(subst("$0[1] = $0State;", vname));
            if (gGlobal->gRingPreload && ccs.empty() && isPureRingAccess(exp, preIx) &&
                fIotaHeadNames.count(preIx)) {
                // Ring-preload prototype (the freeverb family) : the ring
                // LOAD issues at the head of the loop body, where the whole
                // family batches -- the cache misses overlap instead of
                // serializing one per stage -- while the [2]-vector update
                // stays at its original slot as a register move, so every
                // consumer keeps reading exactly the value it read before.
                // The Pre scalar does not count as a touch of the vector for
                // the demotion peephole (word-boundary scan), and the write
                // keeps its "$0[0] = " shape, so the demotion still applies.
                fClass->addZone2(subst("$0 \t$1Pre;", ctype, vname));
                fClass->addPreCode(Statement("", subst("$0Pre = $1;", vname, exp)));
                fClass->addExecCode(Statement("", subst("$0[0] = $0Pre;", vname)));
            } else {
                fClass->addExecCode(Statement(ccs, subst("$0[0] = $1;", vname, exp)));
            }
            fClass->addPostCode(Statement("", subst("$0[1] = $0[0];", vname)));
            fClass->addZone3Post(subst("$0State = $0[1];", vname));
            return subst("$0[0]", vname);

        case DelayType::kCopyDelay:
            fClass->addDeclCode(subst("$0 \t$1State[$2]; // Copy Delay", ctype, vname, T(mxd)));
            fClass->addClearCode(
                subst("for (int j = 0; j < $0; j++) { $1State[j] = 0; }", T(mxd), vname));
            fClass->addZone2(subst("$0 \t$1[$2];", ctype, vname, T(mxd + 1)));
            for (int j = 0; j < mxd; j++) {
                fClass->addZone3(subst("$0[$1] = $0State[$2];", vname, T(j + 1), T(j)));
            }
            fClass->addExecCode(Statement(ccs, subst("$0[0] = $1;", vname, exp)));
            for (int j = 0; j < mxd; j++) {
                // warning ; line stacked in reverse order !!!
                fClass->addPostCode(
                    Statement("", subst("$0[$1] = $0[$2];", vname, T(j + 1), T(j))));
            }
            for (int j = 0; j < mxd; j++) {
                fClass->addZone3Post(subst("$0State[$1] = $0[$2];", vname, T(j), T(j + 1)));
            }
            return subst("$0[0]", vname);

        case DelayType::kDenseDelay:

            // the window is anchored at Cache + gVecSize - 1 and walks one
            // slot down per sample : only valid for count <= gVecSize, so
            // the compute skeleton must chunk (never the flat variant)
            fClass->setBlockBound();
            fClass->addDeclCode(subst("$0 \t$1State[$2]; // Dense Delay", ctype, vname, T(mxd)));
            fClass->addClearCode(
                subst("for (int j = 0; j < $0; j++) { $1State[j] = 0; }", T(mxd), vname));
            fClass->addZone2(
                subst("$0 \t$1Cache[$2+$3];", ctype, vname, T(gGlobal->gVecSize), T(mxd)));
            fClass->addZone3(
                subst("$0* \t$1 = $1Cache + $2 - 1;", ctype, vname, T(gGlobal->gVecSize)));
            fClass->addZone3(
                subst("for (int j = 0; j < $0; j++) { $1[j+1] = $1State[j]; }", T(mxd), vname));
            fClass->addExecCode(Statement(ccs, subst("$0[0] = $1;", vname, exp)));
            fClass->addPostCode(Statement("", subst("--$0;", vname)));
            fClass->addZone3Post(
                subst("for (int j = 0; j < $0; j++) { $1State[j] = $1[j+1]; }", T(mxd), vname));
            return subst("$0[0]", vname);

        case DelayType::kMaskRingDelay:
        case DelayType::kSelectRingDelay:

            // generate code for a long delay : we use a ring buffer of size N = 2**x > mxd
            int N = pow2limit(mxd + 1);

            // we need an iota index
            fMaxIota++;
            // std::cerr << "MaxIota increased" << std::endl;

            // declare and init
            fClass->addDeclCode(subst("$0 \t$1[$2]; // Ring Delay", ctype, vname, T(N)));
            fClass->addClearCode(subst("for (int i = 0; i < $1; i++) { $0[i] = 0; }", vname, T(N)));

            // execute (the write index is pure IOTA : always head-safe)
            std::string idx      = subst("IOTA&$0", T(N - 1));
            std::string cacheidx = generateIotaCache(idx, true);
            fClass->addExecCode(Statement(ccs, subst("$0[$1] = $2;", vname, cacheidx, exp)));
            return subst("$0[$1]", vname, cacheidx);
    }
#endif
}

/**
 * Generate code for a unique IOTA variable increased at each sample
 * and used to index delay buffers.
 */
void ScalarCompiler::ensureIotaCode()
{
    // std::cerr << "ensureIotaCode called " << fMaxIota << std::endl;
    if (fMaxIota >= 0) {
        fClass->addDeclCode("int \tIOTA;");
        fClass->addClearCode(subst("IOTA = $0;", T(fMaxIota)));
        fClass->addPostCode(Statement("", "IOTA = faust_wrap_add(IOTA, 1);"));
    }
}

/*****************************************************************************
 WAVEFORM
 *****************************************************************************/

/**
 * Generate code for a waveform. The waveform will be declared as a static field.
 * The name of the waveform is returned in vname and its size in size.
 */
void ScalarCompiler::declareWaveform(Tree sig, string& vname, int& size)
{
    // computes C type and unique name for the waveform
    string ctype;
    getTypedNames(getCertifiedSigType(sig), "Wave", ctype, vname);

    size = sig->arity();

    // Converts waveform into a string : "{a,b,c,...}"
    stringstream content;

    char sep = '{';
    for (int i = 0; i < size; i++) {
        content << sep << ppsig(sig->branch(i));
        sep = ',';
    }
    content << '}';

    // Declares the Waveform
    fClass->addDeclCode(subst("static $0 \t$1[$2];", ctype, vname, T(size)));
    fClass->addDeclCode(subst("int \tidx$0;", vname));
    fClass->addInitCode(subst("idx$0 = 0;", vname));
    fClass->getTopParentKlass()->addStaticFields(
        subst("$0 \t$1::$2[$3] = ", ctype, fClass->getFullClassName(), vname, T(size)) +
        content.str() + ";");
}

string ScalarCompiler::generateWaveform(Tree sig)
{
    string vname;
    int    size;

    declareWaveform(sig, vname, size);
    fClass->addPostCode(
        Statement(getConditionCode(sig), subst("idx$0 = (idx$0 + 1) % $1;", vname, T(size))));
    return generateCacheCode(sig, subst("$0[idx$0]", vname));
}
