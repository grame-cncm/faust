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

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "DirectedGraphAlgorythm.hh"
#include "export.hh"
#include "tlib-error.hh"
#include "tlib.hh"

using namespace std;

// The recursion symbols and property keys are owned by the library. The symbols are interned at
// tlib::init()/cleanup() reset time so calcTreeAperture(), called on every tree construction, does
// not have to run a lazy initialization path for ordinary trees.
// The property-key TREES (recdefKey, debruijn2symKey) are still created lazily, but only from the
// rec/deBruijn2SymCached entry points, never during construction.
static Sym  gDebruijnSym     = nullptr;
static Sym  gDebruijnRefSym  = nullptr;
static Sym  gSymRecSym       = nullptr;
static Sym  gSubstituteSym   = nullptr;
static Sym  gSymLiftnSym     = nullptr;
static Tree gRecDefKey       = nullptr;
static Tree gDeBruijn2SymKey = nullptr;

static inline void initRecSymbols()
{
    gDebruijnSym    = symbol("DEBRUIJN");
    gDebruijnRefSym = symbol("DEBRUIJNREF");
    gSymRecSym      = symbol("SYMREC");
    gSubstituteSym  = symbol("SUBSTITUTE");
    gSymLiftnSym    = symbol("LIFTN");
}

static inline Tree recdefKey()
{
    if (gRecDefKey == nullptr) {
        gRecDefKey = tree(symbol("RECDEF"));
    }
    return gRecDefKey;
}

static inline Tree debruijn2symKey()
{
    if (gDeBruijn2SymKey == nullptr) {
        gDeBruijn2SymKey = tree(symbol("deBruijn2Sym"));
    }
    return gDeBruijn2SymKey;
}

// Internal hook used by tlib::init()/cleanup() (see tlib.cpp)
void tlibResetRecInternals()
{
    gDebruijnSym     = nullptr;
    gDebruijnRefSym  = nullptr;
    gSymRecSym       = nullptr;
    gSubstituteSym   = nullptr;
    gSymLiftnSym     = nullptr;
    gRecDefKey       = nullptr;
    gDeBruijn2SymKey = nullptr;
    initRecSymbols();
}

// Local memos for the conversions : the memo lives for one conversion call
// and dies with it, so the conversion leaves no property attached to the
// trees (see REWRITE-SPEC.md, "Memo local par appel"). The property-cached
// variants (deBruijn2SymCached, substituteReady) are kept for callers that
// explicitly want a persistent cache.
//
// The substitution memo is keyed by (tree, level) : 'id' is fixed for one
// substitution call, and 'level' grows when the traversal crosses a rec
// binder. The sym2deBruijn memo is keyed by (tree, env) : the same subtree
// can convert differently under different binder environments.
struct TreeIntPairHash {
    std::size_t operator()(const std::pair<Tree, int>& k) const
    {
        return std::hash<const void*>()(k.first) * 31u + std::size_t(k.second);
    }
};
using SubstMemo = std::unordered_map<std::pair<Tree, int>, Tree, TreeIntPairHash>;

struct TreePairHash {
    std::size_t operator()(const std::pair<Tree, Tree>& k) const
    {
        return std::hash<const void*>()(k.first) * 31u + std::hash<const void*>()(k.second);
    }
};
using Sym2DebMemo = std::unordered_map<std::pair<Tree, Tree>, Tree, TreePairHash>;

// Declaration of implementation
static Tree deBruijn2SymCachedReady(Tree t);
static Tree calcDeBruijn2SymCachedReady(Tree t);
static Tree deBruijn2SymMemo(Tree t, std::unordered_map<Tree, Tree>& memo);
static Tree substituteMemo(Tree t, int level, Tree id, SubstMemo& memo);
static std::ostream& printTreeExpr(std::ostream& out, Tree t);
static Tree substituteReady(Tree t, int n, Tree id);
static Tree calcsubstituteReady(Tree t, int level, Tree id);
Tree        liftn(Tree t, int threshold);
static Tree calcliftnReady(Tree t, int threshold);

static inline bool isDebruijnRec(Tree t, Tree& body)
{
    return isTree(t, gDebruijnSym, body);
}

static inline bool isDebruijnRef(Tree t, int& level)
{
    Tree u;
    if (!isTree(t, gDebruijnRefSym, u)) return false;
    return isInt(u->node(), &level);
}

static inline bool isSymbolicRec(Tree t, Tree& var, Tree& body)
{
    if (!isTree(t, gSymRecSym, var)) return false;
    body = t->getProperty(recdefKey());
    return true;
}

static inline bool isSymbolicRef(Tree t, Tree& var)
{
    return isTree(t, gSymRecSym, var);
}

// Tree	NOVAR = tree("NOVAR");

//-----------------------------------------------------------------------------------------
// rec, isRec : declare recursive trees
//-----------------------------------------------------------------------------------------

// de Bruijn declaration of a recursive tree
Tree rec(Tree body)
{
    return tree(gDebruijnSym, body);
}

bool isRec(Tree t, Tree& body)
{
    return isDebruijnRec(t, body);
}

Tree ref(int level)
{
    TLIB_ASSERT(level > 0);
    return tree(gDebruijnRefSym,
                tree(level));  // reference to enclosing recursive tree starting from 1
}

bool isRef(Tree t, int& level)
{
    return isDebruijnRef(t, level);
}

//-----------------------------------------------------------------------------------------
// Recursive tree in symbolic notation (using a recursive definition property)
//-----------------------------------------------------------------------------------------

// declaration of a recursive tree using a symbolic variable
Tree rec(Tree var, Tree body)
{
    Tree t = tree(gSymRecSym, var);
    t->setProperty(recdefKey(), body);
    return t;
}

bool TLIB_API isRec(Tree t, Tree& var, Tree& body)
{
    return isSymbolicRec(t, var, body);
}

Tree ref(Tree id)
{
    return tree(gSymRecSym, id);  // reference to a symbolic id
}

bool isRef(Tree t, Tree& v)
{
    return isSymbolicRef(t, v);
}

//-----------------------------------------------------------------------------------------
// The aperture of a tree is the deepest deBruijn reference it contains.
// Symbolic references count as zero which means that a tree with aperture
// 0 has no free deBruijn references.

int CTree::calcTreeAperture(const Node& n, const tvec& br)
{
    return calcTreeAperture(n, int(br.size()), br.empty() ? nullptr : br.data());
}

int CTree::calcTreeAperture(const Node& n, int ar, const Tree br[])
{
    int x;
    if (n == gDebruijnRefSym) {
        TLIB_ASSERT(br[0]);
        if (isInt(br[0]->node(), &x)) {
            return x;
        } else {
            return 0;
        }

    } else if (n == gDebruijnSym) {
        TLIB_ASSERT(br[0]);
        return br[0]->fAperture - 1;

    } else {
        // return max aperture of branches
        int rc = 0;
        for (int i = 0; i < ar; ++i) {
            if (br[i]->aperture() > rc) {
                rc = br[i]->aperture();
            }
        }
        return rc;
    }
}

//-----------------------------------------------------------------------------------------
// The kinds occurring in a tree : a synthesized set, unioned over the branches (see the
// CONVENTION note on CTree::kContainsRec in tree.hh).
//
// Defined here rather than in tree.cpp because this is where the recursive node symbols
// live -- the same arrangement calcTreeAperture already uses.
//
// SOUNDNESS DURING INITIALIZATION : the three symbols are nullptr until initRecSymbols()
// runs, so a tree built before that compares equal to none of them and gets kContainsRec
// clear. That is correct, not a race : building a recursive node requires passing the
// symbol to tree(), so a pre-init tree provably is not one, and cannot contain one.
// calcTreeAperture already relies on exactly this argument.
//
// SOUNDNESS UNDER MUTATION : a symbolic rec node carries its body as a PROPERTY, attached
// after construction. The rule below never reads properties -- only the node and the
// branches, both fixed at construction -- so the bit cannot go stale. A rec node is caught
// by its own symbol, whether it occurs as a definition or as a reference (in symbolic form
// the two are the same node), so "no recursive node below" really does mean the subtree is
// a finite, recursion-free DAG.

unsigned int CTree::calcTreeContains(const Node& n, const tvec& br)
{
    return calcTreeContains(n, int(br.size()), br.empty() ? nullptr : br.data());
}

unsigned int CTree::calcTreeContains(const Node& n, int ar, const Tree br[])
{
    // Union, never replacement : the node's own kind is added to what the branches carry,
    // so a rule for one bit can never discard another bit's information.
    unsigned int c =
        (n == gSymRecSym || n == gDebruijnSym || n == gDebruijnRefSym) ? kContainsRec : 0;
    for (int i = 0; i < ar; ++i) {
        c |= br[i]->contains();
    }
    return c;
}

// Test/debug : recompute the kind bits of every live tree by an independent traversal and
// compare with what the constructor stored. This is the real safety net for a synthesized
// attribute -- it validates the bits on every tree the test suite ever built, not just on
// the handful a hand-written test remembers to check.
static unsigned int recomputeContains(Tree t, std::unordered_map<Tree, unsigned int>& memo)
{
    auto it = memo.find(t);
    if (it != memo.end()) {
        return it->second;
    }
    const Node&  n = t->node();
    unsigned int c =
        (n == gSymRecSym || n == gDebruijnSym || n == gDebruijnRefSym) ? CTree::kContainsRec : 0;
    // Insert before descending : a shared subtree may be reached again, and the branch DAG
    // is acyclic (a symbolic rec keeps its body in a property, not in a branch).
    memo[t]         = c;
    const int ar    = t->arity();
    for (int i = 0; i < ar; ++i) {
        c |= recomputeContains(t->branch(i), memo);
    }
    memo[t] = c;
    return c;
}

std::size_t CTree::checkContainsInvariant()
{
    std::unordered_map<Tree, unsigned int> memo;
    std::size_t                            mismatches = 0;
    for (std::size_t i = 0; i < gHashTableSize; i++) {
        for (Tree t = gHashTable[i]; t; t = t->fNext) {
            if (recomputeContains(t, memo) != t->contains()) {
                mismatches++;
            }
        }
    }
    return mismatches;
}

// lift(t) : increase free references by 1

Tree lift(Tree t)
{
    return liftn(t, 1);
}

Tree liftn(Tree t, int threshold)
{
    Tree L  = tree(Node(gSymLiftnSym), tree(Node(threshold)));
    Tree t2 = t->getProperty(L);

    if (!t2) {
        t2 = calcliftnReady(t, threshold);
        t->setProperty(L, t2);
    }
    return t2;
}

static Tree calcliftnReady(Tree t, int threshold)
{
    int  n;
    Tree u;

    if (isClosed(t)) {
        return t;

    } else if (isDebruijnRef(t, n)) {
        if (n < threshold) {
            // it is a bounded reference
            return t;
        } else {
            // it is a free reference
            return ref(n + 1);
        }

    } else if (isDebruijnRec(t, u)) {
        return rec(liftn(u, threshold + 1));

    } else {
        int  n1 = t->arity();
        tvec br(n1);
        for (int i = 0; i < n1; i++) {
            br[i] = liftn(t->branch(i), threshold);
        }
        return tree(t->node(), br);
    }
}

//-----------------------------------------------------------
// Transform a tree from deBruijn to symbolic representation
//-----------------------------------------------------------

Tree deBruijn2Sym(Tree t)
{
    TLIB_ASSERT(isClosed(t));
    std::unordered_map<Tree, Tree> memo;
    return deBruijn2SymMemo(t, memo);
}

Tree deBruijn2SymCached(Tree t)
{
    TLIB_ASSERT(isClosed(t));
    return deBruijn2SymCachedReady(t);
}

static Tree deBruijn2SymCachedReady(Tree t)
{
    Tree t2 = t->getProperty(debruijn2symKey());

    if (!t2) {
        t2 = calcDeBruijn2SymCachedReady(t);
        t->setProperty(debruijn2symKey(), t2);
    }
    return t2;
}

static Tree deBruijn2SymMemo(Tree t, std::unordered_map<Tree, Tree>& memo)
{
    auto it = memo.find(t);
    if (it != memo.end()) {
        return it->second;
    }

    Tree body, var;
    int  i;
    Tree result;

    if (isDebruijnRec(t, body)) {
        var = tree(unique("W"));
        SubstMemo smemo;
        result = rec(var, deBruijn2SymMemo(substituteMemo(body, 1, ref(var), smemo), memo));

    } else if (isSymbolicRef(t, var)) {
        result = t;

    } else if (isDebruijnRef(t, i)) {
        tlib::error("ASSERT : free de Bruijn reference found in deBruijn2Sym\n");
        result = t;

    } else {
        int  a = t->arity();
        tvec br(a);
        for (int i1 = 0; i1 < a; i1++) {
            br[i1] = deBruijn2SymMemo(t->branch(i1), memo);
        }
        result = tree(t->node(), br);
    }

    memo[t] = result;
    return result;
}

static Tree calcDeBruijn2SymCachedReady(Tree t)
{
    Tree body, var;
    int  i;

    if (isDebruijnRec(t, body)) {
        var = tree(unique("W"));
        return rec(var, deBruijn2SymCachedReady(substituteReady(body, 1, ref(var))));

    } else if (isSymbolicRef(t, var)) {
        return t;

    } else if (isDebruijnRef(t, i)) {
        tlib::error("ASSERT : free de Bruijn reference found in deBruijn2Sym\n");
        return t;

    } else {
        int  a = t->arity();
        tvec br(a);
        for (int i1 = 0; i1 < a; i1++) {
            br[i1] = deBruijn2SymCachedReady(t->branch(i1));
        }
        return tree(t->node(), br);
    }
}

//-----------------------------------------------------------
// Transform a tree from symbolic to deBruijn representation
//
// The conversion is organized around the DAG of mutually recursive groups
// (the strongly connected components of the dependency graph between
// recursive variables). A recursive node of the component currently being
// converted is inlined by extending the environment (mutual recursion needs
// the single-binder de Bruijn inlining); a recursive node of any OTHER
// component is converted separately, under an empty environment, into a
// CLOSED de Bruijn term reused from a closed memo. Every subterm whose
// converted form is closed (aperture 0, an O(1) test) is memoized by term
// only; the open skeleton uses the (term, environment) memo. Environments
// therefore stay small (the variables of one component) and shared closed
// sub-DAGs are converted exactly once.
//-----------------------------------------------------------

static int symbolicLevel(Tree var, Tree env)
{
    int level = 1;
    for (Tree l = env; isList(l); l = tl(l), ++level) {
        if (hd(l) == var) {
            return level;
        }
    }
    return 0;
}

// A tree is INVARIANT by sym2deBruijn (sym2deBruijn(t) == t) when no symbolic recursive
// node is reachable through its branches : every other node reconstructs to itself by
// hash-consing.
//
// This used to be a lazily memoized tree property. It is now a corollary of the
// synthesized kContainsRec bit : isRecFree() is slightly stronger (it also excludes
// deBruijn recursive nodes), so using it here is sound. It would only be less precise on
// a MIXED tree -- symbolic and deBruijn recursive nodes in the same term -- which the
// conversion never sees : sym2deBruijnAux only ever descends into symbolic subterms.
// Even then the cost would be a lost shortcut, never a wrong result : the generic branch
// rebuilds the node and hash-consing hands back the very same tree.
bool isSym2deBruijnInvariant(Tree t)
{
    return t->isRecFree();
}

struct Sym2DebState {
    const RecPlan&                 plan;             ///< the shared component partition
    std::unordered_map<Tree, Tree> closedMemo;       ///< closed results, keyed by term
    Sym2DebMemo                    envMemo;          ///< open results, keyed by (term, env)
    int                            currentSCC = -1;  ///< component being converted

    explicit Sym2DebState(const RecPlan& p) : plan(p) {}
};

// Collect every symbolic recursive node occurring in t WITHOUT crossing
// recursive definitions (bodies are attached as properties, not branches).
static void scanForRecs(Tree t, std::unordered_set<Tree>& visited, std::vector<Tree>& found)
{
    if (isSym2deBruijnInvariant(t)) {
        return;  // no symbolic recursive node below : nothing to collect
    }
    if (!visited.insert(t).second) {
        return;
    }
    Tree var;
    if (isSymbolicRef(t, var)) {
        found.push_back(t);  // rec and ref are the same node in symbolic form
        return;
    }
    for (int i = 0; i < t->arity(); i++) {
        scanForRecs(t->branch(i), visited, found);
    }
}

// Register every symbolic recursive node reachable from root (crossing recursive
// definitions through a worklist), build the dependency digraph, and partition it into
// strongly connected components.
//
// The components come from DirectedGraph's Tarjan rather than a hand-written one :
// recursive-node components are exactly what graph2dag/partition were written for. Only
// the PARTITION matters -- sccOf is consumed solely by "same component ?" tests -- so any
// numbering of the components is correct. A node with no outgoing recursive edge is added
// on its own so it still gets a singleton component ; a direct self-reference becomes a
// self-loop, hence again a singleton, which is the intended behaviour for x = f(x).
RecPlan::RecPlan(Tree root)
{
    std::vector<Tree>        work;
    std::unordered_set<Tree> known;
    digraph<Tree>            graph;

    {
        std::unordered_set<Tree> visited;
        std::vector<Tree>        found;
        scanForRecs(root, visited, found);
        for (Tree r : found) {
            if (known.insert(r).second) {
                work.push_back(r);
            }
        }
    }
    while (!work.empty()) {
        Tree r = work.back();
        work.pop_back();
        graph.add(r);  // ensure r is a node even if its body holds no recursion
        Tree var, body;
        if (!(isSymbolicRec(r, var, body) && body)) {
            continue;  // free reference: reported by the conversion itself
        }
        std::unordered_set<Tree> visited;
        std::vector<Tree>        found;
        scanForRecs(body, visited, found);
        std::unordered_set<Tree> dedup;
        for (Tree s2 : found) {
            if (dedup.insert(s2).second) {
                graph.add(r, s2);
            }
            if (known.insert(s2).second) {
                work.push_back(s2);
            }
        }
    }

    // Collapse the graph into its DAG of components, then serialize that DAG in
    // dependencies-first (reverse topological) order. A component's id is its index in
    // that order, so fSccOf and fComponents share one numbering that increases along the
    // dependency order -- exactly what a fixpoint iterator needs to solve lower
    // components before the ones that use them. sym2deBruijn does not care about the
    // order, only about the partition, so this renumbering is neutral for it.
    for (const digraph<Tree>& component : serialize(graph2dag(graph))) {
        const int         id = int(fComponents.size());
        std::vector<Tree> members;
        for (Tree r : component.nodes()) {
            members.push_back(r);
            fSccOf[r] = id;
        }
        fComponents.push_back(std::move(members));
    }
}

int RecPlan::sccOf(Tree recNode) const
{
    auto it = fSccOf.find(recNode);
    return (it != fSccOf.end()) ? it->second : -1;
}

static Tree sym2deBruijnAux(Tree t, Tree env, Sym2DebState& state);

// Convert a recursive node of another (lower) component, standalone: the
// result is closed and ends up in the closed memo.
static Tree sym2deBruijnRec(Tree recNode, Sym2DebState& state)
{
    auto it = state.closedMemo.find(recNode);
    if (it != state.closedMemo.end()) {
        return it->second;
    }

    const int id = state.plan.sccOf(recNode);
    if (id < 0) {
        tlib::error("ASSERT : unregistered recursive node in sym2deBruijn\n");
    }

    const int saved  = state.currentSCC;
    state.currentSCC = id;
    Tree result      = sym2deBruijnAux(recNode, nil(), state);
    state.currentSCC = saved;

    if (!isClosed(result)) {
        tlib::error("ASSERT : component conversion is not closed in sym2deBruijn\n");
    }
    return result;
}

static Tree sym2deBruijnAux(Tree t, Tree env, Sym2DebState& state)
{
    // Invariant subtrees convert to themselves : no traversal, no memo entry
    if (isSym2deBruijnInvariant(t)) {
        return t;
    }

    // A closed result does not depend on the environment
    auto cIt = state.closedMemo.find(t);
    if (cIt != state.closedMemo.end()) {
        return cIt->second;
    }

    const std::pair<Tree, Tree> key(t, env);
    auto                        oIt = state.envMemo.find(key);
    if (oIt != state.envMemo.end()) {
        return oIt->second;
    }

    Tree body, var;
    Tree result;

    if (isSymbolicRef(t, var)) {
        int level = symbolicLevel(var, env);
        if (level > 0) {
            result = ref(level);
        } else if (isSymbolicRec(t, var, body) && body) {
            const int id = state.plan.sccOf(t);
            if (id >= 0 && id == state.currentSCC) {
                // Mutual recursion inside the current component: inline
                result = rec(sym2deBruijnAux(body, cons(var, env), state));
            } else {
                // Another component: splice its closed conversion
                result = sym2deBruijnRec(t, state);
            }
        } else {
            tlib::error("ASSERT : free symbolic reference found in sym2deBruijn\n");
            result = t;
        }
    } else {
        int  ar = t->arity();
        tvec br(ar);
        for (int i = 0; i < ar; i++) {
            br[i] = sym2deBruijnAux(t->branch(i), env, state);
        }
        result = tree(t->node(), br);
    }

    if (isClosed(result)) {
        state.closedMemo[t] = result;
    } else {
        state.envMemo[key] = result;
    }
    return result;
}

Tree sym2deBruijn(Tree t)
{
    RecPlan      plan(t);
    Sym2DebState state(plan);
    return sym2deBruijnAux(t, nil(), state);
}

//-----------------------------------------------------------
// Alpha-equivalence
//-----------------------------------------------------------

// The de Bruijn form is canonical w.r.t. alpha-equivalence : two recursive
// trees are equivalent iff their de Bruijn conversions are the same
// hash-consed tree.
bool areEquiv(Tree a, Tree b)
{
    return (a == b) || (sym2deBruijn(a) == sym2deBruijn(b));
}

//-----------------------------------------------------------
// Pretty printers for recursive trees
//-----------------------------------------------------------

std::string toDeBruijnString(Tree t)
{
    std::ostringstream out;
    printDeBruijn(out, t);
    return out.str();
}

static std::ostream& printTreeExpr(std::ostream& out, Tree t)
{
    out << t->node();
    int ar = t->arity();
    if (ar > 0) {
        out << "(";
        for (int i = 0; i < ar; ++i) {
            if (i > 0) {
                out << ", ";
            }
            printTreeExpr(out, t->branch(i));
        }
        out << ")";
    }
    return out;
}

std::ostream& printDeBruijn(std::ostream& out, Tree t)
{
    Tree body;
    int  level;

    if (isDebruijnRec(t, body)) {
        out << "rec(";
        printDeBruijn(out, body);
        return out << ")";
    }
    if (isDebruijnRef(t, level)) {
        return out << "ref(" << level << ")";
    }

    out << t->node();
    int ar = t->arity();
    if (ar > 0) {
        out << "(";
        for (int i = 0; i < ar; ++i) {
            if (i > 0) {
                out << ", ";
            }
            printDeBruijn(out, t->branch(i));
        }
        out << ")";
    }
    return out;
}

struct SymbolicPrintDef {
    Tree fVar;
    Tree fBody;
};

struct SymbolicPrintState {
    std::vector<SymbolicPrintDef> fDefs;

    bool seen(Tree var) const
    {
        for (const SymbolicPrintDef& def : fDefs) {
            if (def.fVar == var) {
                return true;
            }
        }
        return false;
    }

    void collect(Tree var, Tree body)
    {
        if (body && !seen(var)) {
            fDefs.push_back(SymbolicPrintDef{var, body});
        }
    }
};

static std::ostream& printSymbolicVar(std::ostream& out, Tree var)
{
    return printTreeExpr(out, var);
}

static std::ostream& printSymbolicRec(std::ostream& out, Tree t, SymbolicPrintState& state)
{
    Tree body, var;

    if (isSymbolicRec(t, var, body)) {
        state.collect(var, body);
        printSymbolicVar(out, var);
        return out;
    }

    out << t->node();
    int ar = t->arity();
    if (ar > 0) {
        out << "(";
        for (int i = 0; i < ar; ++i) {
            if (i > 0) {
                out << ", ";
            }
            printSymbolicRec(out, t->branch(i), state);
        }
        out << ")";
    }
    return out;
}

std::ostream& printSymbolic(std::ostream& out, Tree t)
{
    SymbolicPrintState state;
    printSymbolicRec(out, t, state);

    if (!state.fDefs.empty()) {
        out << "\nwith {\n";
        for (std::size_t i = 0; i < state.fDefs.size(); ++i) {
            out << "  ";
            printSymbolicVar(out, state.fDefs[i].fVar);
            out << " := ";
            printSymbolicRec(out, state.fDefs[i].fBody, state);
            out << "\n";
        }
        out << "}";
    }
    return out;
}

std::string toSymbolicString(Tree t)
{
    std::ostringstream out;
    printSymbolic(out, t);
    return out.str();
}

// Local-memo variant used by deBruijn2Sym : same traversal as
// substituteReady/calcsubstituteReady below, but the memo dies with the call
// instead of staying attached to the trees as properties.
static Tree substituteMemo(Tree t, int level, Tree id, SubstMemo& memo)
{
    if (t->aperture() < level) {
        // no free reference at this depth in this subtree : nothing to do
        return t;
    }

    int l;
    if (isDebruijnRef(t, l)) {
        return (l == level) ? id : t;
    }

    const std::pair<Tree, int> key(t, level);

    auto it = memo.find(key);
    if (it != memo.end()) {
        return it->second;
    }

    Tree body;
    Tree result;

    if (isDebruijnRec(t, body)) {
        result = rec(substituteMemo(body, level + 1, id, memo));
    } else {
        int  ar = t->arity();
        tvec br(ar);
        for (int i = 0; i < ar; i++) {
            br[i] = substituteMemo(t->branch(i), level, id, memo);
        }
        result = tree(t->node(), br);
    }

    memo[key] = result;
    return result;
}

static Tree substituteReady(Tree t, int level, Tree id)
{
    Tree S  = tree(Node(gSubstituteSym), tree(Node(level)), id);
    Tree t2 = t->getProperty(S);

    if (!t2) {
        t2 = calcsubstituteReady(t, level, id);
        t->setProperty(S, t2);
    }
    return t2;
}

static Tree calcsubstituteReady(Tree t, int level, Tree id)
{
    int  l;
    Tree body;

    if (t->aperture() < level) {
        // fprintf(stderr, "aperture %d < level %d !!\n", t->aperture(), level);
        return t;
    }
    if (isDebruijnRef(t, l)) {
        return (l == level) ? id : t;
    }
    if (isDebruijnRec(t, body)) {
        return rec(substituteReady(body, level + 1, id));
    }

    int  ar = t->arity();
    tvec br(ar);
    for (int i = 0; i < ar; i++) {
        br[i] = substituteReady(t->branch(i), level, id);
    }
    return tree(t->node(), br);
}
