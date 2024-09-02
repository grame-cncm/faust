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

#include "garbageable.hh"
#include "tree.hh"

template <class P>
class property : public virtual Garbageable {
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
class property<Tree> : public virtual Garbageable {
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
class property<int> : public virtual Garbageable {
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
class property<double> : public virtual Garbageable {
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

#endif
