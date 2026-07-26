/************************************************************************
 ************************************************************************
    FAUST signal library
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
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

#pragma once

/**
 * THE PATTERN ALGEBRA: terms of the free algebra over the signal signature
 * extended with three generators -- pinned constants, variables, and guarded
 * variables. A pattern p matches a tree t iff a substitution sigma with
 * sigma(p) = t exists; match(t) answers, binding each variable's Tree& along
 * the way. The same expression that BUILDS a node in TreeAlgebra DESTRUCTS it
 * here: pattern shapes mirror TreeAlgebra construction, shape for shape, and
 * the depth-1 fragment of this algebra is exactly the isSigXXX destructors
 * (isSigMul(s, x, y) is Mul(var(x), var(y)).match(s)).
 *
 * Discipline:
 *  - patterns are LINEAR: each variable occurs once; cross-branch equality is
 *    a pointer comparison in the rule body (hash-consing makes it exact);
 *  - bindings are WRITE-ONLY until match returns true: after a failed match
 *    (or in the non-succeeding branch of an alternative) the bound trees are
 *    unspecified, like the isSigXXX outputs on false;
 *  - patterns are built INLINE at the call site, at each attempt: they capture
 *    references to stack variables and must not outlive them.
 */

#include <functional>
#include <utility>
#include <vector>

#include "binop.hh"
#include "sigs-export.hh"
#include "sigs-state.hh"
#include "tlib.hh"

namespace pat {

/// A pattern: a composable matcher over signal trees.
class Pat {
    std::function<bool(Tree)> fMatch;  ///< the whole state

   public:
    explicit Pat(std::function<bool(Tree)> m) : fMatch(std::move(m)) {}

    bool match(Tree t) const { return fMatch(t); }

    /// Ordered alternative: only the bindings of the succeeding branch are
    /// meaningful (write-only discipline).
    Pat operator|(const Pat& q) const
    {
        Pat p = *this;
        return Pat([p, q](Tree t) { return p.match(t) || q.match(t); });
    }
};

//--- the three generators ---------------------------------------------------

/// Matches only the tree it was built from (a pinned ground term).
inline Pat constant(Tree t)
{
    return Pat([t](Tree s) { return s == t; });
}

/// Matches everything, binds x to the matched tree.
inline Pat var(Tree& x)
{
    return Pat([&x](Tree s) {
        x = s;
        return true;
    });
}

/// Matches when the guard accepts the tree, then binds x.
template <class Guard>
inline Pat var(Tree& x, Guard g)
{
    return Pat([&x, g](Tree s) {
        if (!g(s)) {
            return false;
        }
        x = s;
        return true;
    });
}

/// An anonymous guarded hole: matches when the guard accepts, binds nothing.
template <class Guard>
inline Pat hole(Guard g)
{
    return Pat([g](Tree s) { return g(s); });
}

//--- derived numeric guards -------------------------------------------------

inline Pat num(Tree& x)
{
    return var(x, [](Tree s) { return isNum(s->node()); });
}
inline Pat negNum(Tree& x)
{
    return var(x, [](Tree s) { return isNegative(s->node()); });
}
inline Pat zero()
{
    return hole([](Tree s) { return isZero(s->node()); });
}
inline Pat one()
{
    return hole([](Tree s) { return isOne(s->node()); });
}
inline Pat minusOne()
{
    return hole([](Tree s) { return isMinusOne(s->node()); });
}

//--- node patterns: one per signature operation, TreeAlgebra shapes ---------

/// F(p1..pn) matches the node TreeAlgebra's F builds: same head, same arity,
/// children matched left to right.
inline Pat node(const Node& head, std::vector<Pat> kids)
{
    return Pat([head, kids = std::move(kids)](Tree t) {
        if (!(t->node() == head) || t->arity() != static_cast<int>(kids.size())) {
            return false;
        }
        for (size_t i = 0; i < kids.size(); i++) {
            if (!kids[i].match(t->branch(static_cast<int>(i)))) {
                return false;
            }
        }
        return true;
    });
}

inline Pat binop(int op, Pat x, Pat y)
{
    return node(Node(sigs::g.SIGBINOP), {constant(tree(op)), std::move(x), std::move(y)});
}

// clang-format off
inline Pat Add (Pat x, Pat y) { return binop(kAdd,  std::move(x), std::move(y)); }
inline Pat Sub (Pat x, Pat y) { return binop(kSub,  std::move(x), std::move(y)); }
inline Pat Mul (Pat x, Pat y) { return binop(kMul,  std::move(x), std::move(y)); }
inline Pat Div (Pat x, Pat y) { return binop(kDiv,  std::move(x), std::move(y)); }
inline Pat Mod (Pat x, Pat y) { return binop(kRem,  std::move(x), std::move(y)); }
inline Pat Lsh (Pat x, Pat y) { return binop(kLsh,  std::move(x), std::move(y)); }
inline Pat ARsh(Pat x, Pat y) { return binop(kARsh, std::move(x), std::move(y)); }
inline Pat LRsh(Pat x, Pat y) { return binop(kLRsh, std::move(x), std::move(y)); }
inline Pat Gt  (Pat x, Pat y) { return binop(kGT,   std::move(x), std::move(y)); }
inline Pat Lt  (Pat x, Pat y) { return binop(kLT,   std::move(x), std::move(y)); }
inline Pat Ge  (Pat x, Pat y) { return binop(kGE,   std::move(x), std::move(y)); }
inline Pat Le  (Pat x, Pat y) { return binop(kLE,   std::move(x), std::move(y)); }
inline Pat Eq  (Pat x, Pat y) { return binop(kEQ,   std::move(x), std::move(y)); }
inline Pat Ne  (Pat x, Pat y) { return binop(kNE,   std::move(x), std::move(y)); }
inline Pat And (Pat x, Pat y) { return binop(kAND,  std::move(x), std::move(y)); }
inline Pat Or  (Pat x, Pat y) { return binop(kOR,   std::move(x), std::move(y)); }
inline Pat Xor (Pat x, Pat y) { return binop(kXOR,  std::move(x), std::move(y)); }
// clang-format on

inline Pat Mem(Pat x)
{
    return node(Node(sigs::g.SIGDELAY1), {std::move(x)});
}
inline Pat Delay(Pat x, Pat n)
{
    return node(Node(sigs::g.SIGDELAY), {std::move(x), std::move(n)});
}
inline Pat IntCast(Pat x)
{
    return node(Node(sigs::g.SIGINTCAST), {std::move(x)});
}
inline Pat BitCast(Pat x)
{
    return node(Node(sigs::g.SIGBITCAST), {std::move(x)});
}
inline Pat FloatCast(Pat x)
{
    return node(Node(sigs::g.SIGFLOATCAST), {std::move(x)});
}
inline Pat Select2(Pat sel, Pat x, Pat y)
{
    return node(Node(sigs::g.SIGSELECT2), {std::move(sel), std::move(x), std::move(y)});
}
inline Pat Enable(Pat x, Pat y)
{
    return node(Node(sigs::g.SIGENABLE), {std::move(x), std::move(y)});
}
inline Pat Control(Pat x, Pat y)
{
    return node(Node(sigs::g.SIGCONTROL), {std::move(x), std::move(y)});
}
inline Pat Input(Pat chan)
{
    return node(Node(sigs::g.SIGINPUT), {std::move(chan)});
}

/// An extended-primitive application, destructured by name (mirrors
/// TreeAlgebra::xt).
inline Pat xt(const char* name, std::vector<Pat> kids)
{
    return node(Node(symbol(name)), std::move(kids));
}

// clang-format off
inline Pat Abs (Pat x)        { return xt("abs",  {std::move(x)}); }
inline Pat Floor(Pat x)       { return xt("floor",{std::move(x)}); }
inline Pat Max (Pat x, Pat y) { return xt("max",  {std::move(x), std::move(y)}); }
inline Pat Min (Pat x, Pat y) { return xt("min",  {std::move(x), std::move(y)}); }
inline Pat Pow (Pat x, Pat y) { return xt("pow",  {std::move(x), std::move(y)}); }
// clang-format on

}  // namespace pat
