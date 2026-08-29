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
#include "superNodes.hh"
#include "revealFIR.hh"
#include "revealIIR.hh"
#include <pthread.h>

#include "placeTemps.hh"
#include "reassociate.hh"
#include "nestSums.hh"
#include "revealSum.hh"
#include "descend.hh"
#include "factorizeFIRs.hh"
#include "kernelCandidacy.hh"
#include "groupPlan.hh"
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

// compact printer for shape trees (holes abbreviated, depth-capped)
static void ocppShapePrint(Tree t, std::ostream& out, int depth)
{
    Sym s;
    if (isSym(t->node(), &s)) {
        std::string n = name(s);
        if (n == "SHAPE_HOLE_F") {
            out << "□f";
        } else if (n == "SHAPE_HOLE_I") {
            out << "□i";
        } else if (n == "SHAPE_HOLE_IN") {
            out << "□in";
        } else if (n == "SHAPE_HOLE_REF") {
            out << "□";
        } else if (n == "SHAPE_HOLE_CYCLE") {
            out << "□@";
        } else {
            out << (n.rfind("Sig", 0) == 0 ? n.substr(3) : n);
            if (t->arity() > 0) {
                if (depth <= 0) {
                    out << "(…)";
                    return;
                }
                out << "(";
                for (int i = 0; i < t->arity(); i++) {
                    if (i) {
                        out << ",";
                    }
                    ocppShapePrint(t->branch(i), out, depth - 1);
                }
                out << ")";
            }
        }
    } else {
        out << t->node();
    }
}

// FAUST_SS_SHAPES=1 : the shape statistics of the scheduled graph -- how
// many nodes live in shapes of multiplicity >= 4 (the SLP packing
// threshold: the Bank move's raw material), and the top shapes.
static void ocppShapeStats(const digraph<Tree>& G)
{
    std::set<Tree, treeorder> inG(G.nodes().begin(), G.nodes().end());
    std::map<Tree, Tree, treeorder> memo;
    std::map<Tree, int, treeorder>  count;
    for (const Tree& t : G.nodes()) {
        std::set<Tree, treeorder> onstack;
        count[ocppShape(t, inG, memo, onstack)]++;
    }
    int total = int(G.nodes().size()), bankable = 0, distinct = int(count.size());
    std::vector<std::pair<int, Tree>> top;
    for (const auto& [sh, c] : count) {
        if (c >= 4) {
            bankable += c;
        }
        top.push_back({c, sh});
    }
    std::sort(top.begin(), top.end(),
              [](const auto& a, const auto& b) { return a.first > b.first; });
    std::cerr << "SS_SHAPES nodes=" << total << " distinct=" << distinct
              << " bankable=" << (total ? 100 * bankable / total : 0) << "%";
    for (size_t i = 0; i < top.size() && i < 5; i++) {
        std::cerr << "  " << top[i].first << "x ";
        ocppShapePrint(top[i].second, std::cerr, 3);
    }
    std::cerr << std::endl;
    // FAUST_SS_SHAPES=full : the whole histogram, one line per shape
    const char* env = getenv("FAUST_SS_SHAPES");
    if (env != nullptr && std::string(env) == "full") {
        for (const auto& [c, sh] : top) {
            std::cerr << "SS_SHAPE " << c << " ";
            ocppShapePrint(sh, std::cerr, 4);
            std::cerr << '\n';
        }
    }
}

// the shape functor for a given graph: boundary = the graph's node set
static std::function<long(const Tree&)> ocppShapeFunctor(const digraph<Tree>& G)
{
    auto inG  = std::make_shared<std::set<Tree, treeorder>>(G.nodes().begin(), G.nodes().end());
    auto memo = std::make_shared<std::map<Tree, Tree, treeorder>>();
    return [inG, memo](const Tree& t) -> long {
        std::set<Tree, treeorder> onstack;
        return (long)(size_t)ocppShape(t, *inG, *memo, onstack);
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
                // FAUST_SS_BANKCAP : experimental override of the bank cap
                // (0 = auto max(R, U)) while the right coupling is calibrated
                unsigned int bc = 0;
                if (const char* e = getenv("FAUST_SS_BANKCAP")) {
                    bc = unsigned(std::atoi(e));
                }
                // FAUST_SS_STAGEC=df : stage C experiment (vertical columns)
                int sc = 0;
                if (const char* e = getenv("FAUST_SS_STAGEC")) {
                    sc = (std::string(e) == "df") ? 1 : (std::string(e) == "layers") ? 2 : 0;
                }
                return bankschedule(G, gGlobal->gLSRegisters, gGlobal->gLSWidth,
                                    ocppShapeFunctor(G), bc, sc,
                                    getenv("FAUST_SS_BANKSTATS") != nullptr);
            }
        case 11:
        case 12:
            // CSSCHEDULE v3 (spec faust-migration/CSSCHEDULE.md) :
            // dominator blocks, K-wide frontiers, Pareto-beam grid
            // combination under (R,U), ASAP closure as the only R
            // certificate. The best trace is emitted even when no
            // candidate closes under R -- hard R is a certificate, not a
            // validity condition ; feasibility is reported under
            // MONODEBUG. K from FAUST_SS_CS2K (default 4).
            // 11 = depth-first spine, 12 = breadth-first spine (wide,
            // parallel -- fdnRev and paradigma clientele).
            {
                unsigned int k2 = 4;
                if (const char* e = getenv("FAUST_SS_CS2K")) {
                    k2 = unsigned(std::max(1, std::atoi(e)));
                }
                long b2 = 1000000;  // global cell budget (FAUST_SS_CS2BUDGET)
                if (const char* e = getenv("FAUST_SS_CS2BUDGET")) {
                    b2 = std::max(100000L, std::atol(e));
                }
                // spine from the strategy ; FAUST_SS_CS2SPINE=bf|df is the
                // forensic override for A/B comparisons
                bool bfsp = (gGlobal->gSchedulingStrategy == 12);
                if (const char* e = getenv("FAUST_SS_CS2SPINE")) {
                    bfsp = (std::string(e) == "bf");
                }
                bool           feas = true;
                cs2stats       st;
                schedule<Tree> S2   = csschedule2(G, gGlobal->gLSRegisters, gGlobal->gLSWidth,
                                                  k2, &feas, b2, &st, bfsp);
                if (getenv("FAUST_SS_MONODEBUG")) {
                    std::cerr << "CS2 feasible-under-R=" << feas
                              << " R=" << gGlobal->gLSRegisters << " pairs=" << st.pairs
                              << " degraded=" << st.degraded << " cells=" << st.cells << "/"
                              << b2 << std::endl;
                }
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

// FAUST_SS_QUALITY=1 : print the quality vector (U x cycles grid of the
// model) of the chosen order -- fill = occupied / available slots. The
// fill is that of the ABSTRACT machine (latency 1, U slots) ; the
// diagnostic question : is a fill effort needed, or does the residue
// live elsewhere (isomorphic adjacency, memory regimes) ?
static schedule<Tree> ocppSchedule(const digraph<Tree>& G)
{
    schedule<Tree> S = ocppScheduleRaw(G);
    if (getenv("FAUST_SS_CHECK")) {
        // is the immediate graph a DAG, and does the emitted order
        // respect it ? (every present edge is a hard constraint : the
        // dependency must be scheduled before its consumer)
        auto H       = graph2dag(G);
        int  ncyclic = 0, maxscc = 0;
        for (const auto& scc : H.nodes()) {
            int n = int(scc.nodes().size());
            if (n > 1) {
                ncyclic++;
                maxscc = std::max(maxscc, n);
            }
        }
        std::map<Tree, int> pos;
        int                 k = 0;
        auto                E = S.elements();
        for (const auto& s : E) {
            pos[s] = k++;
        }
        int nviol = 0;
        for (const auto& u : G.nodes()) {
            for (const auto& d : G.destinations(u)) {
                if (pos[d.first] > pos[u]) {
                    if (nviol < 3) {
                        std::cerr << "SS_CHECK violation: dep at " << pos[d.first]
                                  << " scheduled after consumer at " << pos[u]
                                  << " (edge weight " << d.second << ")" << std::endl;
                    }
                    nviol++;
                }
            }
        }
        std::cerr << "SS_CHECK ss=" << gGlobal->gSchedulingStrategy
                  << " nodes=" << G.nodes().size() << " sccs>1=" << ncyclic
                  << " maxscc=" << maxscc << " violations=" << nviol << std::endl;
    }
    if (getenv("FAUST_SS_SHAPES")) {
        ocppShapeStats(G);
    }
    if (const char* qenv = getenv("FAUST_SS_QUALITY")) {
        // value "R,U" : EVALUATION machine (compare orders generated
        // with different settings against one reference) ; any other
        // value : the generation settings
        unsigned R = gGlobal->gLSRegisters, U = gGlobal->gLSWidth;
        unsigned r2, u2;
        if (sscanf(qenv, "%u,%u", &r2, &u2) == 2 && u2 > 0) {
            R = r2;
            U = u2;
        }
        // memory classification at Tree grain : a delayed read (dmin >= 1)
        // is a buffer load, an input is a stream load. Writes are folded
        // into their producer (v1 approximation). M from FAUST_SS_M
        // (default 3, the M-series load/store width).
        auto memf = std::function<bool(const Tree&)>(ocppIsMemNode);
        unsigned M = 3;
        if (const char* me = getenv("FAUST_SS_M")) {
            M = unsigned(std::atoi(me));
        }
        schedquality q = squality(G, S.elements(), R, U, ocppShapeFunctor(G), memf, M);
        double fill = (q.cycles > 0) ? 100.0 * double(S.size()) / (double(q.cycles) * U) : 0;
        std::cerr << "SS_QUALITY ss=" << gGlobal->gSchedulingStrategy << " nodes=" << S.size()
                  << " cycles=" << q.cycles << " holes=" << q.holes << " fill=" << int(fill)
                  << "% peak=" << q.peak << " isoadj=" << q.isoadj << " packs4=" << q.packs4
                  << " r4n=" << q.r4n << " maxrun=" << q.maxrun << " cplen=" << q.cplen
                  << " cpdil=" << q.cpdil << " cpmax=" << q.cpmax;
        {
            schedule<Tree> SS;
            for (const auto& n : S.elements()) {
                SS.append(n);
            }
            std::cerr << " scost=" << schedulingcost(G, SS) / std::max<size_t>(S.size(), 1);
        }
        std::cerr << " nmem=" << q.nmem << " aluMII=" << q.aluMII << " memMII=" << q.memMII;
        std::cerr << std::endl;
    }
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
    const int tau = getenv("FAUST_GATEQUIV_TAU") ? atoi(getenv("FAUST_GATEQUIV_TAU")) : 12;
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

    // selectN census (FAUST_SELECTN_CENSUS=1) : how many select2 chains
    // or trees share a COMMON selector expression -- the spellings of a
    // semantic N-way selection (ba.selectn builds balanced trees of
    // select2 on (i >= k) range tests ; the DNF atom explosion of
    // lazyselect measures this ENCODING, not real program complexity).
    // Census only : counts and shapes, no transformation.
    if (getenv("FAUST_SELECTN_CENSUS")) {
        std::map<Tree, std::vector<Tree>> families;  // base selector -> select2 nodes
        std::set<Tree>                    seenC;
        std::function<Tree(Tree)> baseOf = [&](Tree sel) -> Tree {
            // the comparison's common expression, through int casts
            int  op;
            Tree a, b, xx;
            if (isSigBinOp(sel, &op, a, b) &&
                (op == kGT || op == kLT || op == kGE || op == kLE || op == kEQ || op == kNE)) {
                Tree base = a;
                if (isSigIntCast(a, xx)) {
                    base = xx;
                }
                int  iv;
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
                Tree base = baseOf(sel);
                if (base != nullptr) {
                    families[base].push_back(t);
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
        walkC(L2);
        int nfam = 0, nsel = 0, biggest = 0;
        for (const auto& f : families) {
            if ((int)f.second.size() >= 2) {
                nfam++;
                nsel += (int)f.second.size();
                biggest = std::max(biggest, (int)f.second.size());
            }
        }
        int singles = 0;
        for (const auto& f : families) {
            if ((int)f.second.size() == 1) {
                singles++;
            }
        }
        // The funnel (spec LE-SELECTN v2, Codex review) : families are an
        // upper bound. A tree is CERTIFIED iff monotone inequalities only
        // and its leaf intervals form the exact anchored saturated
        // partition (-inf,0], {1}.. or grouped middles, [N-1,+inf) -- the
        // ba.selectn spelling. Interval propagation, no unions (==/!=
        // excluded), verify-everything-or-drop.
        const long long INF = 0x3FFFFFFFFFFFLL;
        struct IvLeaf {
            long long lo, hi;
            Tree      leaf;
        };
        int ntrees = 0, ncert = 0, ncertsel = 0, nbranches = 0, maxN = 0;
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
                ntrees++;
                // DFS with interval [lo,hi] ; convention select2(c,x,y)=c?y:x
                std::vector<IvLeaf>  leaves;
                bool                 ok    = true;
                int                  nsize = 0;
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
                        nsize++;
                        Tree sel, x, y, a, b;
                        int  op, k;
                        isSigSelect2(t, sel, x, y);
                        if (!isSigBinOp(sel, &op, a, b)) {
                            ok = false;
                            return;
                        }
                        bool intmode = isSigInt(b, &k);
                        if (!intmode) {
                            // real mode : integral thresholds, kGE/kLT ONLY --
                            // with these two ops every split is half-open [k,..)
                            // and the interval [k,k+1) identifies with the
                            // integer pair [k,k], so selector int(x) is exact
                            // (NaN corner excepted, the gatequiv-admitted one)
                            double rr;
                            if (!isSigReal(b, &rr) || rr != (double)(long long)rr ||
                                (op != kGE && op != kLT)) {
                                ok = false;
                                return;
                            }
                            k = (int)(long long)rr;
                        }
                        long long tlo, thi, flo, fhi;  // true side (y), false side (x)
                        switch (op) {
                            case kGE: tlo = k;      thi = hi;    flo = lo;    fhi = k - 1; break;
                            case kGT: tlo = k + 1;  thi = hi;    flo = lo;    fhi = k;     break;
                            case kLT: tlo = lo;     thi = k - 1; flo = k;     fhi = hi;    break;
                            case kLE: tlo = lo;     thi = k;     flo = k + 1; fhi = hi;    break;
                            default:  ok = false; return;  // ==/!= : unions, hors V1
                        }
                        dive(x, std::max(flo, lo), std::min(fhi, hi));
                        dive(y, std::max(tlo, lo), std::min(thi, hi));
                    };
                // diagnostic : la nature du selecteur racine des gros arbres
                if (getenv("FAUST_SELECTN_DEBUG") && (int)f.second.size() >= 8) {
                    Tree sel, x, y, a, b;
                    int  op, k;
                    isSigSelect2(root, sel, x, y);
                    if (isSigBinOp(sel, &op, a, b)) {
                        int    kk;
                        double rr;
                        if (isSigInt(b, &kk)) {
                            fprintf(stderr, "  racine: op=%d rhs=int %d\n", op, kk);
                        } else if (isSigReal(b, &rr)) {
                            fprintf(stderr, "  racine: op=%d rhs=real %g\n", op, rr);
                        } else {
                            fprintf(stderr, "  racine: op=%d rhs=EXPR\n", op);
                        }
                    } else if (false) {
                        fprintf(stderr, "  racine: selecteur non-binop\n");
                    }
                }
                dive(root, -INF, INF);
                if (!ok || leaves.size() < 3) {
                    if (getenv("FAUST_SELECTN_DEBUG") && nsize >= 4) {
                        fprintf(stderr, "  arbre rejete en descente (%d selects, ok=%d, feuilles=%zu)\n",
                                nsize, (int)ok, leaves.size());
                    }
                    continue;  // N >= 3 (decision Yann/Codex)
                }
                std::sort(leaves.begin(), leaves.end(),
                          [](const IvLeaf& u, const IvLeaf& v) { return u.lo < v.lo; });
                // anchored saturated partition : (-inf,0], [1..], contiguous,
                // last reaches +inf ; grouped middles allowed
                bool part = leaves.front().lo == -INF && leaves.front().hi == 0 &&
                            leaves.back().hi == INF;
                for (size_t i = 1; part && i < leaves.size(); i++) {
                    if (leaves[i].lo != leaves[i - 1].hi + 1) {
                        part = false;
                    }
                }
                if (part) {
                    ncert++;
                    ncertsel += nsize;
                    int N = (int)leaves.back().lo + 1;
                    nbranches += N;
                    maxN = std::max(maxN, N);
                } else if (getenv("FAUST_SELECTN_DEBUG") && nsize >= 8) {
                    fprintf(stderr, "  arbre non-certifie (%d selects, %zu feuilles) intervalles:",
                            nsize, leaves.size());
                    for (size_t i = 0; i < std::min(leaves.size(), (size_t)12); i++) {
                        fprintf(stderr, " [%lld,%lld]",
                                leaves[i].lo == -INF ? -99 : leaves[i].lo,
                                leaves[i].hi == INF ? 99 : leaves[i].hi);
                    }
                    fprintf(stderr, "%s\n", leaves.size() > 12 ? " ..." : "");
                } else if (getenv("FAUST_SELECTN_DEBUG") && !ok && nsize >= 8) {
                    fprintf(stderr, "  arbre rejete en descente (%d selects) : op non-monotone ou intervalle vide\n", nsize);
                }
            }
        }
        fprintf(stderr,
                "SELECTN_CENSUS familles=%d selects=%d arbres=%d certifies=%d "
                "selects_certifies=%d branches=%d maxN=%d isolees=%d\n",
                nfam, nsel, ntrees, ncert, ncertsel, nbranches, maxN, singles);
    }

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
    if ((gGlobal->gLowerSums || getenv("FAUST_LOWERSUMS")) && !gGlobal->gReconstructFIRIIRs &&
        !hasEnableControl(L2)) {
        // -lsum STANDALONE (the old_freeverb bisection, 2026-08-18) :
        // lowerSums was trapped inside the -fir reveal lambda -- alone it
        // was a silent no-op. It needs revealSum's n-ary rows but NOT the
        // kernel injection (-fir costs +46 muls on old_freeverb : kernels
        // revealed where they do not pay). Own big-stack thread, the
        // reveal precedent.
        std::function<void()> lsOnly = [&]() {
            startTiming("Sum revealer (lsum standalone)");
            L2 = revealSum(L2);
            endTiming("Sum revealer (lsum standalone)");
            startTiming("Sum lowering");
            std::set<Tree> keepRows;
            if ((gGlobal->gMatrixRows || getenv("FAUST_MATRIX_ROWOP"))) {
                // matrix rows stay n-ary through the lowering : the -ls
                // row-op regime consumes them whole (spec LA-FORME-MATRICE)
                for (auto& [row, id] : revealMatrix(L2).rowOf) {
                    keepRows.insert(row);
                }
            }
            L2 = lowerSums(L2, keepRows.empty() ? nullptr : &keepRows);
            endTiming("Sum lowering");
        };
        pthread_attr_t lsattr;
        pthread_attr_init(&lsattr);
        pthread_attr_setstacksize(&lsattr, size_t(2048) << 20);
        pthread_t lsth;
        auto      lstramp = [](void* q) -> void* {
            (*static_cast<std::function<void()>*>(q))();
            return nullptr;
        };
        if (pthread_create(&lsth, &lsattr, lstramp, &lsOnly) == 0) {
            pthread_join(lsth, nullptr);
        } else {
            lsOnly();
        }
        pthread_attr_destroy(&lsattr);
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
        pthread_attr_t gqattr;
        pthread_attr_init(&gqattr);
        pthread_attr_setstacksize(&gqattr, size_t(2048) << 20);
        pthread_t gqth;
        auto      gqtramp = [](void* q) -> void* {
            (*static_cast<std::function<void()>*>(q))();
            return nullptr;
        };
        if (pthread_create(&gqth, &gqattr, gqtramp, &gq) == 0) {
            pthread_join(gqth, nullptr);
        } else {
            gq();
        }
        pthread_attr_destroy(&gqattr);
    }
    if (gGlobal->gReconstructFIRIIRs) {
        // -fir stage 1 : the revealed kernels are INJECTED into the
        // pipeline -- n-ary sums (revealSum) then FIR kernels (revealFIR).
        // revealIIR waits for its typing rule (WCPG, see PILE n.12). The
        // reveal recursions are as deep as the signal graph : dedicated
        // big-stack thread, joined immediately (thunder, drumkit).
        std::function<void()> reveal = [&]() {
            startTiming("Sum revealer");
            L2 = revealSum(L2);
            endTiming("Sum revealer");
            startTiming("FIR revealer");
            L2 = revealFIR(L2);
            endTiming("FIR revealer");
            startTiming("IIR revealer");
            L2 = revealIIR(L2);
            endTiming("IIR revealer");
            startTiming("FIR factorizer");
            L2 = factorizeFIRs(L2);
            L2 = kernelCandidacy(L2);  // the retiming law, per site
            if (getenv("FAUST_MATRIX_CENSUS")) {
                revealMatrix(L2);  // analysis only : the fourth gathering's census
            }
            endTiming("FIR factorizer");
            if (getenv("FAUST_SS_MCM")) {
                // stage-3 deposit probe : the WEIGHTED pairs. Atom of a
                // term : c*x -> (x, numeric c) ; x -> (x, 1). An
                // extraction a+lambda*b serves the rows where wb/wa is
                // the same lambda : pairs are bucketed by ratio and the
                // saving is bounded by the sum of (count-1) over the
                // buckets of size >= 2.
                std::vector<std::vector<std::pair<Tree, double>>> rows;
                {
                    std::set<Tree>    seen;
                    std::vector<Tree> work{L2};
                    while (!work.empty()) {
                        Tree t = work.back();
                        work.pop_back();
                        if (!seen.insert(t).second) continue;
                        Tree var, body;
                        if (isRec(t, var, body)) {
                            if (body) work.push_back(body);
                            continue;
                        }
                        if (tvec subs; isSigSum(t, subs)) {
                            std::vector<std::pair<Tree, double>> row;
                            for (Tree s2 : subs) {
                                Tree   a, b;
                                double w = 1.0, num;
                                int    inum;
                                Tree   at = s2;
                                if (isSigMul(s2, a, b) &&
                                    (isSigReal(a, &num) || (isSigInt(a, &inum) && (num = inum, true)))) {
                                    w  = num;
                                    at = b;
                                } else if (isSigMul(s2, a, b) &&
                                           (isSigReal(b, &num) ||
                                            (isSigInt(b, &inum) && (num = inum, true)))) {
                                    w  = num;
                                    at = a;
                                }
                                row.push_back({at, w});
                            }
                            rows.push_back(std::move(row));
                        }
                        for (int k = 0; k < t->arity(); k++) work.push_back(t->branch(k));
                    }
                }
                std::map<std::tuple<Tree, Tree, long long>, int> buckets;
                long terms = 0;
                for (auto& row : rows) {
                    terms += long(row.size());
                    for (size_t i2 = 0; i2 < row.size(); i2++) {
                        for (size_t j2 = i2 + 1; j2 < row.size(); j2++) {
                            Tree   a = row[i2].first, b = row[j2].first;
                            double wa = row[i2].second, wb = row[j2].second;
                            if (a == b || wa == 0.0) continue;
                            treeorder lt;
                            if (lt(b, a)) {
                                std::swap(a, b);
                                std::swap(wa, wb);
                            }
                            long long q = (long long)(std::llround((wb / wa) * 1e9));
                            buckets[{a, b, q}]++;
                        }
                    }
                }
                long pot1 = 0, potw = 0, bigw = 0;
                for (auto& [k2, c2] : buckets) {
                    if (c2 < 2) continue;
                    long long q = std::get<2>(k2);
                    if (q == 1000000000LL || q == -1000000000LL) {
                        pot1 += c2 - 1;  // already served by the +-1 butterfly
                    } else {
                        potw += c2 - 1;
                        bigw++;
                    }
                }
                std::cerr << "SS_MCM sums=" << rows.size() << " terms=" << terms
                          << " lambda=+-1(already done)=" << pot1
                          << " WEIGHTED buckets=" << bigw << " bound=" << potw << std::endl;

                // --- the blind spot : sharing BETWEEN FIR kernels of
                // one SAME source. Three measures per multi-kernel
                // source : (a) shifted windows (equal coefficient vector
                // up to a shift -> share through an output delay),
                // (b) weighted inter-kernel pairs over the taps,
                // (c) common prefixes (partial accumulations).
                {
                    std::map<Tree, std::vector<tvec>, treeorder> bySource;
                    std::set<Tree>    seenF;
                    std::vector<Tree> workF{L2};
                    while (!workF.empty()) {
                        Tree t = workF.back();
                        workF.pop_back();
                        if (!seenF.insert(t).second) continue;
                        Tree var, body;
                        if (isRec(t, var, body)) {
                            if (body) workF.push_back(body);
                            continue;
                        }
                        if (tvec cf; kernelWorkVec(t, cf) && cf.size() > 2) {
                            bySource[cf[0]].push_back(cf);
                        }
                        for (int k = 0; k < t->arity(); k++) workF.push_back(t->branch(k));
                    }
                    long nMulti = 0, nKern = 0, shifts = 0, prefixes = 0, wpairs = 0;
                    for (auto& [src, kerns] : bySource) {
                        if (kerns.size() < 2) continue;
                        nMulti++;
                        nKern += long(kerns.size());
                        // normalized forms (tap coefs, leading zeros removed)
                        auto trimmed = [](const tvec& cf) {
                            size_t b = 1;
                            while (b < cf.size() && isZero(cf[b])) b++;
                            return tvec(cf.begin() + b, cf.end());
                        };
                        for (size_t i2 = 0; i2 < kerns.size(); i2++) {
                            tvec ti = trimmed(kerns[i2]);
                            for (size_t j2 = i2 + 1; j2 < kerns.size(); j2++) {
                                tvec tj = trimmed(kerns[j2]);
                                if (ti == tj && kerns[i2] != kerns[j2]) shifts++;
                                // prefixe commun >= 2 taps
                                size_t common = 0;
                                while (common < ti.size() && common < tj.size() &&
                                       ti[common] == tj[common]) common++;
                                if (common >= 2 && ti != tj) prefixes++;
                            }
                        }
                        // weighted inter-kernel pairs : buckets (i, j, cj/ci)
                        std::map<std::tuple<int, int, long long>, int> kb;
                        for (auto& cf : kerns) {
                            for (size_t i2 = 1; i2 < cf.size(); i2++) {
                                double wi, wj; int ni2, nj2;
                                if (isZero(cf[i2])) continue;
                                if (!(isSigReal(cf[i2], &wi) || (isSigInt(cf[i2], &ni2) && (wi = ni2, true)))) continue;
                                for (size_t j2 = i2 + 1; j2 < cf.size(); j2++) {
                                    if (isZero(cf[j2])) continue;
                                    if (!(isSigReal(cf[j2], &wj) || (isSigInt(cf[j2], &nj2) && (wj = nj2, true)))) continue;
                                    long long q = (long long)std::llround((wj / wi) * 1e9);
                                    kb[{int(i2), int(j2), q}]++;
                                }
                            }
                        }
                        for (auto& [k2, c2] : kb) {
                            if (c2 >= 2) wpairs += c2 - 1;
                        }
                    }
                    std::cerr << "SS_MCM_FIR sources-multi=" << nMulti << " noyaux=" << nKern
                              << " decalages=" << shifts << " prefixes=" << prefixes
                              << " paires-taps-bornees=" << wpairs << std::endl;
                }
            }
            if (gGlobal->gLowerSums || getenv("FAUST_LOWERSUMS")) {
                // experimental co-occurrence lowering : the n-ary sums
                // become binary adds whose shared pairs and canonical
                // prefixes rebuild the structural sharing the flattening
                // destroyed (fdnRev : 823 -> 3056 additions without it)
                startTiming("Sum lowering");
                std::set<Tree> keepRows;
                if ((gGlobal->gMatrixRows || getenv("FAUST_MATRIX_ROWOP"))) {
                    // matrix rows stay n-ary through the lowering : the
                    // -ls row-op regime consumes them whole (spec
                    // LA-FORME-MATRICE)
                    for (auto& [row, id] : revealMatrix(L2).rowOf) {
                        keepRows.insert(row);
                    }
                }
                L2 = lowerSums(L2, keepRows.empty() ? nullptr : &keepRows);
                endTiming("Sum lowering");
            }
        };  // fin du lambda reveal (-fir)
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setstacksize(&attr, size_t(2048) << 20);
        pthread_t th;
        auto      trampoline = [](void* p) -> void* {
            (*static_cast<std::function<void()>*>(p))();
            return nullptr;
        };
        if (pthread_create(&th, &attr, trampoline, &reveal) == 0) {
            pthread_join(th, nullptr);
        } else {
            reveal();  // fallback : main stack
        }
        pthread_attr_destroy(&attr);
    }

    startTiming("conditionAnnotation");
    conditionAnnotation(L2);
    endTiming("conditionAnnotation");

    startTiming("recursivnessAnnotation");
    recursivnessAnnotation(L2);  // Annotate L2 with recursivness information
    endTiming("recursivnessAnnotation");

    if (!getenv("FAUST_SS_NODISPLAYBLOCK")) {
        // spec SIGNAUX-ATTACHES (default since 2026-08-17) : harvest D,
        // dissolve attach and bargraph decorations from the audio path,
        // BEFORE typing (the rebuild creates new trees). The env var is
        // the forensic opt-out for A/B comparisons, not a supported mode.
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
        L2 = applyDelayFloor(L2, gGlobal->gMinDelay);
        conditionAnnotation(L2);
        recursivnessAnnotation(L2);
        typeAnnotation(L2, true);
    }

    if (gGlobal->gReassoc) {
        // -reassoc : late state-join (see reassociate.cpp) -- BEFORE the
        // staging pass, so barriers see the final tree shapes
        startTiming("reassociate");
        L2 = reassociate(L2);
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
        L2 = placeTemps(L2, gGlobal->gTempOps);
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
    Tree Lx = L2;
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
                int order = 0;
                for (size_t k = 3; k < cs.size(); k++) {
                    if (!isZero(cs[k])) {
                        order = int(k) - 2;
                    }
                }
                if (order >= 2 && readers.count(t) == 0) {
                    t->setProperty(tree(symbol("SIGIIRTRANSPOSED")), tree(1));
                }
            }
        }
    }
    fOccMarkup->mark(Lx);  // Annotate L2 (+ condition atoms) with occurrences analysis
    endTiming("occurrences analysis");

    if (getenv("FAUST_SS_DESCENDCHECK")) {
        // descendAttribute v2 validation (absorbing doors) : the
        // max-delays recomputed by the generic descent must agree with
        // OccMarkup on every node it visited. Local edge labels
        // (regime A) + the -1*y tracking (chain, regime B, outside the
        // doors), same values as incOcc.
        auto md = descendAttribute<int>(
            Lx, 0,
            [](Tree parent, int i, const int& pa) -> int {
                Tree x, y;
                int  opnum;
                if (isSigDelay(parent, x, y) && i == 0) {
                    return checkDelayInterval(getCertifiedSigType(y));
                }
                if (isSigPrefix(parent, x, y) && i == 1) {
                    return 1;
                }
                if (isSigBinOp(parent, &opnum, x, y) && opnum == kMul && isMinusOne(x) &&
                    i == 1) {
                    return pa;  // the -1*y sharing propagates (cf. OccMarkup)
                }
                return 0;
            },
            [](const int& a, const int& b) { return a > b ? a : b; });
        long agree = 0, miss = 0;
        for (const auto& [t, d] : md) {
            Occurrences* o = fOccMarkup->retrieve(t);
            if (o == nullptr) {
                continue;  // hors du parcours OccMarkup (gen, descripteurs)
            }
            if (o->getMaxDelay() == d) {
                agree++;
            } else {
                miss++;
                if (miss <= 4) {
                    std::cerr << "SS_DESCENDMISS occ=" << o->getMaxDelay() << " descend=" << d
                              << " " << ppsig(t, 4) << std::endl;
                }
            }
        }
        std::cerr << "SS_DESCENDCHECK agree=" << agree << " miss=" << miss << std::endl;
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

    return L2;
}

Tree ScalarCompiler::prepare2(Tree L0)
{
    startTiming("ScalarCompiler::prepare2");

    recursivnessAnnotation(L0);        // Annotate L0 with recursivness information
    typeAnnotation(L0, true);          // Annotate L0 with type information
    sharingAnalysis(L0, fSharingKey);  // annotate L0 with sharing count

    delete fOccMarkup;
    fOccMarkup = new OccMarkup();
    fOccMarkup->mark(L0);  // annotate L0 with occurrences analysis

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
        return subst("($0 || $1)", and2code(c1), dnf2code(cc));
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
        return subst("($0 && $1)", CS(c1), and2code(cs));
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
        return subst("(($0) && $1)", or2code(c1), cnf2code(cs));
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
        return subst("($0 || $1)", CS(c1), or2code(cs));
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
            if (getenv("FAUST_SELECTN_DEBUG")) {
                fprintf(stderr, "  dispatch reconnu : %zu domaines\n", leaves.size());
            }
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
        if (getenv("FAUST_SELECTN_DEBUG")) {
            fprintf(stderr, "  eq-famille : %zu membres\n", f.second.size());
        }
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
            if (getenv("FAUST_SELECTN_DEBUG")) {
                fprintf(stderr, "  eq-candidat : ok=%d entrees=%zu\n", (int)ok,
                        info.leaves.size());
            }
            if (!ok || info.leaves.size() < 3 || info.leaves.size() > 65) {
                continue;  // entries + default >= 3 (spec N >= 3)
            }
            info.selEff = base;
            fSelectNInfo[root] = info;
            if (getenv("FAUST_SELECTN_DEBUG")) {
                fprintf(stderr, "  chaine== reconnue : %zu entrees + defaut\n",
                        info.leaves.size() - 1);
            }
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
        // the big lock, not the depth). FAUST_LZ_ATOMS overrides for
        // experiments.
        int lzlim = getenv("FAUST_LZ_ATOMS") ? atoi(getenv("FAUST_LZ_ATOMS")) : 4;
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
 Loop-DAG export (experimental, FAUST_OCPP_DUMPDAG)
 *****************************************************************************/

/**
 * Export the program as a DAG of loops, in the JSON format understood by the
 * loop-merging simulator (../loop-splitting/faust_dag.py). The partition is
 * computed by SuperNodeGraph (the single source of truth for materialization
 * and blocks); this class only owns the JSON representation choices required
 * by the simulator's Program model: instantaneous intra-block references are
 * inlined (lock-step multi-output bodies cannot self-read at d=0), delayed
 * ones become self-reads, slow subtrees are pruned to opaque leaves, members
 * never read from outside are dropped from the outputs.
 */
class LoopDagDumper {
    SuperNodeGraph      fSN;
    std::vector<bool>   fNeeded;         // index -> read somewhere => output vector
    std::vector<bool>   fBlockSelfRead;  // block -> emits a self-read
    std::map<Tree, int, treeorder> fSlowId;         // slow leaf -> id

   public:
    LoopDagDumper(OccMarkup* occ, Tree key) : fSN(occ, key) {}

    void dump(Tree L, const std::vector<Tree>& sched, int nins, int nouts, std::ostream& out)
    {
        fSN.build(L, sched);
        int n = (int)fSN.materialized().size();
        fNeeded.assign(n, false);
        fBlockSelfRead.assign(fSN.blockCount(), false);

        // serialize every member body (marks fNeeded and fBlockSelfRead)
        std::vector<std::string> body(n);
        for (int i = 0; i < n; i++) {
            Tree               d = SuperNodeGraph::defOf(fSN.materialized()[i]);
            std::ostringstream b;
            emit(d, &b, fSN.blockOf(i), d == fSN.materialized()[i]);
            body[i] = b.str();
        }
        std::vector<std::string> obody(nouts);
        {
            int  i  = 0;
            Tree L1 = L;
            for (; isList(L1); L1 = tl(L1), i++) {
                std::ostringstream b;
                emit(hd(L1), &b, -2, false);
                obody[i] = b.str();
            }
        }

        // assemble
        out << "{\"inputs\": " << nins << ", \"outputs\": " << nouts << ",\n";
        out << " \"loops\": [\n";
        bool first = true;
        for (int s = 0; s < fSN.blockCount(); s++) {
            const std::vector<int>& members = fSN.blockMembers(s);
            std::vector<int>        vs;
            for (int i : members) {
                if (fNeeded[i]) {
                    vs.push_back(i);
                }
            }
            if (vs.empty()) {
                continue;  // fully inlined into its consumers
            }
            const char* kind = (members.size() > 1 || fBlockSelfRead[s]) ? "rec"
                               : fSN.maxDelayOf(fSN.materialized()[vs[0]]) > 0 ? "delayed"
                                                                               : "shared";
            out << (first ? "  " : ",\n  ") << "{\"vs\": [";
            first = false;
            for (size_t k = 0; k < vs.size(); k++) {
                out << (k ? ", " : "") << vs[k];
            }
            out << "], \"kind\": \"" << kind << "\", \"maxdelays\": [";
            for (size_t k = 0; k < vs.size(); k++) {
                out << (k ? ", " : "") << fSN.maxDelayOf(fSN.materialized()[vs[k]]);
            }
            out << "],\n   \"bodies\": [";
            for (size_t k = 0; k < vs.size(); k++) {
                out << (k ? ",\n              " : "") << body[vs[k]];
            }
            out << "]}";
        }
        for (int i = 0; i < nouts; i++) {
            out << (first ? "  " : ",\n  ");
            first = false;
            out << "{\"vs\": [" << (n + i) << "], \"kind\": \"output\", "
                << "\"output_index\": " << i << ", \"maxdelays\": [0],\n   \"bodies\": ["
                << obody[i] << "]}";
        }
        out << "\n]}\n";
    }

   private:
    static void jsonEscape(std::ostream& out, const std::string& s)
    {
        for (char c : s) {
            if (c == '"' || c == '\\') {
                out << '\\';
            }
            out << c;
        }
    }

    // reference to materialized node m, read with delay dmin (dvar: variable)
    void emitRef(Tree m, int dmin, int dmax, bool dvar, std::ostream* out, int scc)
    {
        int  idx     = fSN.indexOf(m);
        bool sameScc = (scc >= 0) && (fSN.blockOf(idx) == scc);
        if (sameScc && dmin == 0 && !dvar) {
            // instantaneous intra-loop reference: inline the definition
            // (acyclic by causality)
            Tree d = SuperNodeGraph::defOf(m);
            emit(d, out, scc, d == m);
            return;
        }
        if (sameScc && dmin == 0 && dvar) {
            dmin = 1;  // lock-step bodies cannot self-read at d=0
        }
        fNeeded[idx] = true;
        if (sameScc) {
            fBlockSelfRead[scc] = true;
        }
        *out << "{\"read\": " << idx << ", \"d\": " << dmin;
        if (dvar) {
            *out << ", \"dvar\": true, \"dmax\": " << dmax;
        }
        *out << "}";
    }

    void emitOp(const std::string& name, bool call, int r, const std::vector<Tree>& args,
                std::ostream* out, int scc)
    {
        *out << "{\"op\": \"";
        jsonEscape(*out, name);
        *out << "\"";
        if (call) {
            *out << ", \"call\": true";
        }
        if (r > 0) {
            *out << ", \"r\": " << r;
        }
        *out << ", \"args\": [";
        for (size_t i = 0; i < args.size(); i++) {
            if (i > 0) {
                *out << ", ";
            }
            emit(args[i], out, scc, false);
        }
        *out << "]}";
    }

    void emit(Tree t, std::ostream* out, int scc, bool root)
    {
        int     i;
        int64_t i64;
        double  r;
        Tree    x, y, z, sel, ff, largs, tb, size, gen, wi, ws, ri, label;

        // materialized nodes referenced from a body become vector reads
        if (!root && fSN.indexOf(t) >= 0) {
            emitRef(t, 0, 0, false, out, scc);
            return;
        }
        if (isSigInt(t, &i)) {
            *out << "{\"num\": " << i << "}";
        } else if (isSigInt64(t, &i64)) {
            *out << "{\"num\": " << i64 << "}";
        } else if (isSigReal(t, &r)) {
            *out << "{\"num\": " << r << "}";
        } else if (isSigInput(t, &i)) {
            *out << "{\"input\": " << i << "}";
        } else if (isSigAttach(t, x, y) && !SuperNodeGraph::isSlow(y)) {
            // attach takes the TYPE of its left arm but its right arm is a
            // side effect (bargraph) running at sample rate: it must escape
            // the slow pruning below even when the attach node itself is slow
            emitOp("attach", false, 0, {x, y}, out, scc);
        } else if (SuperNodeGraph::isSlow(t)) {
            // opaque slow leaf: computed outside the sample loop
            if (fSlowId.find(t) == fSlowId.end()) {
                int id     = (int)fSlowId.size();
                fSlowId[t] = id;
            }
            *out << "{\"slow\": " << fSlowId[t] << "}";
        } else if (isSigDelay(t, x, y)) {
            int  dmin, dmax;
            bool dvar;
            SuperNodeGraph::delayBounds(y, dmin, dmax, dvar);
            if (fSN.indexOf(x) >= 0) {
                emitRef(x, dmin, dmax, dvar, out, scc);
            } else {
                // delay of a non-materialized signal: only possible for
                // slow/constant values, where the delay is transparent
                emit(x, out, scc, false);
            }
        } else if (isSigPrefix(t, x, y)) {
            emitOp("prefix", false, 1, {x, y}, out, scc);
        } else if (isSigBinOp(t, &i, x, y)) {
            bool call = (i == kRem) && (getCertifiedSigType(t)->nature() == kReal);
            emitOp(gBinOpTable[i]->fName, call, 0, {x, y}, out, scc);
        } else if (getUserData(t)) {
            std::string       name = ((xtended*)getUserData(t))->name();
            std::vector<Tree> args;
            for (int k = 0; k < t->arity(); k++) {
                args.push_back(t->branch(k));
            }
            emitOp(name, SuperNodeGraph::isCallPrim(name), 0, args, out, scc);
        } else if (isSigFFun(t, ff, largs)) {
            std::vector<Tree> args;
            for (Tree l = largs; isList(l); l = tl(l)) {
                args.push_back(hd(l));
            }
            emitOp(ffname(ff), true, 0, args, out, scc);
        } else if (isSigRDTbl(t, tb, ri)) {
            if (isSigWRTbl(tb, size, gen)) {
                emitOp("rdtable", false, 0, {ri}, out, scc);
            } else if (isSigWRTbl(tb, size, gen, wi, ws)) {
                emitOp("rwtable", false, 0, {wi, ws, ri}, out, scc);
            } else {
                emitOp("rdtable", false, 0, {ri}, out, scc);
            }
        } else if (isSigSelect2(t, sel, x, y)) {
            emitOp("select2", false, 0, {sel, x, y}, out, scc);
        } else if (isSigIntCast(t, x) || isSigFloatCast(t, x) || isSigBitCast(t, x)) {
            emitOp("cast", false, 0, {x}, out, scc);
        } else if (isSigAttach(t, x, y)) {
            emitOp("attach", false, 0, {x, y}, out, scc);
        } else if (isSigVBargraph(t, label, x, y, z) || isSigHBargraph(t, label, x, y, z)) {
            emitOp("bargraph", false, 0, {z}, out, scc);
        } else if (isSigControl(t, x, y)) {
            emitOp("control", false, 0, {x, y}, out, scc);
        } else if (isSigAssertBounds(t, x, y, z)) {
            emit(z, out, scc, false);
        } else {
            // generic fallback: dependencies as an anonymous op
            tvec subs;
            getSubSignals(t, subs, false);
            std::ostringstream name;
            name << "op:" << t->node();
            emitOp(name.str(), false, 0, subs, out, scc);
        }
    }
};

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

    // per-buffer emission decisions (materialized index -> ...)
    std::vector<std::string> fBufName;
    std::vector<int>         fAliasIx;  // tap aliasing: member -> producer index (-1: own buffer)
    std::vector<int>         fAliasD;   //   and the constant delay into the producer's history
    std::vector<int>         fMaxD;
    std::vector<bool>        fIsInt;
    std::vector<bool>        fLocal;  // maxDelay == 0: chunk-local buffer
    std::vector<bool> fRing;      // maxDelay > gMaxCopyDelay: masked ring buffer
    std::vector<int>  fRingMask;  // per ring buffer: size - 1 (power of two)
    bool              fHasRing = false;  // at least one ring: emit the fLSIota index

    // per-loop op DAG under scheduling
    struct LSOp {
        std::string code;              // expression, or full statement for stores
        std::vector<int> deps;
        bool isStore = false;
        bool isCall  = false;
        bool isInt   = false;
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
    // row-op emission regime gate (-mxr, or FAUST_MATRIX_ROWOP for
    // forensic A/B comparisons)
    MatrixPlans fMatrix;
    bool        fRowOp = false;

    // the hierarchical grouping (spec LE-GROUPEMENT-HIERARCHIQUE) : the
    // deposit tree. Producers : the super-node partition (Loop layer)
    // and the matrix families (Atomic "matrix-row"). The walk consults
    // the tree ; the regimes keep their private data (fMatrix).
    GroupPlan fPlan;

    void buildGroupPlan()
    {
        fPlan = GroupPlan();
        std::map<int, int> loopNode;  // block -> Loop node id
        for (int b = 0; b < fSN.blockCount(); b++) {
            GroupNode ln{GroupNode::kLoop};
            int       lid = fPlan.add(std::move(ln), 0);
            loopNode[b]   = lid;
            for (int m : fSN.blockMembers(b)) {
                Tree s   = fSN.materialized()[m];
                auto row = fMatrix.rowOf.find(s);
                if (fRowOp && row != fMatrix.rowOf.end()) {
                    // a materialized matrix row : Atomic wrapping its leaf
                    GroupNode an{GroupNode::kAtomic};
                    an.regime     = "matrix-row";
                    an.a          = row->second.first;
                    an.b          = row->second.second;
                    const int n   = (int)fMatrix.families[an.a].tuple.size();
                    an.weight     = std::max(1, (n + 3) / 4 + (n + 2) / 4);
                    int aid       = fPlan.add(std::move(an), lid);
                    fPlan.atomOf.emplace(s, aid);
                    fPlan.leaf(s, m, aid);
                } else {
                    fPlan.leaf(s, m, lid);
                }
            }
        }
        if (fRowOp) {
            // non-materialized rows (claimed expressions) : Atomic under
            // the root -- their loop is only known at consumption time
            for (auto& [s, fr] : fMatrix.rowOf) {
                if (fPlan.atomOf.count(s)) {
                    continue;
                }
                GroupNode an{GroupNode::kAtomic};
                an.regime   = "matrix-row";
                an.a        = fr.first;
                an.b        = fr.second;
                const int n = (int)fMatrix.families[an.a].tuple.size();
                an.weight   = std::max(1, (n + 3) / 4 + (n + 2) / 4);
                int aid     = fPlan.add(std::move(an), 0);
                fPlan.atomOf.emplace(s, aid);
                fPlan.leaf(s, -1, aid);
            }
        }
        if (getenv("FAUST_GROUP_CENSUS")) {
            std::cerr << "GROUP census :\n";
            fPlan.print(std::cerr);
        }
    }
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

    // reference to materialized idx read at delay dcode. An instantaneous
    // read of a producer living in the SAME loop is scalarized: it
    // references the producer's root value directly (a register), not the
    // buffer -- this is what makes fusion pay. The store still happens for
    // external readers; d0-topological member order guarantees the root
    // exists. Variable delays that may be 0 keep the buffer access with a
    // dependency on the store (the runtime delay may be positive).
    std::map<int, Operand> fRootOf;  // materialized index -> its body root

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
        if (isSigInt(t, &i)) {
            o.code = T(i);
            return o;
        }
        if (isSigInt64(t, &i64)) {
            o.code = T(i64);
            return o;
        }
        if (isSigReal(t, &r)) {
            o.code = T(r);
            return o;
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
            o.code = fC->CS(t);  // scalar machinery, code lives outside the loops
            return o;
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
            if (fRowOp && !wrapInt && fPlan.isAtomic(t) && blockHasRecurrence(curScc)) {
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
                const GroupNode&    at  = fPlan.atomic(t);  // regime "matrix-row"
                const int           fam = at.a, row = at.b;
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
                fOps[o.op].weight = at.weight;  // the Atomic's declared weight
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
                    n2.op = newOp(subst("int(uint32_t($0) + uint32_t($1))",
                                        operandCode(acc), operandCode(a)),
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
            o.op = newOp(subst("($0 $1 $2)", operandCode(a), gBinOpTable[i]->fName,
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
            fC->fUITree.addUIWidget(reverse(tl(label)), uiWidget(hd(label), tree(varname), t));
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
        if (getenv("FAUST_GROUP_STICKY")) {
            // sticky-shape probe : digit-erased codes as shapes, span-local
            std::vector<std::string> shapes(hi - lo);
            for (int k = lo; k < hi; k++) {
                std::string sh;
                sh.reserve(fOps[k].code.size());
                for (char ch : fOps[k].code) {
                    if (!isdigit((unsigned char)ch)) {
                        sh += ch;
                    }
                }
                shapes[k - lo] = std::move(sh);
            }
            order = modelSchedule(fOps, lo, hi, gGlobal->gLSRegisters, gGlobal->gLSWidth,
                                  nullptr, nullptr, nullptr, &shapes);
            return order;
        }
        order = modelSchedule(fOps, lo, hi, gGlobal->gLSRegisters, gGlobal->gLSWidth, nullptr,
                              nullptr);
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
                if (d >= lo && d < hi) {
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
                    if (d >= lo && d < hi) {
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
        modelSchedule(sops, 0, (int)sops.size(), gGlobal->gLSRegisters, gGlobal->gLSWidth,
                      &cycles, &overR, &peak);
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
        if (sopsOut) {
            *sopsOut = std::move(sops);
        }
        return (long)gGlobal->gVecSize * (cycles + SPILLW * overR) + CL;
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

void LoopSplitEmitter::emit(Tree L, const std::vector<Tree>& sched, int nouts)
{
    // 0. refuse unsupported constructs before writing anything
    {
        std::set<Tree, treeorder> seen;
        for (Tree l = L; isList(l); l = tl(l)) {
            prescan(hd(l), seen);
        }
    }

    // 0-bis. the matrix form : detect the families ON THE EMITTED LIST
    // (same trees the walk will see -- hash-consing makes the plan's keys
    // pointer-exact). The row-op regime is gated while experimental.
    if ((gGlobal->gMatrixRows || getenv("FAUST_MATRIX_ROWOP"))) {
        fMatrix = revealMatrix(L);
        fRowOp  = !fMatrix.families.empty();
    }

    // 1-2. the partition (materialization, reference graph, blocks).
    // References with certified delay >= the chunk size do not constrain
    // grouping: cycles with long feedback edges split legally (the d < N
    // restriction of LOOPMERGING.md)
    fSN.build(L, sched, gGlobal->gVecSize);

    // 2a-bis. the Dissolve move : a signal materialized ONLY for sharing
    // (not a projection, never read delayed, not an output) may be
    // cheaper INLINED in each consumer than computed once and joined --
    // the bells' mode sum wants per-mode locality, freeverb's comb sum
    // wants the shared member (x0.97). No static rule separates them
    // (three falsified in one day) : the faithful shadow oracle prices
    // both worlds per candidate, duplication included.
    if (gGlobal->gLSFuse && !getenv("FAUST_NO_DISSOLVE")) {
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
            if (isProj(t, &pi, pw) || fSN.maxDelayOf(t) > 0 || outs.count(t)) {
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
                if (getenv("FAUST_LS_DISSOLVE_DEBUG")) {
                    std::cerr << "DISSOLVE member " << m << " consumers=" << cbs.size()
                              << " with=" << with << " without=" << without << std::endl;
                }
            }
        }
        if (!dissolved.empty()) {
            if (getenv("FAUST_LS_DISSOLVE_DEBUG")) {
                std::cerr << "DISSOLVE " << dissolved.size() << " members, rebuild" << std::endl;
            }
            fSN.setExcluded(std::move(dissolved));
            fSN.reset();
            fSN.build(L, sched, gGlobal->gVecSize);
        }
    }

    // 2b. greedy single-consumer fusion (-ls-fuse): contract a block into
    // its only consumer when legal (quotient stays acyclic) and the merged
    // body fits the op budget. The policy of the predictor, as a walk in
    // the lattice of legal partitions.
    if (gGlobal->gLSFuse) {
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
        if (const char* e = getenv("FAUST_LS_STREAMS")) {
            streamBudget = std::atol(e);  // 0 : disabled
        }
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
            if (k && getenv("FAUST_SS_FIRDEBUG")) {
                std::cerr << "  FIRDEBUG kernel block " << b << " taps=" << taps
                          << " ops=" << fSN.opsEstimate(b) << std::endl;
            }
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
                return 0;  // compile-time guard only: the cost oracle decides
            }
            if (!fSN.canContract(b, c)) {
                return 0;
            }
            if (isKernelBlock(b) != isKernelBlock(c)) {
                return 0;  // -fir barrier
            }
            if (streamBudget > 0 && streamsUnion(b, c) > streamBudget) {
                return 0;  // prefetcher stream budget
            }
            long costM = blockCostShadow(fSN.orderedUnion(b, c));
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
            if (bestA >= 0) {
                fSN.contract(bestA, bestB);
                costMemo.clear();
                changed = true;
            }
        }
        fSN.retopo();
    }
    if (gGlobal->gLSFuse && getenv("FAUST_LS_NOTE0")) {
        // CSFUSE stage 0 (spec faust-migration/CSFUSE.md par.6): the
        // portfolio note of every FINAL block, decision-free. One shadow
        // per block, three orders (model / cs2 df-spine / cs2b bf-spine),
        // ONE normative scorer for all three. The per-program aggregation
        // N_sigma = sum of n_sigma over blocks and the confrontation with
        // the stage-1 measured winners happen outside the compiler.
        const long CL = gGlobal->gLSCl, SPILLW = gGlobal->gLSSpillW;
        const int  R = gGlobal->gLSRegisters, U = gGlobal->gLSWidth;
        long       Nm = 0, Nc = 0, Nb = 0;
        for (int b = 0; b < fSN.blockCount(); b++) {
            std::vector<LSOp> sops;
            blockCostShadow(fSN.blockMembers(b), nullptr, nullptr, true, -1, nullptr, &sops);
            int  n = (int)sops.size();
            int  cy, pk, iso, p4;
            long ov, dist;
            // the full feature vector of one order (RUM stage-B bench) :
            // machine axes (cycles, overR, peak) and SLP-visible axes
            // (iso-adjacency, 4-packs, mean operand distance)
            auto features = [&](const char* sig, const std::vector<int>& ord) -> long {
                replayOrderScore(sops, ord, R, U, &cy, &ov, &pk);
                orderFeatures(sops, ord, &iso, &p4, &dist);
                std::cerr << "NOTE0F b=" << b << " n=" << n << " sig=" << sig << " cy=" << cy
                          << " ov=" << ov << " pk=" << pk << " iso=" << iso << " p4=" << p4
                          << " dist=" << dist << std::endl;
                return (long)gGlobal->gVecSize * (cy + SPILLW * ov) + CL;
            };
            std::vector<int> om = modelSchedule(sops, 0, n, R, U, nullptr, nullptr);
            long             nm = features("model", om);
            long             nc = nm, nb = nm;
            if (n > 2) {
                digraph<int> G;
                for (int k = 0; k < n; k++) {
                    G.add(k);
                    for (int d : sops[k].deps) {
                        G.add(k, d, 0);
                    }
                }
                auto toOrd = [&](const schedule<int>& S) {
                    std::vector<int> v;
                    v.reserve(n);
                    for (int o : S.elements()) {
                        v.push_back(o);
                    }
                    return v;
                };
                nc = features("cs2", toOrd(csschedule2(G, R, U, 4u, nullptr, 500000, nullptr, false)));
                nb = features("cs2b", toOrd(csschedule2(G, R, U, 4u, nullptr, 500000, nullptr, true)));
            } else {
                features("cs2", om);
                features("cs2b", om);
            }
            Nm += nm;
            Nc += nc;
            Nb += nb;
        }
        std::cerr << "NOTE0 blocks=" << fSN.blockCount() << " model=" << Nm << " cs2=" << Nc
                  << " cs2b=" << Nb << std::endl;
    }
    if (getenv("FAUST_DEBUG_SUPERNODES")) {
        fSN.print(std::cerr);
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
        if (getenv("FAUST_DEBUG_SUPERNODES") && fSN.blockCount() <= 1) {
            std::cerr << "degenerate check: shadow peak " << peak << "/"
                      << gGlobal->gLSRegisters << ", overR " << overR << ", calls "
                      << hasCall << ", short delays " << shortD << std::endl;
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
                int itmp;
                if (isNum(t) || isSlow(t) || isSigInput(t, &itmp) || fSN.indexOf(t) >= 0) {
                    return 0;  // buffer read, constant or slow : not tail work
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
        if (fSN.blockCount() <= 1 && overR == 0 && peak < gGlobal->gLSRegisters && !hasCall &&
            shortD && tailGain <= 0 && !manyStreams) {
            throw LoopSplitUnsupported("single super-node within the register budget", true);
        }
    }
    const std::vector<Tree>& mat = fSN.materialized();
    int                      n   = (int)mat.size();

    // 2d. the deposit tree (spec LE-GROUPEMENT-HIERARCHIQUE) : the
    // partition is FINAL here (dissolution and fusion moves done) --
    // record it, with the matrix families' Atomic deposits, before any
    // emission decision reads it.
    buildGroupPlan();

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
            if (getenv("FAUST_SS_FIRDEBUG")) {
                std::cerr << "  FIRDEBUG ring candidate ptr=" << (void*)mat[i]
                          << " maxD=" << fMaxD[i] << " sig=" << ppsig(mat[i], 12) << std::endl;
            }
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
    std::ostringstream loops;
    for (int b = 0; b < fSN.blockCount(); b++) {
        int lo = (int)fOps.size();
        fOpOf.clear();  // tls temporaries are loop-scoped
        fMatGather.clear();
        fMatResolved.clear();
        fCurReadStreams.clear();
        fCurWriteStreams.clear();
        fCurRotDepth.clear();
        for (int m : fSN.blockMembers(b)) {
            if (fAliasIx[m] >= 0) {
                continue;  // aliased tap: no body, no store -- reads redirect
            }
            fCurWriteStreams.insert(m);
            Tree             d    = defOf(mat[m]);
            Operand          root = walk(d, b, d == mat[m]);
            fRootOf[m]            = root;
            std::vector<int> deps;
            addDep(deps, root);
            int st = newOp(subst("$0 = $1;", storeCode(m), operandCode(root)), deps, true,
                           false, fIsInt[m]);
            fStoreOf[m] = st;
        }
        // output adoption is OPT-IN (-ls-adopt) : the campaign that
        // followed its unconditional landing measured x1.26-1.83 fusion
        // regressions on ten programs (six bells, wfs, drums, djembe,
        // modularInterp) -- two extra output stores in a large host
        // flipped clang's vectorization of the whole body -- against a
        // single -2% win (statespace fibfu, a non-elected lane). The
        // oracle that accepted it prices registers and slots, not
        // clang's SLP moods : the urns arbitrate instead.
        if (gGlobal->gLSAdopt || getenv("FAUST_LS_ADOPT")) {
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
            buildOutput(outPlans[k], -1);
            outPlans[k].placed = true;
            if (gGlobal->gLSFuse && (gGlobal->gLSAdopt || getenv("FAUST_LS_ADOPT"))) {
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
    int  R = gGlobal->gLSRegisters, U = gGlobal->gLSWidth;
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
    if (getenv("FAUST_GROUP_CENSUS")) {
        // the HARVEST (spec LE-GROUPEMENT-HIERARCHIQUE par.2) : the groups
        // the scheduler FORMED without naming them -- what a recolte pass
        // would reify as Adjacent deposits
        std::cerr << "GROUP recolte loop " << fLoopNo << " : " << harvest.size()
                  << " runs adjacents (tailles";
        for (int r : harvest) {
            std::cerr << " " << r;
        }
        std::cerr << ") sur " << n << " ops\n";
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
                << "d" << d << " = " << fBufName[rot.first] << "[" << (fMaxD[rot.first] - d)
                << "];";
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
    out << "\n\t\t\t}\n\t\t\t";
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
        pthread_attr_t        attr;
        pthread_attr_init(&attr);
        pthread_attr_setstacksize(&attr, size_t(2048) << 20);
        pthread_t th;
        auto      trampoline = [](void* p) -> void* {
            (*static_cast<std::function<void()>*>(p))();
            return nullptr;
        };
        if (pthread_create(&th, &attr, trampoline, &body) == 0) {
            pthread_join(th, nullptr);
        } else {
            compileMultiSignalAux(L);  // fallback : main stack
        }
        pthread_attr_destroy(&attr);
        return;
    }
    compileMultiSignalAux(L);
}

void ScalarCompiler::compileMultiSignalAux(Tree L)
{
    // contextor recursivness(0);
    L = prepare(L);  // optimize, share and annotate expression
    censusAdjacentReads(L);
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
        if (getenv("FAUST_SS_SPLIT")) {
            projSCCReport(Lf);  // post-normalisation : doit ressortir minimal
        }
        Tree Li = Lf;  // IIRs revealed by prepare (stage-2 injection)
        int  nfir = 0, niir = 0, maxtaps = 0;
        long taps = 0;
        std::set<Tree>    seen;
        std::vector<Tree> work;
        for (Tree l = Li; isList(l); l = tl(l)) {
            work.push_back(hd(l));
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
                if (getenv("FAUST_SS_IIRORDER")) {
                    int order = 0;
                    for (size_t k2 = 3; k2 < cs.size(); k2++) {
                        if (!isZero(cs[k2])) order = int(k2) - 2;
                    }
                    std::cerr << "SS_IIRORDER " << order << std::endl;
                }
                niir++;
            }
            for (int k = 0; k < t->arity(); k++) {
                work.push_back(t->branch(k));
            }
        }
        std::cerr << "SS_FIR fir=" << nfir << " iir=" << niir << " taps=" << taps
                  << " maxtaps=" << maxtaps << " sources=" << fFirFacts.size() << std::endl;
        if (getenv("FAUST_SS_FIRTYPE")) {
            // the typing probe : annotate the revealed copy (FIR nodes go
            // through the fixed-point algebra) and show the type of the
            // first kernel -- nature, variability, interval
            typeAnnotation(Lf, true);
            for (Tree l = Lf; isList(l); l = tl(l)) {
                std::set<Tree>    seen2;
                std::vector<Tree> work2{hd(l)};
                while (!work2.empty()) {
                    Tree t = work2.back();
                    work2.pop_back();
                    if (!seen2.insert(t).second) {
                        continue;
                    }
                    if (isSigFIR(t)) {
                        std::cerr << "SS_FIRTYPE " << ppsig(t, 8) << " : "
                                  << getCertifiedSigType(t) << std::endl;
                        goto done_type;
                    }
                    for (int k = 0; k < t->arity(); k++) {
                        work2.push_back(t->branch(k));
                    }
                }
            }
        done_type:;
        }
        if (getenv("FAUST_SS_FIRDEBUG")) {
            for (auto& [src, f] : fFirFacts) {
                std::cerr << "  FIRDEBUG source ptr=" << (void*)src << " span=" << f.first
                          << " nz=" << f.second << " sig=" << ppsig(src, 12) << std::endl;
            }
        }
        };
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setstacksize(&attr, size_t(2048) << 20);
        pthread_t th;
        auto trampoline = [](void* p) -> void* {
            (*static_cast<std::function<void()>*>(p))();
            return nullptr;
        };
        if (pthread_create(&th, &attr, trampoline, &sideChannel) == 0) {
            pthread_join(th, nullptr);
        } else {
            sideChannel();  // fallback : run on the main stack
        }
        pthread_attr_destroy(&attr);
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
    if (!fDisplayStateful.empty()) {
        auto GA = immediateGraph(L);
        for (Tree sd : fDisplayStateful) {
            if (GA.nodes().count(sd) == 0) {
                Lg = cons(sd, Lg);
            }
        }
    }
    auto G = immediateGraph(Lg);
    if (getenv("FAUST_SS_DOMTREE")) {
        // CSSCHEDULE probe (PILE, spec CSSCHEDULE.md) : the SHAPE of the
        // dominator tree over the pristine immediate DAG decides both the
        // opportunity (sibling banks to interleave) and the cost (flat
        // trees degenerate into one giant root combine). Same idom
        // construction as csschedule, statistics only.
        const schedule<Tree>     topo  = dfschedule(G);
        const std::vector<Tree>& order = topo.elements();
        const int                V     = int(order.size());
        digraph<Tree>            Rg    = reverse(G);
        std::map<Tree, int>      pos;
        for (int i = 0; i < V; i++) {
            pos[order[i]] = i;
        }
        std::vector<int> idom(V + 1, -1);
        idom[V]        = V;
        auto intersect = [&](int a, int b) {
            while (a != b) {
                while (a < b) {
                    a = idom[a];
                }
                while (b < a) {
                    b = idom[b];
                }
            }
            return a;
        };
        int outputs = 0;
        for (int i = V - 1; i >= 0; i--) {
            const Tree& n   = order[i];
            int         nid = -1;
            if (Rg.destinations(n).empty()) {
                nid = V;
                outputs++;
            } else {
                for (const auto& c : Rg.destinations(n)) {
                    int cp = pos[c.first];
                    if (idom[cp] != -1) {
                        nid = (nid == -1) ? cp : intersect(nid, cp);
                    }
                }
                if (nid == -1) {
                    nid = V;
                }
            }
            idom[i] = nid;
        }
        std::vector<int> kids(V + 1, 0), size(V + 1, 1), depth(V + 1, 0);
        int omegaShared = 0;
        for (int i = 0; i < V; i++) {
            kids[idom[i]]++;
            if (idom[i] == V && !Rg.destinations(order[i]).empty()) {
                omegaShared++;  // shared value escaping to the top
            }
        }
        for (int i = 0; i < V; i++) {
            size[idom[i]] += size[i];  // children rank below their idom
        }
        int maxDepth = 0, maxKids = 0, internals = 0, kidsSum = 0, maxBlock = 0;
        for (int i = V - 1; i >= 0; i--) {
            depth[i] = depth[idom[i] == i ? V : idom[i]] + 1;
            maxDepth = std::max(maxDepth, depth[i]);
        }
        for (int i = 0; i < V + 1; i++) {
            if (kids[i] > 0 && i < V) {
                internals++;
                kidsSum += kids[i];
                maxKids = std::max(maxKids, kids[i]);
                maxBlock = std::max(maxBlock, size[i]);
            }
        }
        maxKids = std::max(maxKids, kids[V]);
        std::cerr << "DOMTREE nodes=" << V << " outputs=" << outputs
                  << " omegaKids=" << kids[V] << " omegaShared=" << omegaShared
                  << " depth=" << maxDepth << " maxKids=" << maxKids
                  << " meanKids=" << (internals ? double(kidsSum) / internals : 0)
                  << " maxBlock=" << maxBlock
                  << " maxBlockFrac=" << (V ? double(maxBlock) / V : 0) << std::endl;
    }
    int rfAdded = 0;
    if (!getenv("FAUST_SS_NOREADERSFIRST")) {
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
        if (getenv("FAUST_SS_MONODEBUG")) {
            std::cerr << "READERSFIRST edges +" << added << " sacrificed " << dropped
                      << std::endl;
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
        if (const char* be = getenv("FAUST_SS_RFPEAK")) {
            budget = std::atoi(be);
        }
        // the baseline is REBUILT from scratch : digraph copies share their
        // internal graph (shared_ptr), a plain copy would alias the mutated
        // one -- the very bug that made the gauge blind on its first run
        auto G0   = immediateGraph(Lg);  // the SAME roots as G (display S included)
        auto memf = std::function<bool(const Tree&)>(ocppIsMemNode);
        auto sq1  = squality(G, S.elements(), 8, 4, ocppShapeFunctor(G), memf, 3);
        auto S0   = ocppSchedule(G0);
        auto sq0  = squality(G0, S0.elements(), 8, 4, ocppShapeFunctor(G0), memf, 3);
        bool gated = sq1.peak > std::max(budget, sq0.peak + margin);
        if (getenv("FAUST_SS_MONODEBUG")) {
            std::cerr << "READERSFIRST peak " << sq0.peak << " -> " << sq1.peak << " budget "
                      << budget << (gated ? " GATED" : "") << std::endl;
        }
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
    if (getenv("FAUST_SS_QUALITY")) {
        // ---- calibrated per-op costs (M-series orders of magnitude) :
        // latency enters recurrence chains, reciprocal throughput enters
        // the compute floor (a division blocks the pipe ~8 slots, a libm
        // call ~20 ; mul/add pipeline at 1/cycle despite latency 3)
        auto lat = [](Tree t) -> int {
            int  op, i;
            Tree x, y;
            if (isSigInput(t, &i)) {
                return 4;
            }
            if (isSigDelay(t, x, y)) {
                return 4;  // load-use
            }
            if (isSigBinOp(t, &op, x, y)) {
                if (op == kDiv || op == kRem) {
                    return 10;
                }
                if (op == kMul || op == kAdd || op == kSub) {
                    return 3;
                }
                return 2;
            }
            Tree ff, largs;
            if (isSigFFun(t, ff, largs)) {
                return 25;  // libm
            }
            return 2;
        };
        auto tw = [](Tree t) -> int {
            int  op;
            Tree x, y, ff, largs;
            if (isSigBinOp(t, &op, x, y) && (op == kDiv || op == kRem)) {
                return 8;
            }
            if (isSigFFun(t, ff, largs)) {
                return 20;
            }
            return 1;
        };
        // weighted compute floor over the immediate graph
        {
            long twsum = 0;
            for (const auto& n : G.nodes()) {
                twsum += tw(n);
            }
            unsigned Ue = gGlobal->gLSWidth > 0 ? gGlobal->gLSWidth : 4;
            // weighted critical path per sample : zero-delay skeleton of
            // the FULL graph, node latencies -- the serial spine one
            // sample cannot overlap with itself
            auto        G2 = fullGraph(L);
            auto        sk = cut(G2, 1);
            schedule<Tree> ds = dfschedule(sk);
            std::map<Tree, int> depth;
            int                 cp = 0;
            for (const auto& n : ds.elements()) {
                int d = 0;
                for (const auto& e : sk.destinations(n)) {
                    auto it = depth.find(e.first);
                    if (it != depth.end()) {
                        d = std::max(d, it->second);
                    }
                }
                depth[n] = d + lat(n);
                cp       = std::max(cp, depth[n]);
            }
            std::cerr << "SS_BOUNDS alu2=" << (twsum + Ue - 1) / Ue << " cplat=" << cp
                      << ((cp > long(twsum / Ue)) ? " bind=REC" : " bind=CALC") << std::endl;
        }
        // RecMII estimate : recurrences live in the FULL graph (delay
        // edges included) ; per SCC, the zero-delay skeleton's depth
        // approximates the cycle latency at distance ~1 -- the
        // recurrence bound II >= RecMII no schedule can beat.
        auto lat2 = [](Tree t) -> int {
            int  op, i;
            Tree x, y, ff, largs;
            if (isSigInput(t, &i) || isSigDelay(t, x, y)) {
                return 4;
            }
            if (isSigBinOp(t, &op, x, y)) {
                return (op == kDiv || op == kRem) ? 10
                       : (op == kMul || op == kAdd || op == kSub) ? 3
                                                                  : 2;
            }
            if (isSigFFun(t, ff, largs)) {
                return 25;
            }
            return 2;
        };
        // keep only distance-1 delay edges : the remaining SCCs are the
        // TIGHT recursion nests, whose weighted depth is an exact
        // per-sample bound (long-distance cycles dilute theirs by their
        // delay and are negligible v1)
        auto H      = graph2dag(cut(fullGraph(L), 2));
        int  recmii = 0, nscc = 0;
        for (const auto& scc : H.nodes()) {
            if (scc.nodes().size() > 1) {
                nscc++;
                auto            sk = cut(scc, 1);
                schedule<Tree>  ds = dfschedule(sk);
                std::map<Tree, int> depth;
                int                 dmax = 0;
                for (const auto& n : ds.elements()) {
                    int d = 0;
                    for (const auto& e : sk.destinations(n)) {
                        auto it = depth.find(e.first);
                        if (it != depth.end()) {
                            d = std::max(d, it->second);
                        }
                    }
                    depth[n] = d + lat2(n);
                    dmax     = std::max(dmax, depth[n]);
                }
                recmii = std::max(recmii, dmax);  // distance 1 by construction
            }
        }
        std::cerr << "SS_RECMII sccs=" << nscc << " recMII=" << recmii << std::endl;
    }
    // self-describing artifact : the schedule's quality vector, on the
    // COMMON evaluation machine (R=8, U=4, M=3), as a comment at the top
    // of compute() -- campaigns and archaeology read it straight from
    // the generated code, no environment needed
    if (!getenv("FAUST_SS_NOCOMMENT")) {
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
            if (const char* we = getenv("FAUST_SS_STREAMWIN")) {
                W = std::atoi(we);
            }
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

    // FAUST_SS_SIG : the program's static signature, one line — the raw
    // material of the automatic selector (layer 1). Everything computes
    // without a bench : size, recurrence bound, compute/memory counts,
    // streams (total and windowed peak on the df order), shapes.
    if (getenv("FAUST_SS_SIG")) {
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
        std::cerr << "SS_SIG nodes=" << G.nodes().size() << " recmii=" << ocppTightRecMII(L)
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

    // export the loop DAG for the loop-merging simulator (experimental)
    if (const char* dumpfile = getenv("FAUST_OCPP_DUMPDAG")) {
        std::ofstream out(dumpfile);
        LoopDagDumper(fOccMarkup, fSharingKey)
            .dump(L, S.elements(), fClass->inputs(), fClass->outputs(), out);
        std::cerr << "Loop DAG dumped to " << dumpfile << std::endl;
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
            CS(s);
            gGlobal->gSTEP++;
        }

        std::map<Tree, int, treeorder> firstChan;
        for (int i = 0; isList(L); L = tl(L), i++) {
            Tree s = hd(L);
            if (auto dup = firstChan.find(s);
                dup != firstChan.end() && !getenv("FAUST_NO_OUTPUT_SPLIT")) {
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
            if (getenv("FAUST_SS_MONODEBUG")) {
                std::cerr << "SCALARIZED " << done << "/" << fSingleDelayScalarCandidates.size()
                          << std::endl;
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
    if (getUserData(sig)) {
        return generateXtended(sig);
    } else if (isSigInt(sig, &i)) {
        return generateNumber(sig, T(i));
    } else if (isSigInt64(sig, &i64)) {
        return generateNumber(sig, T(i64));
    } else if (isSigReal(sig, &r)) {
        return generateNumber(sig, T(r));
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
        return generateCacheCode(sig, subst("$0cache->fLength[$1]", CS(sf), CS(x)));
    } else if (isSigSoundfileRate(sig, sf, x)) {
        return generateCacheCode(sig, subst("$0cache->fSR[$1]", CS(sf), CS(x)));
    } else if (isSigSoundfileBuffer(sig, sf, x, y, z)) {
        return generateCacheCode(sig, subst("(($1)$0cache->fBuffers)[$2][$0cache->fOffset[$3]+$4]",
                                            CS(sf), ifloatptrptr(), CS(x), CS(y), CS(z)));
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

string ScalarCompiler::generateBinOp(Tree sig, int opcode, Tree arg1, Tree arg2)
{
    // Special case for -1*a2
    if ((opcode == kMul) && isMinusOne(arg1)) {
        std::string res = CS(arg2);
        if ((res[0] == '(') || (res[0] == 'f') || (res[0] == 'i')) {
            return subst("-$0", res);
        } else {
            return subst("-($0)", res);
        }
        // Special case for a1*-1
    } else if ((opcode == kMul) && isMinusOne(arg2)) {
        std::string res = CS(arg1);
        if ((res[0] == '(') || (res[0] == 'f') || (res[0] == 'i')) {
            return subst("-$0", res);
        } else {
            return subst("-($0)", res);
        }
    } else {
        return generateCacheCode(
            sig, subst("($0 $1 $2)", CS(arg1), gBinOpTable[opcode]->fName, CS(arg2)));
    }
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
        if (getenv("FAUST_SS_RINGPRELOAD") && headSafe) {
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
    if (o == nullptr && getenv("FAUST_SELECTN_DEBUG")) {
        std::stringstream ss;
        ss << ppsig(sig, 20);
        fprintf(stderr, "OCC-NULL sur : %s\n", ss.str().c_str());
    }
    faustassert(o);

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
        bool posInsensitive =
            exp.find("Veeec") == std::string::npos && exp.find("fAdj") == std::string::npos &&
            exp.find("Vec") == std::string::npos && exp.find("wr") == std::string::npos;
        if (gGlobal->gLazySelect && getenv("FAUST_LZ_DUP") && fMainCompilePhase &&
            !fHasEnableControl && posInsensitive && !getConditionCode(sig).empty() &&
            getCertifiedSigType(sig)->variability() == kSamp && exp.size() <= 2048) {
            // memoized as its STRING : built once, inlined at every use
            // site (an unregistered return made every consumer re-derive
            // the subtree -- exponential compile time, dx7 timeout)
            return setCompiledExpression(sig, exp);
        }
        if (false) {
            // EXPERIMENTAL (FAUST_LZ_DUP, spec a venir) -- path-sensitive
            // cache. SLOW nodes NEVER duplicate : per-sample laziness is
            // meaningless for them, inlining pulls their once-per-block
            // computation INTO the loop, and compiling their condition
            // drags the atom cluster -- per-sample STATE READS -- to
            // their (early, meaningless) schedule slot, BEFORE the state
            // updates : the gate_compressor one-sample-late gate.
            // POSITION-SENSITIVITY GUARD : a duplicated string is
            // re-evaluated at its consumer's slot -- a reference to a
            // MUTABLE scalar (mono/single states Veeec, carried fAdj,
            // rotation wr, delay vecs) would read post-update state (the
            // scheduled-position-vs-emission-site lesson, 49f4be216).
            // Only pure references (fTemp, fSlow, tables) may duplicate.
            // path-sensitive cache : every use of this node lives under
            // the same select-side condition. A store would hoist it OUT
            // of the ternary and make it strict -- the very leak that
            // kept seven cubic blends computed per sample where one is
            // taken. Kept INLINE (textually duplicated), it stays inside
            // the ternary : clang evaluates the taken branch only and
            // re-factorizes the duplicates within it (quantizedChords
            // 91.3 -> 49.5 ns, code SMALLER, bit-exact ; the inline form
            // even beats the guarded-statement form 49.5 vs 86.8 -- the
            // mega-ternary is its own schedule). The cap is on the FINAL
            // STRING : nested duplications compound multiplicatively (a
            // 64-op cap per node let dx7's 32 algorithm sides explode to
            // a compiler crash) -- string size bounds the composition.
            return exp;
        }
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
            } else if (fMainCompilePhase && !fHasEnableControl && !getenv("FAUST_LZ_TEMPPERM")) {
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
    fUITree.addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    // return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

string ScalarCompiler::generateCheckbox(Tree sig, Tree path)
{
    string varname = getFreshID("fcheckbox");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    fClass->addInitUICode(subst("$0 = 0.0;", varname));
    fUITree.addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    // return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

string ScalarCompiler::generateVSlider(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
    string varname = getFreshID("fslider");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    fClass->addInitUICode(subst("$0 = $1;", varname, T(tree2double(cur))));
    fUITree.addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    // return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

string ScalarCompiler::generateHSlider(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
    string varname = getFreshID("fslider");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    fClass->addInitUICode(subst("$0 = $1;", varname, T(tree2double(cur))));
    fUITree.addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    // return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

string ScalarCompiler::generateNumEntry(Tree sig, Tree path, Tree cur, Tree min, Tree max,
                                        Tree step)
{
    string varname = getFreshID("fentry");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    fClass->addInitUICode(subst("$0 = $1;", varname, T(tree2double(cur))));
    fUITree.addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    // return generateCacheCode(sig, varname);
    return generateCacheCode(sig, subst("$1($0)", varname, ifloat()));
}

//-----------------------------------------------------------------------------------------
// FAUST_SS_DISPLAYBLOCK (spec SIGNAUX-ATTACHES) : the display list D.
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
void ScalarCompiler::computeDisplayFrontier()
{
    if (fDisplayList == nullptr || !isList(fDisplayList)) {
        return;
    }
    std::set<Tree>    seenS, seenC, walked;
    std::vector<Tree> work;
    for (Tree l = fDisplayList; isList(l); l = tl(l)) {
        Tree path, mn, mx, x;
        if (isSigVBargraph(hd(l), path, mn, mx, x) || isSigHBargraph(hd(l), path, mn, mx, x)) {
            work.push_back(x);
        }
    }
    auto tailCarries = [](Tree t) -> bool {
        int  op;
        Tree x, y, sel;
        return isSigBinOp(t, &op, x, y) || isSigIntCast(t, x) || isSigFloatCast(t, x) ||
               isSigSelect2(t, sel, x, y) || (getUserData(t) != nullptr && t->arity() > 0);
    };
    while (!work.empty()) {
        Tree t = work.back();
        work.pop_back();
        if (!walked.insert(t).second) {
            continue;
        }
        if (getCertifiedSigType(t)->variability() < kSamp) {
            continue;  // consts and slow : inlined at emission
        }
        int  i;
        Tree x, y, g;
        bool stateful = isProj(t, &i, g) || isSigDelay(t, x, y) || isSigPrefix(t, x, y);
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
            if (seenC.insert(t).second) {
                fDisplayCapturePoints.push_back(t);
            }
            continue;
        }
        if (!tailCarries(t)) {
            // inputs, tables, generators... : computed in-loop, captured
            if (seenC.insert(t).second) {
                fDisplayCapturePoints.push_back(t);
            }
            continue;
        }
        for (int k = 0; k < t->arity(); k++) {
            work.push_back(t->branch(k));
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
        return subst("($0 $1 $2)", displayExpr(x), gBinOpTable[op]->fName, displayExpr(y));
    }
    if (isSigIntCast(t, x)) {
        return subst("int(+$0)", displayExpr(x));
    }
    if (isSigFloatCast(t, x)) {
        return subst("$1(+$0)", displayExpr(x), ifloat());
    }
    if (isSigSelect2(t, sel, x, y)) {
        return subst("(($0) ? $1 : $2)", displayExpr(sel), displayExpr(y), displayExpr(x));
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
            fUITree.addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(vn), d));
            setCompiledExpression(d, subst("$1($0)", vn, ifloat()));
            continue;
        }
        std::string varname = getFreshID("fbargraph");
        fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
        fUITree.addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), d));
        fClass->addZone4(subst("$0 = $1;", varname, displayExpr(x)));
    }
}

string ScalarCompiler::generateVBargraph(Tree sig, Tree path, Tree min, Tree max, const string& exp)
{
    string varname = getFreshID("fbargraph");
    fClass->addDeclCode(subst("$1 \t$0;", varname, xfloat()));
    fUITree.addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

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
    fUITree.addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

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

    fUITree.addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

    fClass->addDeclCode(subst("Soundfile* \t$0;", varname));

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
        return generateCacheCode(sig, subst("$0[$1]", CS(tbl), CS(ri)));
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
    std::string dl0 = generateDelayLine(analyzeDelayType(sig), ctype, vecname, delay, count, mono,
                                        CS(def), getConditionCode(def));

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
 * various compilation options. Probe wrapper : FAUST_SS_RESIDENCE prints, once
 * per line, the data of the residence election (depth, real taps, density,
 * elected type) -- the map that will decide the per-line mcd (PILE 24).
 *
 * @param sig
 * @return DelayType
 */
DelayType ScalarCompiler::analyzeDelayType(Tree sig)
{
    DelayType dt = analyzeDelayTypeAux(sig);
    if (getenv("FAUST_SS_RESIDENCE") && fResidenceSeen.insert(sig).second) {
        Occurrences* occ = fOccMarkup->retrieve(sig);
        int          mxd = occ ? occ->getMaxDelay() : 0;
        if (mxd > 0) {
            // real taps : the literal-delay read nodes that actually occur
            // (scan capped at 64 -- deeper lines have vanishing density)
            int scan = std::min(mxd, 64);
            int taps = 0, multi = 0;
            // k = 0 excluded : the current-value read does not consume the
            // line's storage (it compiles to the scalar expression)
            for (int k = 1; k <= scan; k++) {
                Tree fk = sigDelay(sig, sigInt(k));
                if (Occurrences* ok = fOccMarkup->retrieve(fk)) {
                    taps++;
                    if (ok->hasMultiOccurrences()) {
                        multi++;
                    }
                }
            }
            std::cerr << "RESIDENCE type=" << nameDelayType(dt) << " mxd=" << mxd
                      << " taps=" << taps << " multi=" << multi << " capped=" << (mxd > 64)
                      << " density=" << (double(taps + 1) / double(mxd + 1)) << std::endl;
        }
    }
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
            if (getenv("FAUST_SS_MONODEBUG")) {
                std::cerr << "MONOMISS count=" << count << " retrieve=" << (fo != nullptr)
                          << " kept=" << fRFKeptWriters.count(sig)
                          << " sacr=" << fRFSacrificedWriters.count(sig) << " " << ppsig(sig, 2)
                          << std::endl;
            }
        } else if (getenv("FAUST_SS_MONODEBUG")) {
            std::cerr << "MONOMISS count=" << count << " isproj=" << isProj(sig, &i, x) << " "
                      << ppsig(sig, 2) << std::endl;
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
            generateDelayLine(analyzeDelayType(exp[i]), ctype[i], vname[i], delay[i], count[i],
                              mono[i], CS(def), getConditionCode(def));
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

    fClass->addExecCode(Statement(getConditionCode(sig), subst("$0 = $1;", vperm, CS(e))));
    return vtemp;
}

/*****************************************************************************
 SELECT
 *****************************************************************************/

string ScalarCompiler::generateSelect2(Tree sig, Tree sel, Tree s1, Tree s2)
{
    return generateCacheCode(sig, subst("(($0) ? $1 : $2)", CS(sel), CS(s2), CS(s1)));
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
 * carried scalars shift, HIGHEST delay first (a chain d+2, d+1 must move
 * before its source is overwritten). Runs after the whole schedule
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
        std::sort(hs.begin(), hs.end(),
                  [](const AdjHigh* a, const AdjHigh* b) { return a->d > b->d; });
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
                src   = subst("$0[(IOTA-$1)&$2]", vecname, T(h->d), T(N - 1));
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
            return subst("$0[(IOTA-$1)&$2]", vecname, delayidx, T(N - 1));
        }
    }
}

string ScalarCompiler::generateDelayAccessRaw(Tree sig, Tree exp, int delay)
{
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
        std::string y = subst("($0 + $1)", CS(coefs[1]), sname[0]);
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
    oss << CS(coefs[1]);
    for (unsigned int i = coefs.size() - 1; i >= 3; i--) {
        if (isZero(coefs[i])) {
            continue;
        }
        string access = generateDelayAccessRaw(sig, sig, int(i) - 2);
        if (isOne(coefs[i])) {
            oss << " + " << access;
        } else {
            oss << " + (" << CS(coefs[i]) << ") * " << access;
        }
    }
    return generateDelayVec(sig, oss.str(), ctype, vname, o->getMaxDelay(), o->getDelayCount());
}

string ScalarCompiler::generateSum(Tree sig, const tvec& subs)
{
    faustassert(subs.size() > 1);
    // INT sums wrap through UNSIGNED arithmetic : a flat signed chain is
    // UB on overflow, and clang -O3 reassociates it under the no-overflow
    // assumption -- false for anything that lives off the wrap (the LCG
    // noise family : bit-exact under -fwrapv, garbage without). The
    // classic emitter's nested form merely survived by luck.
    const bool wrapInt = (getCertifiedSigType(sig)->nature() == kInt);
    ostringstream oss;
    string        sep   = "";
    int           terms = 0;
    oss << '(';
    if (wrapInt) {
        oss << "int(";
    }
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
    for (unsigned int i = 0; i < subs.size(); ++i) {
        if (!isZero(subs[i])) {
            if (wrapInt) {
                oss << sep << "uint32_t(" << CS(subs[i]) << ')';
            } else {
                oss << sep << CS(subs[i]);
            }
            terms++;
            sep = " + ";
        }
    }
    if (terms == 0) {
        oss << "0";
    }
    if (wrapInt) {
        oss << ')';
    }
    oss << " /* Sum */)";
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
        return generateCacheCode(sig, subst("($0) * ($1)", CS(coefs[1]), CS(coefs[0])));
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
        std::string enter = CS(coefs[0]);
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
                string pair = "(" + generateDelayAccessRaw(sig, exp, t) + " + " +
                              generateDelayAccessRaw(sig, exp, T - 1 - t) + ")";
                if (isOne(coefs[1 + t])) {
                    oss << sep << pair;
                } else {
                    oss << sep << CS(coefs[1 + t]) << " * " << pair;
                }
                sep = " + ";
            }
            if (T % 2 == 1 && !isZero(coefs[1 + T / 2])) {
                oss << sep;
                if (!isOne(coefs[1 + T / 2])) {
                    oss << CS(coefs[1 + T / 2]) << " * ";
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
                oss << sep << '(' << CS(coefs[i]) << ") * " << access;
            } else {
                oss << sep << CS(coefs[i]) << " * " << access;
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
        coefInitStream << CS(coefs[i]);
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
        std::string idx = subst("(IOTA-$0)&$1", CS(delay), T(N - 1));
        return generateCacheCode(sig, subst("$0[$1]", vecname, generateIotaCache(idx)));
    }
#else
    // FIX: We don't compile the delayed signal anymore. This is done by the general scheduling.
    // But we make sure the delayed signal has a vector name.

    // string    code = CS(exp);  // ensure exp is compiled to have a vector name
    std::string ctype, pname;
    getTypedNames(getCertifiedSigType(sig), "Veeec", ctype, pname);
    string    vecname = ensureVectorNameProperty(pname, exp);
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
            result = vecname;
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
                    subst("$0 = $1[(IOTA-$2)&$3];", aname, vecname, T(dc), T(N - 1)));
                fAdjHighs.push_back({exp, dc, aname});
                result = aname;
                break;
            }
            std::string idx = subst("(IOTA-$0)&$1", CS(delay), T(N - 1));
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
            if (getenv("FAUST_SS_RINGPRELOAD") && ccs.empty() && isPureRingAccess(exp, preIx) &&
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
            if (getenv("FAUST_SS_RINGPRELOAD") && ccs.empty() && isPureRingAccess(exp, preIx) &&
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
        fClass->addPostCode(Statement("", "IOTA = IOTA+1;"));
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
