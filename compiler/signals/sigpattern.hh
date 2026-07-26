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
 *  - patterns are LINEAR: each variable occurs once per alternative branch;
 *    cross-branch equality is a pointer comparison in the rule body
 *    (hash-consing makes it exact);
 *  - bindings are WRITE-ONLY until match returns true: after a failed match
 *    (or in the non-succeeding branch of an alternative) the bound trees are
 *    unspecified, like the isSigXXX outputs on false;
 *  - patterns are built INLINE at the call site, at each attempt: they capture
 *    references to stack variables and must not outlive them.
 *
 * Representation: EXPRESSION TEMPLATES. A pattern is a small value type whose
 * composition is resolved at compile time -- no allocation, no indirection;
 * matching inlines to the same test cascade one would write by hand against
 * the isSigXXX destructors.
 */

#include <tuple>
#include <utility>

#include "binop.hh"
#include "sigs-export.hh"
#include "sigs-state.hh"
#include "tlib.hh"

namespace pat {

//--- the three generators ---------------------------------------------------

/// Matches only the tree it was built from (a pinned ground term).
struct Constant {
    using is_pattern = void;
    Tree t;
    bool match(Tree s) const { return s == t; }
};
inline Constant constant(Tree t)
{
    return {t};
}

/// Matches everything, binds x to the matched tree.
struct Var {
    using is_pattern = void;
    Tree& x;
    bool  match(Tree s) const
    {
        x = s;
        return true;
    }
};
inline Var var(Tree& x)
{
    return {x};
}

/// Matches when the guard accepts the tree, then binds x.
template <class Guard>
struct GuardedVar {
    using is_pattern = void;
    Tree& x;
    Guard g;
    bool  match(Tree s) const
    {
        if (!g(s)) {
            return false;
        }
        x = s;
        return true;
    }
};
template <class Guard>
inline GuardedVar<Guard> var(Tree& x, Guard g)
{
    return {x, std::move(g)};
}

/// An anonymous guarded hole: matches when the guard accepts, binds nothing.
template <class Guard>
struct Hole {
    using is_pattern = void;
    Guard g;
    bool  match(Tree s) const { return g(s); }
};
template <class Guard>
inline Hole<Guard> hole(Guard g)
{
    return {std::move(g)};
}

//--- derived numeric guards -------------------------------------------------

struct IsNumG {
    bool operator()(Tree s) const { return isNum(s->node()); }
};
struct IsNegG {
    bool operator()(Tree s) const { return isNegative(s->node()); }
};
struct IsZeroG {
    bool operator()(Tree s) const { return isZero(s->node()); }
};
struct IsOneG {
    bool operator()(Tree s) const { return isOne(s->node()); }
};
struct IsMinusOneG {
    bool operator()(Tree s) const { return isMinusOne(s->node()); }
};

inline GuardedVar<IsNumG> num(Tree& x)
{
    return {x, IsNumG{}};
}
inline GuardedVar<IsNegG> negNum(Tree& x)
{
    return {x, IsNegG{}};
}
inline Hole<IsZeroG> zero()
{
    return {IsZeroG{}};
}
inline Hole<IsOneG> one()
{
    return {IsOneG{}};
}
inline Hole<IsMinusOneG> minusOne()
{
    return {IsMinusOneG{}};
}

//--- composition ------------------------------------------------------------

/// Ordered alternative: only the bindings of the succeeding branch are
/// meaningful (write-only discipline).
template <class P, class Q>
struct Alt {
    using is_pattern = void;
    P p;
    Q q;
    bool match(Tree s) const { return p.match(s) || q.match(s); }
};
template <class P, class Q, class = typename P::is_pattern, class = typename Q::is_pattern>
inline Alt<P, Q> operator|(P p, Q q)
{
    return {std::move(p), std::move(q)};
}

//--- node patterns: one per signature operation, TreeAlgebra shapes ---------

/// F(p1..pn) matches the node TreeAlgebra's F builds: same head, same arity,
/// children matched left to right.
template <class... Ks>
struct NodePat {
    using is_pattern = void;
    Node               head;
    std::tuple<Ks...>  kids;

    bool match(Tree t) const
    {
        if (!(t->node() == head) || t->arity() != static_cast<int>(sizeof...(Ks))) {
            return false;
        }
        return matchKids(t, std::index_sequence_for<Ks...>{});
    }

   private:
    template <std::size_t... I>
    bool matchKids(Tree t, std::index_sequence<I...>) const
    {
        return (std::get<I>(kids).match(t->branch(static_cast<int>(I))) && ...);
    }
};

template <class... Ks>
inline NodePat<Ks...> node(const Node& head, Ks... ks)
{
    return {head, std::tuple<Ks...>{std::move(ks)...}};
}

template <class X, class Y>
inline auto binop(int op, X x, Y y)
{
    return node(Node(sigs::g.SIGBINOP), constant(tree(op)), std::move(x), std::move(y));
}

// clang-format off
template <class X, class Y> inline auto Add (X x, Y y) { return binop(kAdd,  std::move(x), std::move(y)); }
template <class X, class Y> inline auto Sub (X x, Y y) { return binop(kSub,  std::move(x), std::move(y)); }
template <class X, class Y> inline auto Mul (X x, Y y) { return binop(kMul,  std::move(x), std::move(y)); }
template <class X, class Y> inline auto Div (X x, Y y) { return binop(kDiv,  std::move(x), std::move(y)); }
template <class X, class Y> inline auto Mod (X x, Y y) { return binop(kRem,  std::move(x), std::move(y)); }
template <class X, class Y> inline auto Lsh (X x, Y y) { return binop(kLsh,  std::move(x), std::move(y)); }
template <class X, class Y> inline auto ARsh(X x, Y y) { return binop(kARsh, std::move(x), std::move(y)); }
template <class X, class Y> inline auto LRsh(X x, Y y) { return binop(kLRsh, std::move(x), std::move(y)); }
template <class X, class Y> inline auto Gt  (X x, Y y) { return binop(kGT,   std::move(x), std::move(y)); }
template <class X, class Y> inline auto Lt  (X x, Y y) { return binop(kLT,   std::move(x), std::move(y)); }
template <class X, class Y> inline auto Ge  (X x, Y y) { return binop(kGE,   std::move(x), std::move(y)); }
template <class X, class Y> inline auto Le  (X x, Y y) { return binop(kLE,   std::move(x), std::move(y)); }
template <class X, class Y> inline auto Eq  (X x, Y y) { return binop(kEQ,   std::move(x), std::move(y)); }
template <class X, class Y> inline auto Ne  (X x, Y y) { return binop(kNE,   std::move(x), std::move(y)); }
template <class X, class Y> inline auto And (X x, Y y) { return binop(kAND,  std::move(x), std::move(y)); }
template <class X, class Y> inline auto Or  (X x, Y y) { return binop(kOR,   std::move(x), std::move(y)); }
template <class X, class Y> inline auto Xor (X x, Y y) { return binop(kXOR,  std::move(x), std::move(y)); }
// clang-format on

template <class X>
inline auto Mem(X x)
{
    return node(Node(sigs::g.SIGDELAY1), std::move(x));
}
template <class X, class N>
inline auto Delay(X x, N n)
{
    return node(Node(sigs::g.SIGDELAY), std::move(x), std::move(n));
}
template <class X>
inline auto IntCast(X x)
{
    return node(Node(sigs::g.SIGINTCAST), std::move(x));
}
template <class X>
inline auto BitCast(X x)
{
    return node(Node(sigs::g.SIGBITCAST), std::move(x));
}
template <class X>
inline auto FloatCast(X x)
{
    return node(Node(sigs::g.SIGFLOATCAST), std::move(x));
}
template <class S, class X, class Y>
inline auto Select2(S sel, X x, Y y)
{
    return node(Node(sigs::g.SIGSELECT2), std::move(sel), std::move(x), std::move(y));
}
template <class X, class Y>
inline auto Enable(X x, Y y)
{
    return node(Node(sigs::g.SIGENABLE), std::move(x), std::move(y));
}
template <class X, class Y>
inline auto Control(X x, Y y)
{
    return node(Node(sigs::g.SIGCONTROL), std::move(x), std::move(y));
}
template <class C>
inline auto Input(C chan)
{
    return node(Node(sigs::g.SIGINPUT), std::move(chan));
}
template <class X>
inline auto Lowest(X x)
{
    return node(Node(sigs::g.SIGLOWEST), std::move(x));
}
template <class X>
inline auto Highest(X x)
{
    return node(Node(sigs::g.SIGHIGHEST), std::move(x));
}
template <class X, class Y>
inline auto Attach(X x, Y y)
{
    return node(Node(sigs::g.SIGATTACH), std::move(x), std::move(y));
}

/// An extended-primitive application, destructured by name (mirrors
/// TreeAlgebra::xt).
template <class... Ks>
inline auto xt(const char* name, Ks... ks)
{
    return node(Node(symbol(name)), std::move(ks)...);
}

// clang-format off
template <class X>          inline auto Abs  (X x)      { return xt("abs",   std::move(x)); }
template <class X>          inline auto Floor(X x)      { return xt("floor", std::move(x)); }
template <class X, class Y> inline auto Max  (X x, Y y) { return xt("max",   std::move(x), std::move(y)); }
template <class X, class Y> inline auto Min  (X x, Y y) { return xt("min",   std::move(x), std::move(y)); }
template <class X, class Y> inline auto Pow  (X x, Y y) { return xt("pow",   std::move(x), std::move(y)); }
// clang-format on

}  // namespace pat
