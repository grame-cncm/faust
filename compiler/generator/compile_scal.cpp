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

// FAUST_SS_QUALITY=1 : imprime le vecteur qualité (grille U x cycles du
// modèle) de l'ordre choisi -- remplissage = cases occupées / disponibles.
// Le remplissage est celui de la machine ABSTRAITE (latence 1, U slots),
// le diagnostic de Yann : faut-il un effort de remplissage, ou le résidu
// est-il ailleurs (adjacence isomorphe, régimes mémoire) ?
static schedule<Tree> ocppSchedule(const digraph<Tree>& G)
{
    schedule<Tree> S = ocppScheduleRaw(G);
    if (getenv("FAUST_SS_CHECK")) {
        // le graphe immédiat est-il un DAG, et l'ordre émis le
        // respecte-t-il ? (toute arête présente est une contrainte dure :
        // la dépendance doit être ordonnancée avant son consommateur)
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
        // valeur "R,U" : machine d'ÉVALUATION (comparer des ordres générés
        // avec des réglages différents sur une même référence) ; toute
        // autre valeur : les réglages de génération
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

    startTiming("conditionAnnotation");
    conditionAnnotation(L2);
    endTiming("conditionAnnotation");

    startTiming("recursivnessAnnotation");
    recursivnessAnnotation(L2);  // Annotate L2 with recursivness information
    endTiming("recursivnessAnnotation");

    startTiming("L2 typeAnnotation");
    typeAnnotation(L2, true);  // Annotate L2 with type information and check causality
    endTiming("L2 typeAnnotation");

    if (gGlobal->gMinDelay > 0) {
        // semantic delay floor: needs the intervals just computed, rebuilds
        // trees, so the annotations are redone in the same order as above
        L2 = applyDelayFloor(L2, gGlobal->gMinDelay);
        conditionAnnotation(L2);
        recursivnessAnnotation(L2);
        typeAnnotation(L2, true);
    }

    startTiming("sharingAnalysis");
    sharingAnalysis(L2, fSharingKey);  // Annotate L2 with sharing count
    endTiming("sharingAnalysis");

    startTiming("occurrences analysis");
    delete fOccMarkup;
    fOccMarkup = new OccMarkup(fConditionProperty);
    fOccMarkup->mark(L2);  // Annotate L2 with occurrences analysis
    endTiming("occurrences analysis");

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

void ScalarCompiler::conditionAnnotation(Tree l)
{
    while (isList(l)) {
        conditionAnnotation(hd(l), gGlobal->nil);
        l = tl(l);
    }
}

void ScalarCompiler::conditionAnnotation(Tree t, Tree nc)
{
    // Check if we need to annotate the tree with new conditions
    auto p = fConditionProperty.find(t);
    if (p != fConditionProperty.end()) {
        Tree cc = p->second;
        Tree xc = _OR_(cc, nc);
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
    };
    std::vector<LSOp>   fOps;
    std::map<Tree, int, treeorder> fOpOf;      // sample-rate op tree -> index in fOps
    std::map<int, int>  fStoreOf;   // materialized index -> its store op
    int                 fLoopNo = 0;  // emission counter, gives each loop a stable id

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

    // flux par boucle : clés de lecture (tampon, retard/16 -- les retards
    // d'une même ligne de cache forment UN flux pour le préchargeur ;
    // -1 : retard variable) et tampons écrits. Remplis pendant le walk du
    // bloc courant, lus par emitLoop, remis à zéro entre blocs.
    std::set<std::pair<int, int>> fCurReadStreams;
    std::set<int>                 fCurWriteStreams;

    Operand refOperand(int idx, const std::string& dcode, bool maybeInstant, int curScc)
    {
        Operand o;
        if (maybeInstant && fSN.blockOf(idx) == curScc && fAliasIx[idx] < 0) {
            return fRootOf.at(idx);
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
            fCurReadStreams.insert({-1000 - i, 0});  // un flux par canal d'entrée
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
            o.op = newOp(subst("int($0)", operandCode(a)), deps, false, false, true);
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
            o.op = newOp(subst("$1($0)", operandCode(a), ifloat()), deps, false, false, false);
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
                                          int* peakOut = nullptr)
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
            for (int slot = 0; slot < U && !readyNow.empty(); slot++) {
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
                    if (live >= R) {
                        score = 1000 * (freed - creates) + height[k];
                    } else {
                        score = 1000 * height[k] + freed;
                    }
                    // calls prefer low-live cycles: penalize a call issued
                    // while more than RCALLEE values are live
                    if (ops[lo + k].isCall && live > RCALLEE) {
                        score -= 500000;
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
                done++;
                order.push_back(lo + k);
                emittedThisCycle.push_back(k);
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
                         int loadWOverride = -1, bool* hasCallOut = nullptr)
    {
        const long CL = gGlobal->gLSCl, SPILLW = gGlobal->gLSSpillW;
        const std::vector<Tree>& mat = fSN.materialized();
        std::vector<LSOp>        sops;
        std::map<Tree, int, treeorder>      memo;
        std::map<int, int>       rootOf;  // member -> shadow op index (-1: leaf)
        std::set<int>            inSet(members.begin(), members.end());

        // a buffer load costs an issue slot (the model's Read): this is what
        // makes fusion visibly profitable to the oracle -- scalarized in-set
        // reads cost nothing, the same reads across a boundary cost a slot
        const int loadW = (loadWOverride >= 0) ? loadWOverride : gGlobal->gLSLoadW;
        auto load = [&](Tree t, std::vector<int> deps) -> int {
            if (loadW == 0) {
                return -1;  // loads free (leaf)
            }
            int id = -1;
            for (int w = 0; w < loadW; w++) {
                LSOp o;
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
                if (idx >= 0) {
                    // in-set instantaneous reads are scalarized (the root
                    // value); everything else is a buffer load
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
            auto op = [&](std::vector<int> deps, bool call) -> int {
                LSOp o;
                for (int d : deps) {
                    if (d >= 0) {
                        o.deps.push_back(d);
                    }
                }
                o.isCall = call;
                sops.push_back(o);
                int id = (int)sops.size() - 1;
                memo[t] = id;
                return id;
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
                return constantsLive ? op({}, false) : -1;
            }
            if (isSigInput(t, &i)) {
                return -1;
            }
            if (isSigAttach(t, x, y) && !SuperNodeGraph::isSlow(y)) {
                return op({sw(x, false), sw(y, false)}, false);
            }
            if (SuperNodeGraph::isSlow(t)) {
                return constantsLive ? op({}, false) : -1;
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
                    if (dvar && !SuperNodeGraph::isSlow(y)) {
                        return load(t, {sw(y, false)});  // indexed load
                    }
                    return load(t, {});  // constant-delay buffer load
                }
                return sw(x, false);
            }
            if (isSigBinOp(t, &i, x, y)) {
                bool call = (i == kRem) && (getCertifiedSigType(t)->nature() == kReal);
                return op({sw(x, false), sw(y, false)}, call);
            }
            if (getUserData(t)) {
                std::vector<int> deps;
                for (int k = 0; k < t->arity(); k++) {
                    deps.push_back(sw(t->branch(k), false));
                }
                return op(deps,
                          SuperNodeGraph::isCallPrim(((xtended*)getUserData(t))->name()));
            }
            if (isSigFFun(t, ff, largs)) {
                std::vector<int> deps;
                for (int k = 0; k < ffarity(ff); k++) {
                    deps.push_back(sw(nth(largs, k), false));
                }
                return op(deps, true);
            }
            if (isSigSelect2(t, sel, x, y)) {
                return op({sw(sel, false), sw(x, false), sw(y, false)}, false);
            }
            if (isSigIntCast(t, x) || isSigBitCast(t, x) || isSigFloatCast(t, x)) {
                return op({sw(x, false)}, false);
            }
            if (isSigRDTbl(t, tb, ri) && isSigWRTbl(tb, size, gen)) {
                return op({sw(ri, false)}, false);
            }
            if (isSigVBargraph(t, label, x, y, z) || isSigHBargraph(t, label, x, y, z)) {
                return op({sw(z, false)}, false);
            }
            if (isSigAssertBounds(t, x, y, z)) {
                return sw(z, false);
            }
            return op({}, false);  // unknown: one slot, no deps
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
        return (long)gGlobal->gVecSize * (cycles + SPILLW * overR) + CL;
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

    // 1-2. the partition (materialization, reference graph, blocks).
    // References with certified delay >= the chunk size do not constrain
    // grouping: cycles with long feedback edges split legally (the d < N
    // restriction of LOOPMERGING.md)
    fSN.build(L, sched, gGlobal->gVecSize);

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
                        taps++;
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
        // -- terme de FLUX de l'oracle (budget du préchargeur, mesuré
        // S ~ 10-16 sur karplus : G4 a 9 flux et gagne, G8 en a 17 et
        // décroche). Un flux : un tampon d'HISTORique réel (maxDelay >= 16
        // flottants -- les petits locaux chauds ne comptent pas, sinon le
        // budget bloquerait les grandes fusions gagnantes type frenchBell),
        // lu ou écrit, plus les canaux d'entrée. Clés par membre calculées
        // UNE fois ; le refus porte sur l'UNION des flux des deux blocs.
        long streamBudget = 12;
        if (const char* e = getenv("FAUST_LS_STREAMS")) {
            streamBudget = std::atol(e);  // 0 : désactivé
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
                    keys.insert(long(m) * 1000 + 999);  // sa propre écriture
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
                return false;  // budget de flux du préchargeur
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
                return 0;  // budget de flux du préchargeur
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
        if (fSN.blockCount() <= 1 && overR == 0 && peak < gGlobal->gLSRegisters && !hasCall &&
            shortD) {
            throw LoopSplitUnsupported("single super-node within the register budget", true);
        }
    }
    const std::vector<Tree>& mat = fSN.materialized();
    int                      n   = (int)mat.size();

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

    // 4. loop bodies, one per block, in dependencies-first order (members
    // already come in instantaneous-dependency order)
    std::ostringstream loops;
    for (int b = 0; b < fSN.blockCount(); b++) {
        int lo = (int)fOps.size();
        fOpOf.clear();  // tls temporaries are loop-scoped
        fCurReadStreams.clear();
        fCurWriteStreams.clear();
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
        int hi = (int)fOps.size();
        emitLoop(loops, lo, hi);
    }

    // 5. output loops
    {
        int  i  = 0;
        Tree l1 = L;
        for (; isList(l1); l1 = tl(l1), i++) {
            int lo = (int)fOps.size();
            fOpOf.clear();
            fCurReadStreams.clear();
            fCurWriteStreams.clear();
            fCurWriteStreams.insert(-2000 - i);  // le canal de sortie
            Operand root = walk(hd(l1), -1, false);
            std::vector<int> deps;
            addDep(deps, root);
            newOp(subst("output$0[i] = $2$1;", T(i), operandCode(root), xcast()), deps, true,
                  false, false);
            int hi = (int)fOps.size();
            emitLoop(loops, lo, hi);
        }
        faustassert(i == nouts);
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
            runlen = 0;
        }
        prevSh = sh;
        prevIx = k;
    }
    packs4 += (runlen + 1) / 4;
    out << "// loop " << fLoopNo++ << ": " << n << " ops, model(R=" << R << ",U=" << U << "): " << cycles
        << " cycles, pressure " << peak << "/" << R << ", occupancy " << occ << "%"
        << ", iso " << isoadj << " adj / " << packs4 << " packs4"
        << ", streams " << fCurReadStreams.size() << "r+" << fCurWriteStreams.size() << "w";
    if (overR > 0) {
        out << ", over-pressure " << overR << " (spill risk)";
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
    // contextor recursivness(0);
    L = prepare(L);  // optimize, share and annotate expression

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
        Tree Lf = revealFIR(L);  // (revealIIR : étage 2 — motifs horloges)
        int  nfir = 0, niir = 0, maxtaps = 0;
        long taps = 0;
        std::set<Tree>    seen;
        std::vector<Tree> work;
        for (Tree l = Lf; isList(l); l = tl(l)) {
            work.push_back(hd(l));
        }
        while (!work.empty()) {
            Tree t = work.back();
            work.pop_back();
            if (!seen.insert(t).second) {
                continue;
            }
            tvec cs;
            if (isSigFIR(t, cs)) {
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
                // line pool their taps (the identity simplify shim keeps
                // sibling kernels unmerged at stage 1, but their union is
                // what the delay line serves)
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
        if (getenv("FAUST_SS_FIRTYPE")) {
            // la sonde du typage : annoter la copie révélée (les nœuds FIR
            // passent dans l'algèbre du point fixe) et montrer le type du
            // premier noyau -- nature, variabilité, intervalle
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
    // force a specific compilation order
    auto G = immediateGraph(L);
    auto S = ocppSchedule(G);
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
        // pic de flux fenêtré : combien de flux mémoire distincts une
        // fenêtre de W instructions consécutives touche-t-elle ? Un flux :
        // (source, retard/16) en lecture -- les retards d'une même ligne de
        // cache se confondent --, la source elle-même en écriture (son
        // tampon avance en [i]), un par canal d'entrée. Sensible à l'ORDRE :
        // df visite les tampons un à un, un ordre par niveaux les entrelace
        // tous -- le préchargeur ne suit qu'un petit nombre de flux.
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
                // un tampon qui tient dans une ligne de cache (16 floats)
                // a des adresses fixes : ce n'est pas un flux
                auto isStreamBuf = [&](Tree b) {
                    Occurrences* ob = fOccMarkup->retrieve(b);
                    return ob && ob->getMaxDelay() >= 16;
                };
                if (isSigDelay(n, x, y)) {
                    if (isStreamBuf(x)) {
                        interval I = getCertifiedSigType(y)->getInterval();
                        int dmin = int(I.lo());
                        // retard variable (ou non certifié >= 1) : un flux
                        // quand même, à clé propre -- la lecture avance
                        ks.push_back({(long)(size_t)(void*)x, dmin >= 1 ? dmin / 16 : -1});
                    }
                } else if (isSigInput(n, &ich)) {
                    ks.push_back({-1000 - ich, 0});
                }
                if (isStreamBuf(n)) {
                    ks.push_back({(long)(size_t)(void*)n, -7});  // l'écriture du tampon
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

    // FAUST_SS_SIG : la signature statique du programme, une ligne — la
    // matière première du sélecteur automatique (couche 1). Tout se
    // calcule sans bench : taille, borne de récurrence, comptes
    // calcul/mémoire, flux (total et pic fenêtré sur l'ordre df), formes.
    if (getenv("FAUST_SS_SIG")) {
        int nalu = 0, nmem = 0;
        for (const auto& n : G.nodes()) {
            if (ocppIsMemNode(n)) {
                nmem++;
            } else {
                nalu++;
            }
        }
        // flux : clés réelles (tampons >= 16), total + pic fenêtré (64)
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
        // formes : classes, part bankable (multiplicité >= 4), top-3
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
        std::cerr << "SS_SIG nodes=" << G.nodes().size() << " recmii=" << ocppTightRecMII(L)
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

        for (int i = 0; isList(L); L = tl(L), i++) {
            Tree s = hd(L);
            fClass->addExecCode(Statement("", subst("output$0[i] = $2($1);  // Zone Exec Code",
                                                    T(i), generateCacheCode(s, CS(s)), xcast())));
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

string ScalarCompiler::generateCode(Tree sig)
{
    int     i;
    int64_t i64;
    double  r;
    Tree    size, gen, wi, ws, ri, c, sel, x, y, z, label, tb, ff, largs, type, name, file, sf;

    // printf("compilation of %p : ", sig); print(sig); printf("\n");

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

    else if (isSigDelay(sig, x, y)) {
        return generateDelayAccess(sig, x, y);
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
string ScalarCompiler::generateIotaCache(const std::string& exp)
{
    if (fIotaCache.find(exp) == fIotaCache.end()) {
        string vname = getFreshID("vIota");
        fClass->addExecCode(Statement("", subst("int $0 = $1;", vname, exp)));
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
        return generateVariableStore(sig, exp);

    } else if (sharing == 1) {
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

string ScalarCompiler::generateIntCast(Tree sig, Tree x)
{
    return generateCacheCode(sig, subst("int($0)", CS(x)));
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
    return generateCacheCode(sig, subst("$1($0)", CS(x), ifloat()));
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
 * @brief indicate best delay implementation type for a signal according to its max delay and
 * various compilation options
 *
 * @param sig
 * @return DelayType
 */
DelayType ScalarCompiler::analyzeDelayType(Tree sig)
{
    Occurrences* occ = fOccMarkup->retrieve(sig);
    faustassert(occ != nullptr);
    int mxd   = occ->getMaxDelay();
    int count = occ->getDelayCount();

    if (mxd == 0) {
        return DelayType::kZeroDelay;
    }
    if (mxd == 1) {
        // check for special mono delay case
        int  i;
        Tree x, var, le;
        if (count == 1 && isProj(sig, &i, x) && isRec(x, var, le) && (len(le) == 1)) {
            // potential simple recursion if sig@1 is used only once
            Tree f = sigDelay(sig, sigInt(1));  // check if it is a delay
            if (fOccMarkup->retrieve(f) && !fOccMarkup->retrieve(f)->hasMultiOccurrences()) {
                return DelayType::kMonoDelay;
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
            result = vecname;
            break;

        case DelayType::kSingleDelay:
        case DelayType::kCopyDelay:
        case DelayType::kDenseDelay:
            result = subst("$0[$1]", vecname, CS(delay));
            break;

        case DelayType::kMaskRingDelay:
        case DelayType::kSelectRingDelay:
            int         N   = pow2limit(mxd + 1);
            std::string idx = subst("(IOTA-$0)&$1", CS(delay), T(N - 1));
            result          = subst("$0[$1]", vecname, generateIotaCache(idx));
            break;
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
            fClass->addExecCode(Statement(ccs, subst("$0 = $1;", vname, exp)));
            fClass->addZone3Post(subst("$0State = $0;", vname));
            return vname;

        case DelayType::kSingleDelay:
            fClass->addDeclCode(subst("$0 \t$1State; // Single Delay", ctype, vname));
            fClass->addClearCode(subst("$0State = 0;", vname));
            fClass->addZone2(subst("$0 \t$1[$2];", ctype, vname, T(mxd + 1)));
            fClass->addZone3(subst("$0[1] = $0State;", vname));
            fClass->addExecCode(Statement(ccs, subst("$0[0] = $1;", vname, exp)));
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

            // execute
            std::string idx      = subst("IOTA&$0", T(N - 1));
            std::string cacheidx = generateIotaCache(idx);
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
