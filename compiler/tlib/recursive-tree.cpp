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
#include <unordered_map>
#include <utility>
#include <vector>

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
static Tree sym2deBruijnMemo(Tree t, Tree env, Sym2DebMemo& memo);
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
//-----------------------------------------------------------

Tree sym2deBruijn(Tree t)
{
    Sym2DebMemo memo;
    return sym2deBruijnMemo(t, nil(), memo);
}

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

static Tree sym2deBruijnMemo(Tree t, Tree env, Sym2DebMemo& memo)
{
    const std::pair<Tree, Tree> key(t, env);

    auto it = memo.find(key);
    if (it != memo.end()) {
        return it->second;
    }

    Tree body, var;
    Tree result;

    if (isSymbolicRef(t, var)) {
        int level = symbolicLevel(var, env);
        if (level > 0) {
            result = ref(level);
        } else if (isSymbolicRec(t, var, body) && body) {
            result = rec(sym2deBruijnMemo(body, cons(var, env), memo));
        } else {
            tlib::error("ASSERT : free symbolic reference found in sym2deBruijn\n");
            result = t;
        }
    } else {
        int  ar = t->arity();
        tvec br(ar);
        for (int i = 0; i < ar; i++) {
            br[i] = sym2deBruijnMemo(t->branch(i), env, memo);
        }
        result = tree(t->node(), br);
    }

    memo[key] = result;
    return result;
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
