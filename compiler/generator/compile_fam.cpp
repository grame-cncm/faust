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

// The family form (-fam, LA-FORME-FAMILLE) : the ScalarCompiler methods that
// recognize, plan, schedule and emit the families, kept apart from the scalar
// compiler proper. The declarations stay in compile_scal.hh.

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
#include "sigGenCut.hh"
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
            // NEVER TRANSFORM A GENERATOR (sigGenCut.hh). The freeze is not
            // an optimisation, but it is a traversal, and treeRewrite mints a
            // fresh variable for every rec it walks through -- so merely
            // walking past a table generator renames its letrec and makes the
            // free copy a different tree from the frozen one. Two tables of
            // 65536 floats, bit-identical, because a traversal went by.
            return sigGenCut(t);
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

// -fam-align <n> : the contract with the architecture file, checked by the
// generated code itself, in the CONSTRUCTOR. When the DSP is not on an n-byte
// boundary it prints one explicit message and stops the program : a
// deterministic failure at load time, instead of a random fault on the aligned
// loads -- and compute carries nothing of the contract.
//
// The constructor is the only place where nothing has touched the object yet.
// In instanceConstants the check came too late twice over (seen on rizen) :
// the C++ compiler merges the member stores that precede it into aligned
// vector stores, and `new mydsp()` on a class without a constructor
// zero-fills the object, with aligned stores too, before any code of ours
// runs. Declaring the constructor removes that zero-fill ; init sets every
// member anyway.
//
// Neither an exception (targets built without them could not compile the
// class) nor an assert (gone in production builds) would say it as plainly.
// The address goes through a volatile before the modulo : a plain test would
// be folded to "aligned" by the optimizer, which assumes the alignment that the
// type declares -- the very property under test.
void ScalarCompiler::emitFamAlignContract()
{
    const std::string n = T(gGlobal->gFamilyAlign);
    fClass->addIncludeFile("<cstdio>");
    fClass->addIncludeFile("<cstdlib>");
    fClass->addConstructorCode("// -fam-align : the architecture must place this DSP on an aligned address");
    fClass->addConstructorCode("volatile unsigned long long fam_a = (unsigned long long)(void*)this;");
    fClass->addConstructorCode(subst("if (fam_a % $0ULL != 0) {", n));
    fClass->addConstructorCode(subst(
        "\tfprintf(stderr, \"FAUST ERROR: this DSP was compiled with -fam-align $0, which requires the "
        "architecture to place it at an address aligned on $0 bytes. It is at %p (%llu mod $0).\\n\", "
        "(void*)this, fam_a % $0ULL);", n));
    fClass->addConstructorCode("\tabort();");
    fClass->addConstructorCode("}");
    // A declared constructor turns `new mydsp()` from a value-initialisation
    // (the object zero-filled by the language) into a default-initialisation
    // (members indeterminate until init). The object is therefore put in a
    // defined state here, once the alignment is known to hold -- the stores
    // below are then safe : sliders at their default values, states cleared.
    // Only the constants that depend on the sample rate wait for init, which
    // is required anyway. Not under -mem : the memory manager allocates
    // arrays after construction, and instanceClear would write through them.
    if (gGlobal->gMemoryManager < 0) {
        fClass->addConstructorCode("instanceResetUserInterface();");
        fClass->addConstructorCode("instanceClear();");
    }
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
bool famReadsGroupNow(Tree n, Tree group)
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
    bool                                       calls  = false;  // the body calls a transcendental function (log10, pow, exp...)
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
        if (getUserData(t) != (void*)gGlobal->gAbsPrim && getUserData(t) != (void*)gGlobal->gMinPrim &&
            getUserData(t) != (void*)gGlobal->gMaxPrim) {
            g.calls = true;  // a call the C++ vectorizer cannot take without a vector math library
        }
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
        if ((states < 1 && !plan.group) ||
            (outputs && (work < gGlobal->gFamilyMinOut || (int)plan.trees.size() < gGlobal->gFamilyMinMembers))) {
            // an automaton's state is its group ; an output or display family
            // needs enough members too (-fam-out-members, default eight : a loop of
            // six chains with three input arrays lost to the compiler's own
            // packing, spectralLevel x1.15)
            if (trace) {
                std::cerr << "fam refused : " << (outputs ? "outputs, " : "") << "family of " << plan.trees.size() << " : " << work
                          << " operations and " << states << " states per member (one state"
                          << (outputs ? " and " + T(gGlobal->gFamilyMinOut) + " operations, " + T(gGlobal->gFamilyMinMembers) + " members" : "")
                          << " needed)" << std::endl;
            }
            continue;
        }
        // a family of sums is emitted as one loop per host over that host's
        // members : with a member or two per host the loops are of one or two
        // cells (the grid's m<S><4..7>, insects). Whether that pays is the C++
        // compiler's business -- g++ 15 loses x1.2 to x1.7 on the whole grid,
        // Apple clang gains x0.3 to x0.8, clang 22 draws -- so the least number
        // of cells per host loop is an option (-fam-host, default 1), not a
        // rule.
        if (!outputs && !plan.group && plan.hosts.size() > 1 && gGlobal->gFamilyMinHost > 1) {
            std::vector<int> perHost(plan.hosts.size(), 0);
            for (int h : plan.memberHost) {
                perHost[h]++;
            }
            const int least = *std::min_element(perHost.begin(), perHost.end());
            if (least < gGlobal->gFamilyMinHost) {
                if (trace) {
                    std::cerr << "fam refused : family of " << plan.trees.size() << " over " << plan.hosts.size()
                              << " hosts : a host loop of " << least << " cell(s) (-fam-host " << gGlobal->gFamilyMinHost
                              << ")" << std::endl;
                }
                continue;
            }
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
    // -fam-align <n> (default 0 : none) aligns the family's arrays, class
    // members and locals of compute alike, on n bytes. The gain lives in the
    // MEMBERS : at a fixed offset in an object whose alignment the type
    // declares, the C++ compiler vectorizes with aligned loads and no peeling
    // prologue. Aligning the locals alone buys nothing measurable.
    //
    // But the object is placed by the architecture file -- with new, malloc,
    // a buffer, or inside another object -- and nothing obliges it to honour
    // an over-alignment, whatever the C++ standard. The option is therefore a
    // CONTRACT with the architecture : the DSP must sit on an n-byte
    // boundary. An object placed elsewhere would fault on the aligned loads
    // (x86), at random, according to where the allocator put it. So the
    // generated code checks the contract itself in its constructor (see
    // emitFamAlignContract), and stops with an explicit message when it is
    // broken, rather than faulting at random.
    const std::string ali = gGlobal->gFamilyAlign > 0 ? "alignas(" + T(gGlobal->gFamilyAlign) + ") " : "";
    if (gGlobal->gFamilyAlign > 0 && !fFamAlignContract) {
        fFamAlignContract = true;
        emitFamAlignContract();
    }
    // the automaton's index tables, for the neighbourhoods that are not affine
    for (int k : g.autoTables) {
        fClass->addDeclCode(subst(ali + "int \tfFam$0Idx$1[$2];", T(g.id), T(k), T(P)));
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
            fClass->addDeclCode(subst(ali + "$0 \t$1_$2[$3];", g.ty, kv.first, T(k), T(P)));
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
            fClass->addDeclCode(subst(ali + "$0 \tfFam$1D$2[$3];", ct, T(g.id), T(n), T(P)));
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
        fClass->addDeclCode(subst(ali + "$0 \tfFam$1T$2[$3];", ctype, T(g.id), T(k), T(P)));
        for (int m = 0; m < P; m++) {
            const std::string cc = famCoef(slots[m][k]);
            fClass->addZone3(subst("fFam$0T$1[$2] = $3;", T(g.id), T(k), T(m), cc));
        }
    }
    // the delayed inputs of an automaton : captured at the top of the sample
    for (int k : g.usedPreSlots) {
        fClass->addDeclCode(subst(ali + "$0 \tfFam$1Pre$2[$3];", g.ty, T(g.id), T(k), T(P)));
        for (int m = 0; m < P; m++) {
            fClass->addPreCode(Statement("", subst("fFam$0Pre$1[$2] = $3;", T(g.id), T(k), T(m), famCS(plan.aslots[m][k]))));
        }
    }
    // the inputs that differ per member : an array filled every sample, before the loop
    std::ostringstream fill;
    for (int k : g.usedASlots) {
        fill << ali << g.ty << " " << subst("fFam$0In$1[$2];", T(g.id), T(k), T(P));
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
    const int kFamLoopWeightMin  = 20;  // 4 to 7 cells : one masked iteration, worth it for a heavy body only
    // 8 to 15 cells : a full vector of eight, worth it from sixteen operations on (the fine grid, eight chains :
    // 3.2 ns against 7.8 at 16, 3.4 against 9.3 at 18 ; at 12 the edge -- 3.1 against 3.4 there, but
    // parametricEqLab's eleven cells of 13 lose x1.07) -- unless the body calls a transcendental function, which
    // the vectorizer cannot take : the display chains (a log10 each) only lose to an imposed width. A masked
    // remainder (vectorize_predicate) is never right (nine cells : 5.2 -> 18.4 ns).
    const int kFamLoopWeightMin8 = g.calls ? kFamLoopWeightMin : 16;
    const int weight             = (int)plan.priv.size() / std::max(1, P);
    if (trace) {
        std::cerr << "FAM LOOP family " << g.id << " : " << P << " cells, weight " << weight << " (" << plan.priv.size()
                  << " private nodes)" << std::endl;
    }
    auto body = [&](const std::string& acc, int lo, int hi) {
        const int cells = hi - lo;
        if (cells >= kFamLoopMarkerMin && cells < kFamLoopMarkerMax && weight >= (cells >= 8 ? kFamLoopWeightMin8 : kFamLoopWeightMin)) {
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
        loop << ali << g.ty << " " << name << "[" << P << "];";
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
        // the automaton's own arrays, aligned like the rest of the family's
        // (-fam-align, a contract with the architecture : see emitFamilyLoop)
        const std::string ali = gGlobal->gFamilyAlign > 0 ? "alignas(" + T(gGlobal->gFamilyAlign) + ") " : "";
        for (int d = 1; d <= D; d++) {
            fClass->addDeclCode(subst(ali + "$0 \tfFam$1S_$2[$3];", ifloat(), id, T(d), T(N)));
            fClass->addClearCode(subst("for (int j = 0; j < $2; j++) { fFam$0S_$1[j] = 0; }", id, T(d), T(N)));
        }
        fClass->addZone2(subst(ali + "$0 \tfFam$1New[$2];", ifloat(), id, T(N)));
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
