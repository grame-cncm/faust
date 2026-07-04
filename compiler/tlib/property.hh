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

#ifndef __PROPERTY__
#define __PROPERTY__

#include <unordered_map>

#include "garbageable.hh"
#include "tree.hh"

template <class P>
class property : public Garbageable {
    Tree fKey;

    P* access(Tree t)
    {
        Tree d = t->getProperty(fKey);
        return d ? (P*)(d->node().getPointer()) : nullptr;
    }

   public:
    property() : fKey(tree(Node(unique("property_")))) {}

    property(const char* keyname) : fKey(tree(Node(keyname))) {}

    void set(Tree t, const P& data)
    {
        if (P* p = access(t)) {
            *p = data;
        } else {
            t->setProperty(fKey, tree(Node((new GarbageablePtr<P>(data))->getPointer())));
        }
    }

    bool get(Tree t, P& data)
    {
        if (P* p = access(t)) {
            data = *p;
            return true;
        } else {
            return false;
        }
    }

    void clear(Tree t)
    {
        if (P* p = access(t)) {
            delete p;
        }
        t->clearProperty(fKey);
    }
};

template <>
class property<Tree> : public Garbageable {
    Tree fKey;

   public:
    property() : fKey(tree(Node(unique("property_")))) {}

    property(const char* keyname) : fKey(tree(Node(keyname))) {}

    void set(Tree t, Tree data) { t->setProperty(fKey, data); }

    bool get(Tree t, Tree& data)
    {
        if (Tree d = t->getProperty(fKey)) {
            data = d;
            return true;
        } else {
            return false;
        }
    }

    void clear(Tree t) { t->clearProperty(fKey); }
};

template <>
class property<int> : public Garbageable {
    Tree fKey;

   public:
    property() : fKey(tree(Node(unique("property_")))) {}

    property(const char* keyname) : fKey(tree(Node(keyname))) {}

    void set(Tree t, int i) { t->setProperty(fKey, tree(Node(i))); }

    bool get(Tree t, int& i)
    {
        if (Tree d = t->getProperty(fKey)) {
            i = d->node().getInt();
            return true;
        } else {
            return false;
        }
    }

    void clear(Tree t) { t->clearProperty(fKey); }
};

template <>
class property<double> : public Garbageable {
    Tree fKey;

   public:
    property() : fKey(tree(Node(unique("property_")))) {}

    property(const char* keyname) : fKey(tree(Node(keyname))) {}

    void set(Tree t, double x) { t->setProperty(fKey, tree(Node(x))); }

    bool get(Tree t, double& x)
    {
        if (Tree d = t->getProperty(fKey)) {
            x = d->node().getDouble();
            return true;
        } else {
            return false;
        }
    }

    void clear(Tree t) { t->clearProperty(fKey); }
};

// Why: `property<P>` only memoizes unary functions (one Tree -> P). Some call sites actually
// memoize a binary function f(a, b) -> P where 'a' is reused across many distinct 'b' (e.g. the
// box evaluator's eval(box, env), see TLIB.md). Forcing that through property<P> means folding
// 'b' into a freshly hashconsed compound key tree on every single call, so every distinct 'b'
// mints both a new Tree and a new property entry piled onto the same 'a' -- one real case reached
// 56000+ entries on a single node before this existed.
//
// How: generic fallback for P other than Tree. Keeps ONE property slot per property2 instance
// (like property<P>) whose value is nested under 'a', with the first (b, value) pair kept inline
// in a small Slot (no map) and only promoted to a real std::map once a second distinct 'b' shows
// up for the same 'a' -- see the property2<Tree> specialization below for why the inline Slot
// still isn't cheap enough when P = Tree, which is the actually-used case (box evaluator memo).
template <class P>
class property2 : public Garbageable {
    Tree fOuterKey;
    typedef std::map<Tree, P> Inner;

    struct Slot {
        Tree   fB;      // the single 'b' seen so far ; unused once fInner is non-null
        P      fValue;  // its value ; unused once fInner is non-null
        Inner* fInner;  // nullptr until a second distinct 'b' forces promotion
    };

    Slot* access(Tree a)
    {
        Tree d = a->getProperty(fOuterKey);
        return d ? (Slot*)(d->node().getPointer()) : nullptr;
    }

   public:
    property2() : fOuterKey(tree(Node(unique("property2_")))) {}

    property2(const char* keyname) : fOuterKey(tree(Node(keyname))) {}

    void set(Tree a, Tree b, const P& value)
    {
        Slot* s = access(a);
        if (!s) {
            // First (a, b) pair seen for this 'a' : keep it inline, no map allocated yet. Later
            // sets for the same 'a' reuse this same Slot in place, so 'a' never accumulates more
            // than one property entry for this property2.
            s          = new Slot();
            s->fB      = b;
            s->fValue  = value;
            s->fInner  = nullptr;
            a->setProperty(fOuterKey, tree(Node((void*)s)));
        } else if (s->fInner) {
            (*s->fInner)[b] = value;
        } else if (s->fB == b) {
            s->fValue = value;
        } else {
            // Second distinct 'b' for this 'a' : promote the inline pair into a real map.
            s->fInner              = new Inner();
            (*s->fInner)[s->fB]    = s->fValue;
            (*s->fInner)[b]        = value;
        }
    }

    bool get(Tree a, Tree b, P& value)
    {
        Slot* s = access(a);
        if (!s) return false;
        if (s->fInner) {
            typename Inner::iterator it = s->fInner->find(b);
            if (it == s->fInner->end()) return false;
            value = it->second;
            return true;
        }
        if (s->fB == b) {
            value = s->fValue;
            return true;
        }
        return false;
    }

    void clear(Tree a)
    {
        if (Slot* s = access(a)) {
            delete s->fInner;
            delete s;
        }
        a->clearProperty(fOuterKey);
    }
};

// Why: two earlier attempts (see git history / TLIB.md) both regressed memory on costlyexamples/,
// worst on files where most memoized 'a' turn out to need several distinct 'b' (e.g. piano1.dsp,
// ~89% of boxes need more than one env). Both attempts nested a second-level container (a Slot,
// then a std::map) under 'a', and a raw pointer to that container can only ride through
// CTree::setProperty by being wrapped in a brand new CTree -- a full CTree object (hash, branches
// vector, fProperties, etc., 100+ bytes), created fresh per 'a' and never hashcons-shareable
// (unlike an ordinary key tree, since the pointer is unique). A third attempt fell back to the old
// compound-key scheme (tree(fCompoundBase, b) as a shared key directly in a's own fProperties)
// once a second 'b' showed up, which fixed memory but regressed time : every promoted get/set now
// paid a full global hashconsing lookup (hash + bucket walk across the whole program's key trees)
// on top of the local property lookup, whereas a small per-host map never needed that.
//
// How: don't route property2's own bookkeeping through CTree's hashconsing or per-node property
// list at all -- keep it in property2's own hash map, keyed directly by the 'a' pointer (Tree is
// just CTree*, so std::hash<Tree> is the trivial pointer hash, no wrapping needed). The first (b,
// value) pair for a given 'a' lives inline inside that map's own Entry, no extra heap object; a
// second distinct 'b' promotes to a small nested std::map, same bound as before (O(log n) in that
// host's own arity), but as a plain local structure with no global hashconsing traffic and no
// dependency on 'a's own fProperties (so 'a' doesn't even need fProperties allocated just for
// this). Determinism note : this map is only ever point-queried by (a, b), never iterated, so its
// unordered iteration order (which depends on pointer values) cannot leak into generated code.
template <>
class property2<Tree> : public Garbageable {
    struct Entry {
        Tree              fB;             // the single 'b' seen so far ; unused once fInner set
        Tree              fValue;         // its value ; unused once fInner set
        std::map<Tree, Tree>* fInner = nullptr;  // non-null once a 2nd distinct 'b' is seen
    };
    std::unordered_map<Tree, Entry> fOuter;

   public:
    ~property2() { clearAll(); }

    void set(Tree a, Tree b, Tree value)
    {
        auto it = fOuter.find(a);
        if (it == fOuter.end()) {
            // First (a, b) pair seen for this 'a' : stored inline in the Entry itself, no extra
            // heap allocation beyond the map node fOuter already needs to hold it.
            fOuter.emplace(a, Entry{b, value, nullptr});
            return;
        }
        Entry& e = it->second;
        if (e.fInner) {
            (*e.fInner)[b] = value;
        } else if (e.fB == b) {
            e.fValue = value;
        } else {
            // Second distinct 'b' for this 'a' : only now pay for a small nested map.
            e.fInner        = new std::map<Tree, Tree>();
            (*e.fInner)[e.fB] = e.fValue;
            (*e.fInner)[b]    = value;
        }
    }

    bool get(Tree a, Tree b, Tree& value)
    {
        auto it = fOuter.find(a);
        if (it == fOuter.end()) return false;
        Entry& e = it->second;
        if (e.fInner) {
            auto j = e.fInner->find(b);
            if (j == e.fInner->end()) return false;
            value = j->second;
            return true;
        }
        if (e.fB == b) {
            value = e.fValue;
            return true;
        }
        return false;
    }

    void clear(Tree a)
    {
        auto it = fOuter.find(a);
        if (it == fOuter.end()) return;
        delete it->second.fInner;
        fOuter.erase(it);
    }

    void clearAll()
    {
        for (auto& it : fOuter) {
            delete it.second.fInner;
        }
        fOuter.clear();
    }
};

#endif
